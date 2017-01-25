#pragma once
#include <wincon.h>

namespace M2
{
	class EventInterface
	{
	public:
		~EventInterface();

		virtual void SetReceiveKeyboardEvent(bool _isReceive);
		virtual void DidReceiveKeyboardEvent(const INPUT_RECORD _keyMessage) {}

	private:

		static DWORD WINAPI _keyEventTheadFunc(void *_lpThreadParameter);
		bool _isCreatedKeyThead = false;
		bool _isReceiveKeyboardEvent = false;
		DWORD _threadID;
		HANDLE _keyTheardHandle = nullptr;
	};

	
}