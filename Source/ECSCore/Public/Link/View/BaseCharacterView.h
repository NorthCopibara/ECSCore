// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/CharacterType.h"
#include "GameFramework/Actor.h"
#include "BaseCharacterView.generated.h"

USTRUCT(BlueprintType)
struct FCharacterViewData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	ECharacterType CharacterType;
};

UCLASS()
class ECSCORE_API ABaseCharacterView : public AActor
{
	GENERATED_BODY()
public:
	FCharacterViewData GetCharacterViewData() const { return CharacterData; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	FCharacterViewData CharacterData;
};
