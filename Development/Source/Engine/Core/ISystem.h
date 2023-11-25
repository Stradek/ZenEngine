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
		ISystem& operator=(const ISystem& other) = delete;
		
		ISystem() {}
		virtual void StartUp() = 0;

		virtual void Update(const double deltaTime) {};
		virtual void Render() {};

		virtual void ShutDown() = 0;
	};
}