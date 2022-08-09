#pragma once
#include "System.h"

class ECSCORE_API CharacterMoveSystem final : public System
{
public:
	virtual void Update(AMechanism* Mechanism, float DeltaTime) override;
};
