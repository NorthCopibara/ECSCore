#pragma once

#include "InitialComponent.generated.h"

USTRUCT(BlueprintType)
struct FInitialComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value{};

	FInitialComponent(){}

	explicit FInitialComponent(const int32 Value) : Value(Value){}
};
