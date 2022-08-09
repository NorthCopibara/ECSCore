#pragma once

#include "RotationSpeedComponent.generated.h"

USTRUCT(BlueprintType)
struct FRotationSpeedComponent
{
	GENERATED_BODY()
	FRotationSpeedComponent() : Value(){}
	explicit FRotationSpeedComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
};
