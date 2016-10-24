project("MultiView FutTracker")
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
IF(WIN32)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0054 NEW)
ENDIF()
add_subdirectory(Ferramentas)
add_subdirectory(Software)
#file(GLOB ABOUT ${CMAKE_CURRENT_SOURCE_DIR}/README.md ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/README.md ${CMAKE_CURRENT_BINARY_DIR}/README.md COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt ${CMAKE_CURRENT_BINARY_DIR}/LICENSE.txt COPYONLY)
install(FILES ${ABOUT} DESTINATION bin)

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Multiview FutTracker")
SET(CPACK_PACKAGE_VENDOR "Matheus Barcelos de Oliveira")
SET(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt)
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Multiview FutTracker")

IF(UNIX)
    SET(CPACK_GENERATOR DEB)
    SET(CPACK_DEBIAN_PACKAGE_NAME "Multiview FutTracker")
    SET(CPACK_DEBIAN_PACKAGE_VERSION "1.0.0")
    SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Matheus Barcelos de Oliveira")

ENDIF()


IF(WIN32)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
#  SET(CPACK_PACKAGE_ICON ${CMake_SOURCE_DIR}/Software/View/resources/logo63.png)
#  SET(CPACK_NSIS_INSTALLED_ICON_NAME ${CMake_SOURCE_DIR}/Software/View/resources/logo63.png)
    SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Multiview FutTracker")
    SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\piim-lab.decom.cefetmg.br/")
    SET(CPACK_NSIS_CONTACT "matheusbarcelosoliveira@gmail.com")
    SET(CPACK_NSIS_MODIFY_PATH ON)
ENDIF()

#SET(CPACK_PACKAGE_EXECUTABLES "CameraMarker" "CameraMarker")
#SET(CPACK_PACKAGE_EXECUTABLES "extractFrames" "extractFrames")
#SET(CPACK_PACKAGE_EXECUTABLES "TsaiCalibration" "TsaiCalibration")
#SET(CPACK_PACKAGE_EXECUTABLES "vidInfo" "vidInfo")
#SET(CPACK_PACKAGE_EXECUTABLES "vidSync" "vidSync")

set(CPACK_COMPONENTS_ALL application tools)

INCLUDE(CPack)

