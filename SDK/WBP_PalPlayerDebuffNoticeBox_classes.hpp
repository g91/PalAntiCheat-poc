#pragma once

// Dumped with Dumper-7!


namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// CLASSES
//---------------------------------------------------------------------------------------------------------------------

// 0x60 (0x488 - 0x428)
// WidgetBlueprintGeneratedClass WBP_PalPlayerDebuffNoticeBox.WBP_PalPlayerDebuffNoticeBox_C
class UWBP_PalPlayerDebuffNoticeBox_C : public UPalUserWidget
{
public:
	struct FPointerToUberGraphFrame              UberGraphFrame;                                    // 0x428(0x8)(ZeroConstructor, Transient, DuplicateTransient)
	class UHorizontalBox*                        HorizontalBox_Debuff;                              // 0x430(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	TMap<enum class E_PalUIPlayerDebuffNoticeType, class UWBP_DebuffNotice_C*> DisplayingDebuffWidget;                            // 0x438(0x50)(Edit, BlueprintVisible, DisableEditOnInstance, ContainsInstancedReference)

	static class UClass* StaticClass();
	static class UWBP_PalPlayerDebuffNoticeBox_C* GetDefaultObj();

	void RemoveDebuffNotice(enum class E_PalUIPlayerDebuffNoticeType DebuffType, bool CallFunc_Map_Remove_ReturnValue, class UWBP_DebuffNotice_C* CallFunc_Map_Find_Value, bool CallFunc_Map_Find_ReturnValue);
	void AddDebuffNotice(enum class E_PalUIPlayerDebuffNoticeType DebuffType, const struct FMargin& K2Node_MakeStruct_Margin, class APlayerController* CallFunc_GetLocalPlayerController_ReturnValue, class UWBP_DebuffNotice_C* CallFunc_Create_ReturnValue, bool CallFunc_Map_Contains_ReturnValue, class UHorizontalBoxSlot* CallFunc_AddChildToHorizontalBox_ReturnValue);
	void Destruct();
	void ExecuteUbergraph_WBP_PalPlayerDebuffNoticeBox(int32 EntryPoint);
};

}


