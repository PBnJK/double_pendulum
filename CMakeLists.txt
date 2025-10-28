cmake_minimum_required(VERSION 3.28)
project(
	double_pendulum
	VERSION 0.1.0
)

add_executable(
	double_pendulum
	"src/main.c"
)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	raylib
	GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
	FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

target_include_directories(double_pendulum PRIVATE ${PROJECT_SOURCE_DIR}/inc)

target_compile_features(double_pendulum PRIVATE c_std_99)
target_compile_options(double_pendulum PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(double_pendulum PRIVATE ASSETS_DIR="${PROJECT_SOURCE_DIR}/assets")

target_link_libraries(double_pendulum PRIVATE raylib m)
