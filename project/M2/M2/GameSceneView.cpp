#include "stdafx.h"
#include "GameSceneView.h"

namespace M2
{

	CGameSceneView::CGameSceneView()
	{
		OutputDebugString(_T(">>>>>> CGameSceneView::CGameSceneView(): ��Ϸ������ͼ�Ѿ��������ˣ�\n"));
	}


	CGameSceneView::~CGameSceneView()
	{
		OutputDebugString(_T(">>>>>> CGameSceneView::~CGameSceneView(): ��Ϸ������ͼ�Ѿ��������ˣ�\n"));
	}

	void CGameSceneView::Draw()
	{
		CZView::Draw();
		auto canDraw = true;
		static auto time = stoll(m_gameData->m_time);
		auto currentTime = stoll(m_gameData->m_time);

		auto point = m_gameData->playerCurrentPoint;
		switch (m_gameData->playerCurrentDirection)
		{
		case DirectionEnum::Up:
			point.y--;
			break;
		case DirectionEnum::Down:
			point.y++;
			break;
		case DirectionEnum::Left:
			point.x -= 2;
			break;
		case DirectionEnum::Right:
			point.x += 2;
			break;
		default:
			break;
		}

		if (point.x < 0 || point.x > 78 || point.y < 0 || point.y > 39)
		{
			canDraw = false;
		}

		for (auto &p : m_gameData->playerBodyPointList)
		{
			if ((p.x == point.x && p.y == point.y) || (p.x + 1) == point.x && p.y == point.y)
			{
				canDraw = false;
				break;
			}
		}

		if (canDraw)
		{
			if ((int)m_gameData->m_difficuty == 0)
			{
				switch (m_gameData->playerCurrentDirection)
				{
				case DirectionEnum::Up:
					for (int i = 0; i < point.y; i++)
					{
						COORD coord;
						coord.X = point.x;
						coord.Y = i;

						SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
						SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_gray | Color::black);
						WriteConsoleA(GetConsoleOutputHandle(), "|", 1, nullptr, nullptr);
					}
					break;
				case DirectionEnum::Down:
					for (int i = point.y; i < 40; i++)
					{
						COORD coord;
						coord.X = point.x;
						coord.Y = i;

						SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
						SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_gray | Color::black);
						WriteConsoleA(GetConsoleOutputHandle(), "|", 1, nullptr, nullptr);
					}
					break;
				case DirectionEnum::Left:
					for (int i = 0; i < point.x - 1; i++)
					{
						COORD coord;
						coord.X = i;
						coord.Y = point.y;

						SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
						SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_gray | Color::black);
						WriteConsoleA(GetConsoleOutputHandle(), "-", 1, nullptr, nullptr);
					}
					break;
				case DirectionEnum::Right:
					for (int i = point.x + 1; i < 80; i++)
					{
						COORD coord;
						coord.X = i;
						coord.Y = point.y;

						SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
						SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_gray | Color::black);
						WriteConsoleA(GetConsoleOutputHandle(), "-", 1, nullptr, nullptr);
					}
					break;
				default:
					break;
				}
			}

			m_gameData->m_progress = 1;
			if (CMainController::Instance()->m_pMenuController->m_pGameController->m_pGameView->m_subviewsList.size() > 1)
			{
				auto view = CMainController::Instance()->m_pMenuController->m_pGameController->m_pGameView->m_subviewsList.back();
				view->m_isDisplay = false;
			}
			time = currentTime;
			m_gameData->playerBodyPointList.push_front(m_gameData->playerCurrentPoint);

			if (m_gameData->playerBodyPointList.size() > 1)
			{
				m_gameData->playerBodyPointList.pop_back();
			}

			auto isAdded = false;
			if (point.y == m_gameData->currentPoint.y && point.x == m_gameData->currentPoint.x)
			{
				isAdded = true;
				m_gameData->playerBodyPointList.push_front(m_gameData->playerCurrentPoint);
			}
			else if (point.y == m_gameData->currentPoint.y && point.x + 1 == m_gameData->currentPoint.x)
			{
				isAdded = true;
				m_gameData->playerBodyPointList.push_front(m_gameData->playerCurrentPoint);
			}

			m_gameData->playerCurrentPoint = point;

			DWORD written;
			COORD coord;
			coord.X = m_gameData->currentPoint.x;
			coord.Y = m_gameData->currentPoint.y;

			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_gray | Color::Foreground_yellow);
			WriteConsoleA(GetConsoleOutputHandle(), "*", 1, nullptr, nullptr);

			coord.X = m_gameData->playerCurrentPoint.x;
			coord.Y = m_gameData->playerCurrentPoint.y;
			SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_gray | Color::Foreground_white);
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			WriteConsoleA(GetConsoleOutputHandle(), "��", 2, nullptr, nullptr);
			for (auto p : m_gameData->playerBodyPointList)
			{
				coord.X = p.x;
				coord.Y = p.y;
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				WriteConsoleA(GetConsoleOutputHandle(), "��", 2, nullptr, nullptr);
			}

			if (isAdded)
			{
				m_gameData->m_score++;
			
				if (m_gameData->m_score == 1)
				{
					m_gameData->m_achievements = "����";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|���õ�һ��������~|�ٵ����־��ܷ������׳�����";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else if (m_gameData->m_score == 3)
				{
					m_gameData->m_achievements = "�׳�����";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|��������һ���������׳�~|�ٵ����ֽ�����������";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else if (m_gameData->m_score == 6)
				{
					m_gameData->m_achievements = "С�߻���";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|�������Ƕ�������~|�����Ŭ����";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else if (m_gameData->m_score == 12)
				{
					m_gameData->m_achievements = "���߶�ʳ";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|��Ӵ����Ŷ~|���Ѿ�����ɳ��ڣ�|��������ͣ�";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else if (m_gameData->m_score == 24)
				{
					m_gameData->m_achievements = "ǿ���̾�";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|��~������Ŷ~|���Ѿ����ǿ׳�ˣ�";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else if (m_gameData->m_score == 100)
				{
					m_gameData->m_achievements = "��������";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|��~��������Ŷ~|����һ�������ķ��Ĵ��ڣ�";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else if (m_gameData->m_score == 200)
				{
					m_gameData->m_achievements = "�����뺣";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|�����뺣Ѱ����~|���յĴ󺣣�|��Ϊ������һ���ˣ�";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else if (m_gameData->m_score == 400)
				{
					m_gameData->m_achievements = "�߾�Ծ����";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|�߾�����Ծ����~|�����������綯��Ұ��|���ͣ�";
				}
				else if (m_gameData->m_score == 600)
				{
					m_gameData->m_achievements = "���߲�����";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|�������������~|�����£������⡣";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else if (m_gameData->m_score > 800)
				{
					m_gameData->m_achievements = "����Ϊ��";
					m_gameData->m_gameTipsString = m_gameData->m_achievements + "|��֮�󣬲�֪��ǧ��Ҳ~|��Ȼ��֪��|�������";
					CMusic::Instance()->PlayXunZhangMusic();
				}
				else {
					CMusic::Instance()->PlayEffect(3);
				}
				

				while (true)
				{
					Point point;
					srand(timeGetTime());
					point.x = rand() % 80;
					point.y = rand() % 40;
					auto isOk = false;
					auto isCan = true;

					for (auto p : m_gameData->playerBodyPointList)
					{
						if ((p.x == point.x && p.y == point.y) || (p.x + 1 == point.x && p.y == point.y))
						{
							isCan = false;
							break;
						}
					}

					if (point.x != m_gameData->playerCurrentPoint.x && point.y != m_gameData->playerCurrentPoint.y && isCan)
					{
						isOk = true;
					}
					if ((int)m_gameData->m_difficuty != 2)
					{
						if (point.x < 2 || point.x > 76 || point.y < 2 || point.y > 38)
						{
							isOk = false;
						}
					}

					if (isOk)
					{
						m_gameData->currentPoint = point;
						break;
					}
				}
			}
		}
		else
		{
			if (!CMusic::Instance()->isPlayedFailure)
			{
				CMusic::Instance()->PlayFailureMusic();
			}
			
			CMusic::Instance()->PauseBackgroundMusic();
			m_gameData->m_time = to_string(time);
			m_gameData->m_gameTipsString = m_gameData->m_achievements + "|�������ź���~|���� R �������¿�ʼ��";
			CMainController::Instance()->m_pMenuController->m_pGameController->m_isRestart = true;
			if (CMainController::Instance()->m_pMenuController->m_pGameController->m_pGameView->m_subviewsList.size() > 1)
			{
				auto view = CMainController::Instance()->m_pMenuController->m_pGameController->m_pGameView->m_subviewsList.back();
				if (!view->m_isDisplay)
				{
					view->m_isDisplay = true;
					m_gameData->m_progress = 0;
					m_gameData->SaveDataNow();
				}
			}

			if (CMainController::Instance()->m_pMenuController->m_pGameController->m_pGameView->m_subviewsList.size() == 1)
			{
				m_gameData->m_progress = 0;
				m_gameData->SaveDataNow();

				auto view = new CGameItemView;
				view->m_pDelegate = CMainController::Instance()->m_pMenuController->m_pGameController;
				view->m_isHaveBorder = true;
				view->m_borderColor = Color::Background_gray | Color::Foreground_yellow;
				view->m_rect = { 20,16,40,9 };
				view->m_backgroundFillColor = Color::black;
				view->m_title = "�Ѻ���ʾ";
				view->m_text = "GAME OVER(��Ϸ����)��";
				CMainController::Instance()->m_pMenuController->m_pGameController->m_pGameView->AddSubview(view);
			}
		}

	}
}