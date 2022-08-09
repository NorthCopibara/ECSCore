#pragma once

#include "Feature.h"
#include "MechanicalActor.h"
#include "BaseEcsBootstrap.generated.h"

UCLASS()
class ECSCORE_API ABaseEcsBootstrap : public AMechanicalActor
{
	GENERATED_BODY()
public:
	ABaseEcsBootstrap() {}
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SteadyTick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	TArray<TSharedPtr<Feature>> Features;
	
	auto Add(TSharedPtr<Feature> InSystem) -> ABaseEcsBootstrap*;

	template <typename T>
	auto Add() -> Feature*
	{
		return Add(MakeShared<T>());
	}
};