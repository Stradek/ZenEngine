/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

namespace Engine::Core
{
	class ISystem
	{
	public:
		ISystem(ISystem& other) = delete;
		ISystem& operator=(const ISystem& other) = delete;

		virtual void StartUp() = 0;

		virtual void Update(const uint32 deltaTime) {};
		virtual void Render() {};

		virtual void ShutDown() = 0;
	protected:
		ISystem() {}
	};
}