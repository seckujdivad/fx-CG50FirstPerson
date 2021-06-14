#pragma once

//https://en.cppreference.com/w/cpp/types/remove_reference
template<class T> struct remove_reference { typedef T type; };
template<class T> struct remove_reference<T&> { typedef T type; };
template<class T> struct remove_reference<T&&> { typedef T type; };

//#define move(var) (static_cast<remove_reference<decltype(var)>::type&&>(var))

template<class T>
typename remove_reference<T>::type&& move(T&& t) noexcept
{
	return t;
}