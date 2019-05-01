// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// CourseWork2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>

#define BUFSIZE 512


std::mutex consoleLock;
std::condition_variable cv; //will be used for communication between threads (when respond from server is read and next ready message should be triggered)
HANDLE startCommandReceived = CreateEventA(NULL, true, false, NULL);
HANDLE pipeIO = CreateEventA(NULL, true, false, NULL);
HANDLE pipeIO2 = CreateEventA(NULL, true, true, NULL);
HANDLE hFile;


void pipeHandlerRead(HANDLE* hFile);
void pipeHandlerWrite(HANDLE* hFileB, std::exception_ptr ex_ptr);
bool messageReady(HANDLE hFile, char data[], DWORD nBytesToWrite, DWORD nWrittenBytes);
void kb(std::exception_ptr ex_ptr);
void connectAndSendReady(std::exception_ptr ex_ptr);
void parseStringAndCreateObject(char* str);


void kb(std::exception_ptr ex_ptr) {
	try {
		char data[] = "ready";
		char input[10];
		std::cout << "What do you want to do? \n Connect or Disconnect" << std::endl;
		while (true) {
			while (!consoleLock.try_lock()) {
				continue;
			}


			std::cin >> input;
			if (std::string(input)._Equal("Connect")) {

				int startTriggered = WaitForSingleObject(startCommandReceived, 1);

				if (startTriggered == WAIT_OBJECT_0) {
					std::cout << "Connection exists." << std::endl;
					consoleLock.unlock();
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				else {
					std::cout << input << std::endl;
					SetEvent(startCommandReceived);
					consoleLock.unlock();
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

			}

			else if (std::string(input)._Equal("Disconnect")) {

				int startTriggered = WaitForSingleObject(startCommandReceived, 1);
				
				if (startTriggered == WAIT_OBJECT_0) {
					std::cout << "Aborting connection and closing program" << std::endl;

				}
				
				else if (startTriggered == WAIT_TIMEOUT) {
					std::cout << "Connection was not established. Closing program." << std::endl;
				}
				
				std::cout << input << std::endl;
				consoleLock.unlock();
				exit(0);

			}

			else {

				std::cout << "You can either Connect or Disconnect. No other commands please." << std::endl;
				consoleLock.unlock();

			}
		}

	}
	catch (std::exception) {
		ex_ptr = std::current_exception();
		return;
	}
}

void connectAndSendReady(std::exception_ptr ex_ptr) {

	try {
		
		int startTriggered = WaitForSingleObject(startCommandReceived, INFINITE); //waits  for user to initiate the connection
		if (startTriggered == WAIT_FAILED) {
			throw new std::exception("WAIT_FAILED - I couldn't Wait anymore..");
		}

		hFile = CreateFileA("\\\\.\\pipe\\ICS0025", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL); // Opening connection to Pipe

		DWORD nBytesToWrite = 6, nWrittenBytes = 0;

		char data[] = "ready";

		if (hFile == INVALID_HANDLE_VALUE) {
			while (!consoleLock.try_lock()) {
				continue;
			}
			std::cout << "File not created error - " << GetLastError() << std::endl;
			consoleLock.unlock();

		}
		else {
			while (!consoleLock.try_lock()) {
				continue;
			}

			std::cout << "Connection succesfull" << std::endl;

			BOOL resultOfWriting = messageReady(hFile, data, nBytesToWrite, nWrittenBytes);
			if (!resultOfWriting) {
				std::cout << "Error while sending first message has occured. Aborting program" << std::endl;

			}
			else {
				std::cout << "First message - " << data << " - was sent successfully" << std::endl;
			}
		}
		consoleLock.unlock();
		pipeHandlerRead(&hFile); // after sending first message to pipe, the program starts to read from it
	}
	catch (std::exception) {
		ex_ptr = std::current_exception();
		return;
	}

}
void pipeHandlerRead(HANDLE* hFileB) {

	int readOfPipeRequired = WaitForSingleObject(pipeIO2, 3);


	HANDLE hFile = *hFileB;
	DWORD  nBytesToWrite = 6, nWrittenBytes = 0, cbRead;
	char data[] = "ready";

	while (true) {
		if (readOfPipeRequired == WAIT_OBJECT_0) {
			//if(true){
			ResetEvent(pipeIO2);
			unsigned char* chBuf = new unsigned char[BUFSIZE];

			BOOL resultOfReading = ReadFile(
				hFile,    // pipe handle 
				chBuf,    // buffer to receive reply 
				BUFSIZE * sizeof(TCHAR),  // size of buffer 
				&cbRead,  // number of bytes read 
				NULL);    // not overlapped 

			std::cout << chBuf << std::endl;
			std::string stdString(reinterpret_cast<char*>(chBuf)); // reinterpret_cast is used to convert one pointer of another pointer of any type,

			//parseStringAndCreateObject(reinterpret_cast<char*>(chBuf));
			//BOOL resultOfWriting = messageReady(hFile, data, nBytesToWrite, nWrittenBytes);

			SetEvent(pipeIO); // Sets the write event to signaled state

			std::this_thread::sleep_for(std::chrono::seconds(2));
		}

	}

	CloseHandle(hFile);
}
void pipeHandlerWrite(HANDLE* hFileB, std::exception_ptr ex_ptr) {
	try {
		//HANDLE hFile = *hFileB;

		DWORD nBytesToWrite = 6, nWrittenBytes = 0;
		char data[] = "ready";

		while (true) {
			int writeToPipeRequired = WaitForSingleObject(pipeIO, INFINITE); // waits for write event to be signaled
			if (writeToPipeRequired == WAIT_OBJECT_0) {
				ResetEvent(pipeIO); // Sets the write event to nonsignaled state
				BOOL resultOfWriting = messageReady(hFile, data, nBytesToWrite, nWrittenBytes);
				if (!resultOfWriting) {
					throw new std::exception("Error occured when trying to write data in to the pipe");
				}
				SetEvent(pipeIO2); // Sets the Read event to signaled state
			}
		}
	}
	catch (std::exception) {

		ex_ptr = std::current_exception();
		return;
	}

}
bool messageReady(HANDLE hFile, char data[], DWORD nBytesToWrite, DWORD nWrittenBytes) {
	BOOL result = WriteFile(hFile, data, nBytesToWrite, &nWrittenBytes, NULL); // Writes data to the pipe essentially
	if (!result) {
		std::cout << "Data not written " << GetLastError() << std::endl;
		return false;
	}
	else {

		std::cout << "Written amount: (bytes) " << nWrittenBytes << std::endl;
		return true;

	}
	return true;
}
void parseStringAndCreateObject(char* str) {
	char arr[10];

	try {
		strcpy_s(arr, 10, str);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return;
	}

	rsize_t strmax = sizeof str;
	std::cout << arr << std::endl;
	char* tok;
	char* nextToken = NULL;
	tok = strtok_s(str, " <>", &nextToken);

	while (tok != NULL) {
		std::cout << tok << std::endl;
		tok = strtok_s(NULL, " <>", &nextToken);
	}

}

int main() {

	std::exception_ptr ex_ptr = nullptr;

	std::thread keyBoardHandler(kb, ex_ptr); // Thread handeling the keyboard

	std::thread pipeThread(connectAndSendReady, ex_ptr); // Thread to connect to the Pipe

	std::thread pipeWrite(pipeHandlerWrite, &hFile, ex_ptr); // Sending data to server 

	pipeWrite.join();
	pipeThread.join();
	keyBoardHandler.join();

	try {
		if (ex_ptr) {
			std::rethrow_exception(ex_ptr);
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu