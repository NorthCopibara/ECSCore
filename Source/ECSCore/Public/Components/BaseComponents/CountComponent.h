#pragma once

#include "CountComponent.generated.h"

USTRUCT(BlueprintType)
struct FCountComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value{};

	FCountComponent(){}

	explicit FCountComponent(const int32 Value) : Value(Value){}
};
