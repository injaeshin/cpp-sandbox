#pragma once

#include <codecvt> // codecvt_utf8
#include <locale>  // wstring_convert
#include <iostream>
#include "Foo.h"

#include "json/json.hpp"
using json = nlohmann::json;

namespace sb
{
	namespace log
	{
		std::string to_utf8(const std::wstring &wide_string)
		{
			static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
			return utf8_conv.to_bytes(wide_string);
		}

		void to_json(json &j, const LogFoo &l)
		{
			j = json{
				{"act", l.GetAction()},
				{"acnt_idx", l.GetAccountIdx()},
				{"acnt_id", to_utf8(l.GetAccountId())}
			};
		}
	}
}