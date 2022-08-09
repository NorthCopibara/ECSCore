#pragma once
#include "System.h"

class ECSCORE_API SetCachePosSystem final : public System
{
public:
	virtual void Update(AMechanism* Mechanism, float DeltaTime) override;
};
