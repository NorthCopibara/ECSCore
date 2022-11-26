#pragma once
#include "FloatComponent.generated.h"

USTRUCT(BlueprintType)
struct FFloatComponent
{
	GENERATED_BODY()
	FFloatComponent() : Value(){}
	explicit FFloatComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
};
