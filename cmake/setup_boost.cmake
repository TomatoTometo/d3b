set(BOOST_ZIP_EXTRACTION_DONE FALSE CACHE BOOL "Condition checking for boost zip extraction")
set(BOOST_LIB_INSTALLATION_DONE FALSE CACHE BOOL "Condition checking for boost lib installation")

set(BOOST_SOURCE_ZIP_FILE "${EXTERNAL_SOURCE_FOLDER}/boost/boost_1_83_0.zip")
set(BOOST_EXTRACTION_FOLDER "${EXTERNAL_BINARY_FOLDER}/boost/")
set(BOOST_LOCATION_FOLDER "${BOOST_EXTRACTION_FOLDER}/boost_1_83_0/")

if (NOT BOOST_ZIP_EXTRACTION_DONE)

  execute_process(
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BOOST_EXTRACTION_FOLDER}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )

  message(STATUS "[External] Extracting ${BOOST_SOURCE_ZIP_FILE}...")

  execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xzf ${BOOST_SOURCE_ZIP_FILE}
      RESULT_VARIABLE ZIP_EXEC_RESULT
      WORKING_DIRECTORY ${BOOST_EXTRACTION_FOLDER}
  )

  if (ZIP_EXEC_RESULT)
    message(STATUS "[External] Something wrong happened when extracting ${BOOST_SOURCE_ZIP_FILE}")
    message(STATUS "[External] Tried extracting to ${BOOST_EXTRACTION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution result: ${ZIP_EXEC_RESULT}")
  else()
    set(BOOST_ZIP_EXTRACTION_DONE TRUE CACHE BOOL "Condition checking for boost zip extraction" FORCE)
    message(STATUS "[External] Successfully extracted ${BOOST_SOURCE_ZIP_FILE}")
  endif()
endif()

if (NOT BOOST_LIB_INSTALLATION_DONE)

  message(STATUS "[External] Installing Boost libraries to ${BOOST_LOCATION_FOLDER}...")

  execute_process(
      COMMAND ${BOOST_LOCATION_FOLDER}/bootstrap.bat # for windows, @todo do for linux too
      RESULT_VARIABLE BOOST_LIB_SETUP_RESULT
      OUTPUT_VARIABLE BOOST_LIB_SETUP_OUTPUT
      WORKING_DIRECTORY ${BOOST_LOCATION_FOLDER}
  )

  if(BOOST_LIB_SETUP_RESULT)
    message(STATUS "[External] Issue setting up Boost libraries to ${BOOST_LOCATION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution result: ${BOOST_LIB_SETUP_RESULT}")
  endif()

  execute_process(
      COMMAND b2 runtime-link=static
      RESULT_VARIABLE BOOST_LIB_BUILD_RESULT
      OUTPUT_VARIABLE BOOST_LIB_BUILD_OUTPUT
      WORKING_DIRECTORY ${BOOST_LOCATION_FOLDER}
  )

  if(BOOST_LIB_BUILD_RESULT)
    message(STATUS "[External] Issue building Boost libraries to ${BOOST_LOCATION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution output: ${BOOST_LIB_BUILD_RESULT}")
  else()
    message(STATUS "[External] Successfully installed Boost libraries to ${BOOST_LOCATION_FOLDER}")
    set(BOOST_LIB_INSTALLATION_DONE TRUE CACHE BOOL "Condition checking for boost zip extraction" FORCE)
  endif()

endif()

if (BOOST_ZIP_EXTRACTION_DONE AND BOOST_LIB_INSTALLATION_DONE)
  message(STATUS "[External] Boost libraries should be extracted and installed at ${BOOST_LOCATION_FOLDER}")

  set(Boost_COMPILER "-vc142") ## @todo also linux?
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_STATIC_RUNTIME ON)
  set(BOOST_ROOT "${BOOST_LOCATION_FOLDER}/boost")
  set(BOOST_INCLUDEDIR "${BOOST_LOCATION_FOLDER}")
  set(BOOST_LIBRARYDIR "${BOOST_LOCATION_FOLDER}/stage/lib")

  ### Suppress the warning about unknown dependencies for new Boost versions
  set(Boost_NO_WARN_NEW_VERSIONS TRUE)

  find_package(Boost REQUIRED COMPONENTS program_options filesystem system)

  include_directories(${Boost_INCLUDE_DIRS})

endif()


