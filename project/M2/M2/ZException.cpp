#include "stdafx.h"
#include "ZException.h"

namespace M2
{

	CZException::~CZException()
	{
	}

	CZException::CZException(const char *_detail, CZObject *_pMustToDelete, int _line, const char* _address)
	{
		m_pMustToDelete = _pMustToDelete;
		m_numLine = _line;
		message = "\n�����ļ���";
		message += _address;
		message += "\n�����кţ�";
		message += to_string(_line) + "\n";
		message += "�������飺";
		message += _detail;
		strcpy(m_errorAddress, _address);
		strcpy(m_errorDetail, _detail);
	}

	void CZException::SaveException()
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		sprintf(m_errorTime, "%d��%d��%d��%d��%d��%d����", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		// �ϲ����еĵĴ�����Ϣ
		sprintf(m_allError, "��������������ǣ�%s\n����������ļ��ǣ�%s\n���������ڵ�%d��\n�����������Ϣ�ǣ�%s\n\n\n",
			m_errorTime, m_errorAddress, m_numLine, m_errorDetail);

		// д���ļ�
		FILE *file = fopen("errorExt.gamelogger", "a");
		fwrite(m_allError, strlen(m_allError), 1, file);
		fclose(file);
	}
}