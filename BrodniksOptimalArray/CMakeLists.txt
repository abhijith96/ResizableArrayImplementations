

include(CheckMSB.cmake)

add_library(BrodniksOptimalArray STATIC BrodniksOptimalArray.h BrodniksOptimalArrayUtil.cpp)
target_include_directories(BrodniksOptimalArray INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/BrodniksOptimalArray.h)


if( supported )
    set_property(TARGET BrodniksOptimalArray PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
