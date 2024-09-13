if                          (NOT APPLE)
   set                      (linker_flags "-pie -Wl,--export-dynamic")
   set                      (linker_flags "${linker_flags} -Wl,-u,henson_set_contexts,-u,henson_set_namemap")
else                        ()
   set                      (linker_flags "-Wl,-u,_henson_set_contexts,-u,_henson_set_namemap")
endif                       (NOT APPLE)

add_library                 (producer-main SHARED producer.cpp)
target_link_libraries       (producer-main ${libraries})
set_target_properties       (producer-main PROPERTIES PREFIX "")
set_target_properties       (producer-main PROPERTIES SUFFIX ".so")
set_target_properties       (producer-main PROPERTIES LINK_FLAGS ${linker_flags})

add_library                 (consumer-main SHARED consumer.cpp)
target_link_libraries       (consumer-main ${libraries})
set_target_properties       (consumer-main PROPERTIES PREFIX "")
set_target_properties       (consumer-main PROPERTIES SUFFIX ".so")
set_target_properties       (consumer-main PROPERTIES LINK_FLAGS ${linker_flags})

install                     (TARGETS
                            producer-main
                            consumer-main
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson
                            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/netcdf-henson.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

