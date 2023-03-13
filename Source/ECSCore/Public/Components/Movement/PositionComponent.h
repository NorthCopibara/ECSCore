#pragma once
#include "PositionComponent.generated.h"

USTRUCT(BlueprintType)
struct FPositionComponent
{
	GENERATED_BODY()
	FPositionComponent() {}
	explicit FPositionComponent(const FVector Value) : Value(Value){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Value = FVector::ZeroVector;	
};