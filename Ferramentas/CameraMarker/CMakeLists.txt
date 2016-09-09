set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
find_package(Qt5Widgets REQUIRED)


set(CAMERAMARKER_INCLUDE_DIRS 
        ./include
	${Qt5Widgets_INCLUDE_DIRS}
)

file(GLOB CAMERAMARKER_SOURCES ./source/*.cpp)
file(GLOB CAMERAMARKER_HEADERS ./include/*.hpp ./include/*.h)
file(GLOB CAMERAMARKER_FORMS ./forms/*.ui)

include_directories(${CAMERAMARKER_INCLUDE_DIRS})

qt5_wrap_ui(CAMERAMARKER_WRAPPED_IUS ${CAMERAMARKER_FORMS})
qt5_add_resources(CAMERAMARKER_RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)
add_executable(CameraMarker ${CAMERAMARKER_SOURCES} ${CAMERAMARKER_HEADERS} ${CAMERAMARKER_WRAPPED_IUS} ${CAMERAMARKER_RESOURCE})
target_link_libraries(CameraMarker Qt5::Widgets)
