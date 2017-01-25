#pragma once
#include "ZView.h"

namespace M2
{
	class CMenuItemView :
		public CZView
	{
	public:
		CMenuItemView();
		~CMenuItemView();
		void Draw() override;
	};
}


