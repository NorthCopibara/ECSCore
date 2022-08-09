#pragma once

#include "ScaleTransformComponent.generated.h"

USTRUCT(BlueprintType)
struct FScaleTransformComponent
{
	GENERATED_BODY()
	FScaleTransformComponent() : Value(FVector::ZeroVector){}
	explicit FScaleTransformComponent(const FVector Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Value;	
};
