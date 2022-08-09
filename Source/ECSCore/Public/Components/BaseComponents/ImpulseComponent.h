#pragma once

#include "ImpulseComponent.generated.h"

USTRUCT(BlueprintType)
struct FImpulseComponent
{
	GENERATED_BODY()
	FImpulseComponent(){}
	explicit FImpulseComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value{};
};
