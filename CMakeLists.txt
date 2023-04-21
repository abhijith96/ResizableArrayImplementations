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
add_subdirectory(TreeArray)
add_subdirectory(TarjanAndZewicksOptimalArrayLocateOptimized)



add_executable(HATArrayTest mainHAT.cpp)
target_link_libraries(HATArrayTest PRIVATE HashedArrayTree)
target_link_libraries(HATArrayTest PRIVATE BrodniksOptimalArray)

add_executable(BrodnikArrayTest mainBrodnik.cpp)
target_link_libraries(BrodnikArrayTest PRIVATE BrodniksOptimalArray)

add_executable(TarjansArrayTest mainTarjan.cpp)
target_link_libraries(TarjansArrayTest PRIVATE TarjanAndZewicksOptimalArray)


add_executable(VectorTest mainVector.cpp)

add_executable(TreeArrayTest TreeArrayTest.cpp)

add_executable(TarjanAndZewicksOptimalArrayLocateOptimizedTest TarjansArrayLocateOptimizedTest.cpp)

add_executable(TarjanAndZewicksOptimalArrayLocateOptimizedLocateUsingMSBTest TarnsArrayLocateOptimizedLocateUsingMSBTest.cpp)

add_executable(TarjanArrayRGrowsTest TarjansArrayRGrowsTest.cpp)


if( supported )
    message(STATUS "IPO / LTO enabled")
    set_property(TARGET ResizableArrayImplementations PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    set_property(TARGET BrodnikArrayTest PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()
