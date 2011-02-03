cmake_minimum_required (VERSION 2.6) 
 
set (PROJECT parser) 
 
project (${PROJECT}) 
 
set (SOURCES 
	main.cpp) 
 
add_executable (${PROJECT} ${SOURCES})
