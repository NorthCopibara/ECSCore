// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MechanicalActor.h"
#include "Mechanism.h"
#include "DataBase/DataBase.h"
#include "MechanicalActors/BaseEcsBootstrap.h"

#include "BaseGameContext.generated.h"

UCLASS()
class ECSCORE_API ABaseGameContext : public AMechanicalActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void Initialize();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UDataBase> DataBase;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ABaseEcsBootstrap> EcsMainBootstrap;

private:
	void InjectDataToECS() const;
};


