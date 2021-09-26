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

	template<class Action, typename ... Types>
	void Foo(Action act, Types ... args)
	{
		//std::cout << static_cast<int>(act) << std::endl;
		switch (act)
		{
		case Action::One:
		{
			std::cout << "One" << std::endl;
			//	//Bar(args...);
			break;
		}
		default:
			break;
		}
	};
};