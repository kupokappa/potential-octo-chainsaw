// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/InputEmuGameMode.h"
#include "Core/SerialPort.h"
#include "Macros.h"

// Create shared reference construct for FSerialPort
TSharedRef<FSerialPort> serialPort(new FSerialPort);

AInputEmuGameMode::AInputEmuGameMode() {}

void AInputEmuGameMode::HandleABtnPressed() {
	if (!serialPort.Get().GetIsConnected()) {
#ifdef UE_BUILD_DEBUG
		Log("Initializing port");
#endif
		// Connect to the USB-UART bridge at the specified port, with the specified baud rate
		if (InitSerial.IsBound()) {
			// The actual name of the port we'll connect to
			const char* portName = TCHAR_TO_ANSI(*InPortName);
			InitSerial.Execute(portName, (uint32_t)baudRate);
		}
	}
}
// Face buttons
void AInputEmuGameMode::HandleABtnReleased() {}
void AInputEmuGameMode::HandleBBtnPressed() {
	if (serialPort.Get().GetIsConnected()) {
		if (CloseSerial.IsBound()) {
			CloseSerial.Execute();
		}
	}
}
void AInputEmuGameMode::HandleBBtnReleased() {}
void AInputEmuGameMode::HandleXBtnPressed() {
	if (SyncBridge.IsBound()) {
		if (serialPort.Get().GetIsConnected()) {
			SyncBridge.Execute();
		}
	}
}
void AInputEmuGameMode::HandleXBtnReleased() {}
void AInputEmuGameMode::HandleYBtnPressed() {}
void AInputEmuGameMode::HandleYBtnReleased() {}

void AInputEmuGameMode::HandlePlusBtnPressed() {}
void AInputEmuGameMode::HandlePlusBtnReleased() {}
void AInputEmuGameMode::HandleMinusBtnPressed() {}
void AInputEmuGameMode::HandleMinusBtnReleased() {}
void AInputEmuGameMode::HandleHomeBtnPressed() {}
void AInputEmuGameMode::HandleHomeBtnReleased() {}
void AInputEmuGameMode::HandleCaptureBtnPressed() {}
void AInputEmuGameMode::HandleCaptureBtnReleased() {}

// Stick buttons
void AInputEmuGameMode::HandleLStickBtnPressed() {}
void AInputEmuGameMode::HandleLStickBtnReleased() {}
void AInputEmuGameMode::HandleRStickBtnPressed() {}
void AInputEmuGameMode::HandleRStickBtnReleased() {}

// Shoulder buttons
void AInputEmuGameMode::HandleLBtnPressed() {}
void AInputEmuGameMode::HandleLBtnReleased() {}
void AInputEmuGameMode::HandleRBtnPressed() {}
void AInputEmuGameMode::HandleRBtnReleased() {}
void AInputEmuGameMode::HandleZLBtnPressed() {}
void AInputEmuGameMode::HandleZLBtnReleased() {}
void AInputEmuGameMode::HandleZRBtnPressed() {}
void AInputEmuGameMode::HandleZRBtnReleased() {}

// Hat
void AInputEmuGameMode::HandleUpBtnPressed() {}
void AInputEmuGameMode::HandleUpBtnReleased() {}
void AInputEmuGameMode::HandleDownBtnPressed() {}
void AInputEmuGameMode::HandleDownBtnReleased() {}
void AInputEmuGameMode::HandleLeftBtnPressed() {}
void AInputEmuGameMode::HandleLeftBtnReleased() {}
void AInputEmuGameMode::HandleRightBtnPressed() {}
void AInputEmuGameMode::HandleRightBtnReleased() {}

// Called when the game starts or when spawned
void AInputEmuGameMode::BeginPlay() {
	// Bind serial event delegates
	InitSerial.BindSP(serialPort, &FSerialPort::Initialize);
	CloseSerial.BindSP(serialPort, &FSerialPort::Disconnect);
	SyncBridge.BindSP(serialPort, &FSerialPort::Sync);

	Super::BeginPlay();
}

// Called every frame
void AInputEmuGameMode::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void AInputEmuGameMode::EndPlay(const EEndPlayReason::Type endPlayReason) {
	// Close the serial port before quitting, if it's open
	CloseSerial.ExecuteIfBound();

	Super::EndPlay(endPlayReason);
}

AInputEmuGameMode::~AInputEmuGameMode() {

}
