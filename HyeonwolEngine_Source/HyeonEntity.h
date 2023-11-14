#pragma once
#include "CommonInclude.h"

namespace Hyeon
{
	class HyeonEntity
	{
	public:
		HyeonEntity();
		virtual ~HyeonEntity();

		void SetName(const wstring& name) { mName = name; }
		wstring& GetName() { return mName; }
	private:
		wstring mName;
	};
}
