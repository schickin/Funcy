cmake_minimum_required(VERSION 2.6)

project (Funcy.Test)

set (GMOCK_INCLUDE_DIR /usr/local/include)

find_library (GMOCK_LIB gmock)

file (GLOB FUNCY_TEST_SOURCES *.cpp util/*.cpp)

include_directories(${FUNCY_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR} .)

add_executable(funcyTest ${FUNCY_TEST_SOURCES})
target_link_libraries(funcyTest ${GMOCK_LIB} ${PTHREAD_LIB})
