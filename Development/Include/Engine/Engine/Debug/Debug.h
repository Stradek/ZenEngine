/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#ifdef _DEBUG

#include <Engine/Core/ISystem.h>
#include <Engine/Core/Memory.h>

namespace Engine::Debug
{
	enum CounterType
	{
		CounterRaw,
		CounterPerSecond
	};

	namespace Performance
	{
		struct StartFrameData
		{
			uint32 startTime;
			bool isFinished = false;
		};

		using NameToStartFrameData = std::unordered_map<std::string, StartFrameData>;

		struct FrameData
		{
			FrameData() : startTime(0), endTime(0), duration(0) {};

			uint32 startTime;
			uint32 endTime;
			uint32 duration;
		};
		static constexpr size_t s_frameDataCircularBufferSize = 256;
		
		using FrameDataCircularBuffer = Core::Memory::CircularBuffer<FrameData, s_frameDataCircularBufferSize>;
		using NameToFrameDataCircularBuffer = std::unordered_map<std::string, FrameDataCircularBuffer>;

		using FrameDataBuffer = std::vector<FrameData>;
		using NameToFrameDataBuffer = std::unordered_map<std::string, FrameDataBuffer>;

		using NameToFrameData = std::unordered_map<std::string, FrameData>;
		using NameToRawTime = std::unordered_map<std::string, uint32>;

		using NameToCounter = std::unordered_map<std::string, uint32>;

		class PerformanceProfiler
		{
		public:
			PerformanceProfiler();

			void UpdateCounterPerSecond();

			void FrameProfilingStart(std::string functionName);
			void FrameProfilingEnd(std::string functionName);

			void IncrementCounter(std::string functionName, uint32 count);

			NameToRawTime GetAvgFrameTimingData();
			uint32 GetCounterValue(CounterType counterType, std::string functionName);

		private:
			std::unique_ptr<NameToStartFrameData> m_nameToStartFrameData;
			std::unique_ptr<NameToFrameDataCircularBuffer> m_nameToFrameDataCircularBuffer;

			std::shared_ptr<NameToCounter> m_nameToCounterRaw;
			std::shared_ptr<NameToCounter> m_nameToCounterPerSecond;
			
			std::shared_ptr<NameToCounter> m_nameToCounterLastSecond;

			NameToFrameDataBuffer GetFrameProfilingData();
		};
	}

	using PerformanceProfilerPtr = std::shared_ptr<Performance::PerformanceProfiler>;
	using PerformanceProfilerRef = PerformanceProfilerPtr&;

	class DebugManager : Engine::Core::ISystem
	{
	public:
		DebugManager();

		void StartUp() override;
		void ShutDown() override;

		PerformanceProfilerRef GetPerformanceProfiler() { return m_performanceProfiler; };

		void StartPerformanceProfiler();

		void Update(const uint32 deltaTime) override;

	private:
		const Common::DateTime::Time m_debugInfoUpdateFrequency;
		
		PerformanceProfilerPtr m_performanceProfiler;

		bool m_shouldLogStats;

		Common::DateTime::Clock m_debugUpdateClock;

		void DebugManager::ClearEngineCounters();
	};
}

#endif // _DEBUG