#include "stdafx.h"
#include "GameController.h"

namespace M2
{
	bool CGameController::isNewGame = false;

	CGameController::CGameController(bool _isNewGame)
	{
		Self = this;
		isNewGame = _isNewGame;

		if (!m_pGameView)
		{
			m_pGameView = new CGameView;
		}
		
		m_pGameView->m_title = GAME_VIEW_TITLE_MainGameView;
		m_pGameView->m_isHaveBorder = false;
		m_pGameView->m_pDelegate = this;


		OutputDebugString(_T(">>>>>> CGameController::CGameController(): 游戏控制器已经被创建了！\n"));
	}


	CGameController::~CGameController()
	{
		timeKillEvent(m_onSecondTimerID);
		OutputDebugString(_T(">>>>>> CGameController::CGameController(): 游戏控制器已经被销毁了！\n"));
	}
	void CGameController::ArchiveNow()
	{
		m_pGameData->SaveDataNow();
	}
	CGameData* CGameController::LoadMainGameViewData()
	{

		if (CData::doc.LoadFile())
		{
			auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("MainGameView");
			if (ele)
			{
				ele->Attribute("x", &m_pGameData->m_rect.point.x);
				ele->Attribute("y", &m_pGameData->m_rect.point.y);
				ele->Attribute("width", &m_pGameData->m_rect.size.width);
				ele->Attribute("height", &m_pGameData->m_rect.size.height);
				m_pGameData->m_backgroundFillColor = stoi(ele->Attribute("color"));
				if (isNewGame)
				{
					m_pGameData->m_score = 0;
					m_pGameData->m_time = "0";
					m_pGameData->m_achievements = "暂无";
				}
			}
		}
		else
		{
			throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
		}

		return m_pGameData;
	}

	void CGameController::ViewDidLoad()
	{
		m_pGameView->LoadData();

		string s = "Archives" + to_string((int)m_pGameData->m_difficuty) + ".xml";
		m_pGameData->m_archivePath = s;
		
		m_canReceiveKeyboardEvent = true;

		CMainController::Instance()->m_pWindow->m_rect = m_pGameView->m_rect;
		
		if (CData::doc.LoadFile())
		{
			auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("MainGameView")->FirstChildElement("GameItem");
			if (ele)
			{
				auto view = new CGameItemView;
				
				ele->Attribute("x", &view->m_rect.point.x);
				ele->Attribute("y", &view->m_rect.point.y);
				ele->Attribute("width", &view->m_rect.size.width);
				ele->Attribute("height", &view->m_rect.size.height);
				m_pGameData->m_rect = view->m_rect;

				Rect re;
				re.point.x = view->m_rect.point.x + view->m_rect.size.width / 2;
				re.point.y = view->m_rect.point.y + view->m_rect.size.height / 2;
				re.size = { 2,1 };
				m_pGameData->m_playerRectItem.m_rect = re;

				view->m_backgroundFillColor = stoi(ele->Attribute("color"));
				ele->Attribute("isHaveBorder", (int *)&view->m_isHaveBorder);
				ele->Attribute("borderColor", (int*)&view->m_borderColor);
				view->m_title = ele->GetText();

				if (!isNewGame)
				{
					ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
					for (; ele != nullptr; ele = ele->NextSiblingElement("Archives"))
					{
						int d = -1;
						ele->Attribute("difficulty", &d);
						if (d == (int)m_pGameData->m_difficuty)
						{
							ele->Attribute("x", &m_pGameData->m_playerRectItem.m_rect.point.x);
							ele->Attribute("y", &m_pGameData->m_playerRectItem.m_rect.point.y);
							ele->Attribute("width", &m_pGameData->m_playerRectItem.m_rect.size.width);
							ele->Attribute("height", &m_pGameData->m_playerRectItem.m_rect.size.height);
							ele->Attribute("score", &m_pGameData->m_score);
							ele->Attribute("progress", &m_pGameData->m_progress);
							ele->Attribute("sceneID", (int *)&m_pGameData->m_currentSceneID);
							m_pGameData->m_time = ele->Attribute("time");
							m_pGameData->m_gameTipsString = ele->Attribute("tips");
							break;
						}
					}
				}

				view->m_pDelegate = this;
				m_pGameView->AddSubview(view);

				view->LoadData();
			}
		}
		else
		{
			throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
		}

		m_onSecondTimerID = timeSetEvent(1000, 0, CGameController::OneSecondEvent, 0, (UINT)TIME_PERIODIC);
		CMusic::Instance()->PlayBackgroundMusic();
	}

	CGameSceneView* CGameController::LoadGameScene()
	{
		auto view = new CGameSceneView;
		view->m_pDelegate = this;
		view->m_gameData = m_pGameData;
		view->m_backgroundFillColor = Color::Background_gray;
		view->m_isHaveBorder = false;

		view->m_rect = { 0,0,80,40 };
		

		if (isNewGame)
		{
			m_pGameData->playerCurrentDirection = DirectionEnum::Up;
			m_pGameData->playerCurrentPoint = { 40,20 };
			m_pGameData->playerBodyPointList.clear();

			Point point;
			while (true)
			{
				srand(timeGetTime());
				point.x = rand() % 76 + 1;
				point.y = rand() % 38;

				if (point.x != 40 && point.y != 20)
				{
					m_pGameData->currentPoint = point;
					break;
				}
			}

			return view;
		}

		if (CData::doc.LoadFile())
		{
			auto ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
			for (; ele != nullptr; ele = ele->NextSiblingElement("Archives"))
			{
				int d = -1; ele->Attribute("difficulty", &d);
				if (d == (int)m_pGameData->m_difficuty)
				{
					m_pGameData->m_achievements = ele->Attribute("lookAchievements");
					ele->Attribute("sceneID", &d);
					m_pGameData->m_currentSceneID = d;
					auto xmlEle = ele->FirstChildElement("playerItem");

					xmlEle->Attribute("currentX", (int *)&m_pGameData->currentPoint.x);
					xmlEle->Attribute("currentY", (int *)&m_pGameData->currentPoint.y);
					xmlEle->Attribute("currentPlayerX", (int *)&m_pGameData->playerCurrentPoint.x);
					xmlEle->Attribute("currentPlayerY", (int *)&m_pGameData->playerCurrentPoint.y);
					xmlEle->Attribute("direction", (int *)&m_pGameData->playerCurrentDirection);

					m_pGameData->playerBodyPointList.clear();
					auto s = ele->Attribute("archivesPath");

					TiXmlDocument doc(s);
					if (doc.LoadFile())
					{

					}
					auto ele = doc.FirstChildElement("root");
					xmlEle = ele->FirstChildElement("MapRectItem");
					for (; xmlEle != nullptr; xmlEle = xmlEle->NextSiblingElement("MapRectItem"))
					{
						Point item;
						item.x = stoi(xmlEle->Attribute("x"));
						item.y = stoi(xmlEle->Attribute("y"));
						
						m_pGameData->playerBodyPointList.push_back(item);
					}

					return view;
				}
			}
		}
		else
		{
			throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
		}

		return nullptr;
	}


	CGameController* CGameController::Self = nullptr;
	void CALLBACK CGameController::OneSecondEvent(UINT uID,
		UINT uMsg,
		DWORD dwUser,
		DWORD dw1,
		DWORD dw2)
	{
		if (CGameController::Self->m_isRestart)
		{
			return;
		}
		auto t = stoll(CGameController::Self->m_pGameData->m_time);
		++t;
		CGameController::Self->m_pGameData->m_time = to_string(t);
	}

	void CGameController::PressUpKey() 
	{
		if (m_pGameData->playerCurrentDirection != DirectionEnum::Down && m_pGameData->playerCurrentDirection != DirectionEnum::Up && !m_isRestart)
		{
			m_pGameData->playerCurrentDirection = DirectionEnum::Up;
		}
	}
	void CGameController::PressDownKey() 
	{
		if (m_pGameData->playerCurrentDirection != DirectionEnum::Up && m_pGameData->playerCurrentDirection != DirectionEnum::Down && !m_isRestart)
		{
			m_pGameData->playerCurrentDirection = DirectionEnum::Down;
		}
	}
	void CGameController::PressLeftKey()
	{
		if (m_pGameData->playerCurrentDirection != DirectionEnum::Right && m_pGameData->playerCurrentDirection != DirectionEnum::Left && !m_isRestart)
		{
			m_pGameData->playerCurrentDirection = DirectionEnum::Left;
		}
	}
	void CGameController::PressRightKey()
	{
		if (m_pGameData->playerCurrentDirection != DirectionEnum::Left && m_pGameData->playerCurrentDirection != DirectionEnum::Right && !m_isRestart)
		{
			m_pGameData->playerCurrentDirection = DirectionEnum::Right;
		}
	}
	void CGameController::PressESCKey()
	{
		CMusic::Instance()->PauseBackgroundMusic();
		// 返回主菜单
		delete CMainController::Instance()->m_pMenuController->m_pGameController;
		CMainController::Instance()->m_pMenuController->m_pGameController = nullptr;
		CMainController::Instance()->m_pMenuController->m_pMenuView->RemoveSubviews();
		CMainController::Instance()->m_pMenuController->m_pMenuView->m_title = MENU_ITEM_TITLE_MainMenu;
		CMainController::Instance()->m_pMenuController->m_pMenuView->LoadData();
		CMainController::Instance()->m_pMenuController->ViewDidLoad();

		if (CData::doc.LoadFile())
		{
			auto ele = CData::doc.FirstChildElement("ConsoleWindow");
			if (ele)
			{
				Rect re;
				re.point = { 0,0 };
				ele->Attribute("width", &re.size.width);
				ele->Attribute("height", &re.size.height);
				CMainController::Instance()->m_pWindow->m_rect = re;
			}
		}
		else
		{
			throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
		}
	}
	void CGameController::DidReceiveKeyboardEvent(const INPUT_RECORD _keyMessage)
	{
		// 处理按键
		if (_keyMessage.EventType == KEY_EVENT && _keyMessage.Event.KeyEvent.bKeyDown == true && m_canReceiveKeyboardEvent)
		{
			String_ str = _T(">>>>>> CGameController::DidReceiveKeyboardEvent(const INPUT_RECORD _keyMessage): 收到了键盘按下的事件信息\n");
			OutputDebugString(str.c_str());

			
			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_SPACE || _keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
			{

			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'W' || _keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_UP)
			{
				
			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'S' || _keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
			{
				
									
			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'A' || _keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
			{
				
			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'R')
			{
				if (m_isRestart)
				{
					m_isRestart = false;
					PressESCKey();
					CMainController::Instance()->m_pMenuController->DidPressTheReturnKey("开始游戏");
					CMusic::Instance()->PlayBackgroundMusic();
					CMusic::Instance()->PauseFailureMusic();
				}
			}
			

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_TAB)
			{

			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
			{
				CMusic::Instance()->PauseFailureMusic();
				CMusic::Instance()->PlayEffect(5);
				PressESCKey();
			}
		}
	}

}

