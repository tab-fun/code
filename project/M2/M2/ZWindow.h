#pragma once
#include "ZView.h"

namespace M2
{
	class CMainController;
	class WindowDataSourceInterface;
	class CZWindow :
		public CZView
	{
	public:
		
		HANDLE m_hBuffer = nullptr;
		HANDLE m_hBuffer_1 = nullptr;

	public:
		CZWindow();
		~CZWindow();
		WindowDataSourceInterface *m_pDelegate;
		void LoadData();
		void Draw() override;

	private:
		Rect m_previousRect;
	};
}


