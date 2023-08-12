#ifndef dGofDeMin_Main_cpp
#define dGofDeMin_Main_cpp
//headers
//-//string
#include <fmt/format.h>
#include <string_view>
//-//files:
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
//-//system
#include <GLFW/glfw3.h>
//-//graphics
#include <GL/gl.h>
//-//logic
#include <entt/entity/registry.hpp>
//content
namespace nGofDeMin
{
//typedef
//actions
auto fMain(int vArgC, const char **vArgV, const char **vEnvi)
{
	entt::registry vEcs;

	if(::glfwInit() == GLFW_TRUE)
	{
	}
	else
	{
		return EXIT_FAILURE;
	}
	::GLFWwindow *vWindowHandle;
	vWindowHandle = ::
		glfwCreateWindow(0x200, 0x400, dGofDeMin_ProjName, NULL, NULL);
	::glfwMakeContextCurrent(vWindowHandle);

	while(::glfwWindowShouldClose(vWindowHandle) == GLFW_FALSE)
	{
		::glClearColor(0.0, 0.0, 0.0, 0.0);
		::glClear(GL_COLOR_BUFFER_BIT);

		::glBegin(GL_QUADS);
		::glColor3ub(0xff, 0xff, 0xff);
		::glVertex2f(-0.5f, -0.5f);
		::glVertex2f(+0.5f, -0.5f);
		::glVertex2f(+0.5f, +0.5f);
		::glVertex2f(-0.5f, +0.5f);
		::glEnd();

		::glfwSwapBuffers(vWindowHandle);
		::glfwPollEvents();
		if(::glfwGetKey(vWindowHandle, GLFW_KEY_Q) == GLFW_PRESS)
		{
			::glfwSetWindowShouldClose(vWindowHandle, GLFW_TRUE);
		}
	}//loop

	::glfwTerminate();

	return EXIT_SUCCESS;
}//fMain
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
auto main(int vArgC, const char **vArgV, const char **vEnvi) -> int
{
	boost::filesystem::current_path(dGofDeMin_FilePathBase);

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

	return nGofDeMin::fMain(vArgC, vArgV, vEnvi);
}//main
#endif//ifd(dGofDeMin_MakeTexe)
#if defined(dGofDeMin_MakeTest)
const tTestTab vTestTab = {
	{"tHelloWorld",
	 []()
	 {
		 fmt::println("HelloWorld");
		 return EXIT_SUCCESS;
	 }},
	{"tFileSystem",
	 []()
	 {
		 auto vFilePath = boost::filesystem::current_path();
		 vFilePath			= boost::filesystem::relative(vFilePath);
		 fmt::println("FilePath=={}", vFilePath.c_str());
		 return EXIT_SUCCESS;
	 }},
	{"tEnttSystem",
	 []()
	 {
		 entt::registry vEcs;

		 auto vEnt = vEcs.create();

		 typedef struct
		 {
			 int v;
		 } tCom;

		 auto &vCom = vEcs.emplace<tCom>(vEnt);

		 fmt::println("vCom.v={}", vCom.v);

		 return EXIT_SUCCESS;
	 }},
	{"tGlfwWindow",
	 []()
	 {
		 if(::glfwInit() == GLFW_TRUE)
		 {
		 }
		 else
		 {
			 return EXIT_FAILURE;
		 }
		 ::GLFWwindow *vWindowHandle;
		 vWindowHandle = ::
			 glfwCreateWindow(0x100, 0x100, dGofDeMin_ProjName, NULL, NULL);
		 ::glfwMakeContextCurrent(vWindowHandle);

		 while(::glfwWindowShouldClose(vWindowHandle) == GLFW_FALSE)
		 {
			 ::glfwSwapBuffers(vWindowHandle);
			 ::glfwPollEvents();
			 if(::glfwGetKey(vWindowHandle, GLFW_KEY_Q) == GLFW_PRESS)
			 {
				 ::glfwSetWindowShouldClose(vWindowHandle, GLFW_TRUE);
			 }
		 }//loop

		 ::glfwTerminate();
		 return EXIT_SUCCESS;
	 }},
};		//vTestTab
#endif//ifd(dGofDeMin_MakeTest)
#endif//dGofDeMin_Main_cpp
