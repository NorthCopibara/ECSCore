#pragma once
#include "Systems/ReactiveSystems/ReactiveAddSystem.h"

class ECSCORE_API CharacterOnSetMovementTypeSystem final : public ReactiveAddSystem
{
public:
	virtual bool HasComponents(FSubjectHandle Subject) override;
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject) override;
	virtual void Initialize(AMechanism* Mechanism) override;
};
