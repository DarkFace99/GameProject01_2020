#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Srand
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

/* Core Log Macro */
#define SR_SYSTEM_TRACE(...)	::Srand::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SR_SYSTEM_INFO(...)		::Srand::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SR_SYSTEM_WARN(...)		::Srand::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SR_SYSTEM_ERROR(...)	::Srand::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SR_SYSTEM_FATAL(...)	::Srand::Log::GetCoreLogger()->fatal(__VA_ARGS__)

/* Client Log Macro */
#define SR_TRACE(...)	::Srand::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SR_INFO(...)	::Srand::Log::GetClientLogger()->info(__VA_ARGS__)
#define SR_WARN(...)	::Srand::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SR_ERROR(...)	::Srand::Log::GetClientLogger()->error(__VA_ARGS__)
#define SR_FATAL(...)	::Srand::Log::GetClientLogger()->fatal(__VA_ARGS__)