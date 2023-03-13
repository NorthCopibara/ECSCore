#include "Systems/AbilityReactiveSystem/CancelAbilitySystem.h"

#include "Components/OwnerUIdComponent.h"
#include "Components/UIdComponent.h"
#include "Components/Abilities/AbilityCountComponent.h"
#include "Components/Abilities/AbilityCounterComponent.h"
#include "Components/Abilities/ActivateAbilityComponent.h"
#include "Components/Abilities/CancelAbilityComponent.h"
#include "Components/Abilities/EndAbilityComponent.h"
#include "Components/Flags/AbilityUserComponent.h"
#include "Extensions/EcsExtensions.h"

void CancelAbilitySystem::Initialize(AMechanism* Mechanism)
{
	SetupTrigger(FCancelAbilityComponent::StaticStruct());
	DeleteTrigger = false;
}

bool CancelAbilitySystem::HasComponents(FSubjectHandle Subject)
{
	if (!Subject.HasTrait<FAbilityCounterComponent>() || !Subject.HasTrait<FAbilityCountComponent>())
	{
		Subject.RemoveTrait<FActivateAbilityComponent>();
		return false;
	}
	return true;
}

void CancelAbilitySystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle AbilitySub)
{
	if (AbilitySub.HasTrait<FActivateAbilityComponent>())
	{
		AbilitySub.RemoveTrait<FActivateAbilityComponent>();
		AbilitySub.SetTrait(FAbilityCounterComponent(0));
	}

	if (AbilitySub.HasTrait<FEndAbilityComponent>())
	{
		AbilitySub.RemoveTrait<FEndAbilityComponent>();
		AbilitySub.SetTrait(FAbilityCounterComponent(0));
	}

	if (!AbilityType || !AbilitySub.HasTrait(AbilityType))
	{
		auto Counter = AbilitySub.GetTrait<FAbilityCounterComponent>().Value;
		const auto Count = AbilitySub.GetTrait<FAbilityCountComponent>().Value;

		if (Counter >= Count)
		{
			//If owner has not ability or can't used ability
			AbilitySub.SetTrait(FAbilityCounterComponent(0));
			AbilitySub.RemoveTrait<FCancelAbilityComponent>();
			return;
		}
		Counter++;
		AbilitySub.SetTrait(FAbilityCounterComponent(Counter));
		return;
	}

	if (!AbilitySub.HasTrait<FOwnerUIdComponent>()) return;
	const auto AbilityOwnerUid = AbilitySub.GetTrait<FOwnerUIdComponent>();

	const auto OwnerFilter = FFilter::Make<FAbilityUserComponent, FUIdComponent>();
	const auto Enchain = Mechanism->Enchain<FUnsafeChain>(OwnerFilter);
	Enchain->Operate([&](const FUnsafeSubjectHandle OwnerSub, const FUIdComponent OwnerUid)
	{
		if (OwnerUid.Value != AbilityOwnerUid.Value) return;

		//If ability has not active type
		if (!OwnerSub.HasTrait(AbilityType))
		{
			AbilitySub.RemoveTrait<FCancelAbilityComponent>();
			//UE_LOG(LogAbilitySystem, Display, TEXT("Cancel ability: %s"), *AbilityType->GetName())
			AbilitySub.SetTrait(FAbilityCounterComponent(0));
			return;
		}

		if (OwnerHasComponents(OwnerSub)) CancelAbility(Mechanism, OwnerSub);

		Enchain->StopIterating();
	});

	AbilitySub.SetTrait(FAbilityCounterComponent(0));
	AbilitySub.RemoveTrait<FCancelAbilityComponent>();
}

void CancelAbilitySystem::CancelAbility(AMechanism* Mechanism, FUnsafeSubjectHandle OwnerSub)
{
	EcsExtensions::EndAbility(Mechanism, OwnerSub, AbilityType);
}

bool CancelAbilitySystem::OwnerHasComponents(FSubjectHandle OwnerSub)
{
	return true;
}

void CancelAbilitySystem::SetupAbility(UScriptStruct* Trigger)
{
	AbilityType = Trigger;
}
