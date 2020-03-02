#Grab all the header files
file(GLOB_RECURSE FILES_H *.h)

#Grab the correct compilable code
if (APPLE)
	file(GLOB_RECURSE FILES_SRC *.mm)
else(APPLE)
	file(GLOB_RECURSE FILES_SRC *.cpp)
endif(APPLE)

#Create the executable
add_executable(Math_Library ${FILES_SRC} ${FILES_H})
