// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UserPawn.h"
#include <Core/SerialPort.h>
#include <Core/InputEmuGameMode.h>
#include "Macros.h"
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStatics.h>

#include <string>
#include <sstream>
#include <iostream>

AInputEmuGameMode* gameMode;

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
	// Get GameMode reference
	gameMode = GetWorld()->GetAuthGameMode<AInputEmuGameMode>();

	Super::BeginPlay();
}

void AUserPawn::EndPlay(const EEndPlayReason::Type endPlayReason) {

	Super::EndPlay(endPlayReason);
}

// Called every frame
void AUserPawn::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	/* Bind input events */
	// Face buttons
	InputComponent->BindAction("SW_A", IE_Pressed, this, &AUserPawn::AButtonPressed);
	InputComponent->BindAction("SW_A", IE_Released, this, &AUserPawn::AButtonReleased);
	InputComponent->BindAction("SW_B", IE_Pressed, this, &AUserPawn::BButtonPressed);
	InputComponent->BindAction("SW_B", IE_Released, this, &AUserPawn::BButtonReleased);
	InputComponent->BindAction("SW_X", IE_Pressed, this, &AUserPawn::XButtonPressed);
	InputComponent->BindAction("SW_X", IE_Released, this, &AUserPawn::XButtonReleased);
	InputComponent->BindAction("SW_Y", IE_Pressed, this, &AUserPawn::YButtonPressed);
	InputComponent->BindAction("SW_Y", IE_Released, this, &AUserPawn::YButtonReleased);

	InputComponent->BindAction("SW_PLUS", IE_Pressed, this, &AUserPawn::PlusButtonPressed);
	InputComponent->BindAction("SW_PLUS", IE_Released, this, &AUserPawn::PlusButtonReleased);
	InputComponent->BindAction("SW_MINUS", IE_Pressed, this, &AUserPawn::MinusButtonPressed);
	InputComponent->BindAction("SW_MINUS", IE_Released, this, &AUserPawn::MinusButtonReleased);
	InputComponent->BindAction("SW_HOME", IE_Pressed, this, &AUserPawn::HomeButtonPressed);
	InputComponent->BindAction("SW_HOME", IE_Released, this, &AUserPawn::HomeButtonReleased);
	InputComponent->BindAction("SW_CAPTURE", IE_Pressed, this, &AUserPawn::CaptureButtonPressed);
	InputComponent->BindAction("SW_CAPTURE", IE_Released, this, &AUserPawn::CaptureButtonReleased);

	InputComponent->BindAction("SW_RStick", IE_Pressed, this, &AUserPawn::RStickButtonPressed);
	InputComponent->BindAction("SW_RStick", IE_Released, this, &AUserPawn::RStickButtonReleased);
	InputComponent->BindAction("SW_LStick", IE_Pressed, this, &AUserPawn::LStickButtonPressed);
	InputComponent->BindAction("SW_LStick", IE_Released, this, &AUserPawn::LStickttonReleased);
	
	InputComponent->BindAction("SW_L", IE_Pressed, this, &AUserPawn::LButtonPressed);
	InputComponent->BindAction("SW_L", IE_Released, this, &AUserPawn::LButtonReleased);
	InputComponent->BindAction("SW_R", IE_Pressed, this, &AUserPawn::RButtonPressed);
	InputComponent->BindAction("SW_R", IE_Released, this, &AUserPawn::RButtonReleased);
	InputComponent->BindAction("SW_ZL", IE_Pressed, this, &AUserPawn::ZLButtonPressed);
	InputComponent->BindAction("SW_ZL", IE_Released, this, &AUserPawn::ZLButtonReleased);
	InputComponent->BindAction("SW_ZR", IE_Pressed, this, &AUserPawn::ZRButtonPressed);
	InputComponent->BindAction("SW_ZR", IE_Released, this, &AUserPawn::ZRButtonReleased);

	InputComponent->BindAction("SW_HAT_U", IE_Pressed, this, &AUserPawn::UpButtonPressed);
	InputComponent->BindAction("SW_HAT_U", IE_Released, this, &AUserPawn::UpButtonReleased);
	InputComponent->BindAction("SW_HAT_D", IE_Pressed, this, &AUserPawn::DownButtonPressed);
	InputComponent->BindAction("SW_HAT_D", IE_Released, this, &AUserPawn::DownButtonReleased);
	InputComponent->BindAction("SW_HAT_L", IE_Pressed, this, &AUserPawn::LeftButtonPressed);
	InputComponent->BindAction("SW_HAT_L", IE_Released, this, &AUserPawn::LeftButtonReleased);
	InputComponent->BindAction("SW_HAT_R", IE_Pressed, this, &AUserPawn::RightButtonPressed);
	InputComponent->BindAction("SW_HAT_R", IE_Released, this, &AUserPawn::RightButtonReleased);
}

