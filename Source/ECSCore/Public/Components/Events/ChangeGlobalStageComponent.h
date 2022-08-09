#pragma once

#include "Enums/EGlobalGameState.h"
#include "ChangeGlobalStageComponent.generated.h"


USTRUCT(BlueprintType)
struct FChangeGlobalStageComponent
{
	GENERATED_BODY()
	FChangeGlobalStageComponent() : Value(EGlobalGameState()){}
	explicit FChangeGlobalStageComponent(const EGlobalGameState Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EGlobalGameState Value;
};