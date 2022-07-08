function(git_update_all_submodules MSG_TYPE)
  message(STATUS "Updating git submodules...")
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    RESULT_VARIABLE UPDATE_SUBMODULES_RESULT)

  message(STATUS "${RESULT_VARIABLE}")
  if(NOT UPDATE_SUBMODULES_RESULT EQUAL "0")
    message(${MSG_TYPE} "git submodule update failed")
  endif()
endfunction()

function(git_update_submodules)
  message(STATUS "Updating requested git submodules...")

  foreach(module IN LISTS ARGV)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} submodule update --init ${module}
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      RESULT_VARIABLE UPDATE_SUBMODULES_RESULT)

    if(NOT UPDATE_SUBMODULES_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update failed: ${module}")
    endif()
  endforeach()

endfunction()
