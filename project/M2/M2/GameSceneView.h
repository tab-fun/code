#pragma once
#include "ZView.h"

namespace M2
{
	class CGameData;
	class CGameController;
	class CGameSceneView :
		public CZView
	{

	public:
		CGameSceneView();
		~CGameSceneView();
		void *data = nullptr;
		CGameData *m_gameData = nullptr;
		CGameController *m_pDelegate = nullptr;
		void Draw() override;
	};

}
