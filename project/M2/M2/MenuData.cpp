#include "stdafx.h"
#include "MenuData.h"


namespace M2
{
	CMenuData::CMenuData(CData _data)
	{

	}
	CMenuData::CMenuData()
	{
		//m_title = "主菜单";
		//auto windowRect = CMainController::Instance()->m_windowData->m_windowRect;
		//Size size;
		//size.width = windowRect.size.width * 0.618;
		//size.height = windowRect.size.height * 0.618;

		//if (size.width % 2 != 0)
		//	size.width--;
		//if (size.height % 2 != 0)
		//	size.height--;

		//Point point;
		//point.x = windowRect.size.width / 2 - size.width / 2;
		//point.y = windowRect.size.height / 2 - size.height / 2;
		//m_rect = { point,size };
		//m_backgroundFillColor = Color::Background_white;

		//// 边框
		//MakeBoxData(point, size);

		//// 菜单项
		//for (size_t i = 0; i < 6; i++)
		//{
		//	m_menuItemsDataVec.push_back(CData());
		//}
		//m_menuItemsDataVec[0].m_textString = _T("继续游戏");
		//m_menuItemsDataVec[1].m_textString = _T("重新开始游戏");
		//m_menuItemsDataVec[2].m_textString = _T("游戏设置");
		//m_menuItemsDataVec[3].m_textString = _T("游戏帮助");
		//m_menuItemsDataVec[4].m_textString = _T("关于游戏");
		//m_menuItemsDataVec[5].m_textString = _T("退出游戏");
	}

	void CMenuData::MakeBoxData(Point point, Size size)
	{
		for (SHORT y = point.y; y < size.height + point.y; y++)
		{
			CData data;
			if (y == point.y)
			{
				data.m_textString = _T("┏");
			}
			else if (y == size.height + point.y - 1)
			{
				data.m_textString = _T("┗");
			}
			else
			{
				data.m_textString = _T("┃");
				COORD coord;
				coord.X = point.x;
				coord.Y = y;
				data.m_cursorPosition = coord;
				data.m_priority = Priority::Priority_highest;
				m_screenDataList.push_back(data);
				data.m_textString = _T("");
			}
			for (SHORT x = 0; x < (size.width) / 2 - 2; x++)
			{
				if (y == point.y || y == size.height + point.y - 1)
				{
					data.m_textString += _T("━");
				}
			}
			if (y == point.y)
			{
				data.m_textString += _T("┓");
			}
			else if (y == size.height + point.y - 1)
			{
				data.m_textString += _T("┛");
			}
			else
			{
				data.m_textString += _T("┃");
				COORD coord;
				coord.X = point.x + size.width - 2;
				coord.Y = y;
				data.m_cursorPosition = coord;
				data.m_priority = Priority::Priority_highest;
				m_screenDataList.push_back(data);
				continue;
			}
			COORD coord;
			coord.X = point.x;
			coord.Y = y;
			data.m_cursorPosition = coord;
			data.m_priority = Priority::Priority_highest;
			m_screenDataList.push_back(data);
		}
	}

}

