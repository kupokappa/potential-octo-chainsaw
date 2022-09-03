// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SerialPort.h"
#include "Macros.h"
#include <string>
#include <sstream>
#include <iostream>

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"
#include "Winnt.h"
#endif

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
	_handle = CreateFileA(port, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// Check for an invalid handle
	if (_handle == INVALID_HANDLE_VALUE) {

		// Print an on-screen debug message telling us our handle is invalid.
#ifdef UE_BUILD_DEBUG
		std::ostringstream oss;
		oss << "Failed to open port \"" << port << "\": ";
		auto res = GetLastError();
		oss << "Err " << res;
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

void FSerialPort::Receive(unsigned char& data, unsigned int numBytes) {
	ReadFile(_handle, &data, numBytes, NULL, NULL);
}

void FSerialPort::Send(unsigned char* data, unsigned int numBytes) {
	WriteFile(_handle, data, numBytes, NULL, NULL);
}

void FSerialPort::Connect() {
	//
}

void FSerialPort::Disconnect() {
	//
}

bool FSerialPort::GetIsConnected() {
	return isConnected;
}

void FSerialPort::Sync() {
	// Perform handshake here
}

// Deconstructor
FSerialPort::~FSerialPort() {
	if (isConnected) {
		if (CloseHandle(_handle)) {
			/* Print an on-screen debug message telling us
			the handle to our serial port couldn't be closed. */
#ifdef UE_BUILD_DEBUG
			Log("Successfully closed serial handle");
#endif
			// TODO: Report to the user that this task failed.
			isConnected = false;
		}
		else {
#ifdef UE_BUILD_DEBUG
			LogErr("Failed to close serial handle");
#endif
		}
	}
}

#if PLATFORM_WINDOWS
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif
