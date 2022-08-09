// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubjectHandle.h"
#include "UObject/Interface.h"
#include "ILinkableWidget.generated.h"

UINTERFACE()
class UILinkableWidget : public UInterface
{
	GENERATED_BODY()
};

class ECSCORE_API IILinkableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetLinkedSub(FSubjectHandle LinkedSub);
};
