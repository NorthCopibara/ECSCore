#pragma once

#include "CurrentAbilityConfigIdComponent.generated.h"

USTRUCT(BlueprintType)
struct FCurrentAbilityConfigIdComponent
{
	GENERATED_BODY()
	FCurrentAbilityConfigIdComponent() : Value(){}
	explicit FCurrentAbilityConfigIdComponent(const int32 Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value;	
};