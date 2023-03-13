#pragma once
#include "UIdComponent.h"
#include "OwnerUIdComponent.generated.h"

USTRUCT(BlueprintType)
struct FOwnerUIdComponent : public FUIdComponent
{
	GENERATED_BODY()
	FOwnerUIdComponent() {}
	explicit FOwnerUIdComponent(const FUId Value) : FUIdComponent(Value) {}
};
