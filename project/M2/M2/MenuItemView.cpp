#include "stdafx.h"
#include "MenuItemView.h"

namespace M2
{
	CMenuItemView::CMenuItemView()
	{
	}


	CMenuItemView::~CMenuItemView()
	{
		OutputDebugString(_T(">>>>>> CMenuItemView::~CMenuItemView()���˵�����ͼ�������ˣ�\n"));
	}

	void CMenuItemView::Draw()
	{
		CZView::Draw();

		COORD coord;
		coord.X = m_rect.point.x + m_rect.size.width / 2 - m_title.length() / 2;
		coord.Y = m_rect.point.y + 1;

		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), m_backgroundFillColor | black);
		WriteConsoleA(GetConsoleOutputHandle(), m_title.c_str(), m_title.length(), nullptr, nullptr);
	}
}

