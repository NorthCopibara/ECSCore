#pragma once

#include "TeamType.Generated.h"

UENUM(BlueprintType)
enum class ETeamType : uint8
{
	None,
	Friend,
	Aggressive,
	Neutral,
	World
};