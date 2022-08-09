#include "Systems/Movement/CharacterMoveSystem.h"

#include "NavigationSystem.h"
#include "Components/LinkComponent.h"
#include "Components/Flags/PawnComponent.h"
#include "Components/Movement/BlockMovementComponent.h"
#include "Components/Movement/MoveDirectionComponent.h"
#include "Components/Movement/MoveSpeedComponent.h"
#include "Components/Movement/MoveSpeedMultiplierComponent.h"
#include "Components/Movement/PositionComponent.h"
#include "Components/Movement/VelocityComponent.h"
#include "Components/States/IsDeathComponent.h"
#include "ECSCore/Public/Utils.h"
#include "Extensions/CommonExtensions.h"

void CharacterMoveSystem::Update(AMechanism* Mechanism, float DeltaTime)
{
	auto* UWorld = Mechanism->GetWorld();
	const auto CharacterFilter = FFilter::Make<FPawnComponent,
	                                           FPositionComponent,
	                                           FVelocityComponent,
	                                           FMoveSpeedMultiplierComponent,
	                                           FMoveSpeedComponent,
	                                           FMoveDirectionComponent,
	                                           FLinkComponent>().Exclude<FIsDeathComponent>();

	Mechanism->EnchainSolid(CharacterFilter)->Operate([&](FSolidSubjectHandle SubjectHandle,
	                                                      const FMoveSpeedMultiplierComponent& MoveSpeedMultiplier,
	                                                      FPositionComponent& Pos,
	                                                      FVelocityComponent& Vel,
	                                                      const FMoveDirectionComponent& MoveDir,
	                                                      const FMoveSpeedComponent& MoveSpeed,
	                                                      const FLinkComponent& Link)
	{
		const auto Sub = SubjectHandle;
		const FVector Loc = Sub.GetTrait<FPositionComponent>().Value;
		if (MoveDir.Value.SizeSquared() >= 0.01f && !Sub.HasTrait<FBlockMovementComponent>())
		{
			const auto Multiply = MoveDir.Value * MoveSpeed.Value * MoveSpeedMultiplier.Value;
			const auto NewPosition = FVector(Loc.X + Multiply.X, Loc.Y + Multiply.Y, Loc.Z);
			const auto OwnerInstanceID = Link.Value->GetInstanceId();
			const auto NavSystem = UNavigationSystemV1::GetCurrent(UWorld);
			if (!NavSystem) return;

			if (FNavLocation NavLoc; NavSystem->ProjectPointToNavigation(NewPosition, NavLoc))
			{
				FVector OutHitNormal(FVector::ZeroVector);
				FVector OutHit(FVector::ZeroVector);
				bool Stop;
				if (CommonExtensions::OverlapCheckPosition(Mechanism, SubjectHandle,
				                                           CAPSULE_OFFSET(NavLoc),
				                                           CAPSULE_OFFSET(NavLoc), Stop, OutHit,
				                                           OutHitNormal, TraceTypeQuery1, OwnerInstanceID))
					//&& !Cursor.GetSubject().HasTrait<FRollAbilityComponent>()) // TODO: {REF}
				{
					auto Offset = OutHit + OutHitNormal;
					if (NavSystem->ProjectPointToNavigation(Offset, NavLoc)
					)
					{
						if (CommonExtensions::OverlapCheckPosition(Mechanism, SubjectHandle, CAPSULE_OFFSET(Loc),
						                                           CAPSULE_OFFSET(NavLoc),
						                                           Stop, OutHit,
						                                           OutHitNormal, TraceTypeQuery1, OwnerInstanceID))
						{
							Offset = OutHit + OutHitNormal;
							if (NavSystem->ProjectPointToNavigation(Offset, NavLoc) && !Stop)
								Pos.Value = NavLoc;
						}
						else { Pos.Value = NavLoc; }
					}
				}
				else
				{
					Pos.Value = NavLoc;
				}
			}
		}
		
		Vel.Value = FVector::Dist(Loc, Pos.Value);
	});
}
