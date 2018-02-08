#pragma once

#include "EnMath.h"

template<typename T>
class container
{
public:
	container();
	void Set(T maximum);
	T current;
	T maximum;
};

template<typename T>
inline container<T>::container()
{
	current = 0;
	maximum = 0;
}

template<typename T>
inline void container<T>::Set(T maximum)
{
	this->maximum = maximum;
	this->current = maximum;
}