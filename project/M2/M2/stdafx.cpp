// stdafx.cpp : 只包括标准包含文件的源文件
// M2.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用
int ConsoleApplicationMain(int argc, char *argv[])
{
	try
	{
		return CMainController::CreateMainController(argc, argv);
	}
	catch (CZException &e)
	{
		auto obj = gcnew SendMailClass;
		auto s = gcnew String("main() : 程序没有正常退出！");
		auto s2 = gcnew String("——捕获异常  来自玩家：");
		s2 += gcnew String(CMainController::Instance()->m_pMenuController->m_pGameData->m_playerName.data()) + "-> " + gcnew String(CMainController::Instance()->m_pMenuController->m_userEmailAddress.data());
		obj->SendNow(s, s2);
		if (e.m_pMustToDelete)
		{
			delete e.m_pMustToDelete;
			e.m_pMustToDelete = nullptr;
		}
		OutputDebugStringA(e.message.c_str());

		MessageBox(nullptr, _T("程序没有正常退出"), _T("捕获异常！"), MB_OK);

		return EXIT_FAILURE;
	}
	catch (...)
	{
		throw;
	}
}

HANDLE GetConsoleOutputHandle() { return CMainController::Instance()->m_pWindow->m_hBuffer; }