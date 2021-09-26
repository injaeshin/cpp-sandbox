#pragma once

#include <iostream>
namespace sb
{
	namespace util
	{

		enum class eError : unsigned char
		{
			SUCCESS = 0,					//!< 성공!
			FAIL,							//!< 실패
		};

#ifdef _DEBUG
#define _CheckReturnErrorCode   return __FUNCTION__ + //FUNCTION을 가지고 가야 DEBUG_LOG가 정상적으로 출력됨..
		eError operator+(const char* szFunctionName, eError eErrorCode) //내부에서 에러코드를 검사
		{
			if (eError::SUCCESS != eErrorCode)
			{
				std::cout << szFunctionName << std::endl;
				std::cout << "Fail" << std::endl;
			}

			return eErrorCode;
		}
#else
#define _CheckReturnErrorCode return
#endif

		eError Foo()
		{
			_CheckReturnErrorCode eError::SUCCESS;
		}

		void Bar()
		{
			auto ret = Foo();
			if (ret == eError::FAIL)
				std::cout << "fail";
		}
	}
}