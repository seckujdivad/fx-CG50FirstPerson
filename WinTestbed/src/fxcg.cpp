//horrible solution, but I don't want to have to reimplement the entirety of PrizmSDK for wxWidgets
#pragma warning(push, 0)
namespace fxcg
{
#include "World.cpp"
#include "WorldTracing.cpp"
#include "Q_rsqrt.cpp"
#include "Maths.cpp"
}
#pragma warning(pop)