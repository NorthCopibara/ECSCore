#include "Systems/AbilityReactiveSystem/ActivateAbilitySystem.h"

#include "Components/OwnerUidComponent.h"
#include "Components/UidComponent.h"
#include "Components/Abilities/AbilityCountComponent.h"
#include "Components/Abilities/AbilityCounterComponent.h"
#include "Components/Abilities/ActivateAbilityComponent.h"
#include "Components/Abilities/CancelAbilityComponent.h"
#include "Components/Abilities/EndAbilityComponent.h"
#include "Components/Flags/AbilityUserComponent.h"
#include "Extensions/EcsExtenstions.h"

DEFINE_LOG_CATEGORY_STATIC(LogAbilitySystem, All, All);

void ActivateAbilitySystem::Initialize(AMechanism* Mechanism)
{
	SetupTrigger(FActivateAbilityComponent::StaticStruct());
	DeleteTrigger = false;
}

bool ActivateAbilitySystem::HasComponents(FSubjectHandle Subject)
{
	if (!Subject.HasTrait<FAbilityCounterComponent>() || !Subject.HasTrait<FAbilityCountComponent>())
	{
		Subject.RemoveTrait<FActivateAbilityComponent>();
		return false;
	}
	return true;
}

void ActivateAbilitySystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle AbilitySub)
{
	if (AbilitySub.HasTrait<FCancelAbilityComponent>())
	{
		AbilitySub.RemoveTrait<FActivateAbilityComponent>();
		AbilitySub.SetTrait(FAbilityCounterComponent(0));
		return;
	}

	if (AbilitySub.HasTrait<FEndAbilityComponent>())
	{
		AbilitySub.RemoveTrait<FActivateAbilityComponent>();
		AbilitySub.SetTrait(FAbilityCounterComponent(0));
		return;
	}

	if (!AbilityType || !AbilitySub.HasTrait(AbilityType))
	{
		auto Counter = AbilitySub.GetTrait<FAbilityCounterComponent>().Value;
		const auto Count = AbilitySub.GetTrait<FAbilityCountComponent>().Value;

		if (Counter >= Count)
		{
			//If owner has not ability or can't used ability
			AbilitySub.SetTrait(FAbilityCounterComponent(0));
			AbilitySub.RemoveTrait<FActivateAbilityComponent>();
			return;
		}
		Counter++;
		AbilitySub.SetTrait(FAbilityCounterComponent(Counter));
		return;
	}

	if (!AbilitySub.HasTrait<FOwnerUidComponent>()) return;
	const auto AbilityOwnerUid = AbilitySub.GetTrait<FOwnerUidComponent>();

	const auto OwnerFilter = FFilter::Make<FAbilityUserComponent, FUidComponent>();
	const auto Enchain = Mechanism->Enchain<FUnsafeChain>(OwnerFilter);
	Enchain->Operate([&](const FUnsafeSubjectHandle OwnerSub, const FUidComponent OwnerUid)
	{
		if (OwnerUid.Value != AbilityOwnerUid.Value) return;
		if (OwnerHasComponents(OwnerSub) && CanActivate(Mechanism, OwnerSub))
		{
			const auto Result = EcsExtensions::SetAbilityAndFire(Mechanism,
			                                                     OwnerSub,
			                                                     AbilityType,
			                                                     0); //TODO: get current config index
			if (Result == EActivateAbilityStatus::Success)
			{
				UE_LOG(LogAbilitySystem, Display, TEXT("Acticate ability: %s"), *AbilityType->GetName())
				ActivateAbility(Mechanism, OwnerSub);
			}
		}
		Enchain->StopIterating();
	});

	AbilitySub.SetTrait(FAbilityCounterComponent(0));
	AbilitySub.RemoveTrait<FActivateAbilityComponent>();
}

bool ActivateAbilitySystem::OwnerHasComponents(FSubjectHandle OwnerSub)
{
	return true;
}

bool ActivateAbilitySystem::CanActivate(AMechanism* Mechanism, FSubjectHandle OwnerSub)
{
	return true;
}

void ActivateAbilitySystem::ActivateAbility(AMechanism* Mechanism, FUnsafeSubjectHandle OwnerSub)
{
}

void ActivateAbilitySystem::SetupAbility(UScriptStruct* Trigger)
{
	AbilityType = Trigger;
}
