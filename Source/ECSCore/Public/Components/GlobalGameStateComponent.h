#pragma once

#include "Enums/EGlobalGameState.h"
#include "GlobalGameStateComponent.generated.h"


USTRUCT(BlueprintType)
struct FGlobalGameStateComponent
{
	GENERATED_BODY()
	FGlobalGameStateComponent() : Value(EGlobalGameState()){}
	explicit FGlobalGameStateComponent(const EGlobalGameState Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EGlobalGameState Value;
};