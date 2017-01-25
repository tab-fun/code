#pragma once
#include "ZView.h"

namespace M2
{
	class MenuDataSourceInterface;
	class CMenuView :
		public CZView
	{
	public:
		CMenuView();
		~CMenuView();
		MenuDataSourceInterface *m_pDelegate = nullptr;
		void LoadData() override;
		void Draw() override;

		vector<vector<string>> m_looks;
	};
}


