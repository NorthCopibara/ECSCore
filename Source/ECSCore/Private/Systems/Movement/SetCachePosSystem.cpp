#include "Systems/Movement/SetCachePosSystem.h"

#include "Components/Movement/CachePositionComponent.h"
#include "Components/Movement/CacheRotationComponent.h"
#include "Components/Movement/PositionComponent.h"
#include "Components/Movement/RotationComponent.h"


void SetCachePosSystem::Update(AMechanism* Mechanism, float DeltaTime) //TODO: Make concurrency 
{
	const auto Filter = FFilter::Make<FPositionComponent,
	                                  FCachePositionComponent,
	                                  FRotationComponent,
	                                  FCacheRotationComponent>();
	Mechanism->EnchainSolid(Filter)->Operate([&](const FPositionComponent& Pos,
	                                             FCachePositionComponent& CachePos,
	                                             const FRotationComponent& Rot,
	                                             FCacheRotationComponent& CacheRot)
	{
		CachePos.Value = Pos.Value;
		CacheRot.Value = Rot.Value;
	});
}