/* Input events */
// Face buttons
void AUserPawn::AButtonPressed() { gameMode->HandleABtnPressed(); }
void AUserPawn::AButtonReleased() {	gameMode->HandleABtnReleased(); }
void AUserPawn::BButtonPressed() { gameMode->HandleBBtnPressed(); }
void AUserPawn::BButtonReleased() { gameMode->HandleBBtnReleased(); }
void AUserPawn::XButtonPressed() { gameMode->HandleXBtnPressed(); }
void AUserPawn::XButtonReleased() { gameMode->HandleXBtnReleased(); }
void AUserPawn::YButtonPressed() { gameMode->HandleYBtnPressed(); }
void AUserPawn::YButtonReleased() { gameMode->HandleYBtnReleased(); }

void AUserPawn::PlusButtonPressed() { gameMode->HandlePlusBtnPressed(); }
void AUserPawn::PlusButtonReleased() { gameMode->HandlePlusBtnReleased(); }
void AUserPawn::MinusButtonPressed() { gameMode->HandleMinusBtnPressed(); }
void AUserPawn::MinusButtonReleased() { gameMode->HandleMinusBtnReleased(); }
void AUserPawn::HomeButtonPressed() { gameMode->HandleHomeBtnPressed(); }
void AUserPawn::HomeButtonReleased() { gameMode->HandleHomeBtnReleased(); }
void AUserPawn::CaptureButtonPressed() { gameMode->HandleCaptureBtnPressed(); }
void AUserPawn::CaptureButtonReleased() { gameMode->HandleCaptureBtnReleased(); }

// Stick buttons
void AUserPawn::LStickButtonPressed() { gameMode->HandleLStickBtnPressed(); }
void AUserPawn::LStickttonReleased() { gameMode->HandleLStickBtnReleased(); }
void AUserPawn::RStickButtonPressed() { gameMode->HandleRStickBtnPressed(); }
void AUserPawn::RStickButtonReleased() { gameMode->HandleRStickBtnReleased(); }

// Shoulder buttons
void AUserPawn::LButtonPressed() { gameMode->HandleLBtnPressed(); }
void AUserPawn::LButtonReleased() { gameMode->HandleLBtnReleased(); }
void AUserPawn::RButtonPressed() { gameMode->HandleRBtnPressed(); }
void AUserPawn::RButtonReleased() { gameMode->HandleRBtnReleased(); }
void AUserPawn::ZLButtonPressed() { gameMode->HandleZLBtnPressed(); }
void AUserPawn::ZLButtonReleased() { gameMode->HandleZLBtnReleased(); }
void AUserPawn::ZRButtonPressed() { gameMode->HandleZRBtnPressed(); }
void AUserPawn::ZRButtonReleased() { gameMode->HandleZRBtnReleased(); }

// Hat
void AUserPawn::UpButtonPressed() { gameMode->HandleUpBtnPressed(); }
void AUserPawn::UpButtonReleased() { gameMode->HandleUpBtnReleased(); }
void AUserPawn::DownButtonPressed() { gameMode->HandleDownBtnPressed(); }
void AUserPawn::DownButtonReleased() { gameMode->HandleDownBtnReleased(); }
void AUserPawn::LeftButtonPressed() { gameMode->HandleLeftBtnPressed(); }
void AUserPawn::LeftButtonReleased() { gameMode->HandleLeftBtnReleased(); }
void AUserPawn::RightButtonPressed() { gameMode->HandleRightBtnPressed(); }
void AUserPawn::RightButtonReleased() { gameMode->HandleRightBtnReleased(); }

AUserPawn::~AUserPawn() {

}
