#pragma once
class IAnimation
{
public:
	IAnimation();

	virtual ~IAnimation();

	virtual void Initialize(void* object_pointer) = 0;
private:
	
};