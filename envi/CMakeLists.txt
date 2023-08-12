cmake_minimum_required(VERSION 3.8)

include(CMakeDependentOption)

# proj

set(vProjNameBase "GofDeMin")
set(vProjNameTlib "t${vProjNameBase}Lib")
set(vProjNameTdll "t${vProjNameBase}Dll")
set(vProjNameTsll "t${vProjNameBase}Sll")
set(vProjNameTexe "t${vProjNameBase}Exe")
set(vProjNameTest "t${vProjNameBase}Try")
set(vProjNameDefs "d${vProjNameBase}_")

set(vProjVnumMajor 0)
set(vProjVnumMinor 0)
set(vProjVnumMicro 0)
set(vProjVnumWhole "${vProjVnumMajor}.${vProjVnumMinor}.${vProjVnumMicro}")

set(vProjDesc "Game Of Developing Mind")

project(${vProjNameBase} VERSION ${vProjVnumWhole} DESCRIPTION ${vProjDesc})

# lang

enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# file

set(vFilePathBase "${CMAKE_SOURCE_DIR}/..")
set(vFilePathCode "${vFilePathBase}/code")
set(vFileListCode "${vFilePathCode}/Main.cpp")
set(vFilePathData "${vFilePathBase}/data")
set(vFilePathMake "${vFilePathBase}/make")

# make

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Project Build Configuration" FORCE)
set(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})

##lib

add_library(${vProjNameTlib} INTERFACE)

##dll

option(oMakeTdll "Make Target: dynamically linked library" OFF)
if(oMakeTdll)
  
  add_library(${vProjNameTdll} SHARED ${vFileListCode})
  target_compile_definitions(${vProjNameTdll} PRIVATE ${vProjNameDefs}MakeTdll)
  target_link_libraries(${vProjNameTdll} PRIVATE ${vProjNameTlib})

endif(oMakeTdll)

##sll

option(oMakeTsll "Make Target: statically linked library" OFF)
if(oMakeTsll)

  add_library(${vProjNameTsll} STATIC ${vFileListCode})
  target_compile_definitions(${vProjNameTsll} PRIVATE ${vProjNameDefs}MakeTsll)
  target_link_libraries(${vProjNameTsll} PRIVATE ${vProjNameTlib})

endif(oMakeTsll)

##exe

option(oMakeTexe "Make Target: executable" ON)
if(oMakeTexe)

  add_executable(${vProjNameTexe} ${vFileListCode})
  target_compile_definitions(${vProjNameTexe} PRIVATE ${vProjNameDefs}MakeTexe)
  target_link_libraries(${vProjNameTexe} PRIVATE ${vProjNameTlib})

endif(oMakeTexe)

# test

cmake_dependent_option(oMakeTest "Make Testing" ON oMakeTexe OFF)
if(oMakeTest)

  include(CTest)

  enable_testing()

endif(oMakeTest)