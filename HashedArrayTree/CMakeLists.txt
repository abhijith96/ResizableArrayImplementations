
add_library(HashedArrayTree STATIC HashedArrayTree.cpp HashedArrayTree.h)
target_include_directories(HashedArrayTree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/HashedArrayTree.h)