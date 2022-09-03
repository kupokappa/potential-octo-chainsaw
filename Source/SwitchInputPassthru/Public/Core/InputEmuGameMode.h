// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InputEmuGameMode.generated.h"

/**
 *
 */
UCLASS()
class SWITCHINPUTPASSTHRU_API AInputEmuGameMode : public AGameModeBase {
	GENERATED_BODY()

public:
	AInputEmuGameMode();

	UPROPERTY(EditAnywhere)
	FString PortName;

	~AInputEmuGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
