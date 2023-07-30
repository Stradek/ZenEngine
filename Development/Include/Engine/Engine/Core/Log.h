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
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& Log::GetEngineLogger() { return s_engineLogger; }
		inline static std::shared_ptr<spdlog::logger>& Log::GetGameLogger() { return s_gameLogger; }

	private:
		typedef spdlog::sinks::stdout_color_sink_mt output_sink;
		typedef spdlog::sinks::basic_file_sink_mt file_sink;

	private:
		template<class SinkType> 
		static std::shared_ptr<SinkType>	CreateSink(const spdlog::level::level_enum level, const std::string pattern, const std::filesystem::path fileSinkPath = "");

		static std::shared_ptr<output_sink>	CreateOutputSink(const spdlog::level::level_enum level);
		static std::shared_ptr<file_sink>	CreateFileSink(const spdlog::level::level_enum level, const std::filesystem::path fileSinkPath);

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

#define ENGINE_ASSERT(expression, msg)				if(!((bool) (expression)))														\
													{																				\
														std::string assertMsg = "ASSERT: {}, file {}, line {}, Message: ";			\
														assertMsg += msg;															\
														ENGINE_WARN(assertMsg,														\
														std::string(#expression), std::string(__FILE__), (unsigned)(__LINE__));		\
													}

#define ENGINE_FATAL_ASSERT(expression, msg)		if(!((bool) (expression)))														\
													{																				\
														std::string assertMsg = "FATAL ASSERT: {}, file {}, line {}, Message: ";	\
														assertMsg += msg;															\
														ENGINE_WARN(assertMsg,														\
														std::string(#expression), std::string(__FILE__), (unsigned)(__LINE__));		\
														abort();																	\
													}
