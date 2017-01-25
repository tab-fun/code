#include "stdafx.h"
#include "GameItemView.h"

namespace M2
{
	CGameItemView::CGameItemView()
	{
		OutputDebugString(_T(">>>>>> CGameItemView::CGameItemView(): 游戏窗口已经被创建了！\n"));
	}


	CGameItemView::~CGameItemView()
	{
		OutputDebugString(_T(">>>>>> CGameItemView::~CGameItemView(): 游戏窗口已经被销毁了！\n"));
	}

	void CGameItemView::Draw()
	{
		CZView::Draw();

		if (m_title == "友好提示" && m_isDisplay)
		{
			string s = m_text;
			COORD coord;
			coord.X = m_rect.point.x + m_rect.size.width / 2 - m_title.length()-2;
			coord.Y = m_rect.point.y + m_rect.size.height / 2;

			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			SetConsoleTextAttribute(GetConsoleOutputHandle(), m_backgroundFillColor | Color::Foreground_yellow);
			WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);

		}
	}

	void CGameItemView::LoadData()
	{
		if (m_title == "游戏窗口视图")
		{
			auto view = m_pDelegate->LoadGameScene();
			if (view)
			{
				AddSubview(view);
			}
		}
	}
}
