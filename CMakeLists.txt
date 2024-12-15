cmake_minimum_required(VERSION 3.19)
project(SatSim LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(SatSim
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    timedriver.h timedriver.cpp
    spaceentity.h spaceentity.cpp
    vcpkg.json
    perturbations.h perturbations.cpp
    perturbations.cpp
    perturbations.h
    electromagnetics.h electromagnetics.cpp
    base_definitions.h
    base_definitions.cpp

)

# Enable the vcpkg toolchain



message("Your CMAKE Version: ${CMAKE_VERSION}")
message("C++ Version Setting (Not Guaranteed): ${CMAKE_CXX_STANDARD}")

find_package(boost_multiprecision REQUIRED CONFIG)
    target_link_libraries(SatSim PRIVATE Boost::multiprecision)

target_link_libraries(SatSim
    PRIVATE
        Qt::Core
        Qt::Widgets
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
