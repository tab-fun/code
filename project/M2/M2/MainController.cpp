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
					Instance()->m_pMenuController->DidReceiveKeyboardEvent(_keyMessag);// 通知菜单控制器处理键盘消息
				}
				else
				{
					Instance()->m_pMenuController->m_pGameController->DidReceiveKeyboardEvent(_keyMessag);// 通知游戏控制器处理键盘消息

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

				OutputDebugString(_T(">>>>>> CMainController::HandleArchive(DWORD _dwFrequency)：正在存档！\n"));
				Instance()->m_pMenuController->m_pGameController->ArchiveNow();
			}
		}
	}
	// 构造和析构
	CMainController::CMainController()
	{
		OutputDebugString(_T(">>>>>> CMainController::CMainController()：主控制器被创建了！\n"));
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

		OutputDebugString(_T(">>>>>> CMainController::CMainController()：主控制器被销毁了！\n"));
	}


	// 静态成员的初始化和定义
	DWORD CMainController::dwFrame = 15;
	CMainController *CMainController::pMainController = nullptr;
	CMainController *CMainController::Instance()
	{
		if (pMainController == nullptr)
			pMainController = new CMainController;

		return pMainController;
	}

	/// 创建主控制器方法
	int CMainController::CreateMainController(int _argc, char **_argv)
	{
		SetConsoleTitleA("贪吃蛇__M2版");

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
					cout << "退出（Esc）";
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

		// 加载窗口
		Instance()->m_pWindow = new CZWindow;
		SetFrameRate(30);
		Instance()->m_pWindow->m_pDelegate = Instance();
		Instance()->m_pWindow->LoadData();
		Instance()->ViewDidLoad();

		// 创建主事件循环：刷新屏幕
		while (!Instance()->m_isQuit)
		{
			Instance()->UpdatingScreen();
		}

		// 清理自己
		delete pMainController;
		pMainController = nullptr;

		return EXIT_SUCCESS;
	}

	/// 设置更新频率
	void CMainController::UpdatingScreen()
	{

		// 控制刷新率
		// 显式第一个缓冲区
		::SetConsoleActiveScreenBuffer(m_pWindow->m_hBuffer);

		if (!m_pMenuController->m_pGameData->m_playerName.empty() && m_pMenuController->m_pMenuView->m_title != "进化蝴蝶：修改存档名字")
		{
			// 交换缓冲区
			auto temp = m_pWindow->m_hBuffer;
			m_pWindow->m_hBuffer = m_pWindow->m_hBuffer_1;
			m_pWindow->m_hBuffer_1 = temp;

			// 在主事件循环中处理键盘事件——目前无法实现线程之间的同步，所以只有把键盘事件的处理放在主线程中

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

		// 处理存档事件
		HandleArchive(200);


		// 在另一个缓冲区中绘制
		m_pWindow->Draw();

		Sleep(GetFrameRate);

	}
	

	/// 给窗口代理加载数据
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
			throw CZException("xml文件加载失败！",nullptr,__LINE__,__FILE__);
		}
		return CWindowData();
	}

	/// 视图已经加载了
	void CMainController::ViewDidLoad()
	{
		// 加载菜单控制器
		m_pMenuController = new CMenuController;

		// 添加菜单视图
		m_pWindow->AddSubview(m_pMenuController->m_pMenuView);

		// 菜单视图已经加载完成
		m_pMenuController->ViewDidLoad();
	}
}

