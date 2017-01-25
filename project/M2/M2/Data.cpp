#include "stdafx.h"
#include "Data.h"

namespace M2
{
	TiXmlDocument CData::doc = TiXmlDocument(DOCUMENT_NAME);
	CData::~CData()
	{
		doc.Clear();
	}
}