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

	void Log::Init()
	{
		const Common::DateTime::Date currentDate = Common::DateTime::GetCurrentDate();
		const Common::DateTime::TimeDetails currentTime = Common::DateTime::GetTime().GetTimeDetails();

		const std::string datetimeString = fmt::format("{}-{}-{}-{}-{}-{}", currentDate.year, currentDate.month, currentDate.day, currentTime.hours, currentTime.minutes, currentTime.seconds);

		const std::string engineLogFilename = fmt::format("engine-{}.log", datetimeString);
		const std::filesystem::path engineLogPath = engineLogDirectoryPath / engineLogFilename;

		const std::string gameLogFilename = fmt::format("game-{}.log", datetimeString);
		const std::filesystem::path gameLogPath = gameLogDirectoryPath / gameLogFilename;

		InitEngineLogger(engineLogPath);
		InitGameLogger(gameLogPath);
	}

	void Log::InitEngineLogger(const std::filesystem::path logFilePath)
	{
		OutputSinkPtr m_engineOutputSink	= CreateSink<OutputSink>(spdlog::level::debug, defaultLoggingPattern);
		FileSinkPtr m_engineFileSink		= CreateSink<FileSink>(spdlog::level::trace, defaultLoggingPattern, logFilePath);

		s_engineLogger = std::make_shared<spdlog::logger>(
			spdlog::logger(
				"EngineLogger", 
				{ 
					std::move(m_engineOutputSink),
					std::move(m_engineFileSink)
				}
			)
		);
		s_engineLogger->set_level(spdlog::level::trace);
	}

	void Log::InitGameLogger(const std::filesystem::path logFilePath)
	{
		OutputSinkPtr m_gameOutputSink	= CreateSink<OutputSink>(spdlog::level::info, defaultLoggingPattern);
		FileSinkPtr m_gameFileSink		= CreateSink<FileSink>(spdlog::level::trace, defaultLoggingPattern, logFilePath);

		s_gameLogger = std::make_shared<spdlog::logger>(
			spdlog::logger("GameLogger", 
				{ 
					std::move(m_gameOutputSink), 
					std::move(m_gameFileSink) 
				}
			)
		);

		s_gameLogger->set_level(spdlog::level::debug);
	}

	template<class SinkType>
	std::unique_ptr<SinkType> Log::CreateSink(const spdlog::level::level_enum level, const std::string pattern, const std::filesystem::path sinkFilePath)
	{
		static_assert(std::is_base_of_v<spdlog::sinks::sink, SinkType>);

		std::unique_ptr<SinkType> sink;
		if constexpr(std::is_base_of_v<FileSink, SinkType>)
		{
			assert(!sinkFilePath.empty());

			sink = std::make_unique<FileSink>(sinkFilePath.string(), false);
		}
		else
		{
			sink = std::make_unique<SinkType>();
		}

		sink->set_level(level);
		sink->set_pattern(pattern);

		return std::move(sink);
	}

	void Log::Close()
	{
		GAME_LOG("Closing Game Logging System...");
		s_gameLogger.reset();

		ENGINE_LOG("Closing Engine Logging System...");
		s_engineLogger.reset();
	}
}