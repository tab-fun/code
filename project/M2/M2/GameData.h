#pragma once
#include "Data.h"
#include <string>

namespace M2
{

	class CGameData :
		public CData
	{
	public:
		CGameData();
		~CGameData();

		string m_playerName;
		int m_progress;
		DifficultyEnum m_difficuty;
		Rect m_rect;
		WORD m_backgroundFillColor;

		Point currentPoint;
		Point playerCurrentPoint;
		DirectionEnum playerCurrentDirection;
		list<Point> playerBodyPointList;

		string m_achievements;
		string m_time;
		WORD m_defense = 0;
		WORD m_hp = 0;
		int m_score = 0;
		string m_gameTipsString;
		string m_archivePath;



		vector<CMapRectItem> m_mapVec;
		SceneID m_currentSceneID;
		CMapRectItem m_playerRectItem;
		vector<CMapRectItem> m_enemyVec;

		void SaveDifficulty();
		void SaveDataNow();
		bool CollisionHandle();
	};
}


