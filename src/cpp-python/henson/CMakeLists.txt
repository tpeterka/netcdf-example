if                          (NOT APPLE)
   set                      (linker_flags "-pie -Wl,--export-dynamic")
   set                      (linker_flags "${linker_flags} -Wl,-u,henson_set_contexts,-u,henson_set_namemap")
else                        ()
   set                      (linker_flags "-Wl,-u,_henson_set_contexts,-u,_henson_set_namemap")
endif                       (NOT APPLE)

add_library                 (cpp-producer-henson SHARED producer.cpp)
target_link_libraries       (cpp-producer-henson ${libraries})
set_target_properties       (cpp-producer-henson PROPERTIES PREFIX "")
set_target_properties       (cpp-producer-henson PROPERTIES SUFFIX ".so")
set_target_properties       (cpp-producer-henson PROPERTIES LINK_FLAGS ${linker_flags})

install                     (TARGETS
                            cpp-producer-henson
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/cpp-python/henson
                            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/cpp-py-netcdf-henson.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/cpp-python/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/consumer.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/cpp-python/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

