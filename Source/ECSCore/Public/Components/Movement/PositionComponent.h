#pragma once

#include "PositionComponent.generated.h"

USTRUCT(BlueprintType)
struct FPositionComponent
{
	GENERATED_BODY()
	FPositionComponent() : Value(FVector::ZeroVector){}
	explicit FPositionComponent(const FVector Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Value;	
};