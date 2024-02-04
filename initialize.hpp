#pragma once
#include "SDK.hpp"
#include "config.h"
#include "detours.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdarg> // For va_list, va_start, va_end
#include <cstdio>  // For vsnprintf


typedef SDK::APlayerController* (*SpawnPlayActorType)(SDK::UWorld* that, SDK::UPlayer* player, SDK::ENetRole role, const SDK::FURL* url, const SDK::FUniqueNetIdRepl* uid, SDK::FString* error, uint8_t index);
SpawnPlayActorType engine_spawn_play_actor;

typedef void(__stdcall* tProcessEvent) (const SDK::UObject*, SDK::UFunction*, void*);
tProcessEvent pProcessEvent;

SDK::APlayerController* spawn_play_actor_proxy(SDK::UWorld* that, SDK::UPlayer* player, SDK::ENetRole role, const SDK::FURL* url, const SDK::FUniqueNetIdRepl* uid, SDK::FString* error, uint8_t index);

uintptr_t GetImageBaseOffset() {
    return uintptr_t(GetModuleHandle(0));
}

// Function to log formatted text to a log file
void logToFile(const std::string& logFilePath, const char* format, ...) {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    // Start variadic argument list
    va_list args;
    va_start(args, format);

    // Format the string and store it in buffer
    vsnprintf(buffer, BUFFER_SIZE, format, args);

    // End variadic argument list
    va_end(args);

    // Open the log file in append mode
    std::ofstream logFile(logFilePath, std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file for writing." << std::endl;
        return;
    }

    // Write the formatted text to the file
    logFile << buffer << std::endl;
    std::cout << buffer << std::endl;

    // Close the file
    logFile.close();
}

bool containsSegment(const std::string& text, const std::string& segment) {
    return text.find(segment) != std::string::npos;//
}

void  HookedProcessEvent(const SDK::UObject* Object, class SDK::UFunction* Function, void* Parms) 
{
        //add item fix  it does not seem that this function is called by the client at all unless it's cheating so just returning disables the function 
        if (!strcmp(Function->GetFullName().c_str(), "Function Pal.PalNetworkPlayerComponent.RequestAddItem_ToServer")) {
            SDK::Params::UPalNetworkPlayerComponent_RequestAddItem_ToServer_Params* AddItemParms = (SDK::Params::UPalNetworkPlayerComponent_RequestAddItem_ToServer_Params*)Parms;
            logToFile("app.log", "[CMD::ProcessEventHook] Function  = RequestAddItem_ToServer Cheater ItemId: %i Count: %i  Object: 0x%X Actor: 0x%X raw_name: %s Object name: %s\n", AddItemParms->StaticItemId, AddItemParms->Count, Object);
            logToFile("log\\RequestAddItem_ToServer.log", "[CMD::ProcessEventHook] Function  = RequestAddItem_ToServer Cheater ItemId: %i Count: %i  Object: 0x%X Actor: 0x%X raw_name: %s Object name: %s\n", AddItemParms->StaticItemId, AddItemParms->Count, Object);
            return;
        }

        //
        else if (containsSegment(Function->GetFullName().c_str(), "admin")) {
            logToFile("log\\admin.log", "[CMD::ProcessEventHook] admin  = %s Object: 0x%X\n", Function->GetFullName().c_str(), Object);
            //return;
        }

        //kill area fix   this command doesn't seem to be called from the client SendDeath_ToServer so we're able just to return to disable it
        else if (!strcmp(Function->GetFullName().c_str(), "Function Pal.PalPlayerState.SendDeath_ToServer")) {
            //g_Console->printdbg("[CMD::ProcessEventHook] _ToServer  = %s\n", g_Console->color.green, Function->GetFullName().c_str());
            logToFile("log\\SendDeath_ToServer.log", "[CMD::ProcessEventHook] SendDeath_ToServer = %s  Object: 0x%X\n", Function->GetFullName().c_str(), Object);
            return;
        }

        //this command doesn't seem to be called from the client
        else if (!strcmp(Function->GetFullName().c_str(), "Function Pal.PalPlayerState.SendDamage_ToServer")) {
            SDK::Params::APalPlayerState_SendDamage_ToServer_Params* NewParms = (SDK::Params::APalPlayerState_SendDamage_ToServer_Params*)Parms;
            //g_Console->printdbg("[CMD::ProcessEventHook] _ToServer  = %s\n", g_Console->color.green, Function->GetFullName().c_str());
            logToFile("log\\SendDamage_ToServer.log", "[CMD::ProcessEventHook] SendDamage_ToServer = %s  NativeDamageValue: %i Object: 0x%X\n", Function->GetFullName().c_str(), Object, NewParms->Info.NativeDamageValue);
        }

        //easier to remove unnecessary strings from showing up in the logs so you can see what is necessary
        else if (!strcmp(Function->GetFullName().c_str(), "Function Pal.PalOptionSubsystem.GetOptionWorldSettings") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AudioSetting.BP_AudioSetting_C.SetAudioBusVolume") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalRandomIncidentSpawner.BP_PalRandomIncidentSpawner_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAudioWorldSubsystem.BP_PalAudioWorldSubsystem_C.Tick_BP") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_SeaSide.BP_PalAmbientSoundArea_SeaSide_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_Desert.BP_PalAmbientSoundArea_Desert_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_Forest.BP_PalAmbientSoundArea_Forest_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_CoopSkillSearchEffectController.BP_CoopSkillSearchEffectController_C.IsRunning") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalWindController.BP_PalWindController_C.UpdateNiagaraParameterCollection") ||
            !strcmp(Function->GetFullName().c_str(), "Function SunSky.SunSky_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_Volcano.BP_PalAmbientSoundArea_Volcano_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_SnowyMountain.BP_PalAmbientSoundArea_SnowyMountain_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_Forest.BP_PalAmbientSoundArea_Forest_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_Desert.BP_PalAmbientSoundArea_Desert_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_Cave.BP_PalAmbientSoundArea_Cave_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalBiomeEffectController.BP_PalBiomeEffectController_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalCharacterMaterialVolume.BP_PalCharacterMaterialVolume_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalBiomeLightingAdjuster.BP_PalBiomeLightingAdjuster_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AudioSetting.BP_AudioSetting_C.Tick_BP") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalBiomeLightingAdjuster.BP_PalBiomeLightingAdjuster_C.ExecuteUbergraph_BP_PalBiomeLightingAdjuster") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PPSkyCreator_Controller.BP_PPSkyCreator_Controller_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PPSkyCreatorWeatherPresetController.BP_PPSkyCreatorWeatherPresetController_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAudioWorldSubsystem.BP_PalAudioWorldSubsystem_C.Tick_BP") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalTimeManager.BP_PalTimeManager_C.Tick_BP") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AudioSetting.BP_AudioSetting_C.Tick_BP") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalFoliageISMComponentBase.OnRegisterInstance") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalAmbientSoundArea_Forest2.BP_PalAmbientSoundArea_Forest2_C.GetAreaCollision") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_WorldSecurity_AreaInvasion_Volume.BP_WorldSecurity_AreaInvasion_Volume_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_NPC_RelaxBase.BP_AIAction_NPC_RelaxBase_C.SetSightSkipFlag") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalVisualEffectBase.CanDeleteInstance") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_MapObject_PickupItem_Base.BP_MapObject_PickupItem_Base_C.ExecuteUbergraph_BP_MapObject_PickupItem_Base") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalNetworkMulticastGateComponent.SendToServer_bool") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalStatusBase.TickStatus") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalStatusBase.IsEndStatus") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_VisualEffect_SpawnFadeIn.BP_VisualEffect_SpawnFadeIn_C.Update") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_SimpleWater.BP_SimpleWater_C.ReceiveActorBeginOverlap") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_Status_ShieldRecovery.BP_Status_ShieldRecovery_C.TickStatus") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_Action_WaitLoadingWorldPartition.BP_Action_WaitLoadingWorldPartition_C.TickAction") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_WildLife.BP_AIAction_WildLife_C.Event_StopFalse") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalActionBase.IsEndAction") ||
            !strcmp(Function->GetFullName().c_str(), "Function Engine.Character.ClientMoveResponsePacked") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalPlayerController.BP_PalPlayerController_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function Engine.AnimInstance.BlueprintThreadSafeUpdateAnimation") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalVisualEffectBase.IsEndVisualEffect") ||
            !strcmp(Function->GetFullName().c_str(), "Function Engine.AnimInstance.BlueprintUpdateAnimation") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_WantedPolice_NPCSpawner.BP_WantedPolice_NPCSpawner_C.BlueprintTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalPlayerController.BP_PalPlayerController_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_NPCAIController.BP_NPCAIController_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_GliderComponent.BP_GliderComponent_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_NPC_RelaxBase.BP_AIAction_NPC_RelaxBase_C.ActionPostTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalVisualEffectBase.OnDeleteInstance") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_Player_Female.BP_Player_Female_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalClimbingComponent.BP_PalClimbingComponent_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_Status_FallDamage.BP_Status_FallDamage_C.TickStatus") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalWeaponBase.GetOwnerCharacter") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_ShotgunBase.BP_ShotgunBase_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalActionBase.TickAction") ||
            !strcmp(Function->GetFullName().c_str(), "Function Engine.AnimNotifyState.Received_NotifyTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function Engine.AnimInstance.BlueprintPostEvaluateAnimation") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_WildLife.BP_AIAction_WildLife_C.ActionTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_MonsterAIControllerBase.BP_MonsterAIControllerBase_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_NPC_RelaxBase.BP_AIAction_NPC_RelaxBase_C.ActionTickAnyThread") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_Player_Female.BP_Player_Female_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_WildLife.BP_AIAction_WildLife_C.ActionPostTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function AIModule.PawnAction_BlueprintBase.ActionTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function Engine.Character.ServerMovePacked") ||
            !strcmp(Function->GetFullName().c_str(), "Function Engine.PlayerController.ServerUpdateCamera") ||
            !strcmp(Function->GetFullName().c_str(), "AnyThread") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalAISensorComponent.ReceiveSound") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_HitEffectSlot.BP_HitEffectSlot_C.Initialize") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_MapObject_PickupItem_Base.BP_MapObject_PickupItem_Base_C.ReceiveBeginPlay") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalNetworkMulticastGateComponent.SendToServer_void") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalNetworkMulticastGateComponent.SendToALL_void") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_WildLife.BP_AIAction_WildLife_C.StateUpdate") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_WildLife.BP_AIAction_WildLife_C.ActionTickAnyThread") ||
            !strcmp(Function->GetFullName().c_str(), "Function Engine.AnimNotify.Received_Notify") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalCryNotify.BP_PalCryNotify_C.Received_Notify") ||
            !strcmp(Function->GetFullName().c_str(), "Function AnimNotify_AkEvent.AnimNotify_AkEvent_C.Received_Notify") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PlayerSoundEmitterComponent.BP_PlayerSoundEmitterComponent_C") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_Status_FallDamage.BP_Status_FallDamage_C.OnModeChange") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalActionComponent.CancelAllAction_Internal") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalSpawner_Standard.BP_PalSpawner_Standard_C.Spawn Delegate") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_WildLife.BP_AIAction_WildLife_C.ActionStart") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalActionComponent.PlayAction_ToServer") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalCharacterParameterComponent.SetOverrideTargetLocation_ToServer") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalPlayerController.SetCameraRotatorToPlayerCharacter_ToServer") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalShooterComponent.SetTargetDirection_ToServer") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalNetworkIndividualComponent.DespawnIndividualActor_ToServer") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalNetworkCharacterComponent.RequestReflectAction_ToServer") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalAIController.OnChangeChangeImportance") ||
            !strcmp(Function->GetFullName().c_str(), "Function AIModule.AIAsyncTaskBlueprintProxy.OnMoveCompleted") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIActionEscape.BP_AIActionEscape_C.ActionTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_AIAction_FriendlyLookat.BP_AIAction_FriendlyLookat_C.ActionTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalActionBase.OnBreakAction") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalPlayerController.OnJump") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalPlayerController.OnLanded") ||
            !strcmp(Function->GetFullName().c_str(), "Function Pal.PalMapObject.BP_OnSetConcreteModel") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_CascadeRiverTool.BP_CascadeRiverTool_C.ReceiveTick") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalSpawner_Standard.BP_PalSpawner_Standard_C.BlueprintTick_Spawning") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_PalPlayerController.BP_PalPlayerController_C.Regene_CustomEvent") ||
            !strcmp(Function->GetFullName().c_str(), "Function BP_OtomoPalHolderComponent.BP_OtomoPalHolderComponent_C.ReceiveTick") ||


            containsSegment(Function->GetFullName().c_str(), "Function Pal.PalVisualEffectComponent") ||
            containsSegment(Function->GetFullName().c_str(), "Function Pal.PalStatusComponent") ||
            containsSegment(Function->GetFullName().c_str(), "Function BP_ActionRandomRest.BP_ActionRandomRest_C") ||
            //containsSegment(Function->GetFullName().c_str(), "Function Pal.PalNetworkTransmitter") ||
            containsSegment(Function->GetFullName().c_str(), "Function BP_PlayerSoundEmitterComponent") ||
            containsSegment(Function->GetFullName().c_str(), "Function BP_PlayerSoundEmitterComponent.BP_PlayerSoundEmitterComponent_C") ||
            containsSegment(Function->GetFullName().c_str(), "Function BP_AIAction_WildLife.BP_AIAction_WildLife_C")) 
        {

        }
        else if (containsSegment(Function->GetFullName().c_str(), "Function Pal.PalNetworkPlayerComponent")) {
            logToFile("log\\PalNetworkPlayerComponent.log", "[CMD::ProcessEventHook] PalNetworkPlayerComponent = % s Object : 0x%X\n", Function->GetFullName().c_str(), Object);
        }
        else if (containsSegment(Function->GetFullName().c_str(), "Function BP_PalPlayerController")) {
                logToFile("log\\BP_PalPlayerController.log", "[CMD::ProcessEventHook] BP_PalPlayerController = % s Object : 0x%X\n", Function->GetFullName().c_str(), Object);
        }
        else if (containsSegment(Function->GetFullName().c_str(), "Function Pal.PalPlayerState")) {
                    logToFile("log\\PalPlayerState.log", "[CMD::ProcessEventHook] PalPlayerState = % s Object : 0x%X\n", Function->GetFullName().c_str(), Object);

        }
        else if (containsSegment(Function->GetFullName().c_str(), "Function Pal.PalNetworkPlayerComponent")) {
            logToFile("log\\PalNetworkPlayerComponent.log", "[CMD::ProcessEventHook] PalNetworkPlayerComponent = % s Object : 0x%X\n", Function->GetFullName().c_str(), Object);
        
        }
        else if (containsSegment(Function->GetFullName().c_str(), "Function Pal.PalPlayerController")) {
            logToFile("log\\PalPlayerController.log", "[CMD::ProcessEventHook] PalPlayerController = %s   Object: 0x%X\n", Function->GetFullName().c_str(), Object);
        }
        else if (containsSegment(Function->GetFullName().c_str(), "Function Pal.PalNetworkMapObjectComponent.RequestDamageFoliage_ToServer")) {
            SDK::Params::UPalNetworkMapObjectComponent_RequestDamageFoliage_ToServer_Params* NewParms = (SDK::Params::UPalNetworkMapObjectComponent_RequestDamageFoliage_ToServer_Params*)Parms;
            logToFile("log\\RequestDamageFoliage_ToServer.log", "[CMD::ProcessEventHook] RequestDamageFoliage_ToServer = %s   Object: 0x%X\n", Function->GetFullName().c_str(), Object);
            //NewParms.
        }
        else if (containsSegment(Function->GetFullName().c_str(), "_ToServer")) {
            //g_Console->printdbg("[CMD::ProcessEventHook] _ToServer  = %s\n", //g_Console->color.green, Function->GetFullName().c_str());
            logToFile("log\\ToServer.log", "[CMD::ProcessEventHook] ToServer = %s   Object: 0x%X\n", Function->GetFullName().c_str(), Object);
        }else logToFile("log\\ac-all-Function.log", "[CMD::ProcessEventHook] Function  = %s   Object: 0x%X\n", Function->GetFullName().c_str(), Object);
      
    pProcessEvent(Object, Function, Parms);
}


//credit: VeroFess
//https://github.com/VeroFess/PalWorld-Server-Unoffical-Api/blob/main/src/hooks/spawn_play_actor.cpp
SDK::APlayerController* spawn_play_actor_proxy(SDK::UWorld* that, SDK::UPlayer* player, SDK::ENetRole role, const SDK::FURL* url, const SDK::FUniqueNetIdRepl* uid, SDK::FString* error, uint8_t index) {
    static SDK::UPalUtility* utility = nullptr;
    if (!utility) {
        utility = SDK::UPalUtility::GetDefaultObj();
    }

    auto controller = engine_spawn_play_actor(that, player, role, url, uid, error, index);
    if (!controller) {
        return nullptr;
    }

    auto state_raw = controller->PlayerState;

    if (!state_raw) {
        //g_Console->printdbg("state is null!");
        return nullptr;
    }

    if (!state_raw->IsA(SDK::APalPlayerState::StaticClass())) {
        //g_Console->printdbg("state not a APalPlayerState!");
        return nullptr;
    }

    std::string address = std::string("[UNK]");

    if (controller->NetConnection) {
        //auto fsaddress = LowLevelGetRemoteAddress(static_cast<SDK::UIpConnection*>(controller->NetConnection), true);

        //if (fsaddress && fsaddress->IsValid() && fsaddress->Count() > 1) {
        //    address = fsaddress->ToString();
        //}
    }

    auto     state = static_cast<SDK::APalPlayerState*>(state_raw);
    auto     raw_name = state->GetPlayerName();
    uint32_t pid = 0;

    if (state->PlayerUId.A != 0) {
        pid = static_cast<uint32_t>(state->PlayerUId.A);
    }
    else if (state->LoginTryingPlayerUId_InServer.A != 0) {
        pid = static_cast<uint32_t>(state->LoginTryingPlayerUId_InServer.A);
    }
    else {
        pid = state->GetPlayerId();
    }

    logToFile("app.log", "[Event::Login] player{%s} login from{} with id{%i}, \n", raw_name.ToString(), static_cast<uint32_t>(pid));
    //g_Console->printdbg("\n[Event::Login] player{%s} login from{} with id{%i}, \n", //g_Console->color.green, raw_name.ToString(), static_cast<uint32_t>(pid));
    // if we return null, connection will close

    return controller;
}

DWORD WINAPI MainThread_Initialize()
{
    pProcessEvent = (tProcessEvent)Detours::X64::DetourFunction(uintptr_t(Config.ClientBase) +  Offsets::ProcessEvent, (uintptr_t)HookedProcessEvent);
    engine_spawn_play_actor = (SpawnPlayActorType)Detours::X64::DetourFunction(uintptr_t(Config.ClientBase) + Offsets::SpawnPlayActor, (uintptr_t)spawn_play_actor_proxy);


    while (true)
    {
        std::cout << "Loader > ";
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "test") {

        }
    }

    return EXIT_SUCCESS;
}