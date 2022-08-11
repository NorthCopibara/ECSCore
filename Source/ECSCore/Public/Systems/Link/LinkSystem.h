#pragma once

#include "Components/LinkComponent.h"
#include "Systems/ReactiveSystems/ReactiveAddSystem.h"

class ECSCORE_API LinkSystem final : public ReactiveAddSystem
{
public:
	virtual void Initialize(AMechanism* Mechanism) override;
protected:
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject) override;
	virtual bool HasComponents(FSubjectHandle Subject) override	{ return !Subject.HasTrait<FLinkComponent>(); }
};
