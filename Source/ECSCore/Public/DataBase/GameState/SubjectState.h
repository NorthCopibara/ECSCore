#pragma once

#include "CoreMinimal.h"
#include "Mechanism.h"

#include "SubjectHandle.h"
#include "Components/LinkComponent.h"
#include "Components/Events/FAssetNameComponent.h"
#include "Components/Movement/StaticComponent.h"
#include "Extensions/EcsExtenstions.h"

#include "SubjectState.generated.h"

USTRUCT(BlueprintType)
struct ECSCORE_API FSubjectState
{
	GENERATED_BODY()

	FSubjectState()
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSubjectRecord SubjectRecord;

	void WriteState(const FSubjectHandle Subject)
	{
		SubjectRecord = FSubjectRecord(Subject);
	}

	FSubjectHandle ReadState(AMechanism* Mechanism) const
	{
		auto Subject = Mechanism->SpawnSubject(SubjectRecord);

		if (Subject.HasTrait<FLinkComponent>())
		{
			Subject.RemoveTrait<FLinkComponent>();
			if (Subject.HasTrait<FAssetNameComponent>())
			{
				const auto AssetName = Subject.GetTrait<FAssetNameComponent>().Value;
				EcsExtensions::SetTraitAndFire(Mechanism, Subject, FAssetNameComponent(AssetName));
			}
		}

		//TODO: {REF}
/*
		if (Subject.HasTrait<FAttackInputComponent>()) Subject.RemoveTrait<FAttackInputComponent>();
		if (Subject.HasTrait<FIsEquippingComponent>()) Subject.RemoveTrait<FIsEquippingComponent>();
		if (Subject.HasTrait<FAbilityUserComponent>())
		{
			if (Subject.HasTrait<FEquipAbilityComponent>()) Subject.RemoveTrait<FEquipAbilityComponent>();
			if (Subject.HasTrait<FAttackAbilityComponent>()) Subject.RemoveTrait<FAttackAbilityComponent>();
			if (Subject.HasTrait<FRollAbilityComponent>()) EcsExtensions::CancelAbility<FRollAbilityComponent>(
				Mechanism, Subject);
		}

		if (Subject.HasTrait<FAIPawnComponent>())
			Mechanism->SpawnSubject().SetTrait(FEventAddComponent(FAIPawnComponent::StaticStruct(), Subject));


		if (Subject.HasTrait<FPlayerCameraComponent>())
			Mechanism->SpawnSubject().SetTrait(FEventAddComponent(FPlayerCameraComponent::StaticStruct(), Subject));

		if (Subject.HasTrait<FHasHPBarComponent>())
			Mechanism->SpawnSubject().SetTrait(FEventAddComponent(FHasHPBarComponent::StaticStruct(), Subject));


		if (Subject.HasTrait<FHitResultComponent>())
			Subject.RemoveTrait<FHitResultComponent>();
*/
		if (Subject.HasTrait<FStaticComponent>())
			Subject.RemoveTrait<FStaticComponent>();

		return Subject;
	}
};
