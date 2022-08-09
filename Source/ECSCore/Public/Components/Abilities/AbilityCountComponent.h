#pragma once

#include "AbilityCountComponent.generated.h"

USTRUCT(BlueprintType)
struct FAbilityCountComponent
{
	GENERATED_BODY()
	FAbilityCountComponent() : Value(){}
	explicit FAbilityCountComponent(const int32 Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value;	
};