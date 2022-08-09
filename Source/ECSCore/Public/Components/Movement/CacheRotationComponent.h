#pragma once

#include "CacheRotationComponent.generated.h"

USTRUCT(BlueprintType)
struct FCacheRotationComponent
{
	GENERATED_BODY()
	FCacheRotationComponent() : Value(FRotator::ZeroRotator){}
	explicit FCacheRotationComponent(const FRotator Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator Value;	
};
