#include "ErrorLogger.h"

using namespace std;

ErrorLogger::ErrorLogger(){}

void ErrorLogger::writeToLog(const string message, const char* filePath){
	
	FILE* file = fopen(filePath, "a");
	if(file != NULL){
		fprintf(file, "%s\n", message.c_str());
		fclose(file);
	}
}
