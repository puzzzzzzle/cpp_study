# 获取目录的子目录
#function(GetSubDirs Dir Result)
#    file(GLOB Children ${Dir} ${Dir}/*)
#    foreach(Child ${Children})
#        if(NOT IS_DIRECTORY ${Child})
#            continue()
#        endif()
#        if (${Child} STREQUAL ${Dir})
#            continue()
#        endif()
#        list(APPEND AllDirs ${Child})
#    endforeach()
#    set(${Result} ${AllDirs} PARENT_SCOPE)
#endfunction()

# 获取目录的子目录
function(GetSubDirs Dir Result)
    EXECUTE_PROCESS(
            COMMAND ${CMAKE_SOURCE_DIR}/common/CMake/get_all_dirs.sh ${Dir}
            OUTPUT_VARIABLE DIRS
    )
    set(${Result} ${DIRS} PARENT_SCOPE)
    #    message("All dirs ${DIRS}")
endfunction()

#set(auto_analisis_dir_list
#        stl_old
#        cpp_language
#        boost_stud
#        libgo_study
#        libco_study
#        aoi_study
#        nasm_study
#        )
#foreach (auto_analisis_dir ${auto_analisis_dir_list})
#    file(GLOB files RELATIVE ${PROJECT_SOURCE_DIR}/${auto_analisis_dir} CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/${auto_analisis_dir}/*)
#    message("- ${auto_analisis_dir}")
#    foreach (f ${files})
#        set(build_temp ${auto_analisis_dir}_${f})
#        #        message("\t ${PROJECT_SOURCE_DIR}/${auto_analisis_dir}/${f}/CMakeLists.txt")
#        if (EXISTS ${PROJECT_SOURCE_DIR}/${auto_analisis_dir}/${f}/CMakeLists.txt)
#            message("\t - ${build_temp}")
#            add_subdirectory(${auto_analisis_dir}/${f})
#        else ()
#            message("\t - !!!${build_temp} without CMakeLists.txt, ignore!")
#        endif ()
#        #        message("\t\t - done")
#    endforeach (f ${RPLACE_LIST})
#endforeach ()

function(AddAllSubDir)
    GetSubDirs(${CMAKE_SOURCE_DIR}/cpp_study SubDir)
    foreach (dir ${SubDir})
        #    message("sub : ${dir}")
        string(REPLACE "${CMAKE_SOURCE_DIR}/cpp_study/" "" build_temp ${dir})
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
