if(ALAFF_AVX2)
    if (MSVC)
        add_compile_options(/arch:AVX2)
    else()
        add_compile_options(-mavx2)
    endif()
endif()

set(UTIL_SOURCES
    FLA_Clock.c
    MaxAbsDiff.c
    RandomMatrix.c
)
add_library(util ${UTIL_SOURCES})

add_custom_target(run_all_orderings)

foreach(ORD ${GEMM_ORDERINGS})
    add_executable(gemm_${ORD} driver.c Gemm_${ORD}.c)

    target_link_libraries(gemm_${ORD}
        PRIVATE
        util
        BLAS::BLAS
    )

    add_custom_target(run_${ORD}
        COMMAND $<TARGET_FILE:gemm_${ORD}> ${NREPEATS} ${NFIRST} ${NLAST} ${NINC} > ${CMAKE_CURRENT_SOURCE_DIR}/data/output_${ORD}.m
    )

    add_dependencies(run_${ORD} gemm_${ORD})
    add_dependencies(run_all_orderings run_${ORD})
endforeach()

# Copy BLIS dll in the executable folder
get_filename_component(BLAS_LIB_PATH ${BLAS_LIBRARIES} DIRECTORY)
add_custom_command(TARGET gemm_IJP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${BLAS_LIB_PATH}/../bin/libblis.3.dll
    $<TARGET_FILE_DIR:gemm_IJP>
)
