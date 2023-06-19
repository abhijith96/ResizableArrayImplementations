

find_package(GTest CONFIG REQUIRED)
add_executable(TestPushBack TestPushBack.cpp)
target_link_libraries(TestPushBack PUBLIC HashedArrayTree GTest::GTest)

add_executable(TestLocateAndInsert TestLocateAndInsert.cpp)
target_link_libraries(TestLocateAndInsert PUBLIC HashedArrayTree GTest::GTest)

add_executable(TestPopBack TestPopBack.cpp)
target_link_libraries(TestPopBack PUBLIC HashedArrayTree GTest::GTest)