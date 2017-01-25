#pragma once
#include "Others.h"
#include <string>
#include "ZObject.h"

namespace M2
{
#define CZ_EXCEPTION_DEFAULT_DETAIL "���������һ���쳣��"
	class CZException
	{
	public:
		~CZException();

		CZException(const char *_detail = CZ_EXCEPTION_DEFAULT_DETAIL, CZObject *_pMustToDelete = nullptr, int _line = __LINE__, const char* _address = __FILE__);

		std::string message;
		// ���������ڴ���ĵڼ���
		int m_numLine;
		void *m_pMustToDelete;

		// ���������ʱ��
		char m_errorTime[100];
		// ��������ĵص�
		char m_errorAddress[512];

		// ���������ԭ��
		char m_errorDetail[512];

		// ���еĴ����ܽ���һ��
		char m_allError[400];

		// �����쳣
		void SaveException();
	};
}
