// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/TeamType.h"

#include "UObject/Object.h"
#include "TeamsConfig.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogTeamConfigs, All, All);

USTRUCT(BlueprintType)
struct FTeamTable
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	TArray<ETeamType> Enemies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	TArray<ETeamType> Friends;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	TArray<ETeamType> Neutrals;
};

UCLASS(Blueprintable)
class ECSCORE_API UTeamsConfig : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<ETeamType, FTeamTable> TeamsConfigs;

public:
	bool IsEnemy(ETeamType MyTeam, ETeamType TargetTeam)
	{
		if (TargetTeam == ETeamType::None || MyTeam == ETeamType::None)
		{
			UE_LOG(LogTeamConfigs, Error, TEXT("None team"))
			return false;
		}
		
		check(TeamsConfigs.Contains(MyTeam));
		return CheckTeam(TargetTeam, TeamsConfigs[MyTeam].Enemies);
	}

	bool IsFriend(ETeamType MyTeam, ETeamType TargetTeam)
	{
		if (TargetTeam == ETeamType::None || MyTeam == ETeamType::None)
		{
			UE_LOG(LogTeamConfigs, Error, TEXT("None team"))
			return false;
		}
		
		check(TeamsConfigs.Contains(MyTeam));
		return CheckTeam(TargetTeam, TeamsConfigs[MyTeam].Friends);
	}

	bool IsNeutrals(ETeamType MyTeam, ETeamType TargetTeam)
	{
		if (TargetTeam == ETeamType::None || MyTeam == ETeamType::None)
		{
			UE_LOG(LogTeamConfigs, Error, TEXT("None team"))
			return false;
		}

		check(TeamsConfigs.Contains(MyTeam));
		return CheckTeam(TargetTeam, TeamsConfigs[MyTeam].Neutrals);
	}

private:
	static bool CheckTeam(ETeamType TargetTeam, TArray<ETeamType> TargetArray)
	{
		for (auto Team : TargetArray)
		{
			if (Team == TargetTeam)
			{
				return true;
			}
		}
		return false;
	};
};
