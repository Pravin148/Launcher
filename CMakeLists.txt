cmake_minimum_required(VERSION 3.16)

project(AppLauncher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Xml)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appAppLauncher
    main.cpp
)

qt_add_qml_module(appAppLauncher
    URI AppLauncher
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES applauncher.h
            applauncher.cpp
    RESOURCES res.qrc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAppLauncher PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAppLauncher
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAppLauncher
    PRIVATE Qt6::Quick
        Qt6::Xml
)

include(GNUInstallDirs)
install(TARGETS appAppLauncher
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
