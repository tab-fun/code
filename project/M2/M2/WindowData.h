#pragma once
#include "Data.h"

namespace M2
{
	struct CWindowData :
		public CData
	{
		std::string m_windowTitle;
		Rect m_windowRect;
		WORD m_windowBackgroundFillColor;
		HANDLE m_hWindowBuffer;
		HANDLE m_hWindowBuffer_1;
	};
}


