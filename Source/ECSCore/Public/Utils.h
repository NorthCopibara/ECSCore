#pragma once

#define STRINGIFY(Identifier) #Identifier
#define ENUM_VALUE_TO_STRING(EnumType, EnumValue) \
FindObject<UEnum>(ANY_PACKAGE, TEXT(STRINGIFY(EnumType)), true)->GetNameStringByIndex(static_cast<uint8>(EnumValue));
