# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MagWork_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MagWork_autogen.dir\\ParseCache.txt"
  "MagWork_autogen"
  )
endif()
