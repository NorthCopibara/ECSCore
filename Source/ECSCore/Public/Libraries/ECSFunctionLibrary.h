// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Machine.h"
#include "SubjectHandle.h"
#include "Components/EventAddComponent.h"
#include "Components/EventRemoveComponent.h"
#include "Components/UidComponent.h"
#include "Enums/TeamType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UId/UId.h"
#include "UId/UidSubjectManager.h"

#include "ECSFunctionLibrary.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogFuncLib, All, All)

UCLASS()
class ECSCORE_API UECSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, CustomThunk,
		Meta = (DisplayName = "Set Trait And Fire",
			WorldContext = "WorldContextObject",
			CustomStructureParam = "TraitData",
			KeyWords = "subject add new trait +",
			UnsafeDuringActorConstruction))
	static void
	SetSubjectTraitAndFire(UObject* const WorldContextObject,
	                       UPARAM(DisplayName="Subject") const FSubjectHandle& SubjectHandle,
	                       UPARAM(DisplayName="Type") UScriptStruct* const TraitType,
	                       UPARAM(DisplayName="Trait") const FGenericStruct& TraitData)
	{
		checkNoEntry();
	}

	FORCEINLINE static void
	Generic_SetSubjectTraitAndFire(UObject* const WorldContextObject,
	                               const FSubjectHandle& SubjectHandle,
	                               UScriptStruct* const TraitType,
	                               const void* const TraitData)
	{
		SubjectHandle.SetTrait(TraitType, TraitData);
		auto* const Mechanism = UMachine::ObtainMechanism(WorldContextObject->GetWorld());
		Mechanism->SpawnSubject().SetTrait(FEventAddComponent(TraitType, SubjectHandle));
	}

	DECLARE_FUNCTION(execSetSubjectTraitAndFire)
	{
		P_GET_OBJECT(UObject, WorldContextObject);
		P_GET_STRUCT_REF(FSubjectHandle, SubjectHandle);
		P_GET_OBJECT(UScriptStruct, TraitType);

		Stack.StepCompiledIn<FStructProperty>(nullptr);
		const void* const SrcTraitAddr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		P_NATIVE_BEGIN;
			Generic_SetSubjectTraitAndFire(WorldContextObject, SubjectHandle, TraitType, SrcTraitAddr);
		P_NATIVE_END;
	}

	UFUNCTION(BlueprintCallable, CustomThunk,
		Meta = (DisplayName = "Remove Trait And Fire",
			WorldContext = "WorldContextObject",
			KeyWords = "subject remove new trait +",
			UnsafeDuringActorConstruction))
	static void
	RemoveSubjectTraitAndFire(UObject* const WorldContextObject,
	                          UPARAM(DisplayName="Subject") const FSubjectHandle& SubjectHandle,
	                          UPARAM(DisplayName="Type") UScriptStruct* const TraitType)
	{
		checkNoEntry();
	}

	FORCEINLINE static void
	Generic_RemoveSubjectTraitAndFire(UObject* const WorldContextObject,
	                                  const FSubjectHandle& SubjectHandle,
	                                  UScriptStruct* const TraitType)
	{
		SubjectHandle.RemoveTrait(TraitType);
		auto* const Mechanism = UMachine::ObtainMechanism(WorldContextObject->GetWorld());
		Mechanism->SpawnSubject().SetTrait(FEventRemoveComponent(TraitType, SubjectHandle));
	}

	DECLARE_FUNCTION(execRemoveSubjectTraitAndFire)
	{
		P_GET_OBJECT(UObject, WorldContextObject);
		P_GET_STRUCT_REF(FSubjectHandle, SubjectHandle);
		P_GET_OBJECT(UScriptStruct, TraitType);

		P_FINISH;
		P_NATIVE_BEGIN;
			Generic_RemoveSubjectTraitAndFire(WorldContextObject, SubjectHandle, TraitType);
		P_NATIVE_END;
	}

	UFUNCTION(BlueprintCallable)
	static bool Equals(UScriptStruct* const FirstType, UScriptStruct* const SecondType)
	{
		return FirstType == SecondType;
	}

	UFUNCTION(BlueprintCallable)
	static void DespawnSubject(const FSubjectHandle& SubjectHandle)
	{
		FUId UiD{-999};
		if (SubjectHandle.HasTrait<FUidComponent>())
		{
			UiD = SubjectHandle.GetTrait<FUidComponent>().Value;
		}
		if (const auto Status = SubjectHandle.Despawn(); Status == EApparatusStatus::Success && UiD != -999)
			UidSubjectManager::RemoveSubject(UiD);
	}
};
