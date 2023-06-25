/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine
{
	namespace Common
	{
		namespace Time
		{
			typedef std::chrono::high_resolution_clock					high_res_clock;
			typedef std::chrono::time_point<high_res_clock>				time_point;
			typedef std::chrono::milliseconds							milliseconds;
			typedef std::chrono::nanoseconds							nanoseconds;
			typedef std::chrono::duration<double, milliseconds>			milli_duration;

			using std::chrono::duration_cast;

			const unsigned int SECOND = 1000;

			/*
				typedef std::chrono::steady_clock							steady_clock;
				typedef std::chrono::high_resolution_clock					high_res_clock;
				typedef std::chrono::time_point<high_res_clock>				time_point;
				typedef std::chrono::milliseconds							milliseconds;
				typedef std::chrono::nanoseconds							nanoseconds;
				typedef std::chrono::duration<long long, std::nano>			nano_duration;
			*/
			class Clock
			{
			public:
				Clock();
				~Clock();

				const nanoseconds GetDuration();
				const double GetDurationAsDouble();

				void Start();
				void Stop();
				void Reset();

			private:
				time_point m_startTime = time_point::min();
				time_point m_endTime;

				bool m_isRunning = false;
			};


			static time_point GetCurrentTime()
			{
				return high_res_clock::now();
			}

			static milliseconds AsMilliseconds(const double timeInMilliseconds)
			{
				milliseconds durationInMilliseconds = duration_cast<milliseconds>(
					std::chrono::duration<double, std::milli>(timeInMilliseconds)
				);

				return durationInMilliseconds;
			}

			static nanoseconds AsNanoseconds(milliseconds durationInMilliseconds)
			{
				nanoseconds durationInNanoseconds = durationInMilliseconds;

				return durationInNanoseconds;
			}

			static nanoseconds AsNanoseconds(const double timeInMilliseconds)
			{
				nanoseconds durationInNanoseconds = duration_cast<nanoseconds>(
					std::chrono::duration<double, std::milli>(timeInMilliseconds)
				);

				return durationInNanoseconds;
			}

			static const long long DurationToUInt(nanoseconds duration)
			{
				return duration.count();
			}

			static const long long MillisecondsToUInt(const double timeInMilliseconds)
			{
				nanoseconds durationInNanoseconds = AsNanoseconds(timeInMilliseconds);

				return durationInNanoseconds.count();
			}
		}
	}
}