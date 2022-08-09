#include "Systems/Movement/CharacterLookSystem.h"

#include "Components/Movement/BlockRotationComponent.h"
#include "Components/Movement/LookDirectionComponent.h"
#include "Components/Movement/PositionComponent.h"
#include "Components/Movement/RotationComponent.h"
#include "Components/Movement/RotationSpeedComponent.h"
#include "Components/States/IsDeathComponent.h"
#include "Kismet/KismetMathLibrary.h"

void CharacterLookSystem::Update(AMechanism* Mechanism, float DeltaTime)
{
	const auto Filter = FFilter::Make<FLookDirectionComponent, FPositionComponent, FRotationComponent,
	FRotationSpeedComponent>().Exclude<FBlockRotationComponent, FIsDeathComponent>();

	Mechanism->EnchainSolid(Filter)->Operate([&](const FLookDirectionComponent& LookDir,
	                                             FRotationComponent& Rot, const FPositionComponent& Pos,
	                                             const FRotationSpeedComponent& RotSpeed)
	{
		const auto Loc = Pos.Value;
		if (LookDir.Value.SizeSquared() >= 0.01f)
		{
			const auto Direction = FVector(Loc.X + LookDir.Value.X, Loc.Y + LookDir.Value.Y, Loc.Z);
			
			const auto RotTarget = UKismetMathLibrary::FindLookAtRotation(Loc, Direction);
			const auto RotLast = Rot.Value;

			Rot.Value = FMath::RInterpTo(RotLast, RotTarget, DeltaTime, RotSpeed.Value);

			UKismetMathLibrary::RLerp(RotLast, RotTarget, 0.5f, true);
		}
	});
}
