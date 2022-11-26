#pragma once
#include "IntComponent.generated.h"

USTRUCT(BlueprintType)
struct FIntComponent
{
	GENERATED_BODY()
	FIntComponent() : Value(){}
	explicit FIntComponent(const int32 Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value;
};
