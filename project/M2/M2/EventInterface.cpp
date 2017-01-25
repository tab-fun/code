#include "stdafx.h"
#include "EventInterface.h"

namespace M2
{
	EventInterface::~EventInterface()
	{
		DWORD exitCode = 0;
		bool rc;
		rc = GetExitCodeThread(CMainController::Instance()->_keyTheardHandle, &exitCode);
	}


	void EventInterface::SetReceiveKeyboardEvent(bool _isReceive)
	{
		CMainController::Instance()->_isReceiveKeyboardEvent = _isReceive;
		if (!CMainController::Instance()->_isCreatedKeyThead)
		{
			CMainController::Instance()->_isCreatedKeyThead = true;
			CMainController::Instance()->_keyTheardHandle = ::CreateThread(0, 0, _keyEventTheadFunc, this, 0, &_threadID);
			String_ str(_T(">>>>>> EventInterface::SetReceiveKeyboardEvent(bool _isReceive): ������һ���̣߳�"));
			str += To_string(CMainController::Instance()->_threadID) + String_(_T("\n"));
			OutputDebugString(str.c_str());
		}
	}

	DWORD WINAPI EventInterface::_keyEventTheadFunc(void *_lpThreadParameter)
	{
		auto hIn = GetStdHandle(STD_INPUT_HANDLE); // ��ȡ��׼�����豸���
		INPUT_RECORD keyRec;
		DWORD readEventsNumber;

		for (;;)
		{
			if (CMainController::Instance()->_isReceiveKeyboardEvent)
			{
				
				ReadConsoleInput(hIn, &keyRec, 1, &readEventsNumber); // ���߳���ִ��
				CMainController::isHaveNewEventMessage = true;
				CMainController::keyMessage = keyRec; //
				//(*(EventInterface*)_lpThreadParameter).DidReceiveKeyboardEvent(keyRec);
			}
			else
			{
				break;
			}
		}

		String_ str(_T(">>>>>> EventInterface::_keyEventTheadFunc(void *_lpThreadParameter): �̣߳�"));
		str += To_string(CMainController::Instance()->_threadID) + String_(_T(" �˳��ˣ�\n"));
		OutputDebugString(str.c_str());
		return 0;
	}
}