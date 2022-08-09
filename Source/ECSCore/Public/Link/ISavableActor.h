#pragma once

#include "CoreMinimal.h"
#include "SubjectHandle.h"
#include "ISavableActor.generated.h"

UINTERFACE(MinimalAPI)
class USavableActor : public UInterface
{
	GENERATED_BODY()
};

class ECSCORE_API ISavableActor
{
	GENERATED_BODY()
public:
	virtual void SaveOnSubject(FSubjectHandle Subject);
	virtual void LoadFromSub(FSubjectHandle Subject);
};




