#pragma once

#include "VelocityComponent.generated.h"

USTRUCT(BlueprintType)
struct FVelocityComponent
{
	GENERATED_BODY()
	FVelocityComponent() : Value(){}
	explicit FVelocityComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
};