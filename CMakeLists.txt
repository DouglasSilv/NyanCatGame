cmake_minimum_required(VERSION 3.12)

project(EarthDefense)

add_executable(EarthDefense main.cpp "ResourceManager.h" "ResourceManager.cpp" "Texture2D.cpp" "Texture2D.h" "Shader.cpp" "Shader.h" "Game.h" "BackgroundObject.cpp" "BackgroundObject.h" "GameObject.h" "GameObject.cpp" "SpriteRenderer.h" "SpriteRenderer.cpp" "Game.cpp")

target_include_directories(EarthDefense PRIVATE deps/glm
											   deps/stb
											   deps/glfw/include
											   deps/glew/include)

target_link_directories(EarthDefense PRIVATE deps/glfw/lib-vc2019
											deps/glew/lib/Release/x64)

target_link_libraries(EarthDefense PRIVATE glfw3.lib
										  glew32.lib
										  opengl32.lib)

add_custom_command(TARGET EarthDefense POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/glew/bin/Release/x64/glew32.dll" "${CMAKE_BINARY_DIR}/glew32.dll"
				   )