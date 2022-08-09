#pragma once
#include "System.h"

class ECSCORE_API ReactiveSystem : public System
{
public:
	ReactiveSystem();

	virtual void Initialize(AMechanism* Mechanism) override;
	virtual auto Update(AMechanism* Mechanism, float DeltaTime) -> void override;

protected:
	bool DeleteTrigger = true;
	
	virtual bool HasComponents(FSubjectHandle Subject);
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject);
	void SetupTrigger(UScriptStruct* Trigger);

private:
	UScriptStruct* TriggerType = nullptr;
	FFilter ReactiveFilter;
};
