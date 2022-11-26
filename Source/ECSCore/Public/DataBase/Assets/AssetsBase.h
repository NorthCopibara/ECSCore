#pragma once

#include "AssetsBase.generated.h"

UCLASS(Blueprintable)
class ECSCORE_API UAssetsBase : public UDataAsset
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere)
	TMap<FName, TSubclassOf<AActor>> Prefabs;
};