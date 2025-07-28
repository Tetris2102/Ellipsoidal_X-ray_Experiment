cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(FlatTarget)

# Set Xerces-C++ path (MUST come before find_package(Geant4))
set(XercesC_ROOT_DIR "$ENV{HOMEBREW_PREFIX}/opt/xerces-c")
find_package(XercesC REQUIRED)

# Find Geant4 (with GDML support)
find_package(Geant4 REQUIRED ui_all vis_all gdml)

include(${Geant4_USE_FILE})

# Include directories (BOTH Geant4 and Xerces-C++)
include_directories(
    ${Geant4_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
)

# Find sources
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)

# Create executable
add_executable(FlatTarget FlatTarget.cc ${sources})

# Link libraries (BOTH Geant4 and Xerces-C++)
target_link_libraries(FlatTarget
    ${Geant4_LIBRARIES}
    ${XercesC_LIBRARIES}
)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
