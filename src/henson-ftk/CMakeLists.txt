if                          (NOT APPLE)
   set                      (linker_flags "-pie -Wl,--export-dynamic")
   set                      (linker_flags "${linker_flags} -Wl,-u,henson_set_contexts,-u,henson_set_namemap")
else                        ()
   set                      (linker_flags "-Wl,-u,_henson_set_contexts,-u,_henson_set_namemap")
endif                       (NOT APPLE)

add_library                 (producer-henson-ftk SHARED producer.cpp)
target_link_libraries       (producer-henson-ftk ${libraries})
set_target_properties       (producer-henson-ftk PROPERTIES PREFIX "")
set_target_properties       (producer-henson-ftk PROPERTIES SUFFIX ".so")
set_target_properties       (producer-henson-ftk PROPERTIES LINK_FLAGS ${linker_flags})

install                     (TARGETS
                            producer-henson-ftk
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson-ftk
                            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/henson-ftk.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson-ftk
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/ndarray.yaml
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson-ftk
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/run-ftk.sh
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson-ftk
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

