#include "Systems/AbilityReactiveSystem/EndAbilitySystem.h"

#include "Components/OwnerUIdComponent.h"
#include "Components/UIdComponent.h"
#include "Components/Abilities/AbilityCountComponent.h"
#include "Components/Abilities/AbilityCounterComponent.h"
#include "Components/Abilities/ActivateAbilityComponent.h"
#include "Components/Abilities/CancelAbilityComponent.h"
#include "Components/Abilities/EndAbilityComponent.h"
#include "Components/Flags/AbilityUserComponent.h"

void EndAbilitySystem::Initialize(AMechanism* Mechanism)
{
	SetupTrigger(FEndAbilityComponent::StaticStruct());
	DeleteTrigger = false;
}

bool EndAbilitySystem::HasComponents(FSubjectHandle Subject)
{
	if (!Subject.HasTrait<FAbilityCounterComponent>() || !Subject.HasTrait<FAbilityCountComponent>())
	{
		Subject.RemoveTrait<FActivateAbilityComponent>();
		return false;
	}
	return true;
}

void EndAbilitySystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle AbilitySub)
{
	if (AbilitySub.HasTrait<FActivateAbilityComponent>())
	{
		AbilitySub.RemoveTrait<FActivateAbilityComponent>();
		AbilitySub.SetTrait(FAbilityCounterComponent(0));
	}

	if (AbilitySub.HasTrait<FCancelAbilityComponent>())
	{
		AbilitySub.RemoveTrait<FEndAbilityComponent>();
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
			AbilitySub.RemoveTrait<FEndAbilityComponent>();
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
			AbilitySub.SetTrait(FAbilityCounterComponent(0));
			AbilitySub.RemoveTrait<FEndAbilityComponent>();
			return;
		}

		OwnerSub.RemoveTrait(AbilityType);
		if (OwnerHasComponents(OwnerSub)) EndAbility(Mechanism, OwnerSub);

		Enchain->StopIterating();
	});

	AbilitySub.SetTrait(FAbilityCounterComponent(0));
	AbilitySub.RemoveTrait<FEndAbilityComponent>();
}

void EndAbilitySystem::EndAbility(AMechanism* Mechanism, FUnsafeSubjectHandle OwnerSub)
{
}

bool EndAbilitySystem::OwnerHasComponents(FSubjectHandle OwnerSub)
{
	return true;
}

void EndAbilitySystem::SetupAbility(UScriptStruct* Trigger)
{
	AbilityType = Trigger;
}
