#pragma once
#include "AssetNameComponent.generated.h"

USTRUCT(BlueprintType)
struct FAssetNameComponent
{
	GENERATED_BODY()
	FAssetNameComponent() {}
	explicit FAssetNameComponent(const FText Value) : Value(Value){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Value{};	
};
