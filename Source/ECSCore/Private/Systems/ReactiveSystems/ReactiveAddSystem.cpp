#include "Systems/ReactiveSystems/ReactiveAddSystem.h"
#include "Components/EventAddComponent.h"

ReactiveAddSystem::ReactiveAddSystem()
{
	DeleteTrigger = true;
}

void ReactiveAddSystem::Initialize(AMechanism* Mechanism)
{
	ReactiveFilter.Include<FEventAddComponent>();
}

auto ReactiveAddSystem::Update(AMechanism* Mechanism, float DeltaTime) -> void
{
	if(!TriggerOnAdd) return;
	Mechanism->Enchain(ReactiveFilter)->Operate([&](FSubjectHandle Subject, FEventAddComponent Added)
	{
		const auto Sub = Subject;
		if(Added.Value != TriggerOnAdd) return;
		if (HasComponents(Added.Subject))
			Execute(Mechanism, FUnsafeSubjectHandle(Added.Subject));
		if (DeleteTrigger)
			Sub.Despawn();
	});
}

void ReactiveAddSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject){}
bool ReactiveAddSystem::HasComponents(FSubjectHandle Subject){return true;}