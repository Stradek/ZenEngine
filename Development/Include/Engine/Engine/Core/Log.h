/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <spdlog/logger.h>

#include <filesystem>

namespace Engine::Core
{
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& Log::GetEngineLogger() { return s_engineLogger; }
		inline static std::shared_ptr<spdlog::logger>& Log::GetGameLogger() { return s_gameLogger; }

	private:
		static void InitEngineLogger(const std::filesystem::path coreLogPath);
		static void InitGameLogger(const std::filesystem::path gameLogPath);

	private:
		static std::shared_ptr<spdlog::logger> s_engineLogger;
		static std::shared_ptr<spdlog::logger> s_gameLogger;
	};
}

#define CORE_TRACE(...)		::Engine::Core::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define CORE_LOG(...)		::Engine::Core::Log::GetEngineLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)		::Engine::Core::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)		::Engine::Core::Log::GetEngineLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...)	::Engine::Core::Log::GetEngineLogger()->critical(__VA_ARGS__)
