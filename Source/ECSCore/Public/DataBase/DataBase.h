#pragma once
#include "DataBase.generated.h"

UCLASS(Blueprintable)
class ECSCORE_API UDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
	template <typename T>
	T* GetBase()
	{        
		return Cast<T>(DataAssets[T::StaticClass()->GetName()]);
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FString, UDataAsset*> DataAssets;
};
