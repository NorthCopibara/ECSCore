#pragma once
#include "UId/UId.h"

#include "InteractiveUidComponent.generated.h"

USTRUCT(BlueprintType)
struct FInteractiveUidComponent
{
	GENERATED_BODY()
	FInteractiveUidComponent() : Value(FUId()){}
	explicit FInteractiveUidComponent(const FUId Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FUId Value;
};