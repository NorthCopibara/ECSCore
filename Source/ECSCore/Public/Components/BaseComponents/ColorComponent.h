#pragma once

#include "ColorComponent.generated.h"

USTRUCT(BlueprintType)
struct FColorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor Value{};

	FColorComponent(){}

	explicit FColorComponent(const FLinearColor Value) : Value(Value){}
};
