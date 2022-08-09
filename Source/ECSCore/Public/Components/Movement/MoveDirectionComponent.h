#pragma once

#include "MoveDirectionComponent.generated.h"

USTRUCT(BlueprintType)
struct FMoveDirectionComponent
{
	GENERATED_BODY()
	FMoveDirectionComponent() : Value(FVector::ZeroVector){}
	explicit FMoveDirectionComponent(const FVector Value) : Value(Value){}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Value;	
};
