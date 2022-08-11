#pragma once

#include "CoreMinimal.h"
#include "SubjectState.h"
#include "GameFramework/SaveGame.h"
#include "SaveState.generated.h"

UCLASS()
class ECSCORE_API USaveState : public USaveGame
{
	GENERATED_BODY()
public:
	USaveState() {}
	explicit USaveState(const TArray<FSubjectState> State)
	{
		GameState = State;
	}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
    TArray<FSubjectState> GameState;
};