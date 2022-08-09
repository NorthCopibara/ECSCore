#pragma once

#include "InterpolateComponent.generated.h"

USTRUCT(BlueprintType)
struct FInterpolateComponent
{
	GENERATED_BODY()
	FInterpolateComponent() : Value(16){}
	explicit FInterpolateComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
};
