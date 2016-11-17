add_subdirectory(Business)
add_subdirectory(Persistence)
add_subdirectory(View)
add_subdirectory(Control)

find_package(Qt5Widgets REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.yml ${CMAKE_CURRENT_BINARY_DIR}/config.yml COPYONLY)

set(MULTIVIEW_FUTTRACKER_INCLUDE_DIRS 
    ${BUSINESS_INCLUDE_DIR}
    ${PERSISTENCE_INCLUDE_DIR}
    ${VIEW_INCLUDE_DIR}
    ${CONTROL_INCLUDE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS})

file(GLOB MULTIVIEW_FUTTRACKER_SOURCES main.cpp)

include_directories(${MULTIVIEW_FUTTRACKER_INCLUDE_DIRS})

if(WIN32)
add_executable(FutTracker WIN32 ${MULTIVIEW_FUTTRACKER_SOURCES})
else()
add_executable(FutTracker ${MULTIVIEW_FUTTRACKER_SOURCES})
endif()
add_dependencies(FutTracker Control)
target_link_libraries(FutTracker Qt5::Core Control)


install(TARGETS FutTracker RUNTIME DESTINATION "." COMPONENT application)
install(FILES config.yml DESTINATION "." COMPONENT application)
