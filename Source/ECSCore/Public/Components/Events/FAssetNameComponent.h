#pragma once

#include "FAssetNameComponent.generated.h"

USTRUCT(BlueprintType)
struct FAssetNameComponent
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	FName Value;
	FAssetNameComponent(): Value(FName()){}
	explicit FAssetNameComponent(const FName Value)
	{
		this->Value = Value;
	}	
};
