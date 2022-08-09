#pragma once

#include "CharacterType.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	None,
	Player,
	Enemy
};