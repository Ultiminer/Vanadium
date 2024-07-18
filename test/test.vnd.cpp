#include<iostream>
#include<string>
#include<fstream>
using namespace std;
 
struct Test{
float x;
float y;
};


inline void fibonacci(const unsigned long int & a,const unsigned long int & b,const unsigned long int N)noexcept
{
std::cout<<(a)<<std::endl<<std::flush;

if(N>0)fibonacci(b,a+b,N-1);
}

inline constexpr auto dot_prod(const Test & test)noexcept
{
return test.x*test.y;
}
inline auto read(const std::string & path)noexcept
{
std::string data="";
std::ifstream in{path,ios::binary};
std::string line="";
while(std::getline(in,line))
{
data+=line;
}

return line;
}


int main()
{
Test test={5,5};
test.x=10;
fibonacci(0,1,20);
return 0;
}
