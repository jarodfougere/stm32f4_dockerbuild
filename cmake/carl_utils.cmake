cmake_minimum_required(VERSION 3.10)


macro(printvar var)
    message("[PRINTVAR] ${var} == >${${var}}<")
endmacro(printvar var)


macro(define_check varname)
    if(NOT DEFINED ${varname})
        message(FATAL_ERROR "${varname} is not defined. Please define it before continuing")
    endif(NOT DEFINED ${varname})
endmacro(define_check varname)


function(recurse_file_dirs output_var regex)
    foreach(pattern ${regex})
        file(GLOB_RECURSE files "${pattern}")
        foreach(header ${files})
            get_filename_component(header_dir ${header} DIRECTORY)
            list(APPEND dirs ${header_dir})
        endforeach(header ${files})
        list(REMOVE_DUPLICATES dirs)
        message("Indexing directories for files matching ${pattern}")
        foreach(dir ${dirs})
            message("\t${dir}")
        endforeach(dir ${dirs}})
        message("")
    endforeach(pattern ${regex})
    set(${output_var} ${dirs} PARENT_SCOPE)
endfunction(recurse_file_dirs output_var regex)





function(index_sources output_var regex)
    foreach(pattern ${regex})
        file(GLOB_RECURSE files "${pattern}")
        message("Indexing sources matching ${pattern}")
        foreach(file ${files})
            message("\t${file}")
        endforeach(file ${files})
        message("\t${file}")
        list(APPEND matched_sources ${files})
    endforeach(pattern ${regex})
    set(${output_var} ${matched_sources} PARENT_SCOPE)
endfunction(index_sources output_var regex)


