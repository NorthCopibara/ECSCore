// Fill out your copyright notice in the Description page of Project Settings.


#include "Link/LinkableActor.h"


void ILinkableActor::Link(FSubjectHandle Subject)
{
	LinkedSubject = Subject;
}

void ILinkableActor::SetLinkActorLocationRotation(FVector Position, FRotator Rotation)
{
}

void ILinkableActor::EnableLink()
{
}

void ILinkableActor::DisableLink()
{
}

void ILinkableActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
}
