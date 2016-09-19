set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package(Qt5Core REQUIRED)

find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs)

if(${OpenCV_FOUND})
else()
        find_package(OpenCV 2 REQUIRED core highgui)
endif()

set(CONTROL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Control include dir")

set(CONTROL_INCLUDE_DIRS 
        ${CONTROL_INCLUDE_DIR}
        ${Qt5Core_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS})

file(GLOB CONTROL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB CONTROL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

include_directories(${CONTROL_INCLUDE_DIRS})

#qt5_wrap_ui(CAMERAMARKER_WRAPPED_IUS ${CAMERAMARKER_FORMS})
#qt5_add_resources(CAMERAMARKER_RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)
add_library(Control STATIC ${CONTROL_SOURCES} ${CONTROL_HEADERS})
target_link_libraries(Control Qt5::Core ${OpenCV_LIBS})