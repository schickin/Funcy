project (Funcy.Test.Euler)

file (GLOB FUNCY_TEST_EULER_SOURCES *.cpp util/*.cpp)

add_executable(funcyEuler ${FUNCY_TEST_EULER_SOURCES})
target_link_libraries(funcyEuler ${GMOCK_LIB} ${PTHREAD_LIB})
