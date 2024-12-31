cmake_minimum_required(VERSION 3.19)
project(SatSim LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets 3DCore 3DRender 3DInput 3DExtras)


qt_standard_project_setup()

qt_add_executable(SatSim
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    timedriver.h timedriver.cpp
    spaceentity.h spaceentity.cpp
    earth_view.h earth_view.cpp earth_view.ui









)

target_link_libraries(SatSim
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::3DCore
        Qt::3DRender
        Qt::3DInput
        Qt::3DExtras
)

include(GNUInstallDirs)

install(TARGETS SatSim
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SatSim
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
