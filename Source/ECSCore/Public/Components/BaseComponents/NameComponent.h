#pragma once

#include "NameComponent.generated.h"

USTRUCT(BlueprintType)
struct FNameComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Value{};

	FNameComponent(){}

	explicit FNameComponent(const FName Value) : Value(Value){}
};
