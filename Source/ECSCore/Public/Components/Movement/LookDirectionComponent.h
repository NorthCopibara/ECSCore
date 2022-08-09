#pragma once

#include "LookDirectionComponent.generated.h"

USTRUCT(BlueprintType)
struct FLookDirectionComponent
{
	GENERATED_BODY()
	FLookDirectionComponent() : Value(FVector::ZeroVector){}
	explicit FLookDirectionComponent(const FVector Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Value;
};
