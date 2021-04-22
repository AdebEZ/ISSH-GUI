#include "app/ISHparser.h"

ISHParser::ISHParser(int save)
{
	qDebug() << "new process!";
	
    startExternalProgram();
}

ISHParser::~ISHParser()
{

}

// with QProcess
void ISHParser::startExternalProgramWithQt()
{
    process = new QProcess(this);
    QObject::connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    QObject::connect(process, &QProcess::errorOccurred, [=](QProcess::ProcessError pe) {
        qDebug() << "error";
        qDebug() << pe;
    }
    );
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->setNativeArguments(arguments); //https://doc.qt.io/qt-5/qprocess.html#start
    process->start(ish_path);
    //https://www.qtcentre.org/threads/62415-QProcess-not-communicating-with-net-framework-gt-3-5 
}

void ISHParser::readOutput()
{
    qDebug() << "reading output";
    qDebug() << process->readAllStandardError();
    qDebug() << process->readAllStandardOutput();
}

// other way with windows.h
void ISHParser::startExternalProgram()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    // to redirect output  https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output
    // Set the bInheritHandle flag so pipe handles are inherited. 
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    HANDLE g_hChildStd_IN_Rd = NULL;
    HANDLE g_hChildStd_IN_Wr = NULL;
    HANDLE g_hChildStd_OUT_Rd = NULL;
    HANDLE g_hChildStd_OUT_Wr = NULL;
    // Set the bInheritHandle flag so pipe handle
    // Create a pipe for the child process's STDOUT. 
    if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0)) 
    // Ensure the read handle to the pipe for STDOUT is not inherited.
    if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0)) 
    // Create a pipe for the child process's STDIN. 
    if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0)) 
    // Ensure the write handle to the pipe for STDIN is not inherited. 
    if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0)) 

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError = g_hChildStd_OUT_Wr;
    si.hStdOutput = g_hChildStd_OUT_Wr;
    si.hStdInput = g_hChildStd_IN_Rd;
    si.dwFlags |= STARTF_USESTDHANDLES;
    ZeroMemory(&pi, sizeof(pi));

    LPSTR path = const_cast<char*>(ish_path.toStdString().c_str());
    QString test = path + QString(" ") + arguments;
    LPSTR args = const_cast<char*>(test.toStdString().c_str());
    // Start the child process.
    if (!CreateProcess(path, // Application Path
        args, // Argument
        NULL, // Process handle not inheritable
        NULL, // Thread handle not inheritable
        TRUE, // Set handle inheritance to TRUE (for stdin/err/out redirection)
        0, // No creation flags
        NULL, // Use parent's environment block
        NULL, // Use parent's starting directory
        &si, // Pointer to STARTUPINFO structure
        &pi) // Pointer to PROCESS_INFORMATION structure
        ) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        CloseHandle(g_hChildStd_OUT_Wr);
        CloseHandle(g_hChildStd_OUT_Rd);
        CloseHandle(g_hChildStd_IN_Wr);
        CloseHandle(g_hChildStd_IN_Rd);
        return ;
    }
    else {
        qDebug() << "|||||||||||||child process output " << path << " ||||||||||||||||||";
        qDebug() << args;
        // Close handles to the stdin and stdout pipes no longer needed by the child process.
        // If they are not explicitly closed, there is no way to recognize that the child process has ended.
        CloseHandle(g_hChildStd_OUT_Wr);
        CloseHandle(g_hChildStd_IN_Rd);

        DWORD dwRead, dwWritten;
        CHAR chBuf[4096];
        BOOL bSuccess = FALSE;
        HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        QString result;
        for (;;)
        {
            bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, 4096, &dwRead, NULL);
            if (!bSuccess || dwRead == 0) break;

            result += QString(chBuf).left(dwRead);
            bSuccess = WriteFile(hParentStdOut, chBuf, dwRead, &dwWritten, NULL);
            if (!bSuccess) break;
        }
        qDebug() << result;
        // @TODO : parse result
        qDebug() << "|||||||||||||||||||||||||||||||";
        CloseHandle(g_hChildStd_OUT_Rd);
        CloseHandle(g_hChildStd_IN_Wr);
        return;
    }
}
