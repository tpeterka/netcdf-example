file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/py-netcdf-henson.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/python/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/producer.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/python/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/consumer.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/python/henson
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

