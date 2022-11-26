#pragma once
#include "RotatorComponent.generated.h"

USTRUCT(BlueprintType)
struct FRotatorComponent
{
	GENERATED_BODY()
	FRotatorComponent() {}
	explicit FRotatorComponent(const FRotator Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator Value;
};
