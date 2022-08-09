#pragma once

#include "ForceComponent.generated.h"

USTRUCT(BlueprintType)
struct FForceComponent
{
	GENERATED_BODY()
	FForceComponent(){}
	explicit FForceComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value{};
};
