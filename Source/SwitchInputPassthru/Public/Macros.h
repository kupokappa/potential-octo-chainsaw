// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class SWITCHINPUTPASSTHRU_API Macros
{
#define LogSuccess(InString) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, (FString)InString);}
#define Log(InString) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, (FString)InString);}
#define LogWarn(InString) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (FString)InString);}
#define LogErr(InString) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, (FString)InString);}

public:
	Macros();
	~Macros();
};
