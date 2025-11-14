if                          (NOT APPLE)
   set                      (linker_flags "-Wl,--export-dynamic")
   set                      (linker_flags "${linker_flags} -Wl,-u,henson_set_contexts,-u,henson_set_namemap")
else                        ()
   set                      (linker_flags "-Wl,-u,_henson_set_contexts,-u,_henson_set_namemap")
endif                       (NOT APPLE)

add_library                 (producer-henson SHARED producer.cpp)
target_link_libraries       (producer-henson ${libraries})
set_target_properties       (producer-henson PROPERTIES PREFIX "")
set_target_properties       (producer-henson PROPERTIES SUFFIX ".so")
set_target_properties       (producer-henson PROPERTIES LINK_FLAGS ${linker_flags})

add_library                 (consumer-henson SHARED consumer.cpp)
target_link_libraries       (consumer-henson ${libraries})
set_target_properties       (consumer-henson PROPERTIES PREFIX "")
set_target_properties       (consumer-henson PROPERTIES SUFFIX ".so")
set_target_properties       (consumer-henson PROPERTIES LINK_FLAGS ${linker_flags})

install                     (TARGETS
                            producer-henson
                            consumer-henson
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

