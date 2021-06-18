#pragma once

template<bool, typename T = void>
struct enable_if
{
};

template<typename T>
struct enable_if<true, T> {
	typedef T type;
};

template<bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;