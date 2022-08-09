#pragma once
#include "Systems/ReactiveSystems/ReactiveAddSystem.h"


class ECSCORE_API EnableSystem final : public ReactiveAddSystem
{
public:
	virtual void Initialize(AMechanism* Mechanism) override;
	virtual bool HasComponents(FSubjectHandle Subject) override;
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject) override;
};
