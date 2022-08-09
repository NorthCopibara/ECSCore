#pragma once

#include "Mechanism.h"

class ECSCORE_API System
{
protected:
	System(){}
	System(const System&) = default;
	System& operator=(const System&) = default;

public:
	virtual ~System() = default;

	virtual void Initialize(AMechanism* Mechanism){}
	virtual void Update(AMechanism* Mechanism, float DeltaTime){}
	virtual void Teardown(AMechanism* Mechanism){}
};
