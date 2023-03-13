#pragma once
#include "DataBase/DataBase.h"
#include "DataBaseComponent.generated.h"

USTRUCT(BlueprintType)
struct FDataBaseComponent
{
	GENERATED_BODY()
	FDataBaseComponent() {}
	explicit FDataBaseComponent(UDataBase* Value) : Value(Value) {}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	UDataBase* Value = nullptr;
};
