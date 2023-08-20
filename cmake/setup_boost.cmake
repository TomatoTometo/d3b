set(BOOST_ZIP_EXTRACTION_DONE FALSE CACHE BOOL "Condition checking for boost zip extraction")
set(BOOST_LIB_INSTALLATION_DONE FALSE CACHE BOOL "Condition checking for boost lib installation")

set(BOOST_SOURCE_ZIP_FILE "${EXTERNAL_SOURCE_FOLDER}/boost/boost_1_83_0.zip")
set(BOOST_DESTINATION_FOLDER "${EXTERNAL_BINARY_FOLDER}/boost/boost_1_83_0")

if (NOT BOOST_ZIP_EXTRACTION_DONE)

  message(STATUS "[External] Extracting ${BOOST_SOURCE_ZIP_FILE}...")

  execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xzf ${BOOST_SOURCE_ZIP_FILE}
      RESULT_VARIABLE ZIP_EXEC_RESULT
      OUTPUT_VARIABLE ZIP_EXEC_OUTPUT
      WORKING_DIRECTORY ${EXTERNAL_BINARY_FOLDER}/boost/
  )

  if (ZIP_EXEC_RESULT)
    message(STATUS "[External] Something wrong happened when extracting ${BOOST_SOURCE_ZIP_FILE}")
    message(STATUS "[External] Tried extracting to ${BOOST_DESTINATION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution output: ${ZIP_EXEC_OUTPUT}")
  else()
    set(BOOST_ZIP_EXTRACTION_DONE TRUE CACHE BOOL "Condition checking for boost zip extraction" FORCE)
    message(STATUS "[External] Successfully extracted ${BOOST_SOURCE_ZIP_FILE}")
  endif()
endif()

if (NOT BOOST_LIB_INSTALLATION_DONE)

  message(STATUS "[External] Installing Boost libraries to ${BOOST_DESTINATION_FOLDER}...")

  execute_process(
      COMMAND ${BOOST_DESTINATION_FOLDER}/bootstrap.bat # for windows, @todo do for linux too
      RESULT_VARIABLE BOOST_LIB_SETUP_RESULT
      OUTPUT_VARIABLE BOOST_LIB_SETUP_OUTPUT
      WORKING_DIRECTORY ${BOOST_DESTINATION_FOLDER}
  )

  if(BOOST_LIB_SETUP_RESULT)
    message(STATUS "[External] Issue setting up Boost libraries to ${BOOST_DESTINATION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution output: ${BOOST_LIB_SETUP_OUTPUT}")
  endif()

  execute_process(
      COMMAND b2
      RESULT_VARIABLE BOOST_LIB_BUILD_RESULT
      OUTPUT_VARIABLE BOOST_LIB_BUILD_OUTPUT
      WORKING_DIRECTORY ${BOOST_DESTINATION_FOLDER}
  )

  if(BOOST_LIB_BUILD_RESULT)
    message(STATUS "[External] Issue building Boost libraries to ${BOOST_DESTINATION_FOLDER}")
    message(FATAL_ERROR  "[External] Execution output: ${BOOST_LIB_BUILD_OUTPUT}")
  else()
    message(STATUS "[External] Successfully installed Boost libraries to ${BOOST_DESTINATION_FOLDER}")
    set(BOOST_LIB_INSTALLATION_DONE TRUE CACHE BOOL "Condition checking for boost zip extraction" FORCE)
  endif()

endif()

if (BOOST_ZIP_EXTRACTION_DONE AND BOOST_LIB_INSTALLATION_DONE)
  message(STATUS "[External] Boost libraries should be extracted and installed at ${BOOST_DESTINATION_FOLDER}")

  set(Boost_COMPILER "-vc142") ## @todo also linux?
  set(Boost_USE_STATIC_LIBS ON)
  set(BOOST_ROOT "${BOOST_DESTINATION_FOLDER}/boost")
  set(BOOST_INCLUDEDIR "${BOOST_DESTINATION_FOLDER}")
  set(BOOST_LIBRARYDIR "${BOOST_DESTINATION_FOLDER}/stage/lib")

  ### Suppress the warning about unknown dependencies for new Boost versions
  set(Boost_NO_WARN_NEW_VERSIONS TRUE)

  find_package(Boost REQUIRED COMPONENTS program_options)

  include_directories(${Boost_INCLUDE_DIRS})

endif()


