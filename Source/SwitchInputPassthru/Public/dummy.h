// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "dummy.generated.h"

UCLASS()
class SWITCHINPUTPASSTHRU_API Adummy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int32 HitPoints;

public:	
	// Sets default values for this actor's properties
	Adummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
