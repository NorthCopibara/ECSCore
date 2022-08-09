#include "Systems/Link/EnableSystem.h"

#include "Components/LinkComponent.h"
#include "Components/States/IsAvailableComponent.h"

void EnableSystem::Initialize(AMechanism* Mechanism)
{
	ReactiveAddSystem::Initialize(Mechanism);
	TriggerOnAdd = FIsAvailableComponent::StaticStruct();
}

bool EnableSystem::HasComponents(FSubjectHandle Subject)
{
	return Subject.HasTrait<FLinkComponent>();
}

void EnableSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject)
{
	ILinkableActor* Link = Cast<ILinkableActor>(Subject.GetTrait<FLinkComponent>().Value.GetObject());
	if (!Link) return;
	Link->EnableLink();
}
