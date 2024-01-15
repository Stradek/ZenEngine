/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Engine::Core
{
	class Log
	{
	public:
		using LoggerRef = std::shared_ptr<spdlog::logger>&;

		static void Init();
		static void Close();

		inline static LoggerRef GetEngineLogger() { return s_engineLogger; }
		inline static LoggerRef GetGameLogger() { return s_gameLogger; }

		using OutputSink = spdlog::sinks::stdout_color_sink_mt;
		using FileSink = spdlog::sinks::basic_file_sink_mt;

		using OutputSinkPtr = std::unique_ptr<OutputSink>;
		using FileSinkPtr = std::unique_ptr<FileSink>;

	private:
		template<class SinkType> 
		static std::unique_ptr<SinkType> CreateSink(const spdlog::level::level_enum level, const std::string pattern, const std::filesystem::path fileSinkPath = "");

		static void InitEngineLogger(const std::filesystem::path coreLogPath);
		static void InitGameLogger(const std::filesystem::path gameLogPath);

	private:
		static std::shared_ptr<spdlog::logger> s_engineLogger;
		static std::shared_ptr<spdlog::logger> s_gameLogger;
	};
}

#define ENGINE_TRACE(...)							::Engine::Core::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_LOG(...)								::Engine::Core::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...)							::Engine::Core::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...)							::Engine::Core::Log::GetEngineLogger()->error(__VA_ARGS__)
#define ENGINE_CRITICAL(...)						::Engine::Core::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define GAME_TRACE(...)								::Engine::Core::Log::GetGameLogger()->trace(__VA_ARGS__)
#define GAME_LOG(...)								::Engine::Core::Log::GetGameLogger()->info(__VA_ARGS__)
#define GAME_WARN(...)								::Engine::Core::Log::GetGameLogger()->warn(__VA_ARGS__)
#define GAME_ERROR(...)								::Engine::Core::Log::GetGameLogger()->error(__VA_ARGS__)
#define GAME_CRITICAL(...)							::Engine::Core::Log::GetGameLogger()->critical(__VA_ARGS__)

#define ENGINE_DEBUG_BREAK()						__debugbreak()

#define ENGINE_STATIC_ASSERT(expression)			static_assert(expression)

#define ENGINE_ASSERT(expression, ...)											\
	if(!((bool) (expression)))													\
	{																			\
		std::string assertMsg = "ASSERT: {}, file {}, line {}, Message: ";		\
		ENGINE_WARN(assertMsg, std::string(#expression), std::string(__FILE__),	\
		(unsigned)(__LINE__));													\
		ENGINE_WARN(__VA_ARGS__);												\
		ENGINE_DEBUG_BREAK();													\
	}

#define ENGINE_FATAL_ASSERT(expression, ...)									\
	if(!((bool) (expression)))													\
	{																			\
		std::string assertMsg = "FATAL ASSERT: {}, file {}, line {}, Message: ";\
		ENGINE_WARN(assertMsg, std::string(#expression), std::string(__FILE__),	\
		(unsigned)(__LINE__));													\
		ENGINE_WARN(__VA_ARGS__);												\
		ENGINE_DEBUG_BREAK();													\
		abort();																\
	}
