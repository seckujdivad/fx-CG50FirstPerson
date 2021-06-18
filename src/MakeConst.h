#pragma once

template<typename T>
constexpr const T& MakeConst(T& v)
{
    return v;
}