set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(GameEngineLauncher src/main.c)

target_link_libraries(GameEngineLauncher PRIVATE Threads::Threads glfw glad::glad ${OPENGL_LIBRARIES})