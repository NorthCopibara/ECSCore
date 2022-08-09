#pragma once
#include "System.h"
#include "Components/EventRemoveComponent.h"

class ECSCORE_API ReactiveRemoveSystem : public System
{
public:
	virtual void Initialize(AMechanism* Mechanism) override;
	virtual auto Update(AMechanism* Mechanism, float DeltaTime) -> void override;	
	
protected:	
	bool DeleteTrigger = true;
	virtual bool HasComponents(FSubjectHandle Subject);
	virtual void Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject);
	UScriptStruct* TriggerOnRemove = nullptr;
private:
	FFilter ReactiveFilter;
};
