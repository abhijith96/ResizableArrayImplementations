cmake_minimum_required(VERSION 3.24)
include(CheckIPOSupported)

project(ResizableArrayImplementations)
set(CMAKE_CXX_STANDARD 17)
if (CMAKE_BUILD_TYPE EQUAL "Release")
    check_ipo_supported(RESULT supported OUTPUT error)
endif()
add_subdirectory(HashedArrayTree)
add_subdirectory(BrodniksOptimalArray)
add_subdirectory(TarjanAndZewicksOptimalArray)



add_executable(ResizableArrayImplementations1 mainHAT.cpp)
target_link_libraries(ResizableArrayImplementations1 PRIVATE HashedArrayTree)
target_link_libraries(ResizableArrayImplementations1 PRIVATE BrodniksOptimalArray)

add_executable(ResizableArrayImplementations2 mainBrodnik.cpp)
target_link_libraries(ResizableArrayImplementations2 PRIVATE BrodniksOptimalArray)

add_executable(ResizableArrayImplementations3 mainTarjan.cpp)
target_link_libraries(ResizableArrayImplementations3 PRIVATE TarjanAndZewicksOptimalArray)


add_executable(ResizableArrayImplementations0 mainVector.cpp)


if( supported )
    message(STATUS "IPO / LTO enabled")
    set_property(TARGET ResizableArrayImplementations PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    set_property(TARGET ResizableArrayImplementations2 PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()
