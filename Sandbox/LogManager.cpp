#include "LogManager.h"

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/tcp_sink.h"

#include "json/json.hpp"
#include "ToJson.h"

using json = nlohmann::json;
using namespace sb;

log::LogManager::LogManager(const Manager &mgr)
{
	_name = std::move(mgr);
}

log::LogManager::~LogManager()
{
	spdlog::shutdown();
}

void log::LogManager::Init()
{
	try
	{
		spdlog::init_thread_pool(8192, 2);

		//spdlog::sinks::tcp_sink_config cfg("127.0.0.1", 5170);
		//auto tcp_sink = std::make_shared<spdlog::sinks::tcp_sink_st>(cfg);
		//tcp_sink->set_level(spdlog::level::info);
		//tcp_sink->set_pattern("%v");

		auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st >();
		stdout_sink->set_level(spdlog::level::info);
		stdout_sink->set_pattern("%v");

		std::vector<spdlog::sink_ptr> sinks{ stdout_sink/*, tcp_sink*/ };
		auto logger = std::make_shared<spdlog::async_logger>(LOG_MGR, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

		logger->set_error_handler([](const std::string &msg) {
			throw std::runtime_error(msg);
		});

		spdlog::register_logger(logger);
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void log::LogManager::SendFoo(const log::LogFoo &foo)
{
	json j = foo;
	spdlog::get(LOG_MGR)->info(j.dump());
}