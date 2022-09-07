// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SerialPort.h"
#include "Macros.h"
#include <string>
#include <sstream>
#include <iostream>

FSerialPort::FSerialPort() :
	isConnected(false) {
}

FSerialPort::FSerialPort(const char* port, unsigned long baudRate) :
	isConnected(false) {
	Initialize(port, baudRate);
}

void FSerialPort::Initialize(const char* port, unsigned long baudRate) {

	FSerialPort::FSerialPort();

	// Init serial port handle
	_handle = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// Check for an invalid handle
	if (_handle == INVALID_HANDLE_VALUE) {

		// Print an on-screen debug message telling us our handle is invalid.
#ifdef UE_BUILD_DEBUG
		std::ostringstream oss;
		oss << "Failed to open port \"" << port << "\": ";
		
		auto res = GetLastError();

		// User input non-existent port
		if (res == ERROR_FILE_NOT_FOUND) {
			oss << "specified port doesn't exist.";
		}
		else {
			oss << "Err " << res;
		}

		LogErr(oss.str().c_str());
#endif

		// TODO: Report to the user that this task failed.
		return;
	}

	// Init serial parameters
	DCB _serialParams;

	if (!GetCommState(_handle, &_serialParams)) {

		// Print an on-screen debug message telling us our serial parameters are invalid.
#ifdef UE_BUILD_DEBUG
		LogErr("Invalid serial parameters.");
#endif
		// TODO: Report to the user that this task failed.
		return;
	}
	// Successfully opened a handle to our port; set params
	_serialParams.DCBlength = sizeof(DCB);
	_serialParams.BaudRate = baudRate;
	_serialParams.ByteSize = 8;
	_serialParams.StopBits = ONESTOPBIT;
	_serialParams.Parity = 0;

	if (!SetCommState(_handle, &_serialParams)) {
		// Print an on-screen debug message telling us our serial params couldn't be modified.
#ifdef UE_BUILD_DEBUG
		LogErr("Failed to set serial port parameters.");
#endif
		// TODO: Report to the user that this task failed.
		return;
	}

	// Init serial timeouts
	COMMTIMEOUTS _serialTimeouts{ 0 };

	_serialTimeouts.ReadIntervalTimeout = 50;
	_serialTimeouts.ReadTotalTimeoutConstant = 50;
	_serialTimeouts.WriteTotalTimeoutConstant = 50;

	if (!SetCommTimeouts(_handle, &_serialTimeouts)) {
		// Print an on-screen debug message telling us our serial params couldn't be modified.
#ifdef UE_BUILD_DEBUG
		LogErr("Failed to set serial port timeouts.");
#endif
		// TODO: Report to the user that this task failed.
		return;
	}

	// Our serial port is connected and set up
	isConnected = true;

#ifdef UE_BUILD_DEBUG
	std::ostringstream oss;
	oss << "Connected to port " << port;
	LogSuccess(oss.str().c_str());
#endif

	// Purge any queued incoming/outgoing data
	PurgeComm(_handle, PURGE_RXCLEAR | PURGE_TXCLEAR);

#ifdef UE_BUILD_DEBUG
	Log("Purged TX and RX buffers");
#endif
}

bool FSerialPort::Receive(uint8_t &data, uint32_t numBytes) {
	return ReadFile(_handle, &data, numBytes, NULL, NULL);
}

bool FSerialPort::Send(uint8_t* data) {
	return WriteFile(_handle, data, sizeof(data), NULL, NULL);
}

void FSerialPort::Connect() {
	//
}

void FSerialPort::Disconnect() {
	FSerialPort::~FSerialPort();
}

bool FSerialPort::GetIsConnected() {
	return isConnected;
}

void FSerialPort::Sync() {

	std::ostringstream oss;
	oss << std::showbase;

	if (!Send(flush)) {
		LogErr("Failed sending flush buffer");
	}
	
	uint8_t inByte[1];
	if (!Receive(*inByte, 1)) {
		LogErr("Failed receiving data from bridge");
	}

	oss << "Received " << std::hex << inByte << std::endl;
	Log(oss.str().c_str());

	if (inByte[0] == RESP_SYNC_START) {
		LogSuccess("whoa!");
	}
}

// Deconstructor
FSerialPort::~FSerialPort() {
	if (isConnected) {
		if (CloseHandle(_handle)) {

#ifdef UE_BUILD_DEBUG
			Log("Serial connection closed");
#endif

			isConnected = false;
		}
		else {
			/* Print an on-screen debug message telling us
			the handle to our serial port couldn't be closed. */
#ifdef UE_BUILD_DEBUG
			LogErr("Failed to close serial handle");
#endif

			// TODO: Report to the user that this task failed.
		}
	}
}
