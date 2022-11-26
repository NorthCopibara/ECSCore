// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitiesConfigs.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogAbilitiesConfigs, All, All);

struct FSubjectHandle;

UENUM()
enum class EActivateAbilityStatus : uint8
{
	None,
	Success,
	NotFound,
	Block,
	IsAvailable
};

USTRUCT(BlueprintType)
struct FAbilityConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<UScriptStruct*> BlockingComponents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<UScriptStruct*> ComponentsToDelete;
};

USTRUCT(BlueprintType)
struct FAbilitiesConfigsList
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<UScriptStruct*, FAbilityConfig> AbilitiesConfigs;
	
};

UCLASS(Blueprintable)
class ECSCORE_API UAbilitiesConfigs : public UDataAsset
{
	GENERATED_BODY()

public:
	TArray<FAbilitiesConfigsList> GetConfigs() const
	{
		return Configs;
	}

	TMap<UScriptStruct*, FAbilityConfig> GetConfigById(int32 Id)
	{
		if(!Configs.IsValidIndex(Id))
		{
			Id = 0;
			UE_LOG(LogAbilitiesConfigs, Error, TEXT("Ability config index is not valid"))
		}

		check(Configs.IsValidIndex(Id))
		
		return Configs[Id].AbilitiesConfigs;
	}

	int32 GetAbilitiesCount(int32 ConfigId) const
	{
		return Configs[ConfigId].AbilitiesConfigs.Num();
	}

private:
	UPROPERTY(EditAnywhere)
	TArray<FAbilitiesConfigsList> Configs;
};
