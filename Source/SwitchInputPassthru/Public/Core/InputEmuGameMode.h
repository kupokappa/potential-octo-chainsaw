// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InputEmuGameMode.generated.h"

UCLASS()
class SWITCHINPUTPASSTHRU_API AInputEmuGameMode : public AGameModeBase {
	GENERATED_BODY()

public:
	AInputEmuGameMode();

	// User-input port name
	UPROPERTY(EditAnywhere)
	FString InPortName = "\\\\.\\COM3";

	// Probably won't change the baud rate from this
	UPROPERTY(EditAnywhere)
	uint32 baudRate = 19200;

	// Declare and assign SerialPort::Initialize() delegate
	DECLARE_DELEGATE_TwoParams(InitSerialDelegate, const char*, unsigned long)
	InitSerialDelegate InitSerial;

	// Declare and assign SerialPort::Disconnect() delegate
	DECLARE_DELEGATE(CloseSerialDelegate)
	CloseSerialDelegate CloseSerial;

	DECLARE_DELEGATE(SyncBridgeDelegate)
	SyncBridgeDelegate SyncBridge;

	// Face buttons
	void HandleABtnPressed();
	void HandleABtnReleased();
	void HandleBBtnPressed();
	void HandleBBtnReleased();
	void HandleXBtnPressed();
	void HandleXBtnReleased();
	void HandleYBtnPressed();
	void HandleYBtnReleased();

	void HandlePlusBtnPressed();
	void HandlePlusBtnReleased();
	void HandleMinusBtnPressed();
	void HandleMinusBtnReleased();
	void HandleHomeBtnPressed();
	void HandleHomeBtnReleased();
	void HandleCaptureBtnPressed();
	void HandleCaptureBtnReleased();

	// Stick buttons
	void HandleLStickBtnPressed();
	void HandleLStickBtnReleased();
	void HandleRStickBtnPressed();
	void HandleRStickBtnReleased();

	// Shoulder buttons
	void HandleLBtnPressed();
	void HandleLBtnReleased();
	void HandleRBtnPressed();
	void HandleRBtnReleased();
	void HandleZLBtnPressed();
	void HandleZLBtnReleased();
	void HandleZRBtnPressed();
	void HandleZRBtnReleased();

	// Hat
	void HandleUpBtnPressed();
	void HandleUpBtnReleased();
	void HandleDownBtnPressed();
	void HandleDownBtnReleased();
	void HandleLeftBtnPressed();
	void HandleLeftBtnReleased();
	void HandleRightBtnPressed();
	void HandleRightBtnReleased();

	void ConnectToBridge();

	~AInputEmuGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
};
