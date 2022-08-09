#pragma once

#include "ThicknessComponent.generated.h"

USTRUCT(BlueprintType)
struct FThicknessComponent
{
	GENERATED_BODY()
	FThicknessComponent(){}
	explicit FThicknessComponent(const float Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value{};
};
