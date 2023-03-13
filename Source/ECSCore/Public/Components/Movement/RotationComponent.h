#pragma once
#include "RotationComponent.generated.h"

USTRUCT(BlueprintType)
struct FRotationComponent
{
	GENERATED_BODY()
	FRotationComponent() {}
	explicit FRotationComponent(const FRotator Value) : Value(Value){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator Value = FRotator::ZeroRotator;
};