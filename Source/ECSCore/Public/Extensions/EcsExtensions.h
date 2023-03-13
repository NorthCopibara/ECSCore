#pragma once
#include "Mechanism.h"
#include "Components/CooldownComponent.h"
#include "Components/EventAddComponent.h"
#include "Components/EventRemoveComponent.h"
#include "Components/LinkComponent.h"
#include "Components/OwnerUIdComponent.h"
#include "Components/UIdComponent.h"
#include "Components/Abilities/ActivateAbilityComponent.h"
#include "Components/Abilities/CancelAbilityComponent.h"
#include "Components/Abilities/EndAbilityComponent.h"
#include "Components/BaseComponents/DataBaseComponent.h"
#include "Components/Flags/AbilityComponent.h"
#include "Components/Movement/PositionComponent.h"
#include "Components/Movement/RotationComponent.h"
#include "DataBase/DataBase.h"
#include "DataBase/Configs/AbilitiesConfigs.h"
#include "Link/LinkableActor.h"
#include "UId/UId.h"

DECLARE_DELEGATE_RetVal(FSubjectHandle, FReturnSubject);

namespace EcsExtensions
{
	DECLARE_LOG_CATEGORY_CLASS(EcsExtensionsLog, All, All)
	
	namespace EcsExtensionsPrivate
	{
		template <typename T, typename U>
		void ApplyAbility(AMechanism* Mechanism, FSubjectHandle Subject, const U& Trait);

		template <typename T>
		void ApplyAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter, const T& Trait);

		TArray<FSubjectHandle> CreateAbilities(AMechanism* Mechanism, const FUIdComponent UidOwner,
		                                       TArray<UScriptStruct*> Abilities, const int32 AbilitiesCount);

