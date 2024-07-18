#include<iostream>
#include<string>
#include<fstream>
 using namespace std;
 /*
Linear Algebra for vanadium HAHAHAHAHA
*/

inline constexpr float PI=3.141f;

struct Vec2D{
float x;
float y;
};

inline constexpr const Vec2D add(const Vec2D & a,const Vec2D & b)noexcept
{
return {a.x+b.x,a.y+b.y};
}
inline constexpr const Vec2D sub(const Vec2D & a,const Vec2D & b)noexcept
{
return {a.x-b.x,a.y-b.y};
}
inline constexpr const Vec2D prod(const Vec2D & a,const Vec2D & b)noexcept
{
return {a.x*b.x,a.y*b.y};
}
inline constexpr const Vec2D div(const Vec2D & a,const Vec2D & b)noexcept
{
return {a.x/b.x,a.y/b.y};
}
inline constexpr const float dot(const Vec2D & a,const Vec2D & b)noexcept
{
return a.x*b.x+a.y*b.y;
}
