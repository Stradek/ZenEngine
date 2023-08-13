/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Core::Memory
{
	template<typename T, const size_t size>
	class CircularBuffer
	{
	public:
		
		CircularBuffer() : m_bufferSize(size), m_currentIndex(0), m_buffer{}
		{
		}

		void EmplaceBack(const T item)
		{
			m_buffer[m_currentIndex] = item;
			m_currentIndex = ++m_currentIndex % size;
		}

		std::vector<T> GetAll()
		{
			std::vector<T> bufferItems;
			for (size_t i = 0; i < m_bufferSize; ++i)
			{
				bufferItems.push_back(m_buffer[i]);
			}

			return bufferItems;
		}

		uint GetCurrentIndex()
		{
			return m_currentIndex;
		}

	private:
		size_t m_bufferSize;
		T m_buffer[size];
		uint m_currentIndex;
	};
}