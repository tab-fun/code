#pragma once
#include "Controller.h"
#include "WindowDataSourceInterface.h"
#include "WindowData.h"
#include "MenuController.h"

namespace M2
{
	class CZWindow;
	class CWindowData;
	class CMainController :
		public CController,public WindowDataSourceInterface
	{
	private:

	public:
		static CMainController *pMainController;
		static CMainController *Instance();
		static DWORD dwFrame;

		static int CreateMainController(int _argc, char **_argv);
		
		static void HandleKeyboardEvent(const INPUT_RECORD _keyMessag);
		static bool isHaveNewEventMessage;
		static INPUT_RECORD keyMessage;

		static void HandleArchive(DWORD _dwFrequency);


	public:
		CMainController();
		~CMainController();

	public:
		CZWindow *m_pWindow;
		CMenuController *m_pMenuController;
		DWORD m_time = 0;
		bool m_isQuit = false;
		bool _isCreatedKeyThead = false;
		bool _isReceiveKeyboardEvent = false;
		DWORD _threadID;
		HANDLE _keyTheardHandle = nullptr;

		CWindowData LoadWindowData() override;
		void ViewDidLoad() override;

		void UpdatingScreen();
	};
}
