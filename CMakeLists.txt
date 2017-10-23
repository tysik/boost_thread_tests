cmake_minimum_required(VERSION 2.8)
project(boost_thread_tests)

add_compile_options(-std=c++11)
find_package(Boost COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(threads_intro threads_intro.cpp)
target_link_libraries(threads_intro ${Boost_LIBRARIES})

add_executable(threads_synchro threads_synchro.cpp)
target_link_libraries(threads_synchro ${Boost_LIBRARIES})
