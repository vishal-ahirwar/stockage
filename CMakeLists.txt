
#Auto Genrated CMake file by ccli CLI
#Copyright 2023 Vishal Ahirwar. #replace with your copyright notice.
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(stockage)
include_directories(./src/)
option(STATIC_LINK "Enable static linking" ON)

if(STATIC_LINK)
    message(STATUS "Static linking enabled")
    # Ensure static runtime linking on Windows
    if (WIN32)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    endif()
endif()

set(SOURCE ./src/main.cc ./src/stokage.cxx ./src/appmanager.cxx)#add your additional source file here!
add_executable(${PROJECT_NAME} ${SOURCE})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
