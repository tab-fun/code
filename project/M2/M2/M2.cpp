 // M2.cpp : �������̨Ӧ�ó������ڵ㡣
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
		auto s = gcnew String("main() : ����û�������˳���");
		auto s2 = gcnew String("����δ�����쳣����  ������ң�");
		s2 += gcnew String(CMainController::Instance()->m_pMenuController->m_pGameData->m_playerName.data()) + "-> " + gcnew String(CMainController::Instance()->m_pMenuController->m_userEmailAddress.data());
		obj->SendNow(s, s2);
		MessageBox(nullptr, _T("����û�������˳�"), _T("δ�����쳣������"), MB_OK);
		return EXIT_FAILURE;
	}
}

