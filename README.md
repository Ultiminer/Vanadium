## About 
Basically C++ with a bit more convenient Syntax
## Changes
* to include libraries use either #include <LIBRARY_NAME> or import LIBRARY_NAME
* vanadium (.vnd) files are header guarded automatically!
* variables are const per default and are called via (u8, u32, i64, f32,...)
* adding a mut infront of a variable makes it mutable: mut u8 -> char, u8-> const char
* if you wanna make a compile time const use CONST: CONST f32 pi=3.14 -> inline constexpr pi=3.14
* if variables are in functions, they are interpreted as const refs per default: fun( type t )-> fun(const type& t)
* if you wanna remove the reference, use the copy keyword: fun(copy type t) -> fun(const type t)
* functions are marked with fn and interpreted as constexpr per default: fn i32 add(i32 x, i32 y){return x+y;} -> inline constexpr const i32 add(const i32& x, const i32& y)noexcept{return x+y;}
* to remove constexpr add mut:  mut fn i32 add(i32 x, i32 y){return x+y;} -> inline const i32 add(const i32& x, const i32& y)noexcept{return x+y;}
* if you emit type information, functions will try to infer the return type: fn fun() -> inline constexpr auto fun()
* you can use assert per default, if assert(A==B) is false, then the program will exit and "assert failure with A==B" will be print to the console
* if you wanna write pure C++ code and are unsure how the transpiler might change it, you can use ""||*"", ""*||"" to mark pure C++. "VANADIUM_CODE ||* CPP_CODE *|| VANADIUM_CODE"
 
