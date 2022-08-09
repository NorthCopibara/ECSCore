#pragma once

#include "MoveSpeedComponent.generated.h"

USTRUCT(BlueprintType)
struct FMoveSpeedComponent
{
	GENERATED_BODY()
	FMoveSpeedComponent() : Value(){}
	explicit FMoveSpeedComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
};
