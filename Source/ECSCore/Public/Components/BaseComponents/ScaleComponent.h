#pragma once

#include "ScaleComponent.generated.h"

USTRUCT(BlueprintType)
struct FScaleComponent
{
	GENERATED_BODY()
	FScaleComponent(){}
	explicit FScaleComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value{};
};
