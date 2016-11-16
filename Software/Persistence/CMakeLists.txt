set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package(Qt5Core REQUIRED)

find_package(Qt5Sql REQUIRED)

find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs)

if(${OpenCV_FOUND})
else()
        find_package(OpenCV 2 REQUIRED core highgui)
endif()

set(PERSISTENCE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Persistence include dir")

set(PERSISTENCE_INCLUDE_DIRS 
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Sql_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${BUSINESS_INCLUDE_DIR}
        ${PERSISTENCE_INCLUDE_DIR})

file(GLOB PERSISTENCE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB PERSISTENCE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

include_directories(${PERSISTENCE_INCLUDE_DIRS})

#qt5_wrap_ui(CAMERAMARKER_WRAPPED_IUS ${CAMERAMARKER_FORMS})
#qt5_add_resources(CAMERAMARKER_RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)
add_library(Persistence STATIC ${PERSISTENCE_SOURCES} ${PERSISTENCE_HEADERS})
target_link_libraries(Persistence Business Qt5::Core Qt5::Sql ${OpenCV_LIBS})
