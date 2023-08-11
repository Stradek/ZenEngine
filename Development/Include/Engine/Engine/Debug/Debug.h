/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <Core/ISystem.h>

namespace Engine::Debug
{
	namespace Performance
	{
		struct StartFrameData
		{
			time_t frameStartTime;
			bool isFinished = false;
		};

		typedef std::unordered_map<std::string, StartFrameData> NameToStartFrameData;


		struct FrameData
		{
			time_t frameStartTime;
			time_t frameFinishTime;
			time_t frameDuration;
		};

		static constexpr int maxFrameArrayItems = 256;
		typedef std::array<FrameData, maxFrameArrayItems> FrameDataArray;

		typedef std::unordered_map<std::string, FrameDataArray> NameToFrameDataArray;
		typedef std::unordered_map<std::string, FrameData> NameToFrameData;

		typedef std::unordered_map<std::string, time_t> NameToRawTime;

		class PerformanceProfiler
		{
		public:
			PerformanceProfiler();

			void FrameProfilingStart(std::string functionName);
			void FrameProfilingEnd(std::string functionName);

			NameToFrameDataArray GetFrameProfilingData();
			NameToRawTime GetAvgFrameProfilingData();
		private:
			int m_frameArrayIterator;
			NameToFrameDataArray m_nameToFrameDataArray;

			NameToStartFrameData m_nameToStartFrameData;
		};
	}

	class DebugManager : Engine::Core::ISystem
	{
	public:
		void StartUp() override;
		void ShutDown() override;

		Performance::PerformanceProfiler& GetPerformanceProfiler() { return m_performanceProfiler; };

	private:
		Performance::PerformanceProfiler m_performanceProfiler;
	};
}