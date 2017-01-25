#include "stdafx.h"
#include "Music.h"

namespace M2
{

	CMusic::CMusic()
	{
		BASS_Init(-1, 44100, 0, 0, 0);
		bgMusic = BASS_StreamCreateFile(false, "bg.mp3", 0, 0, BASS_SAMPLE_LOOP);
		effect1 = BASS_StreamCreateFile(false, "按钮2.wav", 0, 0, BASS_SAMPLE_MONO);
		effect2 = BASS_StreamCreateFile(false, "按钮.wav", 0, 0, BASS_SAMPLE_MONO);
		effect3 = BASS_StreamCreateFile(false, "吃东西.wav", 0, 0, BASS_SAMPLE_MONO);
		failure = BASS_StreamCreateFile(false, "失败3.wav", 0, 0, BASS_SAMPLE_MONO);
		effect5 = BASS_StreamCreateFile(false, "返回.wav", 0, 0, BASS_SAMPLE_MONO);
		xunzhang = BASS_StreamCreateFile(false, "xunzhang.wav", 0, 0, BASS_SAMPLE_MONO);
		badApple = BASS_StreamCreateFile(false, "badapple.mp3", 0, 0, BASS_SAMPLE_MONO);
	}


	CMusic::~CMusic()
	{
		BASS_ChannelStop(bgMusic);
		BASS_ChannelStop(effect1);
		BASS_ChannelStop(effect2);
		BASS_ChannelStop(effect3);
		BASS_ChannelStop(failure);
		BASS_ChannelStop(effect5);
		BASS_ChannelStop(xunzhang);
		BASS_ChannelStop(badApple);
	}

	void CMusic::PlayeBadApple()
	{
		BASS_ChannelPlay(badApple, true);
	}
	void CMusic::StopBadApple()
	{
		BASS_ChannelStop(badApple);
	}

	CMusic *CMusic::Instance() 
	{
		static auto o = new CMusic;
		return o;
	}
	void CMusic::PlayXunZhangMusic()
	{

		BASS_ChannelPlay(xunzhang, true);
	}
	void CMusic::PlayBackgroundMusic()
	{
		if (!isBackgroundMusicPlaying)
		{
			BASS_ChannelPlay(bgMusic, true);
			isBackgroundMusicPlaying = true;
		}
	}
	void CMusic::PauseBackgroundMusic()
	{
		if (isBackgroundMusicPlaying)
		{
			BASS_ChannelPause(bgMusic);
			isBackgroundMusicPlaying = false;
		}
	}
	void CMusic::PlayFailureMusic()
	{
		if (!isPlayedFailure)
		{
			BASS_ChannelPlay(failure, true);
			isPlayedFailure = true;
		}
	}
	void CMusic::PauseFailureMusic()
	{
		if (isPlayedFailure)
		{
			BASS_ChannelPause(failure);
			isPlayedFailure = false;
		}
	}
	void CMusic::PlayEffect(int _whichOne)
	{
		if (_whichOne == 1)
		{
			BASS_ChannelPlay(effect1, true);
		}
		else if(_whichOne == 2)
		{
			BASS_ChannelPlay(effect2, true);
		}
		else if (_whichOne == 3)
		{
			BASS_ChannelPlay(effect3, true);
		}
		else if (_whichOne == 4)
		{
			
		}
		else if (_whichOne == 5)
		{
			BASS_ChannelPlay(effect5, true);
		}
	}
}

