set(GOOGLETEST_ZIP_EXTRACTION_DONE FALSE CACHE BOOL "Condition checking for googletest zip extraction")
set(GOOGLETEST_LIB_INSTALLATION_DONE FALSE CACHE BOOL "Condition checking for googletest lib installation")

set(GOOGLETEST_SOURCE_ZIP_FILE "${EXTERNAL_SOURCE_FOLDER}/googletest/googletest-1.14.0.tar.gz")
set(GOOGLETEST_EXTRACTION_FOLDER "${EXTERNAL_BINARY_FOLDER}/googletest/")
set(GOOGLETEST_LOCATION_FOLDER "${GOOGLETEST_EXTRACTION_FOLDER}/googletest-1.14.0/")

if (NOT GOOGLETEST_ZIP_EXTRACTION_DONE)

  file(MAKE_DIRECTORY "${GOOGLETEST_EXTRACTION_FOLDER}")
  
  message(STATUS "[External] Extracting ${GOOGLETEST_SOURCE_ZIP_FILE}...")

  execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xzf ${GOOGLETEST_SOURCE_ZIP_FILE}
      RESULT_VARIABLE ZIP_EXEC_RESULT
      WORKING_DIRECTORY ${GOOGLETEST_EXTRACTION_FOLDER}
  )

  if (ZIP_EXEC_RESULT)
    message(STATUS "[External] Something wrong happened when extracting ${GOOGLETEST_SOURCE_ZIP_FILE}")
    message(STATUS "[External] Tried extracting to ${GOOGLETEST_EXTRACTION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution result: ${ZIP_EXEC_RESULT}")
  else()
    set(GOOGLETEST_ZIP_EXTRACTION_DONE TRUE CACHE BOOL "Condition checking for googletest tar extraction" FORCE)
    message(STATUS "[External] Successfully extracted ${GOOGLETEST_SOURCE_ZIP_FILE}")
  endif()
endif()

if (NOT GOOGLETEST_LIB_INSTALLATION_DONE)

  message(STATUS "[External] Installing googletest libraries to ${GOOGLETEST_LOCATION_FOLDER}...")

  file(MAKE_DIRECTORY "${GOOGLETEST_LOCATION_FOLDER}/install/")

  execute_process(
      COMMAND ${CMAKE_COMMAND} -B build/ -DCMAKE_INSTALL_PREFIX=${GOOGLETEST_LOCATION_FOLDER}/install/
      RESULT_VARIABLE GOOGLETEST_LIB_SETUP_RESULT
      OUTPUT_VARIABLE GOOGLETEST_LIB_SETUP_OUTPUT
      WORKING_DIRECTORY ${GOOGLETEST_LOCATION_FOLDER}
  )

  if(GOOGLETEST_LIB_SETUP_RESULT)
    message(STATUS "[External] Issue setting up googletest libraries to ${GOOGLETEST_LOCATION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution result: ${GOOGLETEST_LIB_SETUP_RESULT}")
  endif()

  execute_process(
      COMMAND cmake --build build/ --config Release
      RESULT_VARIABLE GOOGLETEST_LIB_BUILD_RESULT
      OUTPUT_VARIABLE GOOGLETEST_LIB_BUILD_OUTPUT
      WORKING_DIRECTORY ${GOOGLETEST_LOCATION_FOLDER}
  )

  if(GOOGLETEST_LIB_BUILD_RESULT)
    message(STATUS "[External] Issue setting up googletest libraries to ${GOOGLETEST_LOCATION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution result: ${GOOGLETEST_LIB_BUILD_RESULT}")
  endif()

  execute_process(
    COMMAND cmake --install build/
    RESULT_VARIABLE GOOGLETEST_LIB_INSTALL_RESULT
    OUTPUT_VARIABLE GOOGLETEST_LIB_INSTALL_OUTPUT
    WORKING_DIRECTORY ${GOOGLETEST_LOCATION_FOLDER}
  )

  if(GOOGLETEST_LIB_INSTALL_RESULT)
    message(STATUS "[External] Issue building googletest libraries to ${GOOGLETEST_LOCATION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution output: ${GOOGLETEST_LIB_INSTALL_RESULT}")
  else()
    message(STATUS "[External] Successfully installed googletest libraries to ${GOOGLETEST_LOCATION_FOLDER}")
    set(GOOGLETEST_LIB_INSTALLATION_DONE TRUE CACHE BOOL "Condition checking for googletest zip extraction" FORCE)
  endif()

endif()

if (GOOGLETEST_ZIP_EXTRACTION_DONE AND GOOGLETEST_LIB_INSTALLATION_DONE)
  message(STATUS "[External] googletest libraries should be extracted and installed at ${GOOGLETEST_LOCATION_FOLDER}")

  set(GTEST_ROOT "${GOOGLETEST_LOCATION_FOLDER}/install/")
  
  include(CTest)

  find_package(GTest REQUIRED)

  include_directories(${GTEST_INCLUDE_DIRS})

endif()


