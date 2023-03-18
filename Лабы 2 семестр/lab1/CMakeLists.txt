cmake_minimum_required(VERSION 3.23)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DSFML_STATIC)



include_directories("SFML/include/")
link_directories("SFML/lib/")

add_executable(Lab1 main.cpp)

	
target_link_libraries(Lab1 
					    debug sfml-graphics-s-d 
						debug sfml-window-s-d
						debug sfml-system-s-d
						debug sfml-audio-s-d)
						
target_link_libraries(Lab1 
					    optimized sfml-graphics-s 
						optimized sfml-window-s
						optimized sfml-system-s
						optimized sfml-audio-s)
	
target_link_libraries(Lab1 opengl32 freetype winmm gdi32 openal32 flac vorbisenc vorbisfile vorbis ogg)

file(COPY "font.ttf" DESTINATION "/")