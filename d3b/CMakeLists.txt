
add_library(options options.cpp)

target_link_libraries(options ${Boost_LIBRARIES})


add_library(d3b-manager manager.cpp)

target_link_libraries(d3b-manager ${Boost_LIBRARIES} uuid)

include_directories(${PROJECT_SOURCE_DIR}) #@todo do better than this
