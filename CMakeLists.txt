
cmake_minimum_required(VERSION 3.15)
project(Logger VERSION 1.0.0 LANGUAGES CXX)


# If this is a header-only library:
add_library(Logger INTERFACE)

# If the library has sources and needs to be compiled:
# add_library(Logger STATIC
#   src/Logger.cpp
#   src/OtherSource.cpp
# )


# Add include directories for consumers
target_include_directories(Logger
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:src>
)


# (Optional) Link dependencies if your library depends on others
# target_link_libraries(Logger INTERFACE OtherLib)
