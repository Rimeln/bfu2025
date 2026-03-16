# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AuthApp_v2_autogen"
  "CMakeFiles\\AuthApp_v2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AuthApp_v2_autogen.dir\\ParseCache.txt"
  )
endif()
