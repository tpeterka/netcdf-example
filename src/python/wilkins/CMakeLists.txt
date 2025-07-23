file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/wilkins-config.yaml
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/python/wilkins
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                            GROUP_READ GROUP_WRITE
                            WORLD_READ WORLD_WRITE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/wilkins-run.sh
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/python/wilkins
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/producer.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/python/wilkins
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/consumer.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/python/wilkins
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)

