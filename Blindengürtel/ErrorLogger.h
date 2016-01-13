#ifndef ERRORLOGGER_H_
#define ERRORLOGGER_H_

#include <stdio.h>
#include <string>

///The path to the errorlog file.
#define ERROR_LOG_PATH "/home/pi/Desktop/autostartfiles/Blindengürtel/errors.log"

///ErrorLogger will log errors to a logfile.
class ErrorLogger{	
	public:
		///Creates an ErrorLogger object.
		ErrorLogger();
		///Destroys the created ErrorLogger object.
		~ErrorLogger();
		///Writes message to the file in filePath
		///@param message Contains the message that should be logged into the file.
		///@param filePath Is the path to the file in which the message should be logged.
		static void writeToLog(const std::string message, const char* filePath);
};
#endif
