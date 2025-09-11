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
    add_test(NAME ${exec_name}_Test COMMAND ${MPIRUN} -n 4 ./${exec_name})

endforeach()

set_tests_properties(test_init_Test PROPERTIES LABELS "hello_world;rank;size")
set_tests_properties(test_finalize_Test PROPERTIES LABELS "hello_world;rank;size")
set_tests_properties(test_print_Test PROPERTIES LABELS "hello_world;rank;size")

set_tests_properties(test_print_rank_Test PROPERTIES LABELS "rank;size")

set_tests_properties(test_print_size_Test PROPERTIES LABELS "size")

