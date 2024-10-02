class HC_Log {
    private static ref HC_Log instance;
    private string HC_LogFilePath;
    private FileHandle HC_LogFile;

    void HC_Log() {
        string timestamp = GetTimestamp();
        HC_LogFilePath = "$profile:\\Vendetta_HC\\log_" + timestamp + ".txt";
        
        string logDirectory = "$profile:\\Vendetta_HC";
        if (!FileExist(logDirectory)) {
            MakeDirectory(logDirectory);
        }
        HC_LogFile = OpenFile(HC_LogFilePath, FileMode.WRITE);
        if (HC_LogFile == 0) {
            Error("Failed to create log file: " + HC_LogFilePath);
        }
    }
    static HC_Log GetInstance() {
        if (!instance) {
            instance = new HC_Log();
        }
        return instance;
    }

    void ~HC_Log() {
        if (HC_LogFile != 0) {
            CloseFile(HC_LogFile);
        }
    }
    void HC_Write(string message) {
        if (HC_LogFile != 0) {
            FPrintln(HC_LogFile, GetTimestamp() + " - " + message);
        }
    }
    private string GetTimestamp() {
        int year, month, day, hour, minute, second;
        GetYearMonthDayUTC(year, month, day);
        GetHourMinuteSecondUTC(hour, minute, second);

        return string.Format("%1-%2-%3_%4-%5-%6", year, month.ToStringLen(2), day.ToStringLen(2), hour.ToStringLen(2), minute.ToStringLen(2), second.ToStringLen(2));
    }
}
