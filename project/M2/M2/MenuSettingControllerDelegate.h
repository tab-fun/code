#pragma once
#include "GameData.h"

namespace M2
{
	class MenuSettingControllerDelegate
	{
	public:
		virtual void DidCompletedSetup(CGameData *_gameData) = 0;
	};
}