#pragma once
#include "VectorComponent.generated.h"

USTRUCT(BlueprintType)
struct FVectorComponent
{
	GENERATED_BODY()
	FVectorComponent() {}
	explicit FVectorComponent(const FVector Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Value;
};
