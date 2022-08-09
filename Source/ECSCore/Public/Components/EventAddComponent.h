#pragma once
#include "SubjectHandle.h"

#include "EventAddComponent.generated.h"

USTRUCT(BlueprintType)
struct FEventAddComponent
{
	GENERATED_BODY()	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	UScriptStruct* Value;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	FSubjectHandle Subject;
	
	FEventAddComponent(): Value(nullptr)
	{
	}

	explicit FEventAddComponent(UScriptStruct* Value)
	{
		this->Value = Value;
		this->Subject = FSubjectHandle::Invalid;
		
	}	
	explicit FEventAddComponent(UScriptStruct* Value, const FSubjectHandle Subject)
	{
		this->Value = Value;
		this->Subject = Subject;
		
	}
	
	template <typename T>
	explicit FEventAddComponent(T&, const FSubjectHandle& Subject)
	{
		this->Value = T::StaticStruct();
		this->Subject = Subject;
	}
	
	explicit FEventAddComponent(const UScriptStruct& Trait);
};


