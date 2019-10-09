add_library(envArgs INTERFACE)

target_include_directories(envArgs INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>)

