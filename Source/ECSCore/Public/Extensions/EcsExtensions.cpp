#include "EcsExtensions.h"

#include "Components/OwnerUIdComponent.h"
#include "Components/Abilities/AbilityCountComponent.h"
#include "Components/Abilities/AbilityCounterComponent.h"
#include "Components/Flags/AbilityComponent.h"
#include "UId/UIdSubjectManager.h"

namespace EcsExtensions
{
	void SetTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject,
	                     UScriptStruct* TraitBase, const void* const TraitData)
	{
		Subject.SetTrait(TraitBase, TraitData);
		Mechanism->SpawnSubject().SetTrait(FEventAddComponent(TraitBase, Subject));
	}

	void ObtainTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, UScriptStruct* Trait)
	{
		Subject.ObtainTrait(Trait);
		Mechanism->SpawnSubject().SetTrait(FEventAddComponent(Trait, Subject));
	}

	void RemoveTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, UScriptStruct* Trait)
	{
		Subject.RemoveTrait(Trait);
		Mechanism->SpawnSubject().SetTrait(FEventRemoveComponent(Trait, Subject));
	}

	EActivateAbilityStatus SetAbilityAndFire(AMechanism* Mechanism, const FSubjectHandle Subject,
	                                         UScriptStruct* TraitBase, int32 ConfigId)
	{
		const auto Configs = GetDataBaseByType<UAbilitiesConfigs>(Mechanism)->GetConfigById(ConfigId);

		EActivateAbilityStatus Result = EActivateAbilityStatus::Success;
		if (CheckAndRemoveAbilities(Mechanism, Subject, TraitBase, Configs, Result)) return Result;
		Subject.ObtainTrait(TraitBase);
		return Result;
	}

	bool CheckAndRemoveAbilities(AMechanism* Mechanism, const FSubjectHandle Subject, UScriptStruct* Trait,
	                             const TMap<UScriptStruct*, FAbilityConfig> Configs, EActivateAbilityStatus& Result)
	{
		if (Subject.HasTrait(Trait))
		{
			Result = EActivateAbilityStatus::IsAvailable;
			return true;
		}

		if (!Configs.Contains(Trait))
		{
			UE_LOG(LogAbilitiesConfigs, Error, TEXT("Component not found!"))
			Result = EActivateAbilityStatus::NotFound;
			return true;
		}

		for (const auto BlockTrait : Configs[Trait].BlockingComponents)
		{
			if (Subject.HasTrait(BlockTrait))
			{
				Result = EActivateAbilityStatus::Block;
				return true;
			}
		}

		for (const auto TraitToDelete : Configs[Trait].ComponentsToDelete)
		{
			if (Subject.HasTrait(TraitToDelete))
				CancelAbility(Mechanism, Subject, TraitToDelete);
		}

		return false;
	}

	void CancelAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter)
	{
		EcsExtensionsPrivate::ApplyAbility<FCancelAbilityComponent>(Mechanism, Subject, TraitFilter,
		                                                            FCancelAbilityComponent());
	}

	void EndAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter)
	{
		EcsExtensionsPrivate::ApplyAbility<FEndAbilityComponent>(Mechanism, Subject, TraitFilter,
		                                                         FEndAbilityComponent());
	}

	void ApplyFeatures(TArray<UScriptStruct*> Features, FSubjectHandle Subject)
	{
		for (const auto Feature : Features)
			Subject.ObtainTrait(Feature);
	}

	bool AddCooldown(const UScriptStruct* Trait, FSubjectHandle Sub, float Time)
	{
		const FUnsafeSubjectHandle UnSafeSub{Sub};
		return AddCooldown(Trait, UnSafeSub, Time);
	}

	bool AddCooldown(const UScriptStruct* Trait, FUnsafeSubjectHandle Sub, float Time)
	{
		if (Sub.HasTrait<FCooldownComponent>())
		{
			const auto Cooldown = Sub.GetTraitPtr<FCooldownComponent>();
			Cooldown->AddCooldown(Trait->GetFName(), Time);
			return true;
		}
		return false;
	}

	bool RemoveCooldown(const UScriptStruct* Trait, FSubjectHandle Sub)
	{
		const FUnsafeSubjectHandle UnSafeSub{Sub};
		return RemoveCooldown(Trait, UnSafeSub);
	}

	bool RemoveCooldown(const UScriptStruct* Trait, FUnsafeSubjectHandle Sub)
	{
		if (Sub.HasTrait<FCooldownComponent>())
		{
			const auto Cooldown = Sub.GetTraitPtr<FCooldownComponent>();
			Cooldown->Remove(Trait->GetFName());
			return true;
		}
		return false;
	}

	namespace EcsExtensionsPrivate
	{
		TArray<FSubjectHandle> CreateAbilities(AMechanism* Mechanism, const FUIdComponent UidOwner,
		                                       TArray<UScriptStruct*> Abilities, const int32 AbilitiesCount)
		{
			TArray<FSubjectHandle> AbilityEntities;
			for (const auto Ability : Abilities)
			{
				const auto AbilityEntity = CreateAbility(Mechanism, UidOwner, Ability, AbilitiesCount);
				AbilityEntities.Add(AbilityEntity);
			}
			return AbilityEntities;
		}

		FSubjectHandle CreateAbility(AMechanism* Mechanism, const FUIdComponent UidOwner,
		                             UScriptStruct* AbilityType, const int32 AbilityCount)
		{
			const auto Entity = Mechanism->SpawnSubject();
			Entity.SetTrait(FUIdComponent(UIdSubjectManager::Next(Entity)));

			Entity.ObtainTrait(AbilityType);
			Entity.ObtainTrait<FAbilityComponent>();
			Entity.SetTrait(FOwnerUIdComponent(UidOwner.Value));
			Entity.SetTrait(FAbilityCountComponent(AbilityCount));
			Entity.SetTrait(FAbilityCounterComponent(0));

			return Entity;
		}
	}
};
