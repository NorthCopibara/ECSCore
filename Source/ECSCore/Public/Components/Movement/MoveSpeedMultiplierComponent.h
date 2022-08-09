#pragma once

#include "MoveSpeedMultiplierComponent.generated.h"

USTRUCT(BlueprintType)
struct FMoveSpeedMultiplierComponent
{
	GENERATED_BODY()
	FMoveSpeedMultiplierComponent() : Value(){}
	explicit FMoveSpeedMultiplierComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
};
