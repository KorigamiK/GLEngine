cmake_minimum_required(VERSION 3.14)

project(
	engine
	VERSION 0.1.0
	DESCRIPTION "Engine"
	HOMEPAGE_URL "https://korigamik.ml/engine"
	LANGUAGES CXX
)

add_subdirectory(core)

enable_testing()

set(BUILD_TESTING ON CACHE BOOL "Build tests")

if (BUILD_TESTING)
	add_subdirectory(test)
endif()

add_custom_target(
	check
	COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
	DEPENDS test
)

set(GENERATE_DOXYFILE OFF CACHE BOOL "Generate documentation")

if(NOT Emscripten AND GENERATE_DOXYFILE)

	find_package(Doxygen REQUIRED)
	set(DOXYGEN_GENERATE_HTML YES)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in # input
		${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile # output
		@ONLY
	)

endif()

add_custom_target(
	doc
	COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
	COMMENT "Generating API documentation with Doxygen"
	VERBATIM
)
