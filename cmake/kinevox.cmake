#
#recurse to find  .cmake files
#
macro(FindCMAKE path)
	file(GLOB_RECURSE CMAKE_MODS ${path}/*.cmake)
	foreach(p ${CMAKE_MODS})
		GET_FILENAME_COMPONENT(fn ${p} PATH)
		SET(pathList ${pathList} ${fn})
	endforeach()
	list(REMOVE_DUPLICATES pathList)
endmacro()

macro(FindCMakeLists path)
	file(GLOB_RECURSE CMAKE_MODS ${path}/CMakeLists.txt)
	foreach(p ${CMAKE_MODS})
		GET_FILENAME_COMPONENT(fn ${p} PATH)
		SET(cmakelist ${cmakelist} ${fn})
	endforeach()
	list(REMOVE_DUPLICATES cmakelist)
endmacro()


#
macro(ProcessDependencies projName)
	#message(${projName} ${DEP_LIBS})
	include (${projName}dep)
	SET(DebugOptimized "")
	foreach(dep ${DEPENDENCIES})
		FIND_PACKAGE( ${dep}  REQUIRED)
		SET(DEP_INC ${DEP_INC} ${${dep}_INCLUDE_DIR})
		SET(DEP_DLL ${DEP_DLL} ${${dep}_DLL})
		
		FOREACH( d ${${dep}_LIBS} )
			IF(${d} STREQUAL "debug" OR ${d} STREQUAL "optimized")
				SET(DebugOptimized ${d})
			ELSE()
				list(FIND DEP_LIBS ${d} isInList)
				IF(isInList EQUAL -1)
					IF(NOT ${DebugOptimized} STREQUAL "")
						list(APPEND DEP_LIBS ${DebugOptimized})
					ENDIF()
					list(APPEND DEP_LIBS ${d})
					#message("Adding: " ${d})
				ENDIF()
				SET(DebugOptimized "")
			ENDIF()
		ENDFOREACH()
		#SET(DEP_LIBS ${DEP_LIBS} ${${dep}_LIBS})
	endforeach()

	list(LENGTH DEP_INC listLen)
	if (${listLen} GREATER 1)
		list(REMOVE_DUPLICATES DEP_INC)
	endif()
endmacro()

macro(Executable ProjectName)
	INCLUDE(DLL)
	add_executable(${ProjectName} ${${ProjectName}_src} ${DATA_DEP})
	IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		list(REVERSE DEP_LIBS)
	ENDIF()
	target_link_libraries( ${ProjectName} ${DEP_LIBS})
endmacro()

macro(Test ProjectName)
	install (TARGETS ${ProjectName} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	add_test (NAME ${ProjectName}_run WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}  COMMAND ${ProjectName}  )
	set_tests_properties (${ProjectName}_run  PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
	add_dependencies(build_and_test ${ProjectName})
endmacro()


macro(ListSubdirectories curdir)
  file(GLOB sub-dir ${curdir}/*)
  set(list_of_dirs "")
  foreach(dir ${sub-dir})  	
    if(IS_DIRECTORY ${dir})
        set(list_of_dirs ${list_of_dirs} ${dir})
    endif()
  endforeach()
  
endmacro()

#
macro(ProcessData path)
	ListSubdirectories(${path})
	foreach(dataPath ${list_of_dirs})
		get_filename_component(pathName ${dataPath} NAME)
		SET(dataPath ${dataPath}/)
		Include(${pathName})
	endforeach()
endmacro()

macro(FindLibrary varname lib lpath)
	FIND_LIBRARY(${varname} NAMES ${lib}.a ${lib}.lib ${lib}.so ${lib}.dll  PATHS ${lpath} NO_DEFAULT_PATHS  NO_SYSTEM_ENVIRONMENT_PATH  )
endmacro()

