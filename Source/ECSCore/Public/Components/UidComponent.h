#pragma once
#include "UId/UId.h"

#include "UidComponent.generated.h"

USTRUCT(BlueprintType)
struct FUidComponent
{
	GENERATED_BODY()
	FUidComponent() : Value(FUId()){}
	explicit FUidComponent(const FUId Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FUId Value;
};