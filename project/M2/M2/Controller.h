#pragma once
#include "ZObject.h"

namespace M2
{
	class CZView;
	class CData;
	class CController :
		virtual public CZObject
	{
	public:
		CController();
		~CController();

		virtual void ViewDidLoad() {}
	};
}
