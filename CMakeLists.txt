cmake_minimum_required(VERSION 3.16)

project(lkmetrology_sensor_constructor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES lkmetrology_sensor_constructor_en_GB.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    component.h
    catalogue.h
    ${TS_FILES}
    resources.qrc
    sensorgraphicsitem.h
    sensorgraphicsitem.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lkmetrology_sensor_constructor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(lkmetrology_sensor_constructor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(lkmetrology_sensor_constructor
            ${PROJECT_SOURCES}
        )
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(lkmetrology_sensor_constructor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# macOS bundle info (only for older Qt if needed)
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.lkmetrology_sensor_constructor)
endif()

set_target_properties(lkmetrology_sensor_constructor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    OUTPUT_NAME "SensorConstructor"                # binary name (Windows/Linux executable)
    MACOSX_BUNDLE_BUNDLE_NAME "Sensor Constructor" # app name in macOS top menu
)

include(GNUInstallDirs)
install(TARGETS lkmetrology_sensor_constructor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lkmetrology_sensor_constructor)
endif()
