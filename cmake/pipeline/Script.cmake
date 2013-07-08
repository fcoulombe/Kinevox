SET(OUT_SCRIPT_DIR ${CMAKE_CURRENT_BINARY_DIR}/data/Script/)
file(MAKE_DIRECTORY ${OUT_SCRIPT_DIR})
file(GLOB scriptFiles ${dataPath}*.lua)
IF(${WIN32})
    IF(${KINEVOX_ARCHITECTURE} MATCHES "32bit")
    	SET(LUACOMPILER_EXE ${PROJECT_SOURCE_DIR}/3rdParty/lua/bin/luac.exe)
    ELSE()
    	SET(LUACOMPILER_EXE ${PROJECT_SOURCE_DIR}/3rdParty/lua/bin/luac64.exe)
    ENDIF()
ELSE()
    SET(LUACOMPILER_EXE luac)
ENDIF()
foreach(src ${scriptFiles})
	get_filename_component(SrcExt ${src} EXT)
	string(REPLACE ${SrcExt} ".luac" DstFile ${src})
	string(REPLACE ${dataPath} ${OUT_SCRIPT_DIR} DstFile ${DstFile})
	add_custom_command(
		OUTPUT 
		${DstFile}
		COMMAND 
		${LUACOMPILER_EXE} -o ${DstFile} ${src} 
		DEPENDS 
		${src} )
	#list(APPEND DstFiles ${DstFile})
	SET(DATA_DEP ${DATA_DEP} ${DstFile})
endforeach()
#SET(DATA_DEP ${DATA_DEP} ${DstFiles})
