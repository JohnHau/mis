cmake_minimum_required(VERSION 3.10) 

project(tutorial VERSION 1.0)


configure_file(tutorialconfig.h.in  tutorialconfig.h)



add_executable(tutorial main.c)

target_include_directories(tutorial PUBLIC 
	                   "${PROJECT_BINARY_DIR}"
			   )
