# build plugin
add_executable(${PROJECT_NAME}_aroma
        entry.c
)
target_link_libraries(${PROJECT_NAME}_aroma PRIVATE ${PROJECT_NAME})
wut_create_rpl(${PROJECT_NAME}_aroma)
dkp_target_generate_symbol_list(${PROJECT_NAME}_aroma)
target_link_options(${PROJECT_NAME}_aroma PRIVATE
        $<$<CONFIG:Release>:-Wl,--discard-all>
)

get_target_property(BUILD_RESULT ${PROJECT_NAME}_aroma WUT_RPL)
# mark as WUPS plugin
add_custom_command(TARGET ${PROJECT_NAME}_aroma POST_BUILD
        COMMAND echo 'PL' | dd of=${BUILD_RESULT} bs=1 seek=9 count=2 conv=notrunc status=none
)
# copy to build dir
add_custom_command(TARGET ${PROJECT_NAME}_aroma POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${BUILD_RESULT}
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.wps
)

# link libwups
set(WUPS_ROOT "${DEVKITPRO}/wups")
add_library(wups STATIC IMPORTED)
set_target_properties(wups PROPERTIES
        IMPORTED_LOCATION "${WUPS_ROOT}/lib/libwups.a"
        IMPORTED_LOCATION_DEBUG "${WUPS_ROOT}/lib/libwupsd.a"
)
target_include_directories(wups INTERFACE "${WUPS_ROOT}/include")

target_link_libraries(${PROJECT_NAME}_aroma PRIVATE wups)
target_link_options(${PROJECT_NAME}_aroma PRIVATE
        "-T${WUPS_ROOT}/share/wups.ld"
        "-specs=${WUPS_ROOT}/share/wups.specs"
)
