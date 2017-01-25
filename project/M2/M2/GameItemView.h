#pragma once
#include "ZView.h"

namespace M2
{
	class CGameData;
	class CGameItemView :
		public CZView
	{
	public:
		CGameItemView();
		~CGameItemView();

		CGameController *m_pDelegate = nullptr;
		void LoadData() override;
		void Draw() override;
	};
}