#include "..\includes.h"

#include "hooks.h"
#include "../UTILS/interfaces.h"
#include "../UTILS/offsets.h"

#include "../SDK/CInput.h"
#include "../SDK/IClient.h"
#include "../SDK/CPanel.h"
#include "../UTILS/render.h"
#include "../SDK/ConVar.h"
#include "../SDK/CGlowObjectManager.h"
#include "../SDK/IEngine.h"
#include "../SDK/CTrace.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/RecvData.h"
#include "../SDK/CBaseAnimState.h"
#include "../UTILS/NetvarHookManager.h"
#include "../SDK/ModelInfo.h"
#include "../SDK/ModelRender.h"
#include "../SDK/RenderView.h"
#include "../SDK/CTrace.h"
#include "../SDK/CViewSetup.h"
#include "../SDK/CGlobalVars.h"
#include "../SDK/GameEvents.h"
#include "../FEATURES/Movement.h"
#include "../FEATURES/Visuals.h"
#include "../FEATURES/Chams.h"
#include "../FEATURES/AntiAim.h"
#include "../FEATURES/Aimbot.h"
#include "../FEATURES/Resolver.h"
#include "../FEATURES/Backtracking.h"
#include "../FEATURES/FakeWalk.h"
#include "../FEATURES/FakeLag.h"
#include "../FEATURES/EventListener.h"
#include "../MENU/menu_framework.h"

#include <intrin.h>

//--- Other Globally Used Variables ---///
static bool tick = false;

//--- Declare Signatures and Patterns Here ---///
static auto CAM_THINK = UTILS::FindSignature("client.dll", "85 C0 75 30 38 86");
//SDK::CGlowObjectManager* pGlowObjectManager = (SDK::CGlowObjectManager*)(UTILS::FindSignature("client.dll", "0F 11 05 ? ? ? ? 83 C8 01") + 0x3);
static auto linegoesthrusmoke = UTILS::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xEC\x08\x8B\x15\x00\x00\x00\x00\x0F\x57\xC0", "xxxxxxxx????xxx");

namespace HOOKS
{
	CreateMoveFn original_create_move;
	PaintTraverseFn original_paint_traverse;
	FrameStageNotifyFn original_frame_stage_notify;
	DrawModelExecuteFn original_draw_model_execute;
	SceneEndFn original_scene_end;
	TraceRayFn original_trace_ray;
	SendDatagramFn original_send_datagram;
	OverrideViewFn original_override_view;
	//ToFirstPersonFn original_to_firstperson;
	SvCheatsGetBoolFn original_get_bool;
	
	VMT::VMTHookManager iclient_hook_manager;
	VMT::VMTHookManager panel_hook_manager;
	VMT::VMTHookManager model_render_hook_manager;
	VMT::VMTHookManager render_view_hook_manager;
	VMT::VMTHookManager trace_hook_manager;
	VMT::VMTHookManager net_channel_hook_manager;
	VMT::VMTHookManager override_view_hook_manager;
	VMT::VMTHookManager input_table_manager;
	VMT::VMTHookManager get_bool_manager;


	static int ground_tick;
	void ground_ticks()
	{
		auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

		if (!local_player)
			return;

		if (local_player->GetFlags() & FL_ONGROUND)
			ground_tick++;
		else
			ground_tick = 0;
	}
	bool __stdcall HookedCreateMove(float sample_input_frametime, SDK::CUserCmd* cmd)
	{
		if (!cmd || cmd->command_number == 0)
			return false;

		uintptr_t* FPointer; __asm { MOV FPointer, EBP }
		byte* SendPacket = (byte*)(*FPointer - 0x1C);

		if (!SendPacket)
			return false;

		GLOBAL::should_send_packet = *SendPacket;
		// S T A R T

		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
		{
			if (SETTINGS::settings.aim_type == 0)
				slidebitch->do_fakewalk(cmd);

			if (SETTINGS::settings.bhop_bool)
				movement->bunnyhop(cmd);

			if (SETTINGS::settings.strafe_bool)
				movement->autostrafer(cmd);

			if (SETTINGS::settings.aim_type == 0)
			{
	
				aimbot->shoot_enemy(cmd);
				aimbot->fix_recoil(cmd);
				backtracking->backtrack_player(cmd);
				fakelag->do_fakelag();
			 	if(SETTINGS::settings.autozeus_bool) aimbot->autozeus(cmd);


			}

			if (SETTINGS::settings.aim_type == 1 && SETTINGS::settings.back_bool)
				backtracking->run_legit(cmd);

			if (SETTINGS::settings.aa_bool || SETTINGS::settings.aa_type > 0 || SETTINGS::settings.aim_type == 0)
			{
			

					antiaim->do_antiaim(cmd);
					antiaim->fix_movement(cmd);
					
			}



			if (!GLOBAL::should_send_packet)
				GLOBAL::real_angles = cmd->viewangles;
		}

		// E N D
		*SendPacket = GLOBAL::should_send_packet;

		UTILS::ClampLemon(cmd->viewangles);

		return false;
	}
	void __stdcall HookedPaintTraverse(int VGUIPanel, bool ForceRepaint, bool AllowForce)
	{
		std::string panel_name = INTERFACES::Panel->GetName(VGUIPanel);

		if (panel_name == "HudZoom")
			return;

		if (panel_name == "MatSystemTopPanel")
		{
			if (FONTS::ShouldReloadFonts())
				FONTS::InitFonts();

			if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
			{
				
				if (SETTINGS::settings.esp_bool)
				{
					visuals->Draw();
					visuals->ClientDraw();
				}
			}

			MENU::PPGUI_PP_GUI::Begin();
			MENU::Do();
			MENU::PPGUI_PP_GUI::End();

			UTILS::INPUT::input_handler.Update();

			RENDER::DrawSomething();
		}

		original_paint_traverse(INTERFACES::Panel, VGUIPanel, ForceRepaint, AllowForce);
	}
	void __fastcall HookedFrameStageNotify(void* ecx, void* edx, int stage)
	{
		switch (stage)
		{
		case FRAME_NET_UPDATE_POSTDATAUPDATE_START:

			//--- Angle Resolving and Such ---//
			if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
			{
				for (int i = 1; i < 65; i++)
				{
					auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
					auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

					if (!entity)
						continue;

					if (!local_player)
						continue;

					bool is_local_player = entity == local_player;
					bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

					if (is_local_player)
						continue;

					if (is_teammate)
						continue;

					if (entity->GetHealth() <= 0)
						continue;

					//backtracking->DisableInterpolation(entity);

					if (SETTINGS::settings.aim_type == 0)
						resolver->resolve(entity);
				}
			}
			break;

		case FRAME_NET_UPDATE_POSTDATAUPDATE_END:

			break;

		case FRAME_RENDER_START:

			if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
			{
				auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

				if (!local_player)
					return;

				//--- Thirdperson Deadflag Stuff ---//
				if (in_tp)
					*(Vector*)((DWORD)local_player + 0x31C8) = GLOBAL::real_angles;
			}
			break;
		case FRAME_NET_UPDATE_START:
			if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
			{
				if (SETTINGS::settings.beam_bool)
					visuals->DrawBulletBeams();
			}

			break;
		case FRAME_NET_UPDATE_END:

			if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
			{
				for (int i = 1; i < 65; i++)
				{
					auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
					auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

					if (!entity)
						continue;

					if (!local_player)
						continue;

					bool is_local_player = entity == local_player;
					bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

					if (is_local_player)
						continue;

					if (is_teammate)
						continue;

					if (entity->GetHealth() <= 0)
						continue;

					if (SETTINGS::settings.aim_type == 0)
						backtracking->DisableInterpolation(entity);
				}
			}

			break;
		}

		original_frame_stage_notify(ecx, stage);
	}
	void __fastcall HookedDrawModelExecute(void* ecx, void* edx, SDK::IMatRenderContext* context, const SDK::DrawModelState_t& state, const SDK::ModelRenderInfo_t& render_info, matrix3x4_t* matrix)
	{
		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
		{
			for (int i = 1; i < 65; i++)
			{
				auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
				auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

				if (!entity)
					continue;

				if (!local_player)
					continue;

				if (entity && entity->GetIsScoped() && in_tp && entity == local_player)
				{
					auto weapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex()));
					if (!weapon)
						return;
					INTERFACES::RenderView->SetBlend(0.4);
				}
			}
		}

		original_draw_model_execute(ecx, context, state, render_info, matrix);
	}
	void __fastcall HookedSceneEnd(void* ecx, void* edx)
	{

		original_scene_end(ecx);

		static SDK::IMaterial* ignorez = chams->CreateMaterial(true, true, false);
		static SDK::IMaterial* notignorez = chams->CreateMaterial(false, true, false);

		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
		{
			for (int i = 1; i < 65; i++)
			{
				auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
				auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

				if (!entity)
					continue;

				if (!local_player)
					continue;

				bool is_local_player = entity == local_player;
				bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

				if (is_local_player)
					continue;

				if (is_teammate)
					continue;

				//--- Colored Models ---//



				if (entity && SETTINGS::settings.chams_type == 2)
				{
					ignorez->ColorModulate(SETTINGS::settings.imodel_col); //255, 40, 200
					INTERFACES::ModelRender->ForcedMaterialOverride(ignorez);
					entity->DrawModel(0x1, 255);
					notignorez->ColorModulate(SETTINGS::settings.vmodel_col); //0, 125, 255
					INTERFACES::ModelRender->ForcedMaterialOverride(notignorez);
					entity->DrawModel(0x1, 255);
					INTERFACES::ModelRender->ForcedMaterialOverride(nullptr);
				}
				else if (entity && SETTINGS::settings.chams_type == 1)
				{
					notignorez->ColorModulate(SETTINGS::settings.vmodel_col); //255, 40, 200
					INTERFACES::ModelRender->ForcedMaterialOverride(notignorez);
					entity->DrawModel(0x1, 255);
					INTERFACES::ModelRender->ForcedMaterialOverride(nullptr);
				}
			}

			//--- Wireframe Smoke ---//
			std::vector<const char*> vistasmoke_wireframe =
			{
				"particle/vistasmokev1/vistasmokev1_smokegrenade",
			};

			std::vector<const char*> vistasmoke_nodraw =
			{
				"particle/vistasmokev1/vistasmokev1_fire",
				"particle/vistasmokev1/vistasmokev1_emods",
				"particle/vistasmokev1/vistasmokev1_emods_impactdust",
			};

			for (auto mat_s : vistasmoke_wireframe)
			{
				SDK::IMaterial* mat = INTERFACES::MaterialSystem->FindMaterial(mat_s, TEXTURE_GROUP_OTHER);
				mat->SetMaterialVarFlag(SDK::MATERIAL_VAR_WIREFRAME, true); //wireframe
			}

			for (auto mat_n : vistasmoke_nodraw)
			{
				SDK::IMaterial* mat = INTERFACES::MaterialSystem->FindMaterial(mat_n, TEXTURE_GROUP_OTHER);
				mat->SetMaterialVarFlag(SDK::MATERIAL_VAR_NO_DRAW, true);
			}

			static auto smokecout = *(DWORD*)(linegoesthrusmoke + 0x8);
			*(int*)(smokecout) = 0;
		}
	}
			
	void __fastcall HookedOverrideView(void* ecx, void* edx, SDK::CViewSetup* pSetup)
	{
		auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

		if (!local_player)
			return;

		if (UTILS::INPUT::input_handler.GetKeyState(67) & 1)
			in_tp = !in_tp;

		//--- Actual Thirdperson Stuff ---//
		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
		{
	
	auto GetCorrectDistance = [&local_player](float ideal_distance) -> float

			{
				Vector inverse_angles;
				INTERFACES::Engine->GetViewAngles(inverse_angles);

				inverse_angles.x *= -1.f, inverse_angles.y += 180.f;

				Vector direction;
				MATH::AngleVectors(inverse_angles, &direction);

				SDK::CTraceWorldOnly filter;
				SDK::trace_t trace;
				SDK::Ray_t ray;

				ray.Init(local_player->GetVecOrigin() + local_player->GetViewOffset(), (local_player->GetVecOrigin() + local_player->GetViewOffset()) + (direction * (ideal_distance + 5.f)));
				INTERFACES::Trace->TraceRay(ray, MASK_ALL, &filter, &trace);

				return ideal_distance * trace.flFraction;
			};

	if (SETTINGS::settings.tp_bool && in_tp)
	{
		if (local_player->GetHealth() <= 0)
			local_player->SetObserverMode(5);

		if (!INTERFACES::Input->m_fCameraInThirdPerson)
		{
			auto local_player1 = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
			INTERFACES::Input->m_fCameraInThirdPerson = true;
			SDK::CBaseAnimState* animstate = local_player->GetAnimState();

			if (!animstate)
				return;

			if (animstate->m_bInHitGroundAnimation && animstate->m_flHeadHeightOrOffsetFromHittingGroundAnimation)
				INTERFACES::Input->m_vecCameraOffset = Vector(0.0f, GLOBAL::real_angles.y, GetCorrectDistance(100)); //100, GLOBAL::real_angles.x
			else
				INTERFACES::Input->m_vecCameraOffset = Vector(GLOBAL::real_angles.x, GLOBAL::real_angles.y, GetCorrectDistance(100)); //100
			Vector camForward;

			MATH::AngleVectors(Vector(INTERFACES::Input->m_vecCameraOffset.x, INTERFACES::Input->m_vecCameraOffset.y, 0), &camForward);
		}
			}
			else
			{
				INTERFACES::Input->m_fCameraInThirdPerson = false;
				INTERFACES::Input->m_vecCameraOffset = Vector(GLOBAL::real_angles.x, GLOBAL::real_angles.y, 0);
			}

			//if (local_player->GetIsScoped() && !local_player->GetIsScoped())
			//{
				pSetup->fov = 105;
			//}
		}
		original_override_view(ecx, pSetup);
	}
	void __fastcall HookedTraceRay(void *thisptr, void*, const SDK::Ray_t &ray, unsigned int fMask, SDK::ITraceFilter *pTraceFilter, SDK::trace_t *pTrace)
	{
		original_trace_ray(thisptr, ray, fMask, pTraceFilter, pTrace);
		pTrace->surface.flags |= SURF_SKY;
	}
	void __fastcall HookedSendDatagram(void* ecx, void* data)
	{
		original_send_datagram(ecx, data);
	}
	bool __fastcall HookedGetBool(void* pConVar, void* edx)
	{
		if ((uintptr_t)_ReturnAddress() == CAM_THINK)
			return true;

		return original_get_bool(pConVar);
	}
	void InitHooks()
	{

		iclient_hook_manager.Init(INTERFACES::Client);
		original_frame_stage_notify = reinterpret_cast<FrameStageNotifyFn>(
			iclient_hook_manager.HookFunction<FrameStageNotifyFn>(36, HookedFrameStageNotify));
		//iclient_hook_manager.HookTable(true);

		panel_hook_manager.Init(INTERFACES::Panel);
		original_paint_traverse = reinterpret_cast<PaintTraverseFn>(
			panel_hook_manager.HookFunction<PaintTraverseFn>(41, HookedPaintTraverse));
		//panel_hook_manager.HookTable(true);

		model_render_hook_manager.Init(INTERFACES::ModelRender);
		original_draw_model_execute = reinterpret_cast<DrawModelExecuteFn>(model_render_hook_manager.HookFunction<DrawModelExecuteFn>(21, HookedDrawModelExecute));
		//model_render_hook_manager.HookTable(true);
	
		render_view_hook_manager.Init(INTERFACES::RenderView);
		original_scene_end = reinterpret_cast<SceneEndFn>(render_view_hook_manager.HookFunction<SceneEndFn>(9, HookedSceneEnd));
		//render_view_hook_manager.HookTable(true);

		trace_hook_manager.Init(INTERFACES::Trace);
		original_trace_ray = reinterpret_cast<TraceRayFn>(trace_hook_manager.HookFunction<TraceRayFn>(5, HookedTraceRay));
		//trace_hook_manager.HookTable(true);

		override_view_hook_manager.Init(INTERFACES::ClientMode);
		original_override_view = reinterpret_cast<OverrideViewFn>(override_view_hook_manager.HookFunction<OverrideViewFn>(18, HookedOverrideView));
		original_create_move = reinterpret_cast<CreateMoveFn>(override_view_hook_manager.HookFunction<CreateMoveFn>(24, HookedCreateMove));
		//override_view_hook_manager.HookTable(true);

		CGameEvents::ItemPurchaseListener item_purchase_listener;
		CGameEvents::PlayerHurtListener player_hurt_listener;
		CGameEvents::BulletImpactListener bullet_impact_listener;
		INTERFACES::GameEventManager->AddListener(&item_purchase_listener, "item_purchase", false);
		INTERFACES::GameEventManager->AddListener(&player_hurt_listener, "player_hurt", false);
		INTERFACES::GameEventManager->AddListener(&bullet_impact_listener, "bullet_impact", false);

		/*input_table_manager = VMT::CVMTHookManager(INTERFACES::Input);
		original_to_firstperson = reinterpret_cast<ToFirstPersonFn>(input_table_manager.HookFunction(36, HookedToFirstPerson));
		input_table_manager.HookTable(true);*/

		auto sv_cheats = INTERFACES::cvar->FindVar("sv_cheats");
		get_bool_manager = VMT::VMTHookManager(reinterpret_cast<DWORD**>(sv_cheats));
		original_get_bool = reinterpret_cast<SvCheatsGetBoolFn>(get_bool_manager.HookFunction<SvCheatsGetBoolFn>(13, HookedGetBool));
	}

	void EyeAnglesPitchHook(const SDK::CRecvProxyData *pData, void *pStruct, void *pOut)
	{
		*reinterpret_cast<float*>(pOut) = pData->m_Value.m_Float;

		auto entity = reinterpret_cast<SDK::CBaseEntity*>(pStruct);
		if (!entity)
			return;

	}
	void EyeAnglesYawHook(const SDK::CRecvProxyData *pData, void *pStruct, void *pOut)
	{
		*reinterpret_cast<float*>(pOut) = pData->m_Value.m_Float;

		auto entity = reinterpret_cast<SDK::CBaseEntity*>(pStruct);
		if (!entity)
			return;

		//resolver->record(entity, pData->m_Value.m_Float);
	}


	void InitNetvarHooks()
	{
		UTILS::netvar_hook_manager.Hook("DT_CSPlayer", "m_angEyeAngles[0]", EyeAnglesPitchHook);
		UTILS::netvar_hook_manager.Hook("DT_CSPlayer", "m_angEyeAngles[1]", EyeAnglesYawHook);
	
	}
}