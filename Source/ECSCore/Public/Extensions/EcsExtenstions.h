#pragma once
#include "CoreMinimal.h"
#include "CommonExtensions.h"
#include "Mechanism.h"
#include "Components/CooldownComponent.h"
#include "Components/EventAddComponent.h"
#include "Components/EventRemoveComponent.h"
#include "Components/LinkComponent.h"
#include "Components/OwnerUidComponent.h"
#include "Components/UidComponent.h"
#include "Components/Abilities/ActivateAbilityComponent.h"
#include "Components/Abilities/CancelAbilityComponent.h"
#include "Components/Abilities/EndAbilityComponent.h"
#include "Components/BaseComponents/DataBaseComponent.h"
#include "Components/Flags/AbilityComponent.h"
#include "Components/Flags/PlayerComponent.h"
#include "Components/Movement/PositionComponent.h"
#include "Components/Movement/RotationComponent.h"
#include "DataBase/DataBase.h"
#include "ECSCore/Public/Utils.h"
#include "Link/LinkableActor.h"
#include "Link/View/BaseCharacterView.h"
#include "UId/UId.h"
#include "UId/UidSubjectManager.h"

class EcsExtensions
{
public:
	template <typename T>
	static void SetTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, const T& Trait)
	{
		Subject.SetTrait(Trait);
		Mechanism->SpawnSubject().SetTrait(FEventAddComponent(Trait, Subject));
	}

	static void SetTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject,
	                            UScriptStruct* TraitBase, const void* const TraitData)
	{
		Subject.SetTrait(TraitBase, TraitData);
		Mechanism->SpawnSubject().SetTrait(FEventAddComponent(TraitBase, Subject));
	}

	static void ObtainTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, UScriptStruct* Trait)
	{
		Subject.ObtainTrait(Trait);
		Mechanism->SpawnSubject().SetTrait(FEventAddComponent(Trait, Subject));
	}

	template <typename T>
	static void RemoveTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, const T& Trait)
	{
		Subject.RemoveTrait<T>();
		Mechanism->SpawnSubject().SetTrait(FEventRemoveComponent(Trait, Subject));
	}

	static void RemoveTraitAndFire(AMechanism* Mechanism, const FSubjectHandle& Subject, UScriptStruct* Trait)
	{
		Subject.RemoveTrait(Trait);
		Mechanism->SpawnSubject().SetTrait(FEventRemoveComponent(Trait, Subject));
	}

	template <typename T>
	static void SetTraitAndFireDeferred(AMechanism* Mechanism, const FSolidSubjectHandle& Subject, const T& Trait)
	{
		const auto ChangeTrait = Trait;
		Subject.SetTraitDeferred(ChangeTrait);
		const FSubjectHandle EntityNonSolid = static_cast<FSubjectHandle>(Subject);
		Mechanism->SpawnSubjectDeferred<FEventAddComponent>(FEventAddComponent(ChangeTrait, EntityNonSolid));
	}

	static void ObtainTraitAndFireDeferred(AMechanism* Mechanism,
	                                       const FSolidSubjectHandle& Subject,
	                                       UScriptStruct* Trait)
	{
		Subject.ObtainTraitDeferred(Trait);
		const FSubjectHandle EntityNonSolid = static_cast<FSubjectHandle>(Subject);
		Mechanism->SpawnSubjectDeferred<FEventAddComponent>(FEventAddComponent(Trait, EntityNonSolid));
	}

	template <typename T>
	static void RemoveTraitAndFireDeferred(AMechanism* Mechanism, const FSolidSubjectHandle& Subject, const T& Trait)
	{
		const auto ChangeTrait = Trait;
		Subject.SetTraitDeferred(ChangeTrait); //???
		const FSubjectHandle EntityNonSolid = static_cast<FSubjectHandle>(Subject);
		Mechanism->SpawnSubjectDeferred<FEventRemoveComponent>(FEventRemoveComponent(ChangeTrait, EntityNonSolid));
	}

	static void RemoveTraitAndFireDeferred(AMechanism* Mechanism,
	                                       const FSolidSubjectHandle& Subject,
	                                       UScriptStruct* Trait)
	{
		Subject.RemoveTraitDeferred(Trait);
		const FSubjectHandle EntityNonSolid = static_cast<FSubjectHandle>(Subject);
		Mechanism->SpawnSubjectDeferred<FEventRemoveComponent>(FEventRemoveComponent(Trait, EntityNonSolid));
	}

	template <typename T>
	static T* Ctx(AMechanism* Mechanism)
	{
		T* CompPtr = nullptr;
		const auto Filter = FFilter::Make<T>();
		auto Chain = Mechanism->EnchainSolid(Filter);
		Chain->Operate([&](const FSolidChain::FCursor& Cursor)
		{
			CompPtr = Cursor.GetTraitPtr<T>();
			Chain->StopIterating();
		});
		return CompPtr;
	}

	template <typename T, typename ...Ts>
	static T GetSingleton(AMechanism* Mechanism)
	{
		const auto Filter = FFilter::Make<T, Ts...>();
		const auto Chain = Mechanism->Enchain(Filter);

		auto Cursor = Chain->Iterate(0, 1);
		if (!Cursor.Provide())
		{
			checkNoEntry()
			return T();
		}
		const auto Trait = Cursor.template GetTrait<T>();
		verifyf(!Cursor.Provide(), TEXT("Two singleton objects detected!"));
		return Trait;
	}


	template <typename T>
	static FSubjectHandle* GetEntity(AMechanism* Mechanism)
	{
		T* SubPtr = nullptr;
		const auto Filter = FFilter::Make<T>();
		Mechanism->EnchainSolid(Filter)->Operate([&](FSolidSubjectHandle Sub)
		{
			SubPtr = Sub;
		});
		return SubPtr;
	}

	static FSubjectHandle GetEntityFromUId(const FUId Id)
	{
		return UidSubjectManager::GetSubject(Id);
	}

	static FSubjectHandle GetPlayer(AMechanism* Mechanism)
	{
		FSubjectHandle SubPtr;
		const auto Filter = FFilter::Make<FPlayerComponent>();
		Mechanism->Enchain(Filter)->Operate([&](FSubjectHandle Sub)
		{
			SubPtr = Sub;
		});
		return SubPtr;
	}

	static FSolidSubjectHandle GetPlayerSolid(AMechanism* Mechanism)
	{
		FSolidSubjectHandle SubPtr;
		const auto Filter = FFilter::Make<FPlayerComponent>();
		Mechanism->EnchainSolid(Filter)->Operate([&](const FSolidSubjectHandle Sub)
		{
			SubPtr = Sub;
		});
		return SubPtr;
	}
	
	static UDataBase* GetDataBase(AMechanism* Mechanism)
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

	static UDataBase* GetDataBaseSolid(AMechanism* Mechanism)
	{
		const auto DataBaseFilter = FFilter::Make<FDataBaseComponent>();
		const auto Enchain = Mechanism->EnchainSolid(DataBaseFilter);
		UDataBase* DataBase = nullptr;
		Enchain->Operate([&](FDataBaseComponent DataBaseComponent)
		{
			DataBase = DataBaseComponent.Value;
		});

		check(DataBase)
		return DataBase;
	}

	static EActivateAbilityStatus SetAbilityAndFire(AMechanism* Mechanism,
	                                                const FSubjectHandle Subject,
	                                                UScriptStruct* TraitBase,
	                                                int32 ConfigId = 0)
	{
		const auto Configs = GetDataBase(Mechanism)->AbilitySystemApplier.GetDefaultObject()->GetConfigById(ConfigId);

		EActivateAbilityStatus Result = EActivateAbilityStatus::Success;
		if (CheckAndRemoveAbilities(Mechanism, Subject, TraitBase, Configs, Result)) return Result;
		ObtainTraitAndFire(Mechanism, Subject, TraitBase);
		return Result;
	}

	static bool CheckAndRemoveAbilities(AMechanism* Mechanism,
	                                    const FSubjectHandle Subject,
	                                    UScriptStruct* Trait,
	                                    const TMap<UScriptStruct*, FAbilityConfig> Configs,
	                                    EActivateAbilityStatus& Result)
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
			{
				CancelAbility(Mechanism,
				              Subject,
				              TraitToDelete);
			}
		}

		return false;
	}

	template <typename T>
	static void ActivateAbility(AMechanism* Mechanism, FSubjectHandle Subject)
	{
		ApplyAbility<T, FActivateAbilityComponent>(Mechanism, Subject, FActivateAbilityComponent());
	}

	template <typename T>
	static void CancelAbility(AMechanism* Mechanism, FSubjectHandle Subject)
	{
		ApplyAbility<T, FCancelAbilityComponent>(Mechanism, Subject, FCancelAbilityComponent());
	}

	template <typename T>
	static void EndAbility(AMechanism* Mechanism, FSubjectHandle Subject)
	{
		ApplyAbility<T, FEndAbilityComponent>(Mechanism, Subject, FEndAbilityComponent());
	}

	template <typename T>
	static void ActivateAbilityDeferred(AMechanism* Mechanism, FSolidSubjectHandle Subject)
	{
		ApplyAbilityDeferred<T, FActivateAbilityComponent>(Mechanism, Subject, FActivateAbilityComponent());
	}

	template <typename T>
	static void CancelAbilityDeferred(AMechanism* Mechanism, FSolidSubjectHandle Subject)
	{
		ApplyAbilityDeferred<T, FCancelAbilityComponent>(Mechanism, Subject, FCancelAbilityComponent());
	}

	template <typename T>
	static void EndAbilityDeferred(AMechanism* Mechanism, FSolidSubjectHandle Subject)
	{
		ApplyAbilityDeferred<T, FEndAbilityComponent>(Mechanism, Subject, FEndAbilityComponent());
	}

	//??
	static void ActivateAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter)
	{
		ApplyAbility<FActivateAbilityComponent>(Mechanism,
		                                        Subject,
		                                        TraitFilter,
		                                        FActivateAbilityComponent());
	}

	static void CancelAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter)
	{
		ApplyAbility<FCancelAbilityComponent>(Mechanism,
		                                      Subject,
		                                      TraitFilter,
		                                      FCancelAbilityComponent());
	}

	static void EndAbility(AMechanism* Mechanism, FSubjectHandle Subject, UScriptStruct* TraitFilter)
	{
		ApplyAbility<FEndAbilityComponent>(Mechanism,
		                                   Subject,
		                                   TraitFilter,
		                                   FEndAbilityComponent());
	}

	static void ActivateAbilityDeferred(AMechanism* Mechanism,
	                                    FSolidSubjectHandle Subject,
	                                    UScriptStruct* TraitFilter)
	{
		ApplyAbilityDeferred<FActivateAbilityComponent>(Mechanism,
		                                                Subject,
		                                                TraitFilter,
		                                                FActivateAbilityComponent());
	}

	static void CancelAbilityDeferred(AMechanism* Mechanism,
	                                  FSolidSubjectHandle Subject,
	                                  UScriptStruct* TraitFilter)
	{
		ApplyAbilityDeferred<FCancelAbilityComponent>(Mechanism,
		                                              Subject,
		                                              TraitFilter,
		                                              FCancelAbilityComponent());
	}

	static void EndAbilityDeferred(AMechanism* Mechanism, FSolidSubjectHandle Subject, UScriptStruct* TraitFilter)
	{
		ApplyAbilityDeferred<FEndAbilityComponent>(Mechanism,
		                                           Subject,
		                                           TraitFilter,
		                                           FEndAbilityComponent());
	}

	static void ApplyFeatures(TArray<UScriptStruct*> Features, FSubjectHandle Subject)
	{
		for (auto Feature : Features)
		{
			Subject.ObtainTrait(Feature);
		}
	}

	static bool AddCooldown(UScriptStruct* Trait, FSubjectHandle Sub, float Time)
	{
		const FUnsafeSubjectHandle UnSafeSub{Sub};
		return AddCooldown(Trait, UnSafeSub, Time);
	}

	static bool AddCooldown(UScriptStruct* Trait, FUnsafeSubjectHandle Sub, float Time)
	{
		if (Sub.HasTrait<FCooldownComponent>())
		{
			auto Cooldown = Sub.GetTraitPtr<FCooldownComponent>();
			Cooldown->AddCooldown(Trait->GetFName(), Time);
			return true;
		}
		return false;
	}

	static bool RemoveCooldown(UScriptStruct* Trait, FSubjectHandle Sub)
	{
		const FUnsafeSubjectHandle UnSafeSub{Sub};
		return RemoveCooldown(Trait, UnSafeSub);
	}

	static bool RemoveCooldown(UScriptStruct* Trait, FUnsafeSubjectHandle Sub)
	{
		if (Sub.HasTrait<FCooldownComponent>())
		{
			auto Cooldown = Sub.GetTraitPtr<FCooldownComponent>();
			Cooldown->Remove(Trait->GetFName());
			return true;
		}
		return false;
	}

	
	template <typename T>
	static void LinkActorsFromScene(AMechanism* Mechanism, const FReturnSubject ReturnSubject,
									const TFunction<void (ILinkableActor* Actor, FSubjectHandle Subject)> AdditionalOperations = nullptr)
	{
		auto* UWorld = Mechanism->GetWorld();
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(UWorld, T::StaticClass(), Actors);
		for (AActor* TActor : Actors)
		{
			ILinkableActor* LinkActor = Cast<ILinkableActor>(TActor);
			if (LinkActor != nullptr)
			{
				if(!ReturnSubject.IsBound()) return;
				auto SubjectHandle = ReturnSubject.Execute();
				SET_TRAIT_AND_FIRE(Mechanism, SubjectHandle, FLinkComponent(TActor));
				SubjectHandle.SetTrait(FPositionComponent(TActor->GetActorLocation()));
				SubjectHandle.SetTrait(FRotationComponent(TActor->GetActorRotation()));

				if(AdditionalOperations)
				{
					AdditionalOperations(LinkActor, SubjectHandle);
				}
			}
		}
	}

	static void LinkCharactersFromScene(AMechanism* Mechanism, const FReturnSubject ReturnSubject)
	{
		LinkActorsFromScene<ABaseCharacterView>(Mechanism, ReturnSubject, [&](ILinkableActor* Link, const FSubjectHandle SubjectHandle)
			{
				const ABaseCharacterView* Char = Cast<ABaseCharacterView>(Link);
				if (!Char) return;

				//TODO: {REF} init character
				//const auto CharacterType = Char->CharacterData.CharacterType;
				//const auto AssetName = ENUM_VALUE_TO_STRING(ECharacterType, CharacterType);
				//SubjectHandle.SetTrait(FAssetNameComponent(FName(*AssetName)));
				//GameplayExtensions::InitializeCharacter(Mechanism, SubjectHandle, CharacterType);				
			});
	}

	//TODO: {REF} init character
/*
	static FSubjectHandle SpawnCharacterOnScene(AMechanism* Mechanism, ECharacterType CharacterType, const FTransform Transform = FTransform::Identity,
		 const ETeamType TeamType = ETeamType::None)
	{
		const auto AssetName = ENUM_VALUE_TO_STRING(ECharacterType, CharacterType);
		const auto CharacterSubject =  TeamType == ETeamType::None
		? GameExtensions::CreatePawn(Mechanism, Transform, FName(*AssetName))
		: GameExtensions::CreateAIPawn(Mechanism, Transform, FName(*AssetName), TeamType);
		GameplayExtensions::InitializeCharacter(Mechanism, CharacterSubject, CharacterType);
		return CharacterSubject;
	}*/

private:
	template <typename T, typename U>
	static void ApplyAbility(AMechanism* Mechanism, FSubjectHandle Subject, const U& Trait)
	{
		if (!Subject.HasTrait<FUidComponent>()) return;
		const auto OwnerUid = Subject.GetTrait<FUidComponent>();
		FFilter AbilityFilter = FFilter::Make<T, FAbilityComponent, FOwnerUidComponent>();
		const auto AbilityEnchain = Mechanism->Enchain(AbilityFilter);
		AbilityEnchain->Operate([&](const FSubjectHandle AbilitySub, const FOwnerUidComponent OwnerAbility)
		{
			if (OwnerAbility.Value != OwnerUid.Value) return;
			AbilitySub.SetTrait(Trait);
		});
	}

	template <typename T>
	static void ApplyAbility(AMechanism* Mechanism,
	                         FSubjectHandle Subject,
	                         UScriptStruct* TraitFilter,
	                         const T& Trait)
	{
		if (!Subject.HasTrait<FUidComponent>()) return;
		const auto OwnerUid = Subject.GetTrait<FUidComponent>();
		FFilter AbilityFilter = FFilter::Make<FAbilityComponent, FOwnerUidComponent>();
		AbilityFilter.Include(TraitFilter);
		const auto AbilityEnchain = Mechanism->Enchain(AbilityFilter);
		AbilityEnchain->Operate([&](const FSubjectHandle AbilitySub, const FOwnerUidComponent OwnerAbility)
		{
			if (OwnerAbility.Value != OwnerUid.Value) return;
			AbilitySub.SetTrait(Trait);
		});
	}

	template <typename T>
	static void ApplyAbilityDeferred(AMechanism* Mechanism,
	                                 FSolidSubjectHandle Subject,
	                                 UScriptStruct* TraitFilter,
	                                 const T& Trait)
	{
		if (!Subject.HasTrait<FUidComponent>()) return;
		const auto OwnerUid = Subject.GetTrait<FUidComponent>();
		FFilter AbilityFilter = FFilter::Make<FAbilityComponent, FOwnerUidComponent>();

		AbilityFilter.Include(TraitFilter);
		const auto AbilityEnchain = Mechanism->EnchainSolid(AbilityFilter);
		AbilityEnchain->Operate([&](const FSolidSubjectHandle AbilitySub, const FOwnerUidComponent OwnerAbility)
		{
			if (OwnerAbility.Value != OwnerUid.Value) return;
			AbilitySub.SetTraitDeferred(Trait);
		});
	}

	template <typename T, typename U>
	static void ApplyAbilityDeferred(AMechanism* Mechanism, FSolidSubjectHandle Subject, const U& Trait)
	{
		if (!Subject.HasTrait<FUidComponent>()) return;
		const auto OwnerUid = Subject.GetTrait<FUidComponent>();
		FFilter AbilityFilter = FFilter::Make<T, FAbilityComponent, FOwnerUidComponent>();
		const auto AbilityEnchain = Mechanism->EnchainSolid(AbilityFilter);
		AbilityEnchain->Operate([&](const FSolidSubjectHandle AbilitySub, const FOwnerUidComponent OwnerAbility)
		{
			if (OwnerAbility.Value != OwnerUid.Value) return;
			AbilitySub.SetTraitDeferred(Trait);
		});
	}
};
