#include "Systems/Cooldown/CooldownSystem.h"

#include "Components/CooldownComponent.h"


void CooldownSystem::Update(AMechanism* Mechanism, float DeltaTime)
{
	const auto Filter = FFilter::Make<FCooldownComponent>();
	Mechanism->Enchain<FUnsafeChain>(Filter)->Operate([&](FCooldownComponent& Cooldown)
	{
		Cooldown.CalculateCooldown(DeltaTime);
	});
}
