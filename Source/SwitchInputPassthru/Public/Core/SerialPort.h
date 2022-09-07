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

	// Serial port initialization
	void Initialize(const char* port, unsigned long BaudRate);

	// Serial IO
	bool Receive(uint8_t& data, uint32_t numBytes);
	bool Send(uint8_t* data);

	// State handling
	void Connect();
	void Disconnect();
	bool GetIsConnected();
	void Sync();

	enum BridgeState {
		SYNCED,
		SYNC_START,
		SYNC_1,
		OUT_OF_SYNC
	};

	struct OutputPacket {
		uint8_t command;
		uint8_t crc8_ccitt;
		uint8_t receivedBytes;
	};

	enum USBCommand : uint8_t {
		COMMAND_NOP = 0,
		COMMAND_SYNC_1 = 0x33,
		COMMAND_SYNC_2 = 0xCC,
		COMMAND_SYNC_START = 0xFF
	};

	enum USBResponse : uint8_t {
		RESP_USB_ACK = 0x90,
		RESP_UPDATE_ACK = 0x91,
		RESP_UPDATE_NACK = 0x92,
		RESP_SYNC_START = 0xFF,
		RESP_SYNC_1 = 0xCC,
		RESP_SYNC_OK = 0x33
	};

	uint8_t flush[9] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	~FSerialPort();

private:
	HANDLE _handle;
	bool isConnected;
};

#if PLATFORM_WINDOWS
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif
