#pragma once
#include "ZObject.h"

namespace M2
{
	class CMusic :
		public CZObject
	{
		bool isBackgroundMusicPlaying = false;
		HSTREAM bgMusic;
		HSTREAM effect1;
		HSTREAM effect2;
		HSTREAM effect3;
		HSTREAM failure;
		HSTREAM effect5;
		HSTREAM xunzhang;
		HSTREAM badApple;
	public:
		CMusic();
		~CMusic();
		bool isPlayedFailure = false;
		static CMusic *Instance();
		void PlayBackgroundMusic();
		void PauseBackgroundMusic();
		void PlayEffect(int _whichOne);
		void PlayFailureMusic();
		void PauseFailureMusic();
		void PlayXunZhangMusic();

		void PlayeBadApple();
		void StopBadApple();
	};
}
