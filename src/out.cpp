#include<iostream>
#include<string>
/*---- Fizz Buzz ----*/
#include<iostream>
#include<string>
#include "string" 
#include "iostream" 


inline auto input(const std::string & text)noexcept
{
std::string ret="";
std::cout<<(text)<<std::endl<<std::flush;


std::getline(std::cin,ret);
    return ret;}


int main()
{
const long int num=std::atoi(((input("Give me a number:"))).c_str());
std::string ret="";
if(num%5==0)ret+="Fizz";
if(num%7==0)ret+="Buzz";

std::cout<<(ret)<<std::endl<<std::flush;

}



