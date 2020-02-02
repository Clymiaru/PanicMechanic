#include "Debug.h"

#include <spdlog/sinks/stdout_color_sinks.h>


Ref<spdlog::logger> Debug::m_Logger;

void Debug::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	m_Logger = spdlog::stdout_color_mt("APP");
	m_Logger->set_level(spdlog::level::trace);
}

