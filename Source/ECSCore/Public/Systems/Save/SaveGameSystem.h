#pragma once

#include "Systems/ReactiveSystems/ReactiveSystem.h"

class ECSCORE_API SaveGameSystem final : public ReactiveSystem
{
public:
	virtual void Initialize(AMechanism* Mechanism) override;
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject) override;
private:
	void SaveFromViews(FSubjectHandle Subject);
};
