cmake_minimum_required(VERSION 3.10)

project(liTools)

set(CMAKE_FIND_FRAMEWORK LAST)

find_package(PNG REQUIRED 1.6)
find_package(ZLIB REQUIRED)

add_subdirectory(External/ttvfs)
add_subdirectory(External/tinyxml2)

add_library(common STATIC
				   image.cpp
				   image.h
				   residmap.cpp
				   residmap.h
				   sndmanifest.cpp
				   sndmanifest.h
				   stringTools.cpp
				   stringTools.h
				   zpipe.cpp
				   zpipe.h)
				   
target_include_directories(common PUBLIC ${TTVFS_INCLUDE_DIRS}
										 ${PNG_INCLUDE_DIRS}
										 External/tinyxml2)
target_compile_features(common PUBLIC cxx_auto_type)

add_executable(liDecompress liDecompress.cpp
							threadDecompress.cpp
							threadDecompress.h)
target_include_directories(liDecompress PUBLIC ${TTVFS_INCLUDE_DIRS}
											   External/tinyxml2)
target_compile_features(liDecompress PUBLIC cxx_auto_type)

target_link_libraries(liDecompress common
								   ttvfs
								   tinyxml2
								   ${PNG_LIBRARIES}
								   ${ZLIB_LIBRARIES})
