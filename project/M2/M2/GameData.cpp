#include "stdafx.h"
#include "GameData.h"


namespace M2
{
	CGameData::CGameData()
	{
		OutputDebugString(_T(">>>>>> CGameData::CGameData(): 游戏数据已经被创建了！\n"));
	}


	CGameData::~CGameData()
	{
		OutputDebugString(_T(">>>>>> CGameData::~CGameData(): 游戏数据已经被销毁了！\n"));
	}

	bool CGameData::CollisionHandle()
	{
		if (m_currentSceneID == 0)
		{
			TiXmlDocument doc(m_archivePath.data());

			if (doc.LoadFile())
			{
				auto ele = doc.FirstChildElement("root")->FirstChildElement("MapRectItem");

				for (; ele != nullptr; ele = ele->NextSiblingElement("MapRectItem"))
				{
					int x = 0, y = 0, width = 0, height = 0,type = 0;
					ele->Attribute("x", &x);
					ele->Attribute("y", &y);
					ele->Attribute("type", &type);
					Point point = { x,y }, point2 = point;
					point2.x++;


					auto item_2 = m_playerRectItem; 
					item_2.m_rect.point.x++;

					auto isCollision = false;
					switch (item_2.m_direction)
					{
					case DirectionEnum::Up:
					case DirectionEnum::Down:
					case DirectionEnum::Left:
					case DirectionEnum::Right:
						isCollision = item_2.IsCollided(point) || item_2.IsCollided(point2) || m_playerRectItem.IsCollided(point) || m_playerRectItem.IsCollided(point2);
						break;
					case DirectionEnum::UnKnown:
						break;
					default:
						break;
					}

					if (type != 0 && isCollision)
					{
						ele->Parent()->RemoveChild(ele);
						CData::doc.SaveFile();

						auto b = m_mapVec.begin();
						for (; b != m_mapVec.end(); b++)
						{
							if ((*b).IsCollided(point))
							{
								m_mapVec.erase(b);
								break;
							}
						}

						return true;
					}
				}

			}
			else {

				throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);

			}
		}
		
		
		return false;
	}

	void CGameData::SaveDifficulty()
	{
		if (CData::doc.LoadFile())
		{
			auto ele = doc.FirstChildElement("Player")->FirstChildElement("Archives");
			
			auto canCreateNewElement = true;
			for (; ele != nullptr; ele = ele->NextSiblingElement("Archives"))
			{
				if (stoi(ele->Attribute("difficulty")) == (int)m_difficuty)
				{
					canCreateNewElement = false;
					m_archivePath = ele->Attribute("archivesPath");
					break;
				}
			}

			if (canCreateNewElement)
			{
				auto element = new TiXmlElement("Archives");
				element->SetAttribute("name", m_playerName.c_str());
				element->SetAttribute("difficulty", (int)m_difficuty);
				string s = "Archives" + to_string((int)m_difficuty) + ".xml";
				m_archivePath = s;
				element->SetAttribute("archivesPath", s.data());
				element->SetAttribute("progress", 0);
				ele = doc.FirstChildElement("Player");
				ele->LinkEndChild(element);
				doc.SaveFile();
			}
		}
		else {
			
			throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
		
		}
	}

	void CGameData::SaveDataNow()
	{
		string path;
		if (CData::doc.LoadFile())
		{
			auto ele = doc.FirstChildElement("Player")->FirstChildElement("Archives");
		
			for (; ele != nullptr; ele = ele->NextSiblingElement("Archives"))
			{
				if (stoi(ele->Attribute("difficulty")) == (int)m_difficuty)
				{
					path = ele->Attribute("archivesPath");
					ele->SetAttribute("x", m_playerRectItem.m_rect.point.x);
					ele->SetAttribute("y", m_playerRectItem.m_rect.point.y);
					ele->SetAttribute("width", m_playerRectItem.m_rect.size.width);
					ele->SetAttribute("height", m_playerRectItem.m_rect.size.height);
					ele->SetAttribute("sceneID", m_currentSceneID);
					ele->SetAttribute("score", m_score);
					ele->SetAttribute("tips", m_gameTipsString.data());
					ele->SetAttribute("time", m_time.data());
					ele->SetAttribute("progress", m_progress);

					if (stoi(ele->Attribute("lookScore"))< m_score)
					{
						ele->SetAttribute("lookScore", m_score);
					}
					if (stoi(ele->Attribute("lookTime"))< stoi(m_time.data()))
					{
						ele->SetAttribute("lookTime", m_time.data());
					}
					ele->SetAttribute("lookAchievements", m_achievements.data());
					
					auto playerEle = ele->FirstChildElement("playerItem");
					if (playerEle)
					{
						playerEle->SetAttribute("currentX", currentPoint.x);
						playerEle->SetAttribute("currentY", currentPoint.y);
						playerEle->SetAttribute("currentPlayerX", playerCurrentPoint.x);
						playerEle->SetAttribute("currentPlayerY", playerCurrentPoint.y);
						playerEle->SetAttribute("direction", (int)playerCurrentDirection);
					}
					else
					{
						auto xmlEle = new TiXmlElement("playerItem");
						xmlEle->SetAttribute("currentX", currentPoint.x);
						xmlEle->SetAttribute("currentY", currentPoint.y);
						xmlEle->SetAttribute("currentPlayerX", playerCurrentPoint.x);
						xmlEle->SetAttribute("currentPlayerY", playerCurrentPoint.y);
						xmlEle->SetAttribute("direction", (int )playerCurrentDirection);

						ele->LinkEndChild(xmlEle);
					}
					CData::doc.SaveFile();
					break;
				}
			}
		}
		else {

			throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);

		}

		if (!path.empty())
		{
			FILE *file = fopen(path.data(), "w");
			fclose(file);

			TiXmlDocument doc(path.data());
			auto root = new TiXmlElement("root");
			doc.LinkEndChild(root);
			doc.SaveFile();

			if (doc.LoadFile())
			{
				auto ele = doc.FirstChildElement("root");
				for (auto &p : playerBodyPointList)
				{
					auto xmlEle = new TiXmlElement("MapRectItem");
					xmlEle->SetAttribute("x", p.x);
					xmlEle->SetAttribute("y", p.y);
					ele->LinkEndChild(xmlEle);
				}
			}
			doc.SaveFile();
		}
	}
}

