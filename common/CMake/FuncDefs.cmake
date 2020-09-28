# 获取目录的子目录
function(GetSubDirs Dir Result)
    message("get dirs in  ${Dir}")
    #    EXECUTE_PROCESS(
    #            COMMAND chmod +x ${CMAKE_SOURCE_DIR}/common/CMake/travel_dir.py
    #    )
    EXECUTE_PROCESS(
            COMMAND python3 ${CMAKE_SOURCE_DIR}/common/CMake/travel_dir.py ${Dir} d
            OUTPUT_VARIABLE DIRS
    )
    set(${Result} ${DIRS} PARENT_SCOPE)
    message("All dirs ${DIRS}")
endfunction()


function(AddAllSubDir)
    GetSubDirs(${CMAKE_SOURCE_DIR}/src SubDir)
    foreach (dir ${SubDir})
        #    message("sub : ${dir}")
        string(REPLACE "${CMAKE_SOURCE_DIR}/src/" "" build_temp ${dir})
        string(REGEX REPLACE "/" "_" build_temp ${build_temp})
        if (NOT EXISTS "${dir}/CMakeLists.txt")
            continue()
        endif ()
        if (${dir} MATCHES "[\\s\\S]*old_uinx_study[\\s\\S]*")
            continue()
        endif ()
        message("- ${build_temp}")
        add_subdirectory(${dir})
    endforeach ()
endfunction()

function(BuildProto Dir OutPutDir)
    message("build proto ")
    EXECUTE_PROCESS(
            COMMAND python3 ${CMAKE_SOURCE_DIR}/common/CMake/travel_dir.py ${Dir} build_proto ${OutPutDir}
            OUTPUT_VARIABLE TEMP_OUT
    )
    message("All proto ${TEMP_OUT}")

endfunction()
