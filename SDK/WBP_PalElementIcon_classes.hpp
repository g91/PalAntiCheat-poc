#pragma once

// Dumped with Dumper-7!


namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// CLASSES
//---------------------------------------------------------------------------------------------------------------------

// 0xB1 (0x4D9 - 0x428)
// WidgetBlueprintGeneratedClass WBP_PalElementIcon.WBP_PalElementIcon_C
class UWBP_PalElementIcon_C : public UPalUserWidget
{
public:
	struct FPointerToUberGraphFrame              UberGraphFrame;                                    // 0x428(0x8)(ZeroConstructor, Transient, DuplicateTransient)
	class UImage*                                Icon_Element;                                      // 0x430(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	TMap<enum class EPalElementType, class UTexture2D*> IconMap;                                           // 0x438(0x50)(Edit, BlueprintVisible, DisableEditOnInstance)
	TMap<enum class EPalElementType, class UTexture2D*> IconMap_L;                                         // 0x488(0x50)(Edit, BlueprintVisible, DisableEditOnInstance)
	bool                                         IsLargeTexture;                                    // 0x4D8(0x1)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

	static class UClass* StaticClass();
	static class UWBP_PalElementIcon_C* GetDefaultObj();

	void Clear();
	void SetElement(enum class EPalElementType ElementType, bool Temp_bool_Variable, bool CallFunc_NotEqual_ByteByte_ReturnValue, class UTexture2D* CallFunc_Map_Find_Value, bool CallFunc_Map_Find_ReturnValue, class UTexture2D* CallFunc_Map_Find_Value_1, bool CallFunc_Map_Find_ReturnValue_1, class UTexture2D* K2Node_Select_Default);
	void Construct();
	void ExecuteUbergraph_WBP_PalElementIcon(int32 EntryPoint, class UCanvasPanelSlot* CallFunc_SlotAsCanvasSlot_ReturnValue, bool CallFunc_IsValid_ReturnValue);
};

}


