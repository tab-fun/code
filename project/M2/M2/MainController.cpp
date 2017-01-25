#include "stdafx.h"
#include "MainController.h"

namespace M2
{
	bool CMainController::isHaveNewEventMessage = false;
	INPUT_RECORD CMainController::keyMessage;

	void CMainController::HandleKeyboardEvent(const INPUT_RECORD _keyMessag)
	{
			if (Instance()->m_pMenuController)
			{
				if (!Instance()->m_pMenuController->m_pGameController)
				{
					Instance()->m_pMenuController->DidReceiveKeyboardEvent(_keyMessag);// ֪ͨ�˵����������������Ϣ
				}
				else
				{
					Instance()->m_pMenuController->m_pGameController->DidReceiveKeyboardEvent(_keyMessag);// ֪ͨ��Ϸ���������������Ϣ

				}
			}
	}


	void CMainController::HandleArchive(DWORD _dwFrequency)
	{
		if (Instance()->m_pMenuController && Instance()->m_pMenuController->m_pGameController && !Instance()->m_pMenuController->m_pGameController->m_isRestart)
		{
			static auto time = timeGetTime();
			auto currentTime = timeGetTime();
			if (currentTime-time > _dwFrequency)
			{
				time = currentTime;

				OutputDebugString(_T(">>>>>> CMainController::HandleArchive(DWORD _dwFrequency)�����ڴ浵��\n"));
				Instance()->m_pMenuController->m_pGameController->ArchiveNow();
			}
		}
	}
	// ���������
	CMainController::CMainController()
	{
		OutputDebugString(_T(">>>>>> CMainController::CMainController()�����������������ˣ�\n"));
	}
	CMainController::~CMainController()
	{
		if (m_pWindow)
		{
			delete m_pWindow;
			m_pWindow = nullptr;
		}
		if (m_pMenuController)
		{
			delete m_pMenuController;
			m_pMenuController = nullptr;
		}

		OutputDebugString(_T(">>>>>> CMainController::CMainController()�����������������ˣ�\n"));
	}


	// ��̬��Ա�ĳ�ʼ���Ͷ���
	DWORD CMainController::dwFrame = 15;
	CMainController *CMainController::pMainController = nullptr;
	CMainController *CMainController::Instance()
	{
		if (pMainController == nullptr)
			pMainController = new CMainController;

		return pMainController;
	}

	/// ����������������
	int CMainController::CreateMainController(int _argc, char **_argv)
	{
		SetConsoleTitleA("̰����__M2��");

		CONSOLE_CURSOR_INFO info = { 1,false };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		system("mode con cols=105 lines=33");

		FILE* fp = fopen("badapple.txt", "r");
		char buf[1024];
		fps_limit fps(8);
		CMusic::Instance()->PlayeBadApple();
		while (!feof(fp))
		{
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				break;
			}
			COORD coord;
			HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD pos;
			pos.X = 0;
			pos.Y = 0;
			SetConsoleCursorPosition(hConsoleOutput, pos);
			for (int i = 0; i < 32; i++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::Foreground_green);
				fgets(buf, 1024, fp);
				printf("%s", buf);

				coord.X = 90;
				coord.Y = i;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::Foreground_yellow);
				if (i == 16)
				{
					cout << "�˳���Esc��";
				}
				else {
					cout << "         ";
				}
				coord.X = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			}
			fps.delay();
		}
		CMusic::Instance()->StopBadApple();

		// ���ش���
		Instance()->m_pWindow = new CZWindow;
		SetFrameRate(30);
		Instance()->m_pWindow->m_pDelegate = Instance();
		Instance()->m_pWindow->LoadData();
		Instance()->ViewDidLoad();

		// �������¼�ѭ����ˢ����Ļ
		while (!Instance()->m_isQuit)
		{
			Instance()->UpdatingScreen();
		}

		// �����Լ�
		delete pMainController;
		pMainController = nullptr;

		return EXIT_SUCCESS;
	}

	/// ���ø���Ƶ��
	void CMainController::UpdatingScreen()
	{

		// ����ˢ����
		// ��ʽ��һ��������
		::SetConsoleActiveScreenBuffer(m_pWindow->m_hBuffer);

		if (!m_pMenuController->m_pGameData->m_playerName.empty() && m_pMenuController->m_pMenuView->m_title != "�����������޸Ĵ浵����")
		{
			// ����������
			auto temp = m_pWindow->m_hBuffer;
			m_pWindow->m_hBuffer = m_pWindow->m_hBuffer_1;
			m_pWindow->m_hBuffer_1 = temp;

			// �����¼�ѭ���д�������¼�����Ŀǰ�޷�ʵ���߳�֮���ͬ��������ֻ�аѼ����¼��Ĵ���������߳���

			if (CMainController::Instance()->m_pMenuController &&CMainController::Instance()->m_pMenuController->m_pGameController)
			{
				if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
				{
					CMainController::Instance()->m_pMenuController->m_pGameController->PressUpKey();
				}
				if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
				{
					CMainController::Instance()->m_pMenuController->m_pGameController->PressDownKey();
				}
				if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
				{
					CMainController::Instance()->m_pMenuController->m_pGameController->PressLeftKey();
				}
				if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
				{
					CMainController::Instance()->m_pMenuController->m_pGameController->PressRightKey();
				}
			}

			if (isHaveNewEventMessage)
			{
				HandleKeyboardEvent(keyMessage);
				isHaveNewEventMessage = false;
			}
		}

		// ����浵�¼�
		HandleArchive(200);


		// ����һ���������л���
		m_pWindow->Draw();

		Sleep(GetFrameRate);

	}
	

	/// �����ڴ����������
	CWindowData CMainController::LoadWindowData()
	{
		if (CData::doc.LoadFile())
		{
			CWindowData data;
			auto root = CData::doc.FirstChildElement("ConsoleWindow");
			data.m_windowTitle = root->Attribute("title");
			data.m_windowRect.point = { 0,0 };
			data.m_windowRect.size.width = stoi(root->Attribute("width"));
			data.m_windowRect.size.height = stoi(root->Attribute("height"));
			data.m_windowBackgroundFillColor = stoi(root->Attribute("color"));
			data.m_hWindowBuffer = CreateConsoleScreenBuffer(
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				CONSOLE_TEXTMODE_BUFFER,
				NULL
			);
			data.m_hWindowBuffer_1 = CreateConsoleScreenBuffer(
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				CONSOLE_TEXTMODE_BUFFER,
				NULL
			);
			return data;
		}
		else
		{
			throw CZException("xml�ļ�����ʧ�ܣ�",nullptr,__LINE__,__FILE__);
		}
		return CWindowData();
	}

	/// ��ͼ�Ѿ�������
	void CMainController::ViewDidLoad()
	{
		// ���ز˵�������
		m_pMenuController = new CMenuController;

		// ��Ӳ˵���ͼ
		m_pWindow->AddSubview(m_pMenuController->m_pMenuView);

		// �˵���ͼ�Ѿ��������
		m_pMenuController->ViewDidLoad();
	}
}

