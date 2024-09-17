if                          (NOT APPLE)
   set                      (linker_flags "-pie -Wl,--export-dynamic")
   set                      (linker_flags "${linker_flags} -Wl,-u,henson_set_contexts,-u,henson_set_namemap")
else                        ()
   set                      (linker_flags "-Wl,-u,_henson_set_contexts,-u,_henson_set_namemap")
endif                       (NOT APPLE)

add_library                 (producer-wilkins SHARED producer.cpp)
target_link_libraries       (producer-wilkins ${libraries})
set_target_properties       (producer-wilkins PROPERTIES PREFIX "")
set_target_properties       (producer-wilkins PROPERTIES SUFFIX ".so")
set_target_properties       (producer-wilkins PROPERTIES LINK_FLAGS ${linker_flags})

add_library                 (consumer-wilkins SHARED consumer.cpp)
target_link_libraries       (consumer-wilkins ${libraries})
set_target_properties       (consumer-wilkins PROPERTIES PREFIX "")
set_target_properties       (consumer-wilkins PROPERTIES SUFFIX ".so")
set_target_properties       (consumer-wilkins PROPERTIES LINK_FLAGS ${linker_flags})

install                     (TARGETS
                            producer-wilkins
                            consumer-wilkins
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/wilkins
                            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/wilkins-config.yaml
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/wilkins
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/wilkins-run.sh
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/wilkins
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

