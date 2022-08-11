#pragma once

#include "Systems/ReactiveSystems/ReactiveAddSystem.h"

class ECSCORE_API OnLinkedAddSystem final : public ReactiveAddSystem
{
public:
	virtual void Initialize(AMechanism* Mechanism) override;
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject) override;
};
