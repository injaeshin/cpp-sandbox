#pragma once

#include <iostream>

namespace sb
{
	namespace log
	{
		enum class Action : uint8_t
		{
			Create = 1,
			Delete = 2
		};

		struct Foo
		{
			Action      m_action;
			uint32_t    m_account_idx;
			std::wstring m_account_id;
		};

		class LogFoo
		{
		private:
			Foo foo;

		public:
			LogFoo(const Action &act)
			{
				foo.m_action = std::move(act);
			}

		public:
			void Set(uint32_t idx, const std::wstring &id)
			{
				foo.m_account_idx = idx;
				foo.m_account_id = std::move(id);
			}

			inline uint32_t GetAction() const { return static_cast<uint32_t>(foo.m_action); }
			inline uint32_t GetAccountIdx() const { return foo.m_account_idx; }
			inline std::wstring GetAccountId() const { return foo.m_account_id; }
		};		
	}
}