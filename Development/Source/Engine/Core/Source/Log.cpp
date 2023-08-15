/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#include "Log.h"

#include <spdlog/sinks/sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fwd.h>
#include <fmt/core.h>

namespace Engine::Core
{
	// need to replace this constant data later with some kind of config file for engine and it's subsystems
	const std::filesystem::path logDirectoryPath = "logs/";
	const std::filesystem::path engineLogDirectoryPath = logDirectoryPath / "engine";
	const std::filesystem::path gameLogDirectoryPath = logDirectoryPath / "game";

	const std::string defaultLoggingPattern = "[%n - %H:%M:%S] > %v";

	std::shared_ptr<spdlog::logger> Log::s_engineLogger;
	std::shared_ptr<spdlog::logger> Log::s_gameLogger;

	template<class SinkType>
	std::shared_ptr<SinkType> Log::CreateSink(const spdlog::level::level_enum level, const std::string pattern, const std::filesystem::path sinkFilePath)
	{
		static_assert(std::is_base_of_v<spdlog::sinks::sink, SinkType>);

		std::shared_ptr<SinkType> sink = nullptr;
		if constexpr(std::is_base_of_v<file_sink, SinkType>)
		{
			assert(!sinkFilePath.empty());

			sink = std::make_shared<SinkType>(sinkFilePath.string(), false);
		}
		else
		{
			sink = std::make_shared<SinkType>();
		}

		sink->set_level(level);
		sink->set_pattern(pattern);

		return sink;
	}

	std::shared_ptr<Log::output_sink> Log::CreateOutputSink(const spdlog::level::level_enum level)
	{
		auto outputSink = CreateSink<output_sink>(level, defaultLoggingPattern);
		return outputSink;
	}

	std::shared_ptr<Log::file_sink> Log::CreateFileSink(const spdlog::level::level_enum level, const std::filesystem::path sinkFilePath)
	{
		auto fileSink = CreateSink<file_sink>(spdlog::level::trace, defaultLoggingPattern, sinkFilePath);
		return fileSink;
	}

	void Log::InitEngineLogger(const std::filesystem::path engineLogFilePath)
	{
		const auto outputSink	= CreateOutputSink(spdlog::level::debug);
		const auto fileSink		= CreateFileSink(spdlog::level::debug, engineLogFilePath);

		s_engineLogger = std::make_shared<spdlog::logger>(spdlog::logger("EngineLogger", { outputSink, fileSink }));
		s_engineLogger->set_level(spdlog::level::trace);
	}

	void Log::InitGameLogger(const std::filesystem::path gameLogFilePath)
	{
		const auto outputSink = CreateOutputSink(spdlog::level::info);
		const auto fileSink = CreateFileSink(spdlog::level::debug, gameLogFilePath);

		s_gameLogger = std::make_shared<spdlog::logger>(spdlog::logger("GameLogger", {outputSink, fileSink}));
		s_gameLogger->set_level(spdlog::level::debug);
	}

	void Log::Init()
	{
		const Common::DateTime::Date currentDate = Common::DateTime::GetCurrentDate();
		const Common::DateTime::TimeDetails currentTime = Common::DateTime::GetCurrentTime().GetTime();

		const std::string datetimeString = fmt::format("{}-{}-{}-{}-{}-{}", currentDate.year, currentDate.month, currentDate.day, currentTime.hours, currentTime.minutes, currentTime.seconds);

		const std::string engineLogFilename = fmt::format("engine-{}.log", datetimeString);
		const std::filesystem::path engineLogPath = engineLogDirectoryPath / engineLogFilename;

		const std::string gameLogFilename = fmt::format("game-{}.log", datetimeString);
		const std::filesystem::path gameLogPath = gameLogDirectoryPath / gameLogFilename;

		InitEngineLogger(engineLogPath);
		InitGameLogger(gameLogPath);
	}

}