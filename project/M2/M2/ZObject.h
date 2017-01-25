#pragma once
namespace M2
{
	class CZObject
	{
	public:
		CZObject() = default;
		CZObject(const CZObject&) = default;
		CZObject(CZObject&&) = default;
		CZObject& operator= (const CZObject&) = default;
		CZObject& operator= (CZObject&&) = default;
		virtual ~CZObject() = default;

	};
}
