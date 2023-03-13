#pragma once
#include "LinkableObject.h"
#include "LinkableActor.generated.h"

UCLASS()
class ECSCORE_API ALinkableActor : public AActor, public ILinkableObject
{
	GENERATED_BODY()
public:
	virtual void SetLinkActorLocationRotation(const FVector Position, const FRotator Rotation)
	{
		SetActorLocationAndRotation(Position, Rotation);
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText AssetName;
};