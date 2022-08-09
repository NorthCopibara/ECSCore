#pragma once
#include "System.h"

class ECSCORE_API ReactiveAddSystem : public System
{
public:
	ReactiveAddSystem();

	virtual void Initialize(AMechanism* Mechanism) override;
	virtual auto Update(AMechanism* Mechanism, float DeltaTime) -> void override;

protected:
	bool DeleteTrigger;
	virtual bool HasComponents(FSubjectHandle Subject);
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject);
	
	UScriptStruct* TriggerOnAdd = nullptr;
private:
	FFilter ReactiveFilter;
};
