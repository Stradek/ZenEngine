/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Log.h"

#include <Common/CommonDate.h>
#include <Common/TimeTypes.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fwd.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <fmt/core.h>

namespace Engine::Core
{
	// need to replace this constant data later with some kind of config file for engine and it's subsystems
	const std::filesystem::path logDirectoryPath = "logs/";

	std::shared_ptr<spdlog::logger> Log::s_engineLogger;
	std::shared_ptr<spdlog::logger> Log::s_gameLogger;

	void Log::InitEngineLogger(const std::filesystem::path coreLogFilePath)
	{
		auto outputSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		outputSink->set_level(spdlog::level::debug);
		outputSink->set_pattern("[%H:%M:%S] > %v");

		auto logFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(coreLogFilePath.string(), false);
		logFileSink->set_level(spdlog::level::trace);

		s_engineLogger = std::make_shared<spdlog::logger>(spdlog::logger("EngineLogger", { outputSink, logFileSink }));
		s_engineLogger->set_level(spdlog::level::trace);
	}

	void Log::InitGameLogger(const std::filesystem::path gameLogFilePath)
	{
		auto outputSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		outputSink->set_level(spdlog::level::info);
		outputSink->set_pattern("[:%H:%M:%S] %v");

		auto logFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(gameLogFilePath.string(), false);
		logFileSink->set_level(spdlog::level::debug);

		s_gameLogger = std::make_shared<spdlog::logger>(spdlog::logger("GameLogger", {outputSink, logFileSink}));
		s_gameLogger->set_level(spdlog::level::debug);
	}

	void Log::Init()
	{
		const Common::DateTime::Date currentDate {Common::DateTime::GetCurrentDate()};
		const Common::DateTime::Time currentTime = Common::DateTime::GetCurrentTime();

		const std::string datetimeString = fmt::format("{}-{}-{}-{}-{}-{}", currentDate.year, currentDate.month, currentDate.day, currentTime.hour, currentTime.minute, currentTime.second);

		const std::string engineLogFilename = fmt::format("engine-{}.log", datetimeString);
		const std::filesystem::path engineLogPath = logDirectoryPath / "engine" / engineLogFilename;

		const std::string gameLogFilename = fmt::format("game-{}.log", datetimeString);
		const std::filesystem::path gameLogPath = logDirectoryPath / "game" / gameLogFilename;

		InitEngineLogger(engineLogPath);
		InitGameLogger(gameLogPath);
	}
}