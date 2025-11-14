if                          (NOT APPLE)
   set                      (linker_flags "-Wl,--export-dynamic")
   set                      (linker_flags "${linker_flags} -Wl,-u,henson_set_contexts,-u,henson_set_namemap")
else                        ()
   set                      (linker_flags "-Wl,-u,_henson_set_contexts,-u,_henson_set_namemap")
endif                       (NOT APPLE)

add_library                 (producer-henson-cpp SHARED producer.cpp)
target_link_libraries       (producer-henson-cpp ${libraries})
set_target_properties       (producer-henson-cpp PROPERTIES PREFIX "")
set_target_properties       (producer-henson-cpp PROPERTIES SUFFIX ".so")
set_target_properties       (producer-henson-cpp PROPERTIES LINK_FLAGS ${linker_flags})

add_library                 (producer-henson-ftn SHARED producer.f90)
target_link_libraries       (producer-henson-ftn ${libraries})
set_target_properties       (producer-henson-ftn PROPERTIES PREFIX "")
set_target_properties       (producer-henson-ftn PROPERTIES SUFFIX ".so")
set_target_properties       (producer-henson-ftn PROPERTIES LINK_FLAGS ${linker_flags})

install                     (TARGETS
                            producer-henson-cpp
                            producer-henson-ftn
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson-test-pmpi
                            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)
