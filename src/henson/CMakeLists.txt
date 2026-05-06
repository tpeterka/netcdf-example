if                          (NOT APPLE)
   set                      (linker_flags "-Wl,--export-dynamic")
   set                      (linker_flags "${linker_flags} -Wl,-u,henson_set_contexts,-u,henson_set_namemap")
else                        ()
   set                      (linker_flags "-Wl,-u,_henson_set_contexts,-u,_henson_set_namemap")
endif                       (NOT APPLE)

add_library                 (producer-netcdf-henson SHARED producer-netcdf.cpp)
target_link_libraries       (producer-netcdf-henson ${libraries})
set_target_properties       (producer-netcdf-henson PROPERTIES PREFIX "")
set_target_properties       (producer-netcdf-henson PROPERTIES SUFFIX ".so")
set_target_properties       (producer-netcdf-henson PROPERTIES LINK_FLAGS ${linker_flags})

add_library                 (consumer-netcdf-henson SHARED consumer-netcdf.cpp)
target_link_libraries       (consumer-netcdf-henson ${libraries})
set_target_properties       (consumer-netcdf-henson PROPERTIES PREFIX "")
set_target_properties       (consumer-netcdf-henson PROPERTIES SUFFIX ".so")
set_target_properties       (consumer-netcdf-henson PROPERTIES LINK_FLAGS ${linker_flags})

add_library                 (producer-hdf5-henson SHARED producer-hdf5.cpp)
target_link_libraries       (producer-hdf5-henson ${libraries})
set_target_properties       (producer-hdf5-henson PROPERTIES PREFIX "")
set_target_properties       (producer-hdf5-henson PROPERTIES SUFFIX ".so")
set_target_properties       (producer-hdf5-henson PROPERTIES LINK_FLAGS ${linker_flags})

add_library                 (consumer-hdf5-henson SHARED consumer-hdf5.cpp)
target_link_libraries       (consumer-hdf5-henson ${libraries})
set_target_properties       (consumer-hdf5-henson PROPERTIES PREFIX "")
set_target_properties       (consumer-hdf5-henson PROPERTIES SUFFIX ".so")
set_target_properties       (consumer-hdf5-henson PROPERTIES LINK_FLAGS ${linker_flags})

install                     (TARGETS
                            producer-netcdf-henson
                            consumer-netcdf-henson
                            producer-hdf5-henson
                            consumer-hdf5-henson
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson
                            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/netcdf-netcdf-henson.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/hdf5-hdf5-henson.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/netcdf-hdf5-henson.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/hdf5-netcdf-henson.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

