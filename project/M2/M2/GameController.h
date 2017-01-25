#pragma once
#include "Controller.h"


namespace M2
{
	class CGameData;
	class CGameView;
	class CGameSceneView;
	class CMenuController;
	class CGameController :
		public CController
	{
	public:
		CGameController(bool _isNewGame);
		~CGameController();

	public:
		static bool isNewGame;

		CGameView *m_pGameView = nullptr;
		CGameData *m_pGameData = nullptr;

		void ViewDidLoad() override;
		void DidReceiveKeyboardEvent(const INPUT_RECORD _keyMessage);
		void ArchiveNow();


		void PressUpKey();
		void PressDownKey();
		void PressLeftKey();
		void PressRightKey();
		void PressESCKey();


		bool m_canReceiveKeyboardEvent = false;
		bool m_isRestart = false;
		UINT m_onSecondTimerID = 0;
		static void CALLBACK OneSecondEvent(UINT uID,
			UINT uMsg,
			DWORD dwUser,
			DWORD dw1,
			DWORD dw2);
		static CGameController* Self;
		CGameData* LoadMainGameViewData();
		CGameSceneView* LoadGameScene();

	private:
	};
}


