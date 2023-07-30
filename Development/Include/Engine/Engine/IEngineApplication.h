/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

class IEngineApplication
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Close() = 0;
};