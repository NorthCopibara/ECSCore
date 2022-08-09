#pragma once

#include "TeamType.Generated.h"

UENUM(BlueprintType)
enum class ETeamType : uint8
{
	None,
	Player,
	Aggressive,
	World,
	ExplosionWave
};