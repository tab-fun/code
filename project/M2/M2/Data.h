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
		int m_priority; // �ı����ȼ�
		WORD m_textColor; // �ı���ɫ
		COORD m_cursorPosition; // �ı���ʼλ��
		String_ m_textString; // �ı�

		~CData();
	};
}


