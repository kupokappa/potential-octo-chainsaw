// Fill out your copyright notice in the Description page of Project Settings.


#include "dummy.h"
#include "Macros.h"
#include <string>
#include <sstream>

// Sets default values
Adummy::Adummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void Adummy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Adummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
