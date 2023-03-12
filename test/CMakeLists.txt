cmake_minimum_required(VERSION 3.14)

project(zzTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/windows-set-path.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(zz REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(zz_test source/zz_test.cpp)
target_link_libraries(zz_test PRIVATE zz::zz)
target_compile_features(zz_test PRIVATE cxx_std_20)

add_test(NAME zz_test COMMAND zz_test)

# ---- End-of-file commands ----
