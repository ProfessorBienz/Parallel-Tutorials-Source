## Grab all .cpp files in test directory
file(GLOB CPP_SOURCES CONFIGURE_DEPENDS "*.cpp")

## Go through each CPP file
foreach(src ${CPP_SOURCES})
    
    ## Grab the name without full path or extension
    get_filename_component(exec_name ${src} NAME_WE)

    ## Create executable
    add_executable(${exec_name} ${src})

    # Link with MPI 
    target_link_libraries(${exec_name} tutorial ${MPI_LIBRARIES})

    # Add to CTEST
    add_test(NAME ${exec_name}_Test COMMAND ${MPIRUN} -n 2 ./${exec_name})

endforeach()

set_tests_properties(test_init_Test test_finalize_Test test_simple_Test PROPERTIES LABELS "simple;pairwise;ring")

set_tests_properties(test_pairwise_Test PROPERTIES LABELS "pairwise;ring")

set_tests_properties(test_ring_Test PROPERTIES LABELS "ring")


