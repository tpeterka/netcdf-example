file                        (COPY
                            ${CMAKE_CURRENT_SOURCE_DIR}/prod-con.py
                            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/python/prod-con
                            FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_WRITE WORLD_EXECUTE)
