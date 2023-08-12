#ifndef dGofDeMin_Main_cpp
#define dGofDeMin_Main_cpp
//headers
//-//standard
#include <string_view>
#include <iostream>
//content
namespace nGofDeMin
{
}//namespace nGofDeMin
#if defined(dGofDeMin_MakeTexe)
//headers
#include <unordered_map>
#include <functional>
//typedef
using tTestKey = std::string_view;
using tTestCmd = std::function<int(void)>;
using tTestTab = std::unordered_map<tTestKey, tTestCmd>;
//forward
#if defined(dGofDeMin_MakeTest)
extern const tTestTab vTestTab;
#endif//ifd(dGofDeMin_MakeTest)
//actions
int main(int vArgC, const char **vArgV, const char **vEnvi)
{
#if defined(dGofDeMin_MakeTest)
	if(vArgC > 1)
	{
		auto vTestRef = vTestTab.find(vArgV[1]);
		if(vTestRef != vTestTab.end())
		{
			return vTestRef->second();
		}
	}
#endif//ifd(dGofDeMin_MakeTest)
	return EXIT_SUCCESS;
}//main
#endif//ifd(dGofDeMin_MakeTexe)
#if defined(dGofDeMin_MakeTest)
const tTestTab vTestTab = {
	{"tHelloWorld",
	 []()
	 {
		 std::cout << "HelloWorld" << std::endl;
		 return EXIT_SUCCESS;
	 }},
};//vTestTab
#endif//ifd(dGofDeMin_MakeTest)
#endif//dGofDeMin_Main_cpp
