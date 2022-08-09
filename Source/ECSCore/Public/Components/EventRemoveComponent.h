#pragma once

#include "Mechanism.h"
#include "EventRemoveComponent.generated.h"

USTRUCT(BlueprintType)
struct FEventRemoveComponent
{
	GENERATED_BODY()	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	UScriptStruct* Value;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	FSubjectHandle Subject;
	
	FEventRemoveComponent(): Value(nullptr)
	{
	}

	explicit FEventRemoveComponent(UScriptStruct* Value)
	{
		this->Value = Value;
		this->Subject = FSubjectHandle::Invalid;
		
	}	
	explicit FEventRemoveComponent(UScriptStruct* Value, const FSubjectHandle Subject)
	{
		this->Value = Value;
		this->Subject = Subject;
		
	}
	
	template <typename T>
	explicit FEventRemoveComponent(T&, const FSubjectHandle& Subject)
	{
		this->Value = T::StaticStruct();
		this->Subject = Subject;
	}
	
	explicit FEventRemoveComponent(const UScriptStruct& Trait);
};
