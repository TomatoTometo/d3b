
add_library(options options.cpp)

target_link_libraries(options ${Boost_LIBRARIES})


add_library(d3b-manager d3b_manager.cpp)

target_link_libraries(d3b-manager ${Boost_LIBRARIES})
