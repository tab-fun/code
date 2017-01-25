#pragma once
#include "ZObject.h"
#include <string>
#include <list>
#include "Data.h"
namespace M2
{
	class CZView :
		virtual public CZObject
	{
		void DrawBorder();

	public:
		bool m_isDisplay = true;
		std::string m_title;
		std::string m_text;
		WORD m_color;
		Rect m_rect;
		WORD m_backgroundFillColor;
		bool m_isHaveBorder = false;
		WORD m_borderColor;
		Point m_center = { 0,0 }; 
		std::list<CZView *> m_subviewsList;
		std::list<CData> m_screenDataList;

	public:
		~CZView();

		virtual void Draw();
		virtual void LoadData() {}
		virtual void AddSubview(CZView *_view);
		virtual void RemoveView(CZView *_view);
		virtual void RemoveSubviews();
	};



}
