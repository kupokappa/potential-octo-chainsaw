// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UserPawn.h"
#include <Core/SerialPort.h>
#include "Macros.h"
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStatics.h>

#include <string>
#include <sstream>
#include <iostream>

// Create shared reference construct for FSerialPort
TSharedRef<FSerialPort> _sp(new FSerialPort);

// Sets default values
AUserPawn::AUserPawn() {
	// This actor ticks every frame
	PrimaryActorTick.bCanEverTick = true;

	// This pawn is controlled by player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a root component to attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create and attach a CameraComponent to RootComponent
	UCameraComponent* UserCam = CreateDefaultSubobject<UCameraComponent>(TEXT("UserCamera"));
	UserCam->SetupAttachment(RootComponent);

	// Set up initial camera position and rotation
	UserCam->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	UserCam->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// Create and attach a Static Mesh to RootComponent
	UserVisComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UserVisibleComponent"));
	UserVisComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUserPawn::BeginPlay() {
	// Bind serial event delegates
	InitSerial.BindSP(_sp, &FSerialPort::Initialize);
	CloseSerial.BindSP(_sp, &FSerialPort::Disconnect);
	SyncBridge.BindSP(_sp, &FSerialPort::Sync);

	Super::BeginPlay();
}

void AUserPawn::EndPlay(const EEndPlayReason::Type endPlayReason) {
	// Close the serial port before quitting, if it's open
	CloseSerial.ExecuteIfBound();

	Super::EndPlay(endPlayReason);
}

uint8_t inByte;
std::ostringstream oss;

// Called every frame
void AUserPawn::Tick(float DeltaTime) {
	//inByte = 0x00;

	/*if (_sp.Get().Receive(inByte, 1)) {
		if (inByte != NULL) {
			oss.flush();
			oss << std::showbase;
			oss << "Received " << std::hex << inByte;
			if (GEngine) { GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Cyan, (FString)oss.str().c_str()); }
		}
	}*/
	
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	// Bind input events
	InputComponent->BindAction("SW_A", IE_Pressed, this, &AUserPawn::AButtonPressed);
	InputComponent->BindAction("SW_A", IE_Released, this, &AUserPawn::AButtonReleased);

	InputComponent->BindAction("SW_B", IE_Pressed, this, &AUserPawn::BButtonPressed);
	InputComponent->BindAction("SW_B", IE_Released, this, &AUserPawn::BButtonReleased);

	InputComponent->BindAction("SW_X", IE_Pressed, this, &AUserPawn::XButtonPressed);
	InputComponent->BindAction("SW_X", IE_Released, this, &AUserPawn::XButtonReleased);

	InputComponent->BindAction("SW_Y", IE_Pressed, this, &AUserPawn::YButtonPressed);
	InputComponent->BindAction("SW_Y", IE_Released, this, &AUserPawn::YButtonReleased);
}

void AUserPawn::AButtonPressed() {
	if (!_sp.Get().GetIsConnected()) {
#ifdef UE_BUILD_DEBUG
		Log("Initializing port");
#endif
		// TODO: check for and execute delegates based on connection state

		// Connect to the USB-UART bridge at the specified port, with the specified baud rate
		if (InitSerial.IsBound()) {
			// The actual name of the port we'll connect to
			const char* portName = TCHAR_TO_ANSI(*InPortName);
			InitSerial.Execute(portName, 19200);
		}
	}
}

void AUserPawn::AButtonReleased() {}

void AUserPawn::BButtonPressed() {
	if (_sp.Get().GetIsConnected()) {
		if (CloseSerial.IsBound()) {
			CloseSerial.Execute();
		}
	}

	/*
#ifdef UE_BUILD_DEBUG
	Log("Sending flush buffer");
#endif
	_port.Send(flush, sizeof(flush));
	*/
}

void AUserPawn::BButtonReleased() {}

void AUserPawn::XButtonPressed() {
	if (SyncBridge.IsBound()) {
		if (_sp.Get().GetIsConnected()) {
			SyncBridge.Execute();
		}
	}
}

void AUserPawn::XButtonReleased() {}

void AUserPawn::YButtonPressed() {}

void AUserPawn::YButtonReleased() {}

AUserPawn::~AUserPawn() {

}
