#include "Systems/Link/OnLinkedAddSystem.h"

#include "Components/LinkComponent.h"

void OnLinkedAddSystem::Initialize(AMechanism* Mechanism)
{
	ReactiveAddSystem::Initialize(Mechanism);
	TriggerOnAdd = FLinkComponent::StaticStruct();
}

void OnLinkedAddSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject)
{
	const auto LinkActor = Subject.GetTrait<FLinkComponent>().Value;
	LinkActor->Link(Subject);
	LinkActor->Execute_OnLinkedSub(LinkActor.GetObject(), Subject);
}