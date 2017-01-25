#include "stdafx.h"
#include "ZWindow.h"


namespace M2
{
	CZWindow::CZWindow()
	{
		OutputDebugString(_T(">>>>>> CZWindow::CZWindow()�����ڱ������ˣ�\n"));
	}
	CZWindow::~CZWindow()
	{
		OutputDebugString(_T(">>>>>> CZWindow::~CZWindow()�����ڱ������ˣ�\n"));
	}

	void CZWindow::Draw()
	{
		if (m_previousRect != m_rect)
		{
			m_previousRect = m_rect;

			COORD coord;
			coord.X = m_rect.size.width;
			coord.Y = m_rect.size.height;
			CONSOLE_CURSOR_INFO info = { 1,false };


			SetConsoleScreenBufferSize(m_hBuffer, coord);
			SetConsoleActiveScreenBuffer(m_hBuffer);
			string str = "mode con cols=" + to_string(m_rect.size.width) + string(" lines=") + to_string(m_rect.size.height);
			system(str.c_str());
			string str2 = "color " + to_string(m_backgroundFillColor);
			system(str2.c_str());
			SetConsoleCursorInfo(m_hBuffer, &info);
			SetConsoleCursorPosition(m_hBuffer, { 0,0 });


			SetConsoleScreenBufferSize(m_hBuffer_1, coord);
			SetConsoleActiveScreenBuffer(m_hBuffer_1);
			system(str.c_str());
			system(str2.c_str());
			SetConsoleCursorInfo(m_hBuffer_1, &info);
			SetConsoleCursorPosition(m_hBuffer_1, { 0,0 });
		}

		// �����Ļ����
		String_ str(m_rect.size.height*m_rect.size.width, ' ');
		SetConsoleCursorPosition(GetConsoleOutputHandle(), { 0, 0 });
		SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green);
		WriteConsole(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

		SetConsoleTitleA(m_title.c_str());

		if (CMainController::Instance()->m_pMenuController->m_pGameData)
		{
			if (CMainController::Instance()->m_pMenuController->m_pGameData->m_playerName.empty())
			{
				if (CData::doc.LoadFile())
				{
						String_ str = _T("��û���κεĴ浵��Ϣ��");
						COORD coord;
						coord.X = CMainController::Instance()->m_pWindow->m_rect.size.width/2 - str.length();
						coord.Y = CMainController::Instance()->m_pWindow->m_rect.size.height * 0.392 - 4;
						CONSOLE_CURSOR_INFO info = { 1,true };

						SetConsoleCursorInfo(GetConsoleOutputHandle(), &info);
						SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
						SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green | Color::Foreground_red);
						WriteConsole(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

						str = _T("��������Ҵ浵�����֣�");
						coord.X = CMainController::Instance()->m_pWindow->m_rect.size.width * 0.392 - str.length();
						coord.Y = CMainController::Instance()->m_pWindow->m_rect.size.height * 0.392;
						SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
						SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green | Color::Foreground_white);
						WriteConsole(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

						SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green | Color::Foreground_yellow);
						string name;
						cin >> name;
						CMainController::Instance()->m_pMenuController->SetPlayerNewName(name);
				}
				else
				{
					throw CZException("xml�ļ�����ʧ�ܣ�", nullptr, __LINE__, __FILE__);
				}
			}
		}

		// ��ʼ������Ļ
		for (auto view : m_subviewsList)
		{
			view->Draw();
		}
	}

	void CZWindow::LoadData()
	{
		auto data = m_pDelegate->LoadWindowData();
		m_title = data.m_windowTitle;
		m_rect = data.m_windowRect;
		m_hBuffer = data.m_hWindowBuffer;
		m_hBuffer_1 = data.m_hWindowBuffer_1;
		m_backgroundFillColor = data.m_windowBackgroundFillColor;

		
		COORD coord;
		coord.X = m_rect.size.width;
		coord.Y = m_rect.size.height;
		CONSOLE_CURSOR_INFO info = { 1,false };

		
		SetConsoleScreenBufferSize(m_hBuffer, coord);
		SetConsoleActiveScreenBuffer(m_hBuffer);
		string str = "mode con cols=" + to_string(m_rect.size.width) + string(" lines=") + to_string(m_rect.size.height);
		system(str.c_str());
		string str2 = "color " + to_string(m_backgroundFillColor);
		system(str2.c_str());
		SetConsoleCursorInfo(m_hBuffer, &info);
		SetConsoleCursorPosition(m_hBuffer, { 0,0 });

		
		SetConsoleScreenBufferSize(m_hBuffer_1, coord);
		SetConsoleActiveScreenBuffer(m_hBuffer_1);
		system(str.c_str());
		system(str2.c_str());
		SetConsoleCursorInfo(m_hBuffer_1, &info);
		SetConsoleCursorPosition(m_hBuffer_1, { 0,0 });

	}
}

