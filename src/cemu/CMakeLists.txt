# build rpl
add_executable(${PROJECT_NAME}_cemu
        entry.c

        # From https://github.com/devkitPro/wut/pull/388
        crt0.s
        wut_malloc_rpl.c
)
target_link_libraries(${PROJECT_NAME}_cemu PRIVATE ${PROJECT_NAME})
wut_create_rpl(${PROJECT_NAME}_cemu)
dkp_target_generate_symbol_list(${PROJECT_NAME}_cemu)
target_link_options(${PROJECT_NAME}_cemu PRIVATE
        $<$<CONFIG:Release>:-Wl,--discard-all>
)

# copy to build dir
get_target_property(BUILD_RESULT ${PROJECT_NAME}_cemu WUT_RPL)
add_custom_command(TARGET ${PROJECT_NAME}_cemu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${BUILD_RESULT}
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.rpl
)
