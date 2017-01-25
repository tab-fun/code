#pragma once
#include "ZView.h"

namespace M2
{
	class CGameData;
	class CGameView :
		public CZView
	{
	public:
		CGameView();
		~CGameView();

	public:

		CGameController *m_pDelegate = nullptr;
		CGameData* m_gameData = nullptr;

		void LoadData() override;
		void Draw() override;
	};

}

