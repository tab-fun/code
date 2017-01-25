#pragma once

namespace M2
{

#define SetFrameRate(_frame) (CMainController::dwFrame = _frame)
#define GetFrameRate (1000LU / CMainController::dwFrame)

#ifdef UNICODE
#define String_ std::wstring
#define To_string std::to_wstring
#define Char wchar_t
#else
#define String std::string
#define To_string std::to_string
#define Char char
#endif // !UNICODE

#define DOCUMENT_NAME "EvolutionOfButterflies.xml"



#pragma once
#include <wincon.h>


#define CONSOLE_DEFAULT_TITLE "进化蝴蝶"
#define MENU_TITLE "主菜单"
#define GAME_HELP "游戏帮助"
#define GAME_ABOUT "关于游戏"
#define GAME_SETTING "设置"

#define GAME_STATE_RUN "游戏中"
#define GAME_STATE_RUN "暂停"

#define MENU_ITEM_TITLE_ContinueGame "继续游戏"
#define MENU_ITEM_TITLE_StartGame "开始游戏"
#define MENU_ITEM_TITLE_GameSetting "游戏设置"
#define MENU_ITEM_TITLE_GameHelp "游戏帮助"
#define MENU_ITEM_TITLE_QuitGame "退出游戏"
#define MENU_ITEM_TITLE_MainMenu "主菜单"
#define MENU_ITEM_TITLE_HowToPlay "游戏玩法"
#define MENU_ITEM_TITLE_AboutGame "关于游戏"
#define MENU_ITEM_TITLE_DifficultySetting "设置难度"
#define MENU_ITEM_TITLE_ArchiveSetting "设置存档"
#define MENU_ITEM_TITLE_Simple "简简单单"
#define MENU_ITEM_TITLE_General "普普通通"
#define MENU_ITEM_TITLE_Hard "困难之极"
#define MENU_ITEM_TITLE_InitCurrentArchive "当前存档归零"
#define MENU_ITEM_TITLE_InitArchives "所有存档归零"
#define MENU_ITEM_TITLE_ModificationArchivesName "修改存档名字"

#define GAME_VIEW_TITLE_MainGameView "游戏主视图"

#define TIMER_INTERVAL_SEC 1000

#ifdef UNICODE
#define String_ wstring
#else
#define String_ string
#endif

		/*
		┏┳┓┫┛┻┗┣╋━┃
		*/

		struct Point
		{
			int x;
			int y;
		};
		// 定义尺寸：宽、高
		struct Size
		{
			int width;
			int height;
		};

		//bool operator!=(Rect &_rect, Rect &_rect1);
		// 此类定义了一个矩形:
		//     左上角坐标和尺寸
		struct Rect
		{
			Point point;
			Size size;
			bool IsCrossde(const Rect *_rect, bool _isOnlyCompareLeftPoint = false);
		};

		bool operator!=(const Rect &_rect, const Rect &_rect1);
		bool operator==(const Rect &_rect, const Rect &_rect1);

		// 此枚举定义了一些颜色
		enum Color : int
		{
			black = 0,// 黑色

			Foreground_blue = FOREGROUND_BLUE,            // 前景色：蓝色
			Foreground_green = FOREGROUND_GREEN,          // 前景色：绿色
			Foreground_red = FOREGROUND_RED,              // 前景色：红色
			Foreground_intensity = FOREGROUND_INTENSITY,  // 前景色：灰色或加强色

			Foreground_brightBlue = Foreground_blue | Foreground_intensity, // 前景色：
			Foreground_brightRed = Foreground_red | Foreground_intensity, // 前景色：亮红色
			Foreground_brightGreen = Foreground_green | Foreground_intensity, // 前景色：亮绿色

			Foreground_white = Foreground_blue | Foreground_green | Foreground_red | Foreground_intensity, // 前景色：白色
			Foreground_yellow = Foreground_green | Foreground_red | Foreground_intensity,                  // 前景色：黄色
			Foreground_purple = Foreground_blue | Foreground_red | Foreground_intensity,                   // 前景色：紫色
			Foreground_cyan = Foreground_blue | Foreground_green | Foreground_intensity,                   // 前景色：亮青色
			Foreground_gray = Foreground_intensity,                                                        // 前景色：灰色

			Foreground_darkWhite = Foreground_blue | Foreground_green | Foreground_red, // 前景色：暗白色
			Foreground_darkYellow = Foreground_green | Foreground_red,                  // 前景色：暗黄色
			Foreground_darkPurple = Foreground_blue | Foreground_red,                   // 前景色：暗紫色
			Foreground_darkGreen = Foreground_blue | Foreground_green,                  // 前景色：暗青色


			Background_blue = BACKGROUND_BLUE ,           // 背景色：蓝色 
			Background_green = BACKGROUND_GREEN,         // 背景色：绿色
			Background_red = BACKGROUND_RED,             // 背景色：红色
			Background_intensity = BACKGROUND_INTENSITY, // 背景色：灰色或加强色

			Background_brightBlue = Background_blue | Background_intensity,   // 背景色：亮蓝色
			Background_brightRed = Background_red | Background_intensity,     // 背景色：亮红色
			Background_brightGreen = Background_green | Background_intensity, // 背景色：亮绿色

			Background_white = Background_blue | Background_green | Background_red | Background_intensity, // 背景色：白色
			Background_yellow = Background_green | Background_red | Background_intensity,                  // 背景色：黄色
			Background_purple = Background_blue | Background_red | Background_intensity,                   // 背景色：紫色
			Background_brightCyan = Background_green | Background_blue | Background_intensity,             // 背景色：亮青色
			Background_gray = Background_intensity,                                                        // 背景色：灰色

			Background_darkWhite = Background_blue | Background_green | Background_red, // 背景色：暗白色
			Background_darkYellow = Background_red | Background_green,                  // 背景色：暗黄色
			Background_darkPurple = Background_blue | Background_red,                   // 背景色：暗紫色
			Background_darkCyan = Background_green | Background_blue,                   // 背景色：暗青色
		};

		enum Priority
		{
			Priority_default,// 默认优先级 地图、背景
			Priority_low,    // 低优先级   
			Priority_medium, // 中优先级   
			Priority_higher, // 高优先级   
			Priority_highest // 最高优先级 边框、固定文本、玩家
		};

		enum class DifficultyEnum
		{
			Simple,
			General,
			Hard
		};
		enum class DirectionEnum
		{
			Up,
			Down,
			Left,
			Right,
			UnKnown
		};

		typedef WORD SceneID;
		class CZView;
		struct Ammunition
		{
			Point point;
			CZView *m_owner;
			DirectionEnum m_direction;
		}; 
	

		struct CMapRectItem
		{
			DirectionEnum m_direction = DirectionEnum::UnKnown;
			Rect m_rect;
			int m_type;
			int m_sceneID;
			WORD m_backgroundFillColor;
			string m_fillTextString;
			list<Ammunition> m_ammunitionList;
			bool m_isDestroyed = false;
			bool IsCollided(CMapRectItem *_item, bool _isSceneID2 = false);
			bool IsCollided(Point &_item);
		};

		struct fps_limit {

			int previous_time;
			int tpf_limit;
			int tpf;
			fps_limit(int fps = 60) : previous_time(GetTickCount()), tpf(0) {
				limit_fps(fps);
			}
			void reset() {
				previous_time = GetTickCount(),
					tpf = 0;
				tpf_limit = 60;
			}
			void limit_fps(int fps) {
				tpf_limit = (int)(1000.0f / (float)fps);
			}
			void delay() {
				tpf = GetTickCount() - previous_time;

				if (tpf < tpf_limit)
					Sleep(tpf_limit - tpf - 1);

				previous_time = GetTickCount();
			}
		};
}