cmake_minimum_required (VERSION 3.0.2)

project (liTools)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(ZLib REQUIRED)

add_subdirectory(dependencies/tinyxml2)
add_subdirectory(dependencies/ttvfs)
add_subdirectory(dependencies/libpng)

add_executable(liDecompress
	liDecompress.cpp
	residmap.cpp
	sndmanifest.cpp
	threadDecompress.cpp
	zpipe.cpp
	letter.cpp
	catalog.cpp
	parse.cpp
	combodb.cpp
	image.cpp
	itemmanifest.cpp
	loctex.cpp
	wordPackDict.cpp
	matrix.cpp
	font.cpp)
	
target_include_directories(liDecompress PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libpng
	${CMAKE_BINARY_DIR}/dependencies/libpng
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/tinyxml2
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/ttvfs/ttvfs)

target_link_libraries(liDecompress
	${ZLIB_LIBRARIES}
	ttvfs ttvfs_cfileapi ttvfs_zip
	tinyxml2_static
	png16_static)
