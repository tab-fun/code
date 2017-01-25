#include "stdafx.h"
#include "GameView.h"


namespace M2
{
	CGameView::CGameView()
	{
		OutputDebugString(_T(">>>>>> CGameView::CGameView(): 游戏视图已经被创建了！\n"));
	}


	CGameView::~CGameView()
	{
		OutputDebugString(_T(">>>>>> CGameView::~CGameView(): 游戏视图已经被销毁了！\n"));
	}

	void CGameView::LoadData()
	{
		auto data = m_pDelegate->LoadMainGameViewData();
		m_rect = data->m_rect;
		m_backgroundFillColor = data->m_backgroundFillColor;
		m_gameData = data;
	}

	void CGameView::Draw()
	{
		static string timeString;
		auto t = stoll(m_gameData->m_time);
		if (t < 60)
		{
			timeString = "0分" + to_string(t) + "秒";
		}
		else
		{
			timeString = to_string(t / 60) + "分" + to_string(t % 60) + "秒";
		}

		// 清空屏幕内容
		String_ str(m_rect.size.height*m_rect.size.width, ' ');
		SetConsoleCursorPosition(GetConsoleOutputHandle(), { 0, 0 });
		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green);
		WriteConsole(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
		
		WORD textColor = Color::Foreground_green | Color::black;
		

		// 绘制
		CZView::Draw();

		SetConsoleTextAttribute(GetConsoleOutputHandle(), textColor);

		COORD coord;
		coord.X = 81;
		coord.Y = 2;

		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		string s = "玩家：";
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Foreground_red);
		s = m_gameData->m_playerName;
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);

		SetConsoleTextAttribute(GetConsoleOutputHandle(), textColor);

		s = "模式：";
		switch (m_gameData->m_difficuty)
		{
		case DifficultyEnum::Simple:
			s += "简单";
			break;
		case DifficultyEnum::General:
			s += "普通";
			break;
		case DifficultyEnum::Hard:
			s += "困难";
			break;
		default:
			break;
		}

		coord.Y += 2;
		s = "得分：";
		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Foreground_red);

		s = to_string(m_gameData->m_score) + "分";
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), textColor);


		coord.Y += 2;
		s = "时间：";
		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		s = timeString;
		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Foreground_red);

		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), textColor);

		coord.X = 80;
		coord.Y += 3;
		s = "━━━━━━━━━━━━━━━";
		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);

		coord.X = 81;
		coord.Y += 3;
		s = "游戏操作：";
		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Foreground_red);

		coord.Y += 2;
		s = "上下左右";
		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);

		SetConsoleTextAttribute(GetConsoleOutputHandle(), textColor);

		s = " 或 ";
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Foreground_red);

		s = "WASD";
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);

		SetConsoleTextAttribute(GetConsoleOutputHandle(), textColor);

		s = " 控制方向";
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);


		coord.X = 80;
		coord.Y += 3;
		s = "━━━━━━━━━━━━━━━";
		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);

		list<string> list;
		string strg;
		for (auto &ch : m_gameData->m_gameTipsString)
		{
			if (ch != '|')
			{
				strg += ch;
			}
			else
			{
				list.push_back(strg);
				strg = "";
			}
		}
		list.push_back(strg);

		coord.X = 81;
		coord.Y += 4;
		s = "获得勋章：";
		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Foreground_darkYellow);

		s = list.front();
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
		SetConsoleTextAttribute(GetConsoleOutputHandle(), textColor);

		coord.X = 80;
		coord.Y += 4;
		s = "━━━━━━━━━━━━━━━";
		SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
		WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);

		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Foreground_red);
		coord.X = 81;
		coord.Y += 3;
		list.pop_front();
		static DWORD i = 0;
		if (i <= CMainController::Instance()->dwFrame / 8)
		{
			for (auto &str : list)
			{
				coord.Y += 2;
				coord.X = 95 - str.length() / 2;
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
			}
		}
		else {
			i = 0;
		}
		i++;

	}
}
