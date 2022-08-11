#include "Systems/Link/LinkSystem.h"

#include "Components/Events/FAssetNameComponent.h"
#include "Extensions/EcsExtenstions.h"
#include "Link/ISavableActor.h"


DEFINE_LOG_CATEGORY_STATIC(LogLinkSystem, All, All);

void LinkSystem::Initialize(AMechanism* Mechanism)
{
	ReactiveAddSystem::Initialize(Mechanism);
	TriggerOnAdd = FAssetNameComponent::StaticStruct();
	DeleteTrigger = true;
}

void LinkSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject)
{
	const auto DataBaseFilter = FFilter::Make<FDataBaseComponent>();
	Mechanism->Enchain(DataBaseFilter)->Operate([&](FDataBaseComponent DataBase)
	{
		const auto AssetBase = DataBase.Value->AssetBase.GetDefaultObject();
		const auto AssetName = Subject.GetTrait<FAssetNameComponent>().Value;
		if (AssetName.IsNone())
		{
			UE_LOG(LogLinkSystem, Error, TEXT("Asset name is uncorrected : %s"), *AssetName.ToString())
			return;
		}

		const auto Position = Subject.HasTrait<FPositionComponent>()
			                      ? Subject.GetTrait<FPositionComponent>().Value
			                      : FVector{};

		const auto Rotation = Subject.HasTrait<FRotationComponent>()
			                      ? Subject.GetTrait<FRotationComponent>().Value
			                      : FRotator{};

		if(!AssetBase->Prefabs.Contains(AssetName))
		{
			UE_LOG(LogLinkSystem, Error, TEXT("Asset not found: %s"), *AssetName.ToString())
			return;
		}

		auto* Actor = Mechanism->GetWorld()->SpawnActor<AActor>(AssetBase->Prefabs[AssetName],
		                                                        Position,
		                                                        Rotation);			

		if (auto* SavableActor = Cast<ISavableActor>(Actor))
		{
			SavableActor->LoadFromSub(Subject);
		}
		EcsExtensions::SetTraitAndFire(Mechanism, Subject, FLinkComponent(Actor));
	});
}
