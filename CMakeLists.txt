cmake_minimum_required(VERSION 3.21)
project(GMTKGameJam2023 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(GMTKGameJam2023 src/main.cpp src/displayinfo.cpp src/game.cpp src/level.cpp src/fontlibrary.cpp src/texturelibrary.cpp)
target_link_libraries(GMTKGameJam2023 PRIVATE sfml-graphics)
target_link_libraries(GMTKGameJam2023 PRIVATE sfml-audio)
target_compile_features(GMTKGameJam2023 PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
	add_custom_command(TARGET GMTKGameJam2023 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:GMTKGameJam2023> $<TARGET_FILE_DIR:GMTKGameJam2023> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS GMTKGameJam2023)
