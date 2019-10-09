add_executable(
    unit_tests
    constructor.cpp
)

set_target_properties(
    unit_tests
    PROPERTIES
        CXX_STANDARD          17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS        NO
)

target_link_libraries(
    unit_tests
    gtest_main
    envArgs
)

add_test(
    NAME
        unit
    COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)

