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

	/* Input events */
	// Face buttons
	void AButtonPressed();
	void AButtonReleased();
	void BButtonPressed();
	void BButtonReleased();
	void XButtonPressed();
	void XButtonReleased();
	void YButtonPressed();
	void YButtonReleased();
	
	void PlusButtonPressed();
	void PlusButtonReleased();
	void MinusButtonPressed();
	void MinusButtonReleased();
	void HomeButtonPressed();
	void HomeButtonReleased();
	void CaptureButtonPressed();
	void CaptureButtonReleased();

	// Stick buttons
	void LStickButtonPressed();
	void LStickttonReleased();
	void RStickButtonPressed();
	void RStickButtonReleased();

	// Shoulder buttons
	void LButtonPressed();
	void LButtonReleased();
	void RButtonPressed();
	void RButtonReleased();
	void ZLButtonPressed();
	void ZLButtonReleased();
	void ZRButtonPressed();
	void ZRButtonReleased();

	// Hat
	void UpButtonPressed();
	void UpButtonReleased();
	void DownButtonPressed();
	void DownButtonReleased();
	void LeftButtonPressed();
	void LeftButtonReleased();
	void RightButtonPressed();
	void RightButtonReleased();

	~AUserPawn();

private:

};
