#pragma once
#include "Data.h"
#include "Others.h"
#include <vector>
#include <string>
#include <list>
namespace M2
{
	struct CMenuData :
		public CData
	{
		std::string m_title;
		Rect m_rect;
		WORD m_backgroundFillColor;
		bool m_isHaveBorder;
		WORD m_borderColor;
		string m_text;
		std::vector<CData> m_menuItemsDataVec;
		std::list<CData> m_screenDataList;

		void MakeBoxData(Point point, Size size);

		CMenuData();
		CMenuData(CData _data);
	};
}


