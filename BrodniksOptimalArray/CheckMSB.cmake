
include(CheckSymbolExists)
include(CheckCXXCompilerFlag)

SET(MSB_CHECK true)
set(CMAKE_REQUIRED_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

CHECK_CXX_COMPILER_FLAG("-mbuiltin" COMPILER_SUPPORTS_BUILTIN)
if(COMPILER_SUPPORTS_BUILTIN)
    SET(MSB_CHECK true)
endif()

if(MSB_CHECK)
    add_definitions(-DHAS_MSB)
    message(STATUS " Check msb ${MSB_CHECK}")
endif()