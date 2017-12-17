cmake_minimum_required (VERSION 2.6)
project (st)
add_executable(st main.c maths.c)

SET(GCC_CONVERAGE_COMPILE_FLAGS "-g -Wall VERBOSE=1")
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
#if(DEFINED TEST) 

#endif
