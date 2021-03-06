cmake_minimum_required(VERSION 3.12)

project(NyanCatGame)

add_executable(NyanCatGame main.cpp "ResourceManager.h" "ResourceManager.cpp" "Texture2D.cpp" "Texture2D.h" "Shader.cpp" "Shader.h" "Game.h" "BackgroundObject.cpp" "BackgroundObject.h" "GameObject.h" "GameObject.cpp" "SpriteRenderer.h" "SpriteRenderer.cpp" "Game.cpp" "PlayerObject.cpp" "PlayerObject.h" "EnemyObject.cpp" "EnemyObject.h"   "CloudObject.cpp" "CloudObject.h" "BulletObject.cpp" "BulletObject.h")

target_include_directories(NyanCatGame PRIVATE deps/glm
												deps/stb
											    deps/glfw/include
											    deps/glew/include)

target_link_directories(NyanCatGame PRIVATE deps/glfw/lib-vc2019
											deps/glew/lib/Release/x64)

target_link_libraries(NyanCatGame PRIVATE glfw3.lib
										  glew32.lib
										  opengl32.lib)

add_custom_command(TARGET NyanCatGame POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/glew/bin/Release/x64/glew32.dll" "${CMAKE_BINARY_DIR}/glew32.dll"
				   COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/shaders" "${CMAKE_BINARY_DIR}/shaders"
				   COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/textures" "${CMAKE_BINARY_DIR}/textures"
				   )