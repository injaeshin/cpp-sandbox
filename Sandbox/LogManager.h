#pragma once

#ifdef _DEBUG
#	pragma comment(lib, "spdlogd.lib")
#else
#	pragma comment(lib, "spdlogr.lib")
#endif //_DEBUG

#include <iostream>
#include "Register.h"
#include "Foo.h"

namespace sb
{
	namespace log
	{
		constexpr char LOG_MGR[] = "log";

		class LogManager : public util::IRegister
		{
		public:
			LogManager(const Manager &mgr);
			virtual ~LogManager();
			virtual Manager &GetName() override { return _name; }

			void Init();		
			void SendFoo(const LogFoo &foo);

		private:
			Manager _name;
		};
	}
}