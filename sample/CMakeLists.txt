project("EngineTest" LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE EngineCore)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -s USE_WEBGL2=1 -s WASM=1 -std=c++20 -s USE_SDL=2 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 -sASSERTIONS=1") #
endif()