// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubjectHandle.h"
#include "LinkableActor.generated.h"

UINTERFACE(MinimalAPI)
class ULinkableActor : public UInterface
{
	GENERATED_BODY()
};

class ECSCORE_API ILinkableActor
{
	GENERATED_BODY()
public:
	virtual void Link(FSubjectHandle Subject);
	virtual void SetLinkActorLocationRotation(FVector Position, FRotator Rotation);
	virtual uint32 GetInstanceId() = 0;

	virtual void EnableLink();
	virtual void DisableLink();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnDeath();

	UFUNCTION(BlueprintNativeEvent)
	void OnLinkedSub(FSubjectHandle LinkedSub);

	FSubjectHandle GetLinkSubject() const { return LinkedSubject; }
	
protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

protected:
	FSubjectHandle LinkedSubject{};
};