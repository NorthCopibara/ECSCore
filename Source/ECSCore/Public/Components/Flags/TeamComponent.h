#pragma once

#include "Enums/TeamType.h"
#include "TeamComponent.generated.h"

USTRUCT(BlueprintType)
struct FTeamComponent
{
	GENERATED_BODY()
	FTeamComponent() {}
	explicit FTeamComponent(const ETeamType Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ETeamType Value{};
};
