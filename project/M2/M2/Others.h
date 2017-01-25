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


#define CONSOLE_DEFAULT_TITLE "��������"
#define MENU_TITLE "���˵�"
#define GAME_HELP "��Ϸ����"
#define GAME_ABOUT "������Ϸ"
#define GAME_SETTING "����"

#define GAME_STATE_RUN "��Ϸ��"
#define GAME_STATE_RUN "��ͣ"

#define MENU_ITEM_TITLE_ContinueGame "������Ϸ"
#define MENU_ITEM_TITLE_StartGame "��ʼ��Ϸ"
#define MENU_ITEM_TITLE_GameSetting "��Ϸ����"
#define MENU_ITEM_TITLE_GameHelp "��Ϸ����"
#define MENU_ITEM_TITLE_QuitGame "�˳���Ϸ"
#define MENU_ITEM_TITLE_MainMenu "���˵�"
#define MENU_ITEM_TITLE_HowToPlay "��Ϸ�淨"
#define MENU_ITEM_TITLE_AboutGame "������Ϸ"
#define MENU_ITEM_TITLE_DifficultySetting "�����Ѷ�"
#define MENU_ITEM_TITLE_ArchiveSetting "���ô浵"
#define MENU_ITEM_TITLE_Simple "��򵥵�"
#define MENU_ITEM_TITLE_General "����ͨͨ"
#define MENU_ITEM_TITLE_Hard "����֮��"
#define MENU_ITEM_TITLE_InitCurrentArchive "��ǰ�浵����"
#define MENU_ITEM_TITLE_InitArchives "���д浵����"
#define MENU_ITEM_TITLE_ModificationArchivesName "�޸Ĵ浵����"

#define GAME_VIEW_TITLE_MainGameView "��Ϸ����ͼ"

#define TIMER_INTERVAL_SEC 1000

#ifdef UNICODE
#define String_ wstring
#else
#define String_ string
#endif

		/*
		���ש��ϩ��ߩ��ǩ贈��
		*/

		struct Point
		{
			int x;
			int y;
		};
		// ����ߴ磺����
		struct Size
		{
			int width;
			int height;
		};

		//bool operator!=(Rect &_rect, Rect &_rect1);
		// ���ඨ����һ������:
		//     ���Ͻ�����ͳߴ�
		struct Rect
		{
			Point point;
			Size size;
			bool IsCrossde(const Rect *_rect, bool _isOnlyCompareLeftPoint = false);
		};

		bool operator!=(const Rect &_rect, const Rect &_rect1);
		bool operator==(const Rect &_rect, const Rect &_rect1);

		// ��ö�ٶ�����һЩ��ɫ
		enum Color : int
		{
			black = 0,// ��ɫ

			Foreground_blue = FOREGROUND_BLUE,            // ǰ��ɫ����ɫ
			Foreground_green = FOREGROUND_GREEN,          // ǰ��ɫ����ɫ
			Foreground_red = FOREGROUND_RED,              // ǰ��ɫ����ɫ
			Foreground_intensity = FOREGROUND_INTENSITY,  // ǰ��ɫ����ɫ���ǿɫ

			Foreground_brightBlue = Foreground_blue | Foreground_intensity, // ǰ��ɫ��
			Foreground_brightRed = Foreground_red | Foreground_intensity, // ǰ��ɫ������ɫ
			Foreground_brightGreen = Foreground_green | Foreground_intensity, // ǰ��ɫ������ɫ

			Foreground_white = Foreground_blue | Foreground_green | Foreground_red | Foreground_intensity, // ǰ��ɫ����ɫ
			Foreground_yellow = Foreground_green | Foreground_red | Foreground_intensity,                  // ǰ��ɫ����ɫ
			Foreground_purple = Foreground_blue | Foreground_red | Foreground_intensity,                   // ǰ��ɫ����ɫ
			Foreground_cyan = Foreground_blue | Foreground_green | Foreground_intensity,                   // ǰ��ɫ������ɫ
			Foreground_gray = Foreground_intensity,                                                        // ǰ��ɫ����ɫ

			Foreground_darkWhite = Foreground_blue | Foreground_green | Foreground_red, // ǰ��ɫ������ɫ
			Foreground_darkYellow = Foreground_green | Foreground_red,                  // ǰ��ɫ������ɫ
			Foreground_darkPurple = Foreground_blue | Foreground_red,                   // ǰ��ɫ������ɫ
			Foreground_darkGreen = Foreground_blue | Foreground_green,                  // ǰ��ɫ������ɫ


			Background_blue = BACKGROUND_BLUE ,           // ����ɫ����ɫ 
			Background_green = BACKGROUND_GREEN,         // ����ɫ����ɫ
			Background_red = BACKGROUND_RED,             // ����ɫ����ɫ
			Background_intensity = BACKGROUND_INTENSITY, // ����ɫ����ɫ���ǿɫ

			Background_brightBlue = Background_blue | Background_intensity,   // ����ɫ������ɫ
			Background_brightRed = Background_red | Background_intensity,     // ����ɫ������ɫ
			Background_brightGreen = Background_green | Background_intensity, // ����ɫ������ɫ

			Background_white = Background_blue | Background_green | Background_red | Background_intensity, // ����ɫ����ɫ
			Background_yellow = Background_green | Background_red | Background_intensity,                  // ����ɫ����ɫ
			Background_purple = Background_blue | Background_red | Background_intensity,                   // ����ɫ����ɫ
			Background_brightCyan = Background_green | Background_blue | Background_intensity,             // ����ɫ������ɫ
			Background_gray = Background_intensity,                                                        // ����ɫ����ɫ

			Background_darkWhite = Background_blue | Background_green | Background_red, // ����ɫ������ɫ
			Background_darkYellow = Background_red | Background_green,                  // ����ɫ������ɫ
			Background_darkPurple = Background_blue | Background_red,                   // ����ɫ������ɫ
			Background_darkCyan = Background_green | Background_blue,                   // ����ɫ������ɫ
		};

		enum Priority
		{
			Priority_default,// Ĭ�����ȼ� ��ͼ������
			Priority_low,    // �����ȼ�   
			Priority_medium, // �����ȼ�   
			Priority_higher, // �����ȼ�   
			Priority_highest // ������ȼ� �߿򡢹̶��ı������
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