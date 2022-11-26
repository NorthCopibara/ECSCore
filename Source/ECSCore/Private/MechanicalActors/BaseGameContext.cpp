#include "MechanicalActors/BaseGameContext.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/BaseComponents/DataBaseComponent.h"
#include "MechanicalActors/BaseEcsBootstrap.h"

void ABaseGameContext::Initialize()
{
	InjectDataToECS();
	GetWorld()->SpawnActor<AMechanicalActor>(EcsMainBootstrap);	
}

void ABaseGameContext::InjectDataToECS() const
{
	GetMechanism()->SpawnSubject().SetTrait(FDataBaseComponent(DataBase));
}