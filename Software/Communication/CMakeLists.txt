set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package(Qt5Core REQUIRED)

find_package(Qt5Sql REQUIRED)

find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs)

if(${OpenCV_FOUND})
else()
        find_package(OpenCV 2 REQUIRED core highgui)
endif()

set(COMMUNICATION_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Communication include dir")

set(COMMUNICATION_INCLUDE_DIRS 
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Sql_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${BUSINESS_INCLUDE_DIR}
        ${COMMUNICATION_INCLUDE_DIR})

file(GLOB COMMUNICATION_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB COMMUNICATION_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

include_directories(${COMMUNICATION_INCLUDE_DIRS})

#qt5_wrap_ui(CAMERAMARKER_WRAPPED_IUS ${CAMERAMARKER_FORMS})
#qt5_add_resources(CAMERAMARKER_RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)
add_library(Communication STATIC ${COMMUNICATION_SOURCES} ${COMMUNICATION_HEADERS})
target_link_libraries(Communication Business Qt5::Core Qt5::Sql ${OpenCV_LIBS})
