INCLUDE(CheckTypeSize)
CHECK_TYPE_SIZE (size_t SIZE_T_SIZE)

IF(${SIZE_T_SIZE} EQUAL 4)
SET(KINEVOX_ARCHITECTURE "32bit")
else()
SET(KINEVOX_ARCHITECTURE "64bit")
ENDIF()

message("OS: " ${CMAKE_SYSTEM_NAME} ${CMAKE_CXX_COMPILER_ID} )
IF(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
   SET(OS "MACOSX")
ELSEIF(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
   SET(OS "LINUX")
   SET(IS_OPENRL_ENABLED "0")
   SET(IS_GLEW_ENABLED ON)
ELSEIF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
   SET(OS "WIN32")
	IF(${GFXAPI_TO_USE} STREQUAL "OpenGLFix")
		SET(IS_FIX_PIPELINE_ENABLED "1")
		SET(USE_GLFW ON)
		SET(IS_GLEW_ENABLED 1)
		SET(GFXAPI_NAME "GL")
	ELSEIF(${GFXAPI_TO_USE} STREQUAL "OpenGLES1")
		SET(IS_FIX_PIPELINE_ENABLED "1")
		SET(ES1 ON)
		SET(USE_WINAPI ON)
		SET(IS_GLEW_ENABLED 0)
		SET(GFXAPI_NAME "GLES")
	ELSEIF(${GFXAPI_TO_USE} STREQUAL "OpenGLES2")
		SET(IS_FIX_PIPELINE_ENABLED "0")
		SET(ES2 ON)
		SET(USE_WINAPI ON)
		SET(IS_GLEW_ENABLED 0)
		SET(GFXAPI_NAME "GLES")
	ELSEIF(${GFXAPI_TO_USE} STREQUAL "OpenGLES3")
		SET(IS_FIX_PIPELINE_ENABLED "0")
		SET(ES3 ON)
		SET(USE_WINAPI ON)
		SET(IS_GLEW_ENABLED 0)
		SET(GFXAPI_NAME "GLES")
	ELSEIF(${GFXAPI_TO_USE} STREQUAL "OpenGL")
		SET(IS_FIX_PIPELINE_ENABLED "0")
		SET(USE_GLFW ON)
		SET(IS_GLEW_ENABLED 1)
		SET(GFXAPI_NAME "GL")
	ENDIF()
   SET(IS_OPENRL_ENABLED "1")
ENDIF()


IF(${MSVC})
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FIkinevoxconf.h")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
   SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /RTC1")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GF")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GS")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127")  #disable warning about constant condition for asserts
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4702") #unreachable code for template in vertex buffer
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
ELSEIF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include kinevoxconf.h")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fexceptions")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -ftrapv")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fvisibility=hidden")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Werror")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wextra")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pedantic")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O0")	
ENDIF()


configure_file (
  "${PROJECT_SOURCE_DIR}/cmake/kinevoxconf.h.in"
  "${PROJECT_BINARY_DIR}/kinevoxconf.h"
  )
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/3rdParty/include")
