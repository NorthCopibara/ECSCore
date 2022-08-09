#pragma once
#include "Enums/EMovementType.h"

#include "MovementTypeComponent.generated.h"

USTRUCT(BlueprintType)
struct FMovementTypeComponent
{
	GENERATED_BODY()

	FMovementTypeComponent() : Value(EMovementType::None){}
	explicit FMovementTypeComponent(const EMovementType ToSet) : Value(ToSet){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMovementType Value;
};
