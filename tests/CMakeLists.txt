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

set_tests_properties(test_init_Test test_finalize_Test test_send_recv_Test PROPERTIES LABELS "send_recv;ping_pong_send_and_recv;ping_pong_sendrecv")

set_tests_properties(test_ping_pong_send_and_recv_Test PROPERTIES LABELS "ping_pong_send_and_recv;ping_pong_sendrecv")

set_tests_properties(test_ping_pong_sendrecv_Test PROPERTIES LABELS "ping_pong_sendrecv")


