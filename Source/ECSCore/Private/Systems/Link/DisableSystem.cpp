#include "Systems/Link/DisableSystem.h"

#include "Components/LinkComponent.h"
#include "Components/States/IsAvailableComponent.h"


void DisableSystem::Initialize(AMechanism* Mechanism)
{
	ReactiveRemoveSystem::Initialize(Mechanism);
	TriggerOnRemove = FIsAvailableComponent::StaticStruct();
}

bool DisableSystem::HasComponents(FSubjectHandle Subject)
{
	return Subject.HasTrait<FLinkComponent>();
}

void DisableSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject)
{
	ILinkableActor* Link = Cast<ILinkableActor>(Subject.GetTrait<FLinkComponent>().Value.GetObject());
	if (!Link) return;
	Link->DisableLink();
}
