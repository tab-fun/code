 // M2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main(int _argc, char **_argv)
{
	try
	{
		return ConsoleApplicationMain(_argc, _argv);
	}
	catch (const std::exception& e)
	{
		OutputDebugStringA(e.what());
		throw;
	}
	catch (...)
	{
		auto obj = gcnew SendMailClass;
		auto s = gcnew String("main() : 程序没有正常退出！");
		auto s2 = gcnew String("——未捕获异常发生  来自玩家：");
		s2 += gcnew String(CMainController::Instance()->m_pMenuController->m_pGameData->m_playerName.data()) + "-> " + gcnew String(CMainController::Instance()->m_pMenuController->m_userEmailAddress.data());
		obj->SendNow(s, s2);
		MessageBox(nullptr, _T("程序没有正常退出"), _T("未捕获异常发生！"), MB_OK);
		return EXIT_FAILURE;
	}
}

