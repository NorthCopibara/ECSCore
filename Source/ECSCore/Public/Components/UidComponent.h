#pragma once
#include "UId/UId.h"
#include "UIdComponent.generated.h"

USTRUCT(BlueprintType)
struct FUIdComponent
{
	GENERATED_BODY()
	FUIdComponent() : Value(FUId()){}
	explicit FUIdComponent(const FUId Value) : Value(Value) {}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FUId Value;
};