#pragma once

#include "CachePositionComponent.generated.h"

USTRUCT(BlueprintType)
struct FCachePositionComponent
{
	GENERATED_BODY()
	FCachePositionComponent() : Value(FVector::ZeroVector){}
	explicit FCachePositionComponent(const FVector Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Value;	
};