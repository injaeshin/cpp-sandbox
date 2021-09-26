#pragma once

#include <iostream>
#include "Foo.h"

#include "json/json.hpp"
using json = nlohmann::json;

namespace sb
{
	namespace log
	{
		// https://codingtidbit.com/2020/02/09/c17-codecvt_utf8-is-deprecated
		// Convert a wide Unicode string to an UTF8 string
		std::string utf8_encode(const std::wstring &wstr)
		{
			if (wstr.empty()) return std::string();
			int size_needed = ::WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
			std::string strTo(size_needed, 0);
			::WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
			return strTo;
		}

		// Convert an UTF8 string to a wide Unicode String
		std::wstring utf8_decode(const std::string &str)
		{
			if (str.empty()) return std::wstring();
			int size_needed = ::MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
			std::wstring wstrTo(size_needed, 0);
			::MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
			return wstrTo;
		}

		void to_json(json &j, const LogFoo &l)
		{
			j = json{
				{"act", l.GetAction()},
				{"acnt_idx", l.GetAccountIdx()},
				{"acnt_id", utf8_encode(l.GetAccountId())}
			};

			if (l.IsReasonEmpty())
				return;

			auto arr = json::array();
			for (auto &v : l.GetReasonValues())
				arr.push_back({ { "id", v.id }, { "idx", v.idx } });

			j["rsn"].emplace("rsn_type", l.GetReason());
			j["rsn"].emplace("rsn_value", arr);
		}
	}
}