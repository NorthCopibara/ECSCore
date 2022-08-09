#pragma once

#include "LineTraceComponent.generated.h"

USTRUCT(BlueprintType)
struct FLineTraceComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector StartPosition{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector EndPosition{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Direction{};

	FLineTraceComponent()
	{}

	explicit FLineTraceComponent(const FVector StartPos, const FVector EndPos, const FVector Dir) :
		StartPosition(StartPos), EndPosition(EndPos), Direction(Dir)
	{}
};
