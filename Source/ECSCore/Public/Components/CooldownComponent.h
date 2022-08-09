#pragma once

#include "CooldownComponent.generated.h"

USTRUCT(BlueprintType)
struct FCooldownComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<FName, float> CooldownMap{};

	FCooldownComponent()
	{
	};

	explicit FCooldownComponent(const TMap<FName, float> Value)
	{
		CooldownMap = Value;
	}

	void AddCooldown(const FName Trait, const float Time)
	{
		if (CooldownMap.Find(Trait) != nullptr)
			CooldownMap[Trait] = Time;
		else
			CooldownMap.Add(Trait, Time);
	}

	bool HasCooldown(const FName Trait)
	{
		if (CooldownMap.Find(Trait)) return true;
		return false;
	}

	void CalculateCooldown(const float DeltaTime)
	{
		if (CooldownMap.Num() <= 0) return;
		TArray<FName> MyKeys;
		CooldownMap.GetKeys(MyKeys);
		for (auto Key : MyKeys)
		{
			CooldownMap[Key] -= DeltaTime;
			if (CooldownMap[Key] <= 0)
			{
				CooldownMap.Remove(Key);
			}
		}
		CooldownMap.Compact();
	}

	void Remove(const FName Trait)
	{
		if (HasCooldown(Trait))
			CooldownMap.Remove(Trait);
	}
};
