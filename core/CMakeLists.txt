project(
	"EngineCore"
	VERSION 0.1.0
)

file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADERS "include/*.hh")

message(STATUS "Sources: ${SOURCES}")
message(STATUS "Headers: ${HEADERS}")

set(DEFINES "")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")

	message(STATUS "Emscripten detected")

else()

	message(STATUS "Native build detected")
	find_package(OpenGL REQUIRED COMPONENTS OpenGL)
	find_package(SDL2 REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(glm REQUIRED)

	target_link_libraries(
		${PROJECT_NAME}
		PUBLIC
			OpenGL::OpenGL
			SDL2::SDL2
			GLEW::GLEW
			glm
	)

endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${GLM_INCLUDE_DIRS}
)

target_compile_options(
	${PROJECT_NAME}
	PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		# -Werror
)

target_compile_definitions(
	${PROJECT_NAME}
	PRIVATE
		${DEFINES}
)

# Symbolic link of shaders to build directory
execute_process(
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_CURRENT_SOURCE_DIR}/shaders
	${CMAKE_CURRENT_BINARY_DIR}/shaders
)