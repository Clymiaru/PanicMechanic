#pragma once
#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Debug
{
public:
	static void Init();
	inline static Ref<spdlog::logger>& GetLogger() { return m_Logger; }

	/*---------------------------- LOGGER -----------------------------*/
	#if DEBUG
	template <typename... Args>
	static void Trace(const char* formattedMessage, const Args&... args)
	{
		m_Logger->trace(formattedMessage, args...);
	}

	template <typename... Args>
	static void Log(const char* formattedMessage, const Args&... args)
	{
		m_Logger->debug(formattedMessage, args...);
	}

	template <typename... Args>
	static void Info(const char* formattedMessage, const Args&... args)
	{
		m_Logger->info(formattedMessage, args...);
	}

	template <typename... Args>
	static void Warn(const char* formattedMessage, const Args&... args)
	{
		m_Logger->warn(formattedMessage, args...);
	}

	template <typename... Args>
	static void Error(const char* formattedMessage, const Args&... args)
	{
		m_Logger->error(formattedMessage, args...);
	}

	template <typename... Args>
	static void Critical(const char* formattedMessage, const Args&... args)
	{
		m_Logger->critical(formattedMessage, args...);
	}
	#else
	template <typename... Args>
	static void Trace(const char* formattedMessage, const Args&... args)
	{
	}

	template <typename... Args>
	static void Log(const char* formattedMessage, const Args&... args)
	{
	}

	template <typename... Args>
	static void Info(const char* formattedMessage, const Args&... args)
	{
	}

	template <typename... Args>
	static void Warn(const char* formattedMessage, const Args&... args)
	{
	}

	template <typename... Args>
	static void Error(const char* formattedMessage, const Args&... args)
	{
	}

	template <typename... Args>
	static void Critical(const char* formattedMessage, const Args&... args)
	{
	}
	#endif
private:
	static Ref<spdlog::logger> m_Logger;
};