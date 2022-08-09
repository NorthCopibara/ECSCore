#pragma once

#include "StaticFrameCountComponent.generated.h"

USTRUCT(BlueprintType)
struct FStaticFrameCountComponent
{
	GENERATED_BODY()
	FStaticFrameCountComponent() : Value(){}
	explicit FStaticFrameCountComponent(const int32 Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value;
};