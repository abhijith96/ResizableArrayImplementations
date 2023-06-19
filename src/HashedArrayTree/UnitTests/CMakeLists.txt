

find_package(GTest CONFIG REQUIRED)
add_executable(TestPushBack TestPushBack.cpp)
target_link_libraries(TestPushBack PUBLIC HashedArrayTree GTest::GTest)