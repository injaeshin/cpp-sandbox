#pragma once

#include <iostream>
namespace sb
{
	namespace util
	{

		enum class eError : unsigned char
		{
			SUCCESS = 0,					//!< ����!
			FAIL,							//!< ����
		};

#ifdef _DEBUG
#define _CheckReturnErrorCode   return __FUNCTION__ + //FUNCTION�� ������ ���� DEBUG_LOG�� ���������� ��µ�..
		eError operator+(const char* szFunctionName, eError eErrorCode) //���ο��� �����ڵ带 �˻�
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