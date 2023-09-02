add_compile_definitions(TEST_FILES_LOC="${CMAKE_CURRENT_BINARY_DIR}/")

add_executable(test-d3b-manager test_d3b_manager.cpp)

target_link_libraries(test-d3b-manager PUBLIC
  ${GTEST_BOTH_LIBRARIES}
  d3b-manager
)

target_include_directories(test-d3b-manager PUBLIC
  ${PROJECT_SOURCE_DIR}
)
add_test(NAME test-d3b-manager COMMAND test-d3b-manager)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
