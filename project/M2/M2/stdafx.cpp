// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// M2.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������
int ConsoleApplicationMain(int argc, char *argv[])
{
	try
	{
		return CMainController::CreateMainController(argc, argv);
	}
	catch (CZException &e)
	{
		auto obj = gcnew SendMailClass;
		auto s = gcnew String("main() : ����û�������˳���");
		auto s2 = gcnew String("���������쳣  ������ң�");
		s2 += gcnew String(CMainController::Instance()->m_pMenuController->m_pGameData->m_playerName.data()) + "-> " + gcnew String(CMainController::Instance()->m_pMenuController->m_userEmailAddress.data());
		obj->SendNow(s, s2);
		if (e.m_pMustToDelete)
		{
			delete e.m_pMustToDelete;
			e.m_pMustToDelete = nullptr;
		}
		OutputDebugStringA(e.message.c_str());

		MessageBox(nullptr, _T("����û�������˳�"), _T("�����쳣��"), MB_OK);

		return EXIT_FAILURE;
	}
	catch (...)
	{
		throw;
	}
}

HANDLE GetConsoleOutputHandle() { return CMainController::Instance()->m_pWindow->m_hBuffer; }