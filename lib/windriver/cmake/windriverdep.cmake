SET(DEPENDENCIES gcl glext freetype)
IF(${USE_WINAPI})
	SET(DEPENDENCIES ${DEPENDENCIES})
ELSEIF(${USE_GLFW})
	SET(DEPENDENCIES ${DEPENDENCIES} glfw)
ENDIF()