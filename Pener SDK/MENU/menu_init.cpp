#include "../includes.h"
#include "../UTILS/interfaces.h"
#include "../SDK/IEngine.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/CInputSystem.h"
#include "../UTILS/render.h"
#include "../SDK/CBaseWeapon.h"
#include "../SDK/CBaseEntity.h"
#include "Components.h"
#include <d3d9.h>
#include <dinput.h>
#include <winnt.h>

#include "menu_framework.h"
std::vector<std::string> KeyStrings = { "",         "Mouse 1",         "Mouse 2",         "Cancel",         "Middle Mouse",         "Mouse 4",         "Mouse 5",         "",         "Backspace",         "Tab",         "",         "",         "Clear",         "Enter",         "",         "",         "Shift",         "Control",         "Alt",         "Pause",         "Caps",         "",         "",         "",         "",         "",         "",         "Escape",         "",         "",         "",         "",         "Space",         "Page Up",         "Page Down",         "End",         "Home",         "Left",         "Up",         "Right",         "Down",         "",         "",         "",         "Print",         "Insert",         "Delete",         "",         "0",         "1",         "2",         "3",         "4",         "5",         "6",         "7",         "8",         "9",         "",         "",         "",         "",         "",         "",         "",         "A",         "B",         "C",         "D",         "E",         "F",         "G",         "H",         "I",         "J",         "K",         "L",         "M",         "N",         "O",         "P",         "Q",         "R",         "S",         "T",         "U",         "V",         "W",         "X",         "Y",         "Z",         "",         "",         "",         "",         "",         "Numpad 0",         "Numpad 1",         "Numpad 2",         "Numpad 3",         "Numpad 4",         "Numpad 5",         "Numpad 6",         "Numpad 7",         "Numpad 8",         "Numpad 9",         "Multiply",         "Add",         "",         "Subtract",         "Decimal",         "Divide",         "F1",         "F2",         "F3",         "F4",         "F5",         "F6",         "F7",         "F8",         "F9",         "F10",         "F11",         "F12", };
namespace MENU
{
	void InitColors()
	{
		using namespace PPGUI_PP_GUI;

		
		colors[WINDOW_BODY] = CColor(15, 14, 17);
		colors[WINDOW_TITLE_BAR] = CColor(125, 35, 55); //255, 75, 0
		colors[WINDOW_TEXT] = WHITE;

		colors[GROUPBOX_BODY] = CColor(50, 50, 50);
		colors[GROUPBOX_OUTLINE] = GREY;
		colors[GROUPBOX_TEXT] = WHITE;

		colors[SCROLLBAR_BODY] = CColor(90, 90, 90, 255);

		colors[SEPARATOR_TEXT] = WHITE;
		colors[SEPARATOR_LINE] = CColor(90, 90, 90, 255);

		colors[CHECKBOX_CLICKED] = CColor(255, 75, 0); //HOTPINK
		colors[CHECKBOX_NOT_CLICKED] = CColor(90, 90, 90, 255);
		colors[CHECKBOX_TEXT] = WHITE;

		colors[BUTTON_BODY] = CColor(90, 90, 90, 255);
		colors[BUTTON_TEXT] = WHITE;

		colors[COMBOBOX_TEXT] = WHITE;
		colors[COMBOBOX_SELECTED] = CColor(90, 90, 90, 255);
		colors[COMBOBOX_SELECTED_TEXT] = WHITE;
		colors[COMBOBOX_ITEM] = CColor(70, 70, 70, 255);
		colors[COMBOBOX_ITEM_TEXT] = WHITE;

		colors[SLIDER_BODY] = CColor(90, 90, 90, 255);
		colors[SLIDER_VALUE] = CColor(255, 75, 0); //HOTPINK
		colors[SLIDER_TEXT] = WHITE;

		colors[TAB_BODY] = CColor(90, 90, 90, 255);
		colors[TAB_TEXT] = WHITE;
		colors[TAB_BODY_SELECTED] = CColor(255, 75, 0); //HOTPINK
		colors[TAB_TEXT_SELECTED] = WHITE;

		colors[VERTICAL_TAB_BODY] = CColor(70, 70, 70, 255);
		colors[VERTICAL_TAB_TEXT] = WHITE;
		colors[VERTICAL_TAB_OUTLINE] = CColor(0, 0, 0, 100);
		colors[VERTICAL_TAB_BODY_SELECTED] = CColor(100, 100, 100, 255);

		colors[COLOR_PICKER_BODY] = CColor(70, 70, 70, 255);
		colors[COLOR_PICKER_TEXT] = WHITE;
		colors[COLOR_PICKER_OUTLINE] = CColor(0, 0, 0, 100);
	}
	void Do()
	{
		//all of this cool gui stuff made by bolbi, but i decide to just render text and make binds for every feature. sorry bolbi!

		static bool menu_open = false;

		if (UTILS::INPUT::input_handler.GetKeyState(VK_INSERT) & 1)
		{
			menu_open = !menu_open;
			INTERFACES::Engine->ClientCmd(menu_open ? "cl_mouseenable 0" :
				"cl_mouseenable 1");
			INTERFACES::InputSystem->EnableInput(!menu_open);
		}

		if (UTILS::INPUT::input_handler.GetKeyState(VK_END) & 1)
		{
			menu_hide = !menu_hide;
		}

		//--- Flip Bool Stuff ---//
		if (UTILS::INPUT::input_handler.GetKeyState(86) & 1)
			SETTINGS::settings.flip_bool = !SETTINGS::settings.flip_bool;

		//--- New Menu Rendering System --//
		if (menu_hide)
		{
			//menu is hidden entirely, you can do anything here i guess
		}
		else
		{
			if (menu_open)
			{
				using namespace PPGUI_PP_GUI;

				// if menu not open
				if (!menu_open)
					return;

				DrawMouse();

				SetFont(FONTS::menu_window_font);
				WindowBegin("Internaty", Vector2D(200, 200), Vector2D(700, 500));

				std::vector<std::string> tabs = { "aimbot", "visuals", "misc", "antiaim", "config" };
				std::vector<std::string> aim_mode = { "rage", "legit" };
				std::vector<std::string> acc_mode = { "head", "body", "all" };
				std::vector<std::string> chams_mode = { "none", "visible", "invisible" };
				std::vector<std::string> hitmarker = { "none", "cod", "gamesense", "bameware", "bubble", "roblox", "bhop", "penguware", "keyboard" };
				//std::vector<std::string> clantags = { "none", "interwebz", "aimware", "internaty" };
				std::vector<std::string> aa_mode = { "none", "backwards", "sideways", "backjitter", "lby breaker", "static", "spin" };
				std::vector<std::string> configs = { "awp", "legit", "autos", "scouts", "pistols" };
				std::vector<std::string> box_style = { "none", "full"  };
				std::string config;

				switch (Tab("main", tabs, OBJECT_FLAGS::FLAG_NONE))
				{
				case 0:
				{
					Checkbox("enable aimbot", SETTINGS::settings.aim_bool);
					if (SETTINGS::settings.aim_bool)
					{
						Combobox("aimbot mode", aim_mode, SETTINGS::settings.aim_type);
						if (SETTINGS::settings.aim_type == 0)
						{
					
							Slider("hitchance", 0, 100, SETTINGS::settings.chance_val);
							Slider("minimum damage", 1, 100, SETTINGS::settings.damage_val);
							Combobox("aimbot hitbox", acc_mode, SETTINGS::settings.acc_type);
							Checkbox("auto zeus", SETTINGS::settings.autozeus_bool);
						}
						else
						{
							Checkbox("backtracking", SETTINGS::settings.back_bool);
						}
					//	Checkbox("auto scope", SETTINGS::settings.ascope);
						Checkbox("fakelag fix", SETTINGS::settings.fakefix_bool);
					//	Checkbox("increase points", SETTINGS::settings.multi_bool);
					//	if (SETTINGS::settings.multi_bool)
					//	{
						//	Slider("head scale", 0, 1, SETTINGS::settings.point_val);
							//}
						//Checkbox("quick stop", SETTINGS::settings.stop_bool);
					}
				}
				break;
				case 1:
				{
					Checkbox("enable visuals", SETTINGS::settings.esp_bool);
					if (SETTINGS::settings.esp_bool)
					{
						//Checkbox("draw box", SETTINGS::settings.box_bool);
						Combobox("draw box", box_style, SETTINGS::settings.box_type);
						if (SETTINGS::settings.box_type > 0)
							ColorPicker("box", SETTINGS::settings.box_col);
						Checkbox("draw name", SETTINGS::settings.name_bool);
						Checkbox("draw weapon", SETTINGS::settings.weap_bool);
						//Checkbox("draw penetration", SETTINGS::settings.drp);
						Checkbox("scoped indicator", SETTINGS::settings.scoped);
					//	Checkbox("draw skeleton", SETTINGS::settings.drawskel_bool);
					//	Checkbox("draw enemy circles", SETTINGS::settings.draw_dir);
						Checkbox("draw info", SETTINGS::settings.info_bool);
					//	Checkbox("bomb planted", SETTINGS::settings.bomb);
						Checkbox("resolve mode", SETTINGS::settings.resolvemode);
						Checkbox("draw health", SETTINGS::settings.health_bool);
						Checkbox("draw crosshair", SETTINGS::settings.draw_inc);
						Combobox("colored models", chams_mode, SETTINGS::settings.chams_type);
						if (SETTINGS::settings.chams_type > 0)
							ColorPicker("visible model", SETTINGS::settings.vmodel_col);
						if (SETTINGS::settings.chams_type > 1)
							ColorPicker("invisible model", SETTINGS::settings.imodel_col);
					//	Checkbox("night mode", SETTINGS::settings.night_bool);
						Checkbox("fov arrows", SETTINGS::settings.fov_arrow);
						Checkbox("bullet tracers", SETTINGS::settings.beam_bool);
						Checkbox("thirdperson", SETTINGS::settings.tp_bool);
					}
				}
				break;
				case 2:
				{
					Checkbox("enable misc", SETTINGS::settings.misc_bool);
					if (SETTINGS::settings.misc_bool)
					{
						Checkbox("auto bunnyhop", SETTINGS::settings.bhop_bool);
						Checkbox("auto strafer", SETTINGS::settings.strafe_bool);
						Combobox("hitmarker", hitmarker, SETTINGS::settings.hitmarker);
					//	Combobox("clantag", clantags, SETTINGS::settings.clantag);
					
						Checkbox("fakelag", SETTINGS::settings.lag_bool);
						//Slider("standing lag", 1, 15, SETTINGS::settings.stand_lag);
						Slider("moving lag", 1, 15, SETTINGS::settings.move_lag);
						Slider("jumping lag", 1, 15, SETTINGS::settings.jump_lag);
					}
				}
				break;
				case 3:
				{
					Checkbox("enable antiaim", SETTINGS::settings.aa_bool);
					if (SETTINGS::settings.aa_bool)
					{
						if (SETTINGS::settings.aa_bool)
							Combobox("antiaim type", aa_mode, SETTINGS::settings.aa_type);
							
						if (SETTINGS::settings.aa_type == 4)
							Slider("delta", 0, 180, SETTINGS::settings.delta_val);
						//if (SETTINGS::settings.aa_type == 4 || SETTINGS::settings.aa_type == 2)
						//Combobox("flip key", KeyStrings, SETTINGS::settings.flip_key);
						 // Checkbox("freestand", SETTINGS::settings.lby);
						//	Checkbox("anti 1tap", SETTINGS::settings.backwards);
					}
				}
				break;
				case 4:
				{
					switch (Combobox("config", configs, SETTINGS::settings.config_sel))
					{
					case 0: config = "default"; break;
					case 1: config = "legit"; break;
					case 2: config = "auto_hvh"; break;
					case 3: config = "scout_hvh"; break;
					case 4: config = "pistol_hvh"; break;
					
					}
					
					
			
					if (Button("Load"))
						SETTINGS::settings.Load(config);
					if (Button("Save"))
						SETTINGS::settings.Save(config);
					

					//Checkbox("debug", SETTINGS::settings.debug_bool);

					//ColorPicker("menu theme", SETTINGS::settings.menu_col);
				}
				break;
				}

				WindowEnd();


/*				//--- Bools and Binds ---//
				if (UTILS::INPUT::input_handler.GetKeyState(97) & 1)
					bhop_bool = !bhop_bool;

				if (UTILS::INPUT::input_handler.GetKeyState(98) & 1)
					strafe_bool = !strafe_bool;

				if (UTILS::INPUT::input_handler.GetKeyState(99) & 1)
					esp_bool = !esp_bool;

				if (UTILS::INPUT::input_handler.GetKeyState(100) & 1)
				{
					chams_type++;
					if (chams_type == 3)
					{
						chams_type = 0;
					}
				}

				if (UTILS::INPUT::input_handler.GetKeyState(101) & 1)
				{
					xhair_type++;
					if (xhair_type == 3)
					{
						xhair_type = 0;
					}
				}

				if (UTILS::INPUT::input_handler.GetKeyState(102) & 1)
					tp_bool = !tp_bool;

				if (UTILS::INPUT::input_handler.GetKeyState(103) & 1)
				{
					aim_type++;
					if (aim_type == 3)
					{
						aim_type = 0;
					}
				}

				if (UTILS::INPUT::input_handler.GetKeyState(104) & 1)
					aa_bool = !aa_bool;

				if (UTILS::INPUT::input_handler.GetKeyState(105) & 1)
				{
					aa_type++;
					if (aa_type == 6)
					{
						aa_type = 0;
					}
				}

				if (UTILS::INPUT::input_handler.GetKeyState(38) & 1)
				{
					acc_type++;
					if (acc_type == 2)
					{
						acc_type = 0;
					}
				}

				//--- Screen Positioning ---//
				int screen_x;
				int screen_y;
				INTERFACES::Engine->GetScreenSize(screen_x, screen_y);
				screen_x /= 2; screen_y /= 2;

				//--- Feature Defenition ---//
				RENDER::DrawWF(228, 24, FONTS::numpad_menu_font, CColor(255, 255, 255, 255), L"[\u25bc]");
				RENDER::DrawF(256, 24, FONTS::numpad_menu_font, false, false, CColor(140, 140, 140, 255), "stackhack framework"); //255, 5, 210
				RENDER::DrawF(380, 24, FONTS::numpad_menu_font, false, false, CColor(240, 25, 255, 255), "beta");
				RENDER::DrawF(256, 54, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "bunnyhop:");
				RENDER::DrawF(256, 70, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "autostrafer:");
				RENDER::DrawF(256, 86, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "player esp:");
				RENDER::DrawF(256, 102, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "player chams:");
				RENDER::DrawF(256, 118, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "crosshair:");
				RENDER::DrawF(256, 134, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "thirdperson:");
				RENDER::DrawF(256, 150, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "aimbot:");
				RENDER::DrawF(256, 166, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "anti-aimbot:");
				RENDER::DrawF(256, 182, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "anti-aimbot mode:");
				RENDER::DrawF(256, 198, FONTS::numpad_menu_font, false, false, CColor(255, 255, 255, 255), "accuracy:");

				//--- Feature Notification ---//
				if (bhop_bool)
					RENDER::DrawF(366, 54, FONTS::numpad_menu_font, false, false, CColor(0, 255, 0, 255), "[+]"); //346
				else
					RENDER::DrawF(366, 54, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "[-]");

				if (strafe_bool)
					RENDER::DrawF(366, 70, FONTS::numpad_menu_font, false, false, CColor(0, 255, 0, 255), "[+]");
				else
					RENDER::DrawF(366, 70, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "[-]");

				if (esp_bool)
					RENDER::DrawF(366, 86, FONTS::numpad_menu_font, false, false, CColor(0, 255, 0, 255), "[+]");
				else
					RENDER::DrawF(366, 86, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "[-]");

				if (chams_type == 0)
					RENDER::DrawF(366, 102, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "none");
				if (chams_type == 1)
					RENDER::DrawF(366, 102, FONTS::numpad_menu_font, false, false, CColor(0, 255, 0, 255), "visible");
				if (chams_type == 2)
					RENDER::DrawF(366, 102, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "ignore_z");

				if (xhair_type == 0)
					RENDER::DrawF(366, 118, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "none");
				if (xhair_type == 1)
					RENDER::DrawF(366, 118, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "static");
				if (xhair_type == 2)
					RENDER::DrawF(366, 118, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "recoil");
				//if (xhair_type == 3)
					//RENDER::DrawF(366, 118, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "spread");
				//if (xhair_type == 4)
					//RENDER::DrawF(366, 118, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "both");

				if (tp_bool)
					RENDER::DrawF(366, 134, FONTS::numpad_menu_font, false, false, CColor(0, 255, 0, 255), "[+]");
				else
					RENDER::DrawF(366, 134, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "[-]");

				if (aim_type == 0)
					RENDER::DrawF(366, 150, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "off");
				if (aim_type == 1)
					RENDER::DrawF(366, 150, FONTS::numpad_menu_font, false, false, CColor(0, 255, 0, 255), "legit");
				if (aim_type == 2)
					RENDER::DrawF(366, 150, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "hvh");

				if (aa_bool)
					RENDER::DrawF(366, 166, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "[+]");
				else
					RENDER::DrawF(366, 166, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "[-]");

				if (aa_type == 0)
					RENDER::DrawF(366, 182, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "none");
				if (aa_type == 1)
					RENDER::DrawF(366, 182, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "backwards");
				if (aa_type == 2)
					RENDER::DrawF(366, 182, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "sideways");
				if (aa_type == 3)
					RENDER::DrawF(366, 182, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "backjitter");
				if (aa_type == 4)
					RENDER::DrawF(366, 182, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "lowerbody");
				if (aa_type == 5)
					RENDER::DrawF(366, 182, FONTS::numpad_menu_font, false, false, CColor(255, 255, 0, 255), "legit troll");

				if (acc_type == 0)
					RENDER::DrawF(366, 198, FONTS::numpad_menu_font, false, false, CColor(255, 0, 0, 255), "head only");
				if (acc_type == 1)
					RENDER::DrawF(366, 198, FONTS::numpad_menu_font, false, false, CColor(0, 255, 0, 255), "hitbox scan");

					*/
				/*int w, h;
				static int x, y;

				INTERFACES::Engine->GetScreenSize(w, h);
				static bool init = false;
				if (init == false) {
					x = w / 2 - (400 / 2);
					y = h / 2 - (200 / 2);
					init = true;
				}

				RENDER::DrawFilledRect(x - 6, y - 6, x + 406, y + 201, CColor(0, 0, 0));
				RENDER::DrawFilledRect(x - 5, y - 5, x + 405, y + 200, CColor(60, 60, 60));
				RENDER::DrawFilledRect(x, y, x + 400, y + 195, CColor(40, 40, 40));

				Components::Start();
				Components::Checkbox("bhop", &bhop_bool, x, y + 5);
				Components::Checkbox("autostrafe", &strafe_bool, x, y + 5 + 17);
				Components::Checkbox("player esp", &esp_bool, x, y + 5 + 17 * 2);
				const char* chams[] = { "none", "visible", "ignorez" };
				Components::Combo("player chams", &chams_type, chams, 3, x, y + 5 + 17 * 3);
				const char* crosshair[] = { "none", "static", "recoil" };
				Components::Combo("crosshair", &xhair_type, crosshair, 3, x, y + 5 + 17 * 4);
				Components::Checkbox("thirdperson", &tp_bool, x, y + 5 + 17 * 5);
				const char* aimbot[] = { "off", "legit", "rage" };
				Components::Combo("aimbot", &aim_type, aimbot, 3, x, y + 5 + 17 * 6);
				Components::Checkbox("antiaim", &aa_bool, x, y + 5 + 17 * 7);
				const char* antiaim[] = { "none", "backwards", "sideways", "backjitter", "lowerbody", "legit troll" };
				Components::Combo("antiaim type", &aa_type, antiaim, 6, x, y + 5 + 17 * 8);
				Components::Checkbox("fake ping", &up_bool, x, y + 5 + 17 * 9);
				const char* accuracy[] = { "head only", "hitscan" };
				Components::Combo("target", &acc_type, accuracy, 2, x, y + 5 + 17 * 10);

				PPGUI_PP_GUI::DrawMouse();*/
			}
			else
			{
				//RENDER::DrawWF(228, 24, FONTS::numpad_menu_font, CColor(255, 255, 255, 255), L"[\u25b2]");
				//RENDER::DrawF(256, 24, FONTS::numpad_menu_font, false, false, CColor(140, 140, 140, 255), "stackhack framework");
				//RENDER::DrawF(380, 24, FONTS::numpad_menu_font, false, false, CColor(240, 25, 255, 255), "beta");
			}
		}





		//using namespace PPGUI_PP_GUI;

		//static bool menu_open = false;
		//if (UTILS::INPUT::input_handler.GetKeyState(VK_INSERT) & 1)
		//{
		//	menu_open = !menu_open;
		//	INTERFACES::Engine->ClientCmd(menu_open ? "cl_mouseenable 0" : 
		//		"cl_mouseenable 1");
		//	INTERFACES::InputSystem->EnableInput(!menu_open);
		//}

		//// if menu not open
		//if (!menu_open)
		//	return;

		//DrawMouse();

		//SetFont(FONTS::menu_window_font);
		//WindowBegin("Pener SDK", Vector2D(200, 200), Vector2D(700, 500));

		//Checkbox("OOGA WOOGA BOOGA NIGGA");
		//Button("OOGA HOOGA BOOGA JOOGA");

		//WindowEnd();
	}
}