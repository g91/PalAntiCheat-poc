#pragma once

// Dumped with Dumper-7!


namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// CLASSES
//---------------------------------------------------------------------------------------------------------------------

// 0xF (0x480 - 0x471)
// WidgetBlueprintGeneratedClass WBP_Map_IconDeath.WBP_Map_IconDeath_C
class UWBP_Map_IconDeath_C : public UWBP_WorldMap_IconBase_NoDesign_C
{
public:
	uint8                                        Pad_4B4C[0x7];                                     // Fixing Size After Last Property  [ Dumper-7 ]
	class UImage*                                Icon;                                              // 0x478(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

	static class UClass* StaticClass();
	static class UWBP_Map_IconDeath_C* GetDefaultObj();

};

}


