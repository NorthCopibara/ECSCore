#pragma once
#include "Link/LinkableActor.h"

#include "LinkComponent.generated.h"

USTRUCT(BlueprintType)
struct FLinkComponent
{
	GENERATED_BODY()	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	TScriptInterface<ILinkableActor> Value;
	FLinkComponent(): Value(nullptr){}
	explicit FLinkComponent(const TScriptInterface<ILinkableActor> Value)
	{
		this->Value = Value;
	}	
};