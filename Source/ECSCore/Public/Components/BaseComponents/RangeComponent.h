#pragma once

#include "RangeComponent.generated.h"

USTRUCT(BlueprintType)
struct FRangeComponent
{
	GENERATED_BODY()
	FRangeComponent(){}
	explicit FRangeComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value{};
};
