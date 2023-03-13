#pragma once

#include "SubjectHandle.h"
#include "Components/UIdComponent.h"
#include "UId/UId.h"
#include "LinkableObject.generated.h"

UINTERFACE(MinimalAPI)
class ULinkableObject : public UInterface { GENERATED_BODY() };

class ECSCORE_API ILinkableObject
{
	GENERATED_BODY()
public:
	virtual void Link(const FSubjectHandle Subject)
	{
		LinkedSubject = Subject;
	}
	
	FSubjectHandle GetLinkedSubject() const { return LinkedSubject; }
	FUId GetLinkedSubjectUId() const { return LinkedSubjectUId; }
	void SetLinkedSubjectUId(const FUId& UId) { LinkedSubjectUId = UId; }
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDead();

	UFUNCTION(BlueprintNativeEvent)
	void OnLinked(FSubjectHandle LinkedSub);

protected:
	FSubjectHandle LinkedSubject{};
	FUId LinkedSubjectUId;
};