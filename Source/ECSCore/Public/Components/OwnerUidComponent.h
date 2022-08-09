#pragma once
#include "UId/UId.h"

#include "OwnerUidComponent.generated.h"

USTRUCT(BlueprintType)
struct FOwnerUidComponent
{
	GENERATED_BODY()
	FOwnerUidComponent() : Value(FUId()){}
	explicit FOwnerUidComponent(const FUId Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FUId Value;
};
