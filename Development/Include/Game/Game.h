/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <IEngineApplication.h>

class Game : public IEngineApplication
{
public:
	void Init() override;
	void Update() override;
	void Close() override;
};