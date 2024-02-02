#pragma once

// Dumped with Dumper-7!


namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// CLASSES
//---------------------------------------------------------------------------------------------------------------------

// 0x0 (0x90 - 0x90)
// BlueprintGeneratedClass BP_PalBaseCampWorkerEvent_Escape.BP_PalBaseCampWorkerEvent_Escape_C
class UBP_PalBaseCampWorkerEvent_Escape_C : public UPalBaseCampWorkerEvent_Escape
{
public:

	static class UClass* StaticClass();
	static class UBP_PalBaseCampWorkerEvent_Escape_C* GetDefaultObj();

	class FText CreateNotifyMessageText(class FText& LocalizedFormatText, class APalCharacter* Character, const class FString& CallFunc_GetNickName_outName, class FText CallFunc_Conv_StringToText_ReturnValue, const struct FFormatArgumentData& K2Node_MakeStruct_FormatArgumentData, TArray<struct FFormatArgumentData>& K2Node_MakeArray_Array, class FText CallFunc_Format_ReturnValue);
};

}


