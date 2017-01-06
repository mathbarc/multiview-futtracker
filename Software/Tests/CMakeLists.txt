#set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)


if(${WITH_CUDA})
    find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs video cudabgsegm imgproc)
else()
    find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs video imgproc)
endif()

if(${OpenCV_FOUND})
else()
        find_package(OpenCV 2 REQUIRED core highgui video imgproc)
endif()

set(TESTS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Tests include dir")

set(TESTS_INCLUDE_DIRS
    ${TESTS_INCLUDE_DIR}
    ${BUSINESS_INCLUDE_DIR}
    ${COMMUNICATION_INCLUDE_DIR}
    ${VIEW_INCLUDE_DIR}
    ${CONTROL_INCLUDE_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS})

file(GLOB VIDEO_PROCESSOR_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/main_video_processor.cpp ${CMAKE_CURRENT_SOURCE_DIR}/sources/main_window_video_player.cpp)
file(GLOB VIDEO_PROCESSOR_TEST_FORMS ${CMAKE_CURRENT_SOURCE_DIR}/forms/main_window_video_player.ui)
file(GLOB VIDEO_PROCESSOR_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/main_window_video_player.hpp)

qt5_wrap_cpp(VIDEOPROCESSOR_TEST_WRAPPED_HEADERS ${VIDEO_PROCESSOR_TEST_HEADERS})
qt5_wrap_ui(VIDEOPROCESSOR_TEST_WRAPPED_FORMS ${VIDEO_PROCESSOR_TEST_FORMS})

include_directories(${TESTS_INCLUDE_DIRS})

message(${VIDEOPROCESSOR_TEST_WRAPPED_FORMS})

if(WIN32)
add_executable(VideoProcessor WIN32 ${VIDEO_PROCESSOR_TEST_SOURCES} ${VIDEO_PROCESSOR_TEST_HEADERS} ${VIDEOPROCESSOR_TEST_WRAPPED_HEADERS} ${VIDEOPROCESSOR_TEST_WRAPPED_FORMS})
else()
add_executable(VideoProcessor ${VIDEO_PROCESSOR_TEST_SOURCES} ${VIDEO_PROCESSOR_TEST_HEADERS} ${VIDEOPROCESSOR_TEST_WRAPPED_HEADERS} ${VIDEOPROCESSOR_TEST_WRAPPED_FORMS})
endif()
add_dependencies(VideoProcessor Control)
target_link_libraries(VideoProcessor Qt5::Core Qt5::Widgets Business ${OPENCV_LIBS})


install(TARGETS VideoProcessor RUNTIME DESTINATION "." COMPONENT tests)
