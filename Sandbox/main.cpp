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
	foo.SetReason(log::Reason::Battle, 10);
	foo.SetReason(log::Reason::Quest, 1010, 2020);
	foo.SetReason(log::Reason::Use, 1234, 123123);
	foo.SetReason(log::Reason::Use, 1235, 123125);

	auto logManager = util::Register::Instance().Get<log::LogManager>(Manager::LOG);
	logManager->SendFoo(foo);
}