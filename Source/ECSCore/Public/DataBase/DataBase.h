#pragma once
#include "Assets/AssetsBase.h"
#include "Configs/AbilitiesConfigs.h"
#include "Configs/TeamsConfig.h"

#include "DataBase.generated.h"

UCLASS(Blueprintable)
class ECSCORE_API UDataBase : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UAssetsBase> AssetBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Configs")
	TSubclassOf<UAbilitiesConfigs> AbilitySystemApplier;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Configs")
	TSubclassOf<UTeamsConfig> TeamsConfigs;

	//???
	template<typename T>
	T GetBase() { return AssetBase.GetDefaultObject(); }
};
