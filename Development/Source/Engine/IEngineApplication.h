/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

class IEngineApplication
{
public:
	virtual void StartUp() = 0;
	virtual void Update(const double deltaTime) = 0;
	virtual void ShutDown() = 0;
};