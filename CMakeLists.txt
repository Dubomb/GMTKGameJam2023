cmake_minimum_required(VERSION 3.21)
project(GTMKGameJam2023 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(GTMKGameJam2023 src/main.cpp)
target_link_libraries(GTMKGameJam2023 PRIVATE sfml-graphics)
target_link_libraries(GTMKGameJam2023 PRIVATE sfml-audio)
target_compile_features(GTMKGameJam2023 PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET GTMKGameJam2023 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:GTMKGameJam2023> $<TARGET_FILE_DIR:GTMKGameJam2023> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS GTMKGameJam2023)