		FSubjectHandle CreateAbility(AMechanism* Mechanism, const FUIdComponent UidOwner,
		                             UScriptStruct* AbilityType, const int32 AbilityCount);
	}

	template <typename T>
	void SetTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, const T& Trait)
	{
		Subject.SetTrait(Trait);
		Mechanism->SpawnSubject().SetTrait(FEventAddComponent(Trait, Subject));
	}

	template <typename T>
	void SetTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject)
	{
		T Trait;
		Subject.SetTrait(Trait);
		Mechanism->SpawnSubject().SetTrait(FEventAddComponent(Trait, Subject));
	}

	void SetTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject,
	                     UScriptStruct* TraitBase, const void* const TraitData);

	void ObtainTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, UScriptStruct* Trait);

	template <typename T>
	void RemoveTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, const T& Trait)
	{
		Subject.RemoveTrait<T>();
		Mechanism->SpawnSubject().SetTrait(FEventRemoveComponent(Trait, Subject));
	}

	template <typename T>
	void RemoveTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject)
	{
		T Trait;
		Subject.RemoveTrait<T>();
		Mechanism->SpawnSubject().SetTrait(FEventRemoveComponent(Trait, Subject));
	}

	void RemoveTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, UScriptStruct* Trait);

	inline UDataBase* GetDataBase(AMechanism* Mechanism)
	{
		if (!Mechanism) return nullptr;
		const auto DataBaseFilter = FFilter::Make<FDataBaseComponent>();
		const auto Enchain = Mechanism->Enchain(DataBaseFilter);
		UDataBase* DataBase = nullptr;
		Enchain->Operate([&](const FDataBaseComponent DataBaseComponent)
		{
			DataBase = DataBaseComponent.Value;
		});

		check(DataBase)
		return DataBase;
	}

	template <typename T>
	T* GetDataBaseByType(AMechanism* Mechanism)
	{
		const auto DB = GetDataBase(Mechanism);
		if (!DB) return nullptr;

		const auto TargetDB = DB->GetBase<T>();
		return TargetDB;
	}

	EActivateAbilityStatus SetAbilityAndFire(AMechanism* Mechanism, const FSubjectHandle Subject,
	                                         UScriptStruct* TraitBase, int32 ConfigId = 0);

	bool CheckAndRemoveAbilities(AMechanism* Mechanism, const FSubjectHandle Subject, UScriptStruct* Trait,
	                             const TMap<UScriptStruct*, FAbilityConfig> Configs, EActivateAbilityStatus& Result);

	template <typename T>
	void ActivateAbility(AMechanism* Mechanism, FSubjectHandle Subject)
	{
		EcsExtensionsPrivate::ApplyAbility<T, FActivateAbilityComponent>(
			Mechanism, Subject, FActivateAbilityComponent());
	}

	template <typename T>
	void CancelAbility(AMechanism* Mechanism, FSubjectHandle Subject)
	{
		EcsExtensionsPrivate::ApplyAbility<T, FCancelAbilityComponent>(Mechanism, Subject, FCancelAbilityComponent());
	}

	template <typename T>
	void EndAbility(AMechanism* Mechanism, FSubjectHandle Subject)
	{
		EcsExtensionsPrivate::ApplyAbility<T, FEndAbilityComponent>(Mechanism, Subject, FEndAbilityComponent());
	}

	inline void ActivateAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter)
	{
		EcsExtensionsPrivate::ApplyAbility<FActivateAbilityComponent>(Mechanism, Subject,
		                                                              TraitFilter, FActivateAbilityComponent());
	}

	void CancelAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter);
	void EndAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter);
	void ApplyFeatures(TArray<UScriptStruct*> Features, FSubjectHandle Subject);
	bool AddCooldown(const UScriptStruct* Trait, FSubjectHandle Sub, float Time);
	bool AddCooldown(const UScriptStruct* Trait, FUnsafeSubjectHandle Sub, float Time);
	bool RemoveCooldown(const UScriptStruct* Trait, FSubjectHandle Sub);
	bool RemoveCooldown(const UScriptStruct* Trait, FUnsafeSubjectHandle Sub);
	
	template <typename T>
	void LinkActorsFromScene(AMechanism* Mechanism, const FReturnSubject ReturnSubject,
	                         const TFunction<void (ALinkableActor* Actor, FSubjectHandle Subject)> AdditionalOperations = nullptr)
	{
		const auto World = Mechanism->GetWorld();
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, T::StaticClass(), Actors);
		for (const auto& TActor : Actors)
		{
			if (const auto LinkActor = Cast<ALinkableActor>(TActor))
			{
				if (!ReturnSubject.IsBound()) return;
				auto SubjectHandle = ReturnSubject.Execute();
				LinkActor->SetLinkedSubjectUId(SubjectHandle.GetTrait<FUIdComponent>().Value);
				SetTraitAndFire(Mechanism, SubjectHandle, FLinkComponent(TActor));
				SubjectHandle.SetTrait(FPositionComponent(TActor->GetActorLocation()));
				SubjectHandle.SetTrait(FRotationComponent(TActor->GetActorRotation()));

				if (AdditionalOperations)
					AdditionalOperations(LinkActor, SubjectHandle);
			}
		}
	}

	namespace EcsExtensionsPrivate
	{
		template <typename T, typename U>
		void ApplyAbility(AMechanism* Mechanism, FSubjectHandle Subject, const U& Trait)
		{
			if (!Subject.HasTrait<FUIdComponent>()) return;
			const auto OwnerUid = Subject.GetTrait<FUIdComponent>();
			FFilter AbilityFilter = FFilter::Make<T, FAbilityComponent, FOwnerUIdComponent>();
			const auto AbilityEnchain = Mechanism->Enchain(AbilityFilter);
			AbilityEnchain->Operate([&](const FSubjectHandle AbilitySub, const FOwnerUIdComponent OwnerAbility)
			{
				if (OwnerAbility.Value != OwnerUid.Value) return;
				AbilitySub.SetTrait(Trait);
			});
		}

		template <typename T>
		void ApplyAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter, const T& Trait)
		{
			if (!Subject.HasTrait<FUIdComponent>()) return;
			const auto OwnerUid = Subject.GetTrait<FUIdComponent>();
			FFilter AbilityFilter = FFilter::Make<FAbilityComponent, FOwnerUIdComponent>();
			AbilityFilter.Include(TraitFilter);
			const auto AbilityEnchain = Mechanism->Enchain(AbilityFilter);
			AbilityEnchain->Operate([&](const FSubjectHandle AbilitySub, const FOwnerUIdComponent OwnerAbility)
			{
				if (OwnerAbility.Value != OwnerUid.Value) return;
				AbilitySub.SetTrait(Trait);
			});
		}

		TArray<FSubjectHandle> CreateAbilities(AMechanism* Mechanism, const FUIdComponent UidOwner,
		                                       TArray<UScriptStruct*> Abilities, const int32 AbilitiesCount);

		FSubjectHandle CreateAbility(AMechanism* Mechanism, const FUIdComponent UidOwner,
		                             UScriptStruct* AbilityType, const int32 AbilityCount);
	}
};
