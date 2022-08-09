// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SubjectHandle.h"
#include "UObject/Interface.h"
#include "IInteractiveObjectView.generated.h"

UINTERFACE(MinimalAPI)
class UInteractiveObjectView : public UInterface
{
	GENERATED_BODY()
};


class ECSCORE_API IInteractiveObjectView
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnStartInteract(FSubjectHandle Owner);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnEndInteract(FSubjectHandle Owner);
};
