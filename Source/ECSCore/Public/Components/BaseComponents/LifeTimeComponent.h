#pragma once

#include "LifeTimeComponent.generated.h"

USTRUCT(BlueprintType)
struct FLifeTimeComponent
{
	GENERATED_BODY()
	FLifeTimeComponent(){}
	explicit FLifeTimeComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value{};
};
