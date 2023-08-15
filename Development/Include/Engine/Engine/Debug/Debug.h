/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#ifdef _DEBUG

#include <Core/ISystem.h>
#include <Core/Memory.h>

namespace Engine::Debug
{
	namespace Performance
	{
		struct StartFrameData
		{
			uint32 startTime;
			bool isFinished = false;
		};

		typedef std::unordered_map<std::string, StartFrameData> NameToStartFrameData;


		struct FrameData
		{
			FrameData() : startTime(0), endTime(0), duration(0) {};

			uint32 startTime;
			uint32 endTime;
			uint32 duration;
		};
		static constexpr size_t s_frameDataBufferSize = 256;
		typedef Core::Memory::CircularBuffer<FrameData, s_frameDataBufferSize> FrameDataCircularBuffer;
		typedef std::unordered_map<std::string, FrameDataCircularBuffer> NameToFrameDataCircularBuffer;

		typedef std::vector<FrameData> FrameDataBuffer;
		typedef std::unordered_map<std::string, FrameDataBuffer> NameToFrameDataBuffer;

		typedef std::unordered_map<std::string, FrameData> NameToFrameData;
		typedef std::unordered_map<std::string, uint32> NameToRawTime;

		class PerformanceProfiler
		{
		public:
			PerformanceProfiler();

			void FrameProfilingStart(std::string functionName);
			void FrameProfilingEnd(std::string functionName);

			NameToRawTime GetAvgFrameProfilingData();
		private:
			NameToStartFrameData m_nameToStartFrameData;
			NameToFrameDataCircularBuffer m_nameToFrameDataCircularBuffer;

			NameToFrameDataBuffer GetFrameProfilingData();
		};
	}

	class DebugManager : Engine::Core::ISystem
	{
	public:
		void StartUp() override;
		void ShutDown() override;

		Performance::PerformanceProfiler& GetPerformanceProfiler() { return m_performanceProfiler; };

		void Update(const uint32 deltaTime) override;

		void AddToUpdateCounter();
		void AddToRenderFrameCounter();
	private:
		const Common::DateTime::Time m_debugInfoUpdateFrequency = Common::DateTime::Time(Common::DateTime::SECOND_TO_NANOSECONDS);
		
		Performance::PerformanceProfiler m_performanceProfiler;

		bool m_shouldLogStats = false;

		uint m_engineUpdatesLastSecondCounter = 0;
		uint m_renderedFramesLastSecondCounter = 0;

		uint m_currentSecondUpdatesCount = 0;
		uint m_currentSecondRenderFramesCount = 0;

		Common::DateTime::Clock m_debugUpdateClock;

		void DebugManager::ClearEngineCounters();
	};
}

#endif // _DEBUG