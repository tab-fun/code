#include "stdafx.h"
#include "ZView.h"


namespace M2
{
	CZView::~CZView()
	{
		RemoveSubviews();
	}
	void CZView::AddSubview(CZView *_view)
	{
		bool isExist = false;
		for (auto view : m_subviewsList)
		{
			if (view == _view)
				isExist = true;
		}

		if (!isExist)
		{
			m_subviewsList.push_back(_view);
		}
	}
	void CZView::RemoveView(CZView *_view)
	{
		bool isExist = false;
		auto b = m_subviewsList.begin();
		for (; b != m_subviewsList.end(); ++b)
		{
			if (*b == _view)
			{
				isExist = true;
				break;
			}
		}

		if (isExist)
		{
			delete _view;
			m_subviewsList.erase(b);
		}
	}
	void CZView::RemoveSubviews()
	{
		for (auto &p : m_subviewsList)
		{
			if (p)
			{
				delete p;
				p = nullptr;
			}
		}

		m_subviewsList.clear();
	}

	void CZView::Draw()
	{
		if (!m_isDisplay)
		{
			return;
		}
		// 填充背景
		DWORD written;
		for (SHORT y = m_rect.point.y; y < m_rect.size.height + m_rect.point.y; y++)
		{
			for (SHORT x = m_rect.point.x; x < m_rect.size.width + m_rect.point.x; x++)
			{
				bool canDraw = true;
				for (auto pView : m_subviewsList)
				{
					if (pView)
					{
						if ((x >= pView->m_rect.point.x && x < pView->m_rect.point.x + pView->m_rect.size.width) && (y >= pView->m_rect.point.y && y < pView->m_rect.point.y + pView->m_rect.size.height))
						{
							canDraw = false;
							break;
						}
					}
				}
				if (canDraw)
				{
					FillConsoleOutputAttribute(GetConsoleOutputHandle(), m_backgroundFillColor, 1, { x,y }, &written);
				}
			}
		}

		//// 绘制文本
		//map<int, list<CData>> map;
		//for (auto data : m_screenDataList)
		//	map[data.m_priority].push_back(data);

		//for (auto pair : map)
		//{
		//	for (auto data : pair.second)
		//	{
		//		SetConsoleCursorPosition(GetConsoleOutputHandle(), data.m_cursorPosition);
		//		SetConsoleTextAttribute(GetConsoleOutputHandle(), data.m_textColor);
		//		WriteConsole(GetConsoleOutputHandle(), data.m_textString.c_str(), data.m_textString.length(), nullptr, nullptr);
		//
		//	}
		//}


		if (m_isHaveBorder)
		{
			DrawBorder();
		}

		// 绘制子视图
		for (auto pView : m_subviewsList)
			pView->Draw();
	}

	void CZView::DrawBorder()
	{
		for (SHORT y = m_rect.point.y; y < m_rect.size.height + m_rect.point.y; y++)
		{
			String_ str;
			if (y == m_rect.point.y)
			{
				str = _T("┏");
			}
			else if (y == m_rect.size.height + m_rect.point.y - 1)
			{
				str = _T("┗");
			}
			else
			{
				str = _T("┃");
				COORD coord;
				coord.X = m_rect.point.x;
				coord.Y = y;
				
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				SetConsoleTextAttribute(GetConsoleOutputHandle(), m_borderColor);
				WriteConsole(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
				str = _T("");
			}
			for (SHORT x = 0; x < (m_rect.size.width) / 2 - 2; x++)
			{
				if (y == m_rect.point.y || y == m_rect.size.height + m_rect.point.y - 1)
				{
					str += _T("━");
				}
			}
			if (y == m_rect.point.y)
			{
				str += _T("┓");
			}
			else if (y == m_rect.size.height + m_rect.point.y - 1)
			{
				str += _T("┛");
			}
			else
			{
				str += _T("┃");
				COORD coord;
				coord.X = m_rect.point.x + m_rect.size.width - 2;
				coord.Y = y;
				
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				SetConsoleTextAttribute(GetConsoleOutputHandle(), m_borderColor);
				WriteConsole(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
				continue;
			}
			COORD coord;
			coord.X = m_rect.point.x;
			coord.Y = y;
			
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			SetConsoleTextAttribute(GetConsoleOutputHandle(), m_borderColor);
			WriteConsole(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
		}
	}
}