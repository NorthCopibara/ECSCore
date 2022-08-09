#pragma once
#include "DataBase/DataBase.h"

#include "DataBaseComponent.generated.h"

USTRUCT(BlueprintType)
struct FDataBaseComponent
{
	GENERATED_BODY()	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	UDataBase* Value;
	FDataBaseComponent(): Value(nullptr){}
	explicit FDataBaseComponent(UDataBase* Value)
	{
		this->Value = Value;
	}	
};
