#pragma once

#include "CoreMinimal.h"
#include "SubjectHandle.h"
#include "UObject/Interface.h"
#include "LinkableWidget.generated.h"

UINTERFACE()
class ULinkableWidget : public UInterface
{
	GENERATED_BODY()
};

class ECSCORE_API ILinkableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetLinkedSub(FSubjectHandle LinkedSub);
};
