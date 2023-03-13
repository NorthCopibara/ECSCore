#pragma once
#include "Link/LinkableObject.h"
#include "LinkComponent.generated.h"

USTRUCT(BlueprintType)
struct FLinkComponent
{
	GENERATED_BODY()
	
	FLinkComponent(): Value(nullptr){}
	explicit FLinkComponent(const TScriptInterface<ILinkableObject> Value) : Value(Value) {}	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	TScriptInterface<ILinkableObject> Value;
};