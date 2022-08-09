#include "Systems/ReactiveSystems/ReactiveSystem.h"

ReactiveSystem::ReactiveSystem()
{
	DeleteTrigger = true;
}

void ReactiveSystem::Initialize(AMechanism* Mechanism)
{
}

void ReactiveSystem::Update(AMechanism* Mechanism, float DeltaTime)
{	
	if(ReactiveFilter == FFilter::Zero) return;
	Mechanism->Enchain<FUnsafeChain>(ReactiveFilter)->Operate([&](const FUnsafeSubjectHandle Sub)
	{		
		if (HasComponents(Sub)) Execute(Mechanism, Sub);		
		if (DeleteTrigger) Sub.RemoveTrait(TriggerType);
	});
}

void ReactiveSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject){}

void ReactiveSystem::SetupTrigger(UScriptStruct* Trigger)
{
	ReactiveFilter.Include(Trigger);
	TriggerType = Trigger;
}

bool ReactiveSystem::HasComponents(FSubjectHandle Subject){	return true; }