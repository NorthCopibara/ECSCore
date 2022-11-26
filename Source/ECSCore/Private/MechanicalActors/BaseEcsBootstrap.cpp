#include "MechanicalActors/BaseEcsBootstrap.h"

#include "UId/UidSubjectManager.h"

void ABaseEcsBootstrap::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Feature : Features)
	{
		Feature->Initialize(GetMechanism());
	}
}

void ABaseEcsBootstrap::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (const auto& Feature : Features)
	{
		if(!Feature->IsSteadyTick())
		{
			Feature->Update(GetMechanism(), DeltaSeconds);
		}
	}
}

void ABaseEcsBootstrap::SteadyTick(float DeltaTime)
{
	Super::SteadyTick(DeltaTime);

	for (const auto& Feature : Features)
	{
		if(Feature->IsSteadyTick())
		{
			Feature->Update(GetMechanism(), DeltaTime);
		}
	}
}

void ABaseEcsBootstrap::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (const auto& Feature : Features)
	{
		Feature->Teardown(GetMechanism());
	}
	UidSubjectManager::Dispose();
}

auto ABaseEcsBootstrap::Add(TSharedPtr<Feature> InFeature) -> ABaseEcsBootstrap*
{
	Features.Add(InFeature);
	return this;
}
