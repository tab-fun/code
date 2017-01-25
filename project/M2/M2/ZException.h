#pragma once
#include "Others.h"
#include <string>
#include "ZObject.h"

namespace M2
{
#define CZ_EXCEPTION_DEFAULT_DETAIL "这儿发生了一个异常！"
	class CZException
	{
	public:
		~CZException();

		CZException(const char *_detail = CZ_EXCEPTION_DEFAULT_DETAIL, CZObject *_pMustToDelete = nullptr, int _line = __LINE__, const char* _address = __FILE__);

		std::string message;
		// 发生错误在代码的第几行
		int m_numLine;
		void *m_pMustToDelete;

		// 发生错误的时间
		char m_errorTime[100];
		// 发生错误的地点
		char m_errorAddress[512];

		// 发生错误的原因
		char m_errorDetail[512];

		// 所有的错误总结在一起
		char m_allError[400];

		// 保存异常
		void SaveException();
	};
}
