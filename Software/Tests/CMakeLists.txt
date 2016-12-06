find_package(Qt5Core REQUIRED)

if(${WITH_CUDA})
    find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs video cudabgsegm)
else()
    find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs video)
endif()

if(${OpenCV_FOUND})
else()
        find_package(OpenCV 2 REQUIRED core highgui video)
endif()

set(MULTIVIEW_FUTTRACKER_INCLUDE_DIRS
    ${BUSINESS_INCLUDE_DIR}
    ${COMMUNICATION_INCLUDE_DIR}
    ${VIEW_INCLUDE_DIR}
    ${CONTROL_INCLUDE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS})

file(GLOB VIDEO_PROCESSOR_TEST_SOURCES main_video_processor.cpp video_show.hpp)
file(GLOB TEST_HEADERS *.hpp)

include_directories(${MULTIVIEW_FUTTRACKER_INCLUDE_DIRS})
qt5_wrap_cpp(TEST_WRAPPED_HEADERS ${TEST_HEADERS})
if(WIN32)
add_executable(VideoProcessor WIN32 ${VIDEO_PROCESSOR_TEST_SOURCES} ${TEST_HEADERS} ${TEST_WRAPPED_HEADERS})
else()
add_executable(VideoProcessor ${VIDEO_PROCESSOR_TEST_SOURCES} ${TEST_HEADERS} ${TEST_WRAPPED_HEADERS})
endif()
add_dependencies(VideoProcessor Control)
target_link_libraries(VideoProcessor Qt5::Core Control ${OPENCV_LIBS})


install(TARGETS VideoProcessor RUNTIME DESTINATION "." COMPONENT tests)
