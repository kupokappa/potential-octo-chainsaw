// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UserPawn.generated.h"

UCLASS()
class SWITCHINPUTPASSTHRU_API AUserPawn : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	AUserPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Static mesh assigned to this pawn
	UPROPERTY(EditAnywhere)
	USceneComponent* UserVisComponent;

	unsigned char flush[9] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	// Input events
	void AButtonPressed();
	void AButtonReleased();

	void BButtonPressed();
	void BButtonReleased();

	void XButtonPressed();
	void XButtonReleased();

	void YButtonPressed();
	void YButtonReleased();

};
