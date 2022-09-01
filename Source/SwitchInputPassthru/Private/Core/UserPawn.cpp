// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UserPawn.h"
#include <Core/SerialPort.h>
#include "Camera/CameraComponent.h"
#include "Macros.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AUserPawn::AUserPawn()
{
	// This actor ticks every frame
	PrimaryActorTick.bCanEverTick = true;

	// This pawn is controlled by player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create root component to attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* UserCam = CreateDefaultSubobject<UCameraComponent>(TEXT("UserCamera"));
	UserVisComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UserVisibleComponent"));

	UserCam->SetupAttachment(RootComponent);
	UserCam->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	UserCam->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	UserVisComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUserPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUserPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
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

SerialPort _port = SerialPort();

void AUserPawn::AButtonPressed()
{
#ifdef UE_BUILD_DEBUG
	Log("Initializing port");
#endif
	_port.Initialize("\\\\.\\COM3", 19200);
}

void AUserPawn::AButtonReleased()
{
}

void AUserPawn::BButtonPressed()
{
#ifdef UE_BUILD_DEBUG
	Log("Sending flush buffer");
#endif
	_port.Send(flush, sizeof(flush));
}

void AUserPawn::BButtonReleased()
{
}

void AUserPawn::XButtonPressed()
{
	_port.~SerialPort();
}

void AUserPawn::XButtonReleased()
{
}

void AUserPawn::YButtonPressed()
{
}

void AUserPawn::YButtonReleased()
{
}

