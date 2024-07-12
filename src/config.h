#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>

#ifdef UNSAFE_VANADIUM
inline void assert(bool condition, const char* msg)noexcept
{
}
inline void print(const char* txt)noexcept
{
}
template<typename T>
inline void printList(T list)noexcept
{
}
#else
inline void assert(bool condition, const char* msg)noexcept
{
    if(condition)return; 
    std::cerr<<msg<<"\n"<<std::flush;
    exit(EXIT_FAILURE);
}
inline void print(std::string_view txt)noexcept
{
    std::cout<<txt<<"\n"<<std::flush; 
}
template<typename T>
inline void printList(T list)noexcept
{
    for(size_t i=0; i<list.size();++i)std::cout<<"at("<<i<<"): "<<list.at(i)<<"\n"<<std::flush; 
}
#endif

#endif