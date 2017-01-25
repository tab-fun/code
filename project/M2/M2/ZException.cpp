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
		message = "\n错误文件：";
		message += _address;
		message += "\n错误行号：";
		message += to_string(_line) + "\n";
		message += "错误详情：";
		message += _detail;
		strcpy(m_errorAddress, _address);
		strcpy(m_errorDetail, _detail);
	}

	void CZException::SaveException()
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		sprintf(m_errorTime, "%d年%d月%d号%d点%d秒%d毫秒", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		// 合并所有的的错误信息
		sprintf(m_allError, "发生错误的日期是：%s\n发生错误的文件是：%s\n发生错误在第%d行\n发生错误的信息是：%s\n\n\n",
			m_errorTime, m_errorAddress, m_numLine, m_errorDetail);

		// 写入文件
		FILE *file = fopen("errorExt.gamelogger", "a");
		fwrite(m_allError, strlen(m_allError), 1, file);
		fclose(file);
	}
}