find_package(OpenCV REQUIRED core highgui videoio imgcodecs)


set(EXTRACTFRAMES_INCLUDE_DIRS 
	${OpenCV_INCLUDE_DIRS}
)

file(GLOB EXTRACTFRAMES_SOURCES main.cpp)
include_directories(${EXTRACTFRAMES_INCLUDE_DIRS})

add_executable(extractFrames ${EXTRACTFRAMES_SOURCES})
target_link_libraries(extractFrames ${OpenCV_LIBS})
