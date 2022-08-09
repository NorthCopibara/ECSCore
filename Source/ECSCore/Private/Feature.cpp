#include "Feature.h"

auto Feature::Add(TSharedPtr<System> InSystem)->Feature*{
	Systems.Add(InSystem);
	return this;
}

void Feature::Initialize(AMechanism* Mechanism){
	for (const auto& System : Systems)	{
		System->Initialize(Mechanism);
	}
}

void Feature::Update(AMechanism* Mechanism, const float DeltaTime){
	for (const auto& System : Systems)	{
		System->Update(Mechanism, DeltaTime);
	}
}

void Feature::Teardown(AMechanism* Mechanism){
	for (const auto& System : Systems)	{
		System->Teardown(Mechanism);
	}
}

bool Feature::IsSteadyTick()
{
	return false;
}
