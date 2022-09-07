// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UserPawn.generated.h"

UCLASS()
class SWITCHINPUTPASSTHRU_API AUserPawn : public APawn {
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

public:
	// Set default values for this pawn's properties
	AUserPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Static mesh assigned to this pawn
	UPROPERTY(EditAnywhere)
	USceneComponent* UserVisComponent;

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

	// Input events
	void AButtonPressed();
	void AButtonReleased();

	void BButtonPressed();
	void BButtonReleased();

	void XButtonPressed();
	void XButtonReleased();

	void YButtonPressed();
	void YButtonReleased();

	~AUserPawn();

private:

};
