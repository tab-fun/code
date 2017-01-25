#pragma once
#include "ZObject.h"
#include <string>
#include "xml\tinyxml.h"
namespace M2
{
	struct CData: 
		virtual public CZObject
	{
		static TiXmlDocument doc;
		int m_priority; // 文本优先级
		WORD m_textColor; // 文本颜色
		COORD m_cursorPosition; // 文本起始位置
		String_ m_textString; // 文本

		~CData();
	};
}


