#pragma once
#include "Modules/ModuleManager.h"

class ECSCORE_API FECSCoreModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
