#include <iostream>
#include <memory>

#include "Register.h"
#include "LogManager.h"
#include "Foo.h"

using namespace sb;

void Init()
{
	auto logManager = std::make_shared<log::LogManager>(Manager::LOG);	
	logManager->Init();
	
	util::Register::Instance().Set(logManager);
}

int main()
{
	Init();

	log::LogFoo foo(log::Action::Create);
	foo.Set(100, L"Hello");

	auto logManager = util::Register::Instance().Get<log::LogManager>(Manager::LOG);
	logManager->SendFoo(foo);
}

