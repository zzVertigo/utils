cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    zz
    VERSION 0.1.0
    DESCRIPTION "Personal C++ utility header(s)"
    HOMEPAGE_URL "https://github.com/zzVertigo/utils"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    zz_zz INTERFACE
    include/zz/zz.h
    include/zz/fileio.h
    include/zz/logging.h
)
add_library(zz::zz ALIAS zz_zz)

set_property(
    TARGET zz_zz PROPERTY
    EXPORT_NAME zz
)

target_include_directories(
    zz_zz ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(zz_zz INTERFACE cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
