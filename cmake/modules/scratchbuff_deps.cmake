include(FetchContent)

function (scratchbuff_init_deps TARGET_NAME)
 # if (NOT TARGET hashy_static)
 #   FetchContent_Declare(hashy_static
 #     URL /home/ianertson/workspace/hashy
 #   )
 #
 #   FetchContent_MakeAvailable(hashy_static)
 # endif()

  SET(SCRATCHBUFF_DEPS m)

  # target_compile_options(${TARGET_NAME} PRIVATE -fPIC)
  target_link_libraries(${TARGET_NAME} ${SCRATCHBUFF_DEPS})

endfunction()
