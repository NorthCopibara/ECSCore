#pragma once
#include "Systems/ReactiveSystems/ReactiveSystem.h"

class ECSCORE_API CancelAbilitySystem : public ReactiveSystem
{
public:
	virtual void Initialize(AMechanism* Mechanism) override;
	
	virtual bool HasComponents(FSubjectHandle Subject) override;
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject) override;

protected:
	virtual void CancelAbility(AMechanism* Mechanism, FUnsafeSubjectHandle OwnerSub);
	
	virtual bool OwnerHasComponents(FSubjectHandle OwnerSub);

	void SetupAbility(UScriptStruct* Trigger);
private:
	UScriptStruct* AbilityType = nullptr;
};
