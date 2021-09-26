#pragma once

#include <iostream>

namespace sb
{
	enum class Action : std::uint8_t
	{
		None = 0,
		One = 1,
		Two = 2
	};

	void Bar1(int32_t no)
	{
		std::cout << no << std::endl;
	}

	void Bar2(int32_t no, int32_t idx)
	{
		std::cout << no << std::endl;
		std::cout << idx << std::endl;
	}

	template<class Action, typename ... Types>
	void Foo(Action act, Types ... args)
	{
		switch (act)
		{
		case Action::One:
		{
			std::cout << "One" << std::endl;
			//Bar1(args...);
		}
		break;
		case Action::Two:
		{
			std::cout << "Two" << std::endl;
			//Bar2(args...);
		}
		break;
		default:
			break;
		}
	};
};