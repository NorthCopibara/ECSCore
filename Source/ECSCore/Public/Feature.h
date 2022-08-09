#pragma once

#include "System.h"

class ECSCORE_API Feature : public System
{
public:
	auto Add(TSharedPtr<System> InSystem) -> Feature*;

	template <typename T>
	auto Add() -> Feature*
	{
		return Add(MakeShared<T>());
	}

	virtual void Initialize(AMechanism* Mechanism) override;

	virtual void Update(AMechanism* Mechanism, float DeltaTime) override;

	virtual void Teardown(AMechanism* Mechanism) override;

	virtual bool IsSteadyTick();

protected:
	TArray<TSharedPtr<System>> Systems;
};