cmake_minimum_required(VERSION 3.5)

project(polynoms)

add_subdirectory(
	"${CMAKE_CURRENT_SOURCE_DIR}/googletest"
	"googletest"
)

#Main target
file(GLOB sources src/*.cpp)
string(REPLACE "src/main.cpp" "" sources_without_main "${sources}")
file(GLOB headers src/*.h)

add_executable(base ${sources} ${headers})

#Test target
file(GLOB test_sources test/*.cpp)
add_executable(base_test ${test_sources} ${sources_without_main})

set_target_properties(
	base PROPERTIES
	CXX_STANDART 17
	CXX_STANDART_REQUIRED ON
)

target_include_directories(
	base_test PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
	base_test PRIVATE
	gtest gtest_main
)

if (MSVC)
	set(gtest_force_shared_crt ON FORCE)
endif()

#cmake .. -Dgtest_force_shared_crt=ON -G "Visual Studio 16 2019"
