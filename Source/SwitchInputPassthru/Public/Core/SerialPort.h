// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"
#include "Winnt.h"
#endif

class SWITCHINPUTPASSTHRU_API FSerialPort {
public:
	FSerialPort();

	FSerialPort(const char* port, unsigned long BaudRate);

	// Initialization
	void Initialize(const char* port, unsigned long BaudRate);

	// Serial IO
	void Receive(unsigned char& data, unsigned int numBytes);
	void Send(unsigned char* data, unsigned int numBytes);

	// State handling
	void Connect();
	void Sync();
	void Disconnect();
	bool GetIsConnected();

	~FSerialPort();

private:
	HANDLE _handle;
	bool isConnected;
};

#if PLATFORM_WINDOWS
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif
