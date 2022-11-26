#pragma once
#include "MaxLifeTimeComponent.generated.h"

USTRUCT(BlueprintType)
struct FMaxLifeTimeComponent
{
	GENERATED_BODY()
	FMaxLifeTimeComponent(){}
	explicit FMaxLifeTimeComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
};
