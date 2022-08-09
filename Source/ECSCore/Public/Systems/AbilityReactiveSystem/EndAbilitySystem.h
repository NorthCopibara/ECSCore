#pragma once
#include "Systems/ReactiveSystems/ReactiveSystem.h"

class ECSCORE_API EndAbilitySystem : public ReactiveSystem
{
public:
	virtual void Initialize(AMechanism* Mechanism) override;
	
	virtual bool HasComponents(FSubjectHandle Subject) override;
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle AbilitySub) override;

protected:
	virtual void EndAbility(AMechanism* Mechanism, FUnsafeSubjectHandle OwnerSub);
	virtual bool OwnerHasComponents(FSubjectHandle OwnerSub);
	
	void SetupAbility(UScriptStruct* Trigger);
private:
	UScriptStruct* AbilityType = nullptr;
};
