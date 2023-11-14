# CMakeList.txt: CMake-Projekt für "GlaserCalcPlugin". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets CONFIG REQUIRED)
add_library(glaser_calc_plugin SHARED
            GlaserCalcDlg.cpp
            GlaserCalcDlg.h
            GlaserCalcDlgImpl.cpp 
            GlaserCalcDlgImpl.h 
            PluginGlaserCalc.cpp
            PluginGlaserCalc.h
            GlaserCalc.cpp
            GlaserCalc.h
	          PluginObserver.cpp
            PluginObserver.h
            GlaserDiagram.h
            GlaserDiagram.cpp
            GlaserData.h)

target_compile_options(glaser_calc_plugin PRIVATE /utf-8)
target_link_libraries(glaser_calc_plugin PRIVATE ifcexplorer_plugin stdutils ifcdb)
target_link_libraries(glaser_calc_plugin PRIVATE wx::core wx::base)

set_target_properties(glaser_calc_plugin PROPERTIES VCPKG_MANIFEST_MODE FALSE)
