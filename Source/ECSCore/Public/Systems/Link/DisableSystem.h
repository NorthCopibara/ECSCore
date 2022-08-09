#pragma once
#include "Systems/ReactiveSystems/ReactiveRemoveSystem.h"

class ECSCORE_API DisableSystem final : public ReactiveRemoveSystem
{
public:
	virtual void Initialize(AMechanism* Mechanism) override;
	virtual bool HasComponents(FSubjectHandle Subject) override;
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject) override;
};
