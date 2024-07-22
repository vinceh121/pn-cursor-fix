cmake_minimum_required(VERSION 2.8.12)
project(cursor-fix)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER   x86_64-w64-mingw32-gcc)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# fix "unrecognized option -rdynamic"
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

add_executable(cursor-fix src/main.c)

