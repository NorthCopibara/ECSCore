#pragma once

#include "AbilityCounterComponent.generated.h"

USTRUCT(BlueprintType)
struct FAbilityCounterComponent
{
	GENERATED_BODY()
	FAbilityCounterComponent() : Value(){}
	explicit FAbilityCounterComponent(const int32 Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value;	
};