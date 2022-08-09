#pragma once

#define DEBUG_WARN(text) UE_LOG(LogTemp, Warning, TEXT(text))
#define DEBUG_ERR(text) UE_LOG(LogTemp, Error, TEXT(text))
#define DEBUG(text) UE_LOG(LogTemp, Display, TEXT(text))

#define CAPSULE_OFFSET(RefVector) CommonExtensions::CapsuleOffset(RefVector, 45)
#define SET_TRAIT_AND_FIRE(Mechanism, Subject, Trait) EcsExtensions::SetTraitAndFire(Mechanism, Subject, Trait)
#define REMOVE_TRAIT_AND_FIRE(Mechanism, Subject, Trait) EcsExtensions::RemoveTraitAndFire(Mechanism, Subject, Trait)
#define SET_TRAIT_AND_FIRE_DEFERRED(Mechanism, Subject, Trait) EcsExtensions::SetTraitAndFireDeferred(Mechanism, Subject, Trait)
#define REMOVE_TRAIT_AND_FIRE_DEFERRED(Mechanism, Subject, Trait) EcsExtensions::RemoveTraitAndFireDeferred(Mechanism, Subject, Trait)
#define GET_PLAYER(Mechanism) EcsExtensions::GetPlayer(Mechanism)
#define GET_UID_SUB(Mechanism, Uid) EcsExtensions::GetEntityFromUId(Mechanism, Uid)

#define STRINGIFY(Identifier) #Identifier
#define ENUM_VALUE_TO_STRING(EnumType, EnumValue) \
FindObject<UEnum>(ANY_PACKAGE, TEXT(STRINGIFY(EnumType)), true)->GetNameStringByIndex(static_cast<uint8>(EnumValue));
