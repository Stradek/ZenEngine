/*
	Copyright (c) 2023 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

template<class Derived>
class ISystem
{
public:
	ISystem(ISystem& other) = delete;
	ISystem& operator=(const ISystem& other) = delete;

	// Start up other systems this system depends on
	// Do it by calling Derived::Get()
	virtual void InitDependencies() = 0;

	virtual void PreInit() = 0;
	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual void Destroy() = 0;
protected:
	ISystem() {}
};