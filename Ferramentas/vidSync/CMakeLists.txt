find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs)

if(${OpenCV_FOUND})
else()
	find_package(OpenCV 2 REQUIRED core highgui)
endif()

set(VIDSYNC_INCLUDE_DIRS 
	${OpenCV_INCLUDE_DIRS}
)

file(GLOB VIDSYNC_SOURCES main.cpp)
include_directories(${VIDSYNC_INCLUDE_DIRS})

add_executable(vidSync ${VIDSYNC_SOURCES})
target_link_libraries(vidSync ${OpenCV_LIBS})

install(TARGETS vidSync RUNTIME DESTINATION bin COMPONENT tools)
