﻿#include "Systems/ReactiveSystems/ReactiveRemoveSystem.h"

void ReactiveRemoveSystem::Initialize(AMechanism* Mechanism)
{
	ReactiveFilter.Include<FEventRemoveComponent>();
}

auto ReactiveRemoveSystem::Update(AMechanism* Mechanism, float DeltaTime) -> void
{
	if(!TriggerOnRemove) return;
	Mechanism->Enchain(ReactiveFilter)->Operate([&](const FChain::FCursor& Cursor, FEventRemoveComponent Removed)
	{
		const auto Sub = Cursor.GetSubject();		
		if (Removed.Value != TriggerOnRemove) return;
		if(HasComponents(Removed.Subject))
			Execute(Mechanism, FUnsafeSubjectHandle(Removed.Subject));		
		if (DeleteTrigger)
			Sub.Despawn();
	});
}

void ReactiveRemoveSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject){}
bool ReactiveRemoveSystem::HasComponents(FSubjectHandle Subject){return true;}