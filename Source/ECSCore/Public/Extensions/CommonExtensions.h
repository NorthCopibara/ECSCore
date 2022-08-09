#pragma once
#include "Mechanism.h"
#include "Kismet/KismetSystemLibrary.h"

DECLARE_DELEGATE_RetVal(FSubjectHandle, FReturnSubject);

class CommonExtensions
{
public:
	static bool CommonSectionCircle(double x1, double y1,
	                                double x2, double y2,
	                                double xC, double yC, double R)
	{
		x1 -= xC;
		y1 -= yC;
		x2 -= xC;
		y2 -= yC;

		double dx = x2 - x1;
		double dy = y2 - y1;

		double a = dx * dx + dy * dy;
		double b = 2. * (x1 * dx + y1 * dy);
		double c = x1 * x1 + y1 * y1 - R * R;

		if (-b < 0)
			return (c < 0);
		if (-b < (2. * a))
			return ((4. * a * c - b * b) < 0);

		return (a + b + c < 0);
	}

	static FVector CapsuleOffset(const FVector RefFloorValue, const float Offset)
	{
		return FVector(RefFloorValue.X, RefFloorValue.Y, RefFloorValue.Z + Offset);
	}

	static bool OverlapCheckPosition(AMechanism* Mechanism, const FSolidSubjectHandle Subject, const FVector StartPos,
	                                 const FVector EndPos, bool& bStop, FVector& Hit, FVector& HitNormal,
	                                 ETraceTypeQuery TraceTypeQuery, uint32 OwnerInstanceID = 0)
	{
		constexpr float Radius = 44.0f;
		constexpr float Height = 90.0f;
		const TArray<AActor*> IgnoreActors;
		TArray<FHitResult> HitResults;
		auto bHasCollision = false;
		int32 Num = 0;
		UKismetSystemLibrary::CapsuleTraceMulti(Mechanism->GetWorld(),
		                                        StartPos,
		                                        EndPos,
		                                        Radius,
		                                        Height,
		                                        TraceTypeQuery,
		                                        false,
		                                        IgnoreActors,
		                                        EDrawDebugTrace::None,
		                                        HitResults,
		                                        true);

		for (const FHitResult HitResult : HitResults)
		{
			if (HitResult.GetActor()->GetUniqueID() != OwnerInstanceID)
			{
				Num++;
				HitNormal += HitResult.Normal;
				Hit = HitResult.Location;
				bHasCollision = true;
			}
		}
		bStop = Num >= 2;
		return bHasCollision;
	}

	static float Remap(float Value, float from1, float to1, float from2, float to2)
	{
		return (Value - from1) / (to1 - from1) * (to2 - from2) + from2;
	}

	static float Remap01(float Value, float max)
	{
		return Remap(Value, 0, max, 0, 1);
	}

	static float Remap01(int32 Value, float max)
	{
		const auto toFloat = static_cast<float>(Value);
		return Remap(toFloat, 0, max, 0, 1);
	}
};
