SET(DepName "kinetestlib")
ProcessDependencies(${DepName})

SET(kinetestlib_ROOT ${CMAKE_CURRENT_LIST_DIR}/../)
SET(kinetestlib_INCLUDE_DIR ${kinetestlib_ROOT} )


SET(kinetestlib_INCLUDE_DIR ${kinetestlib_INCLUDE_DIR} ${DEP_INC})
list(APPEND kinetestlib_LIBS kinetestlib)
list(APPEND kinetestlib_LIBS ${DEP_LIBS} )

#SET(kinetestlib_LIBS kinetestlib ${DEP_LIBS} )
