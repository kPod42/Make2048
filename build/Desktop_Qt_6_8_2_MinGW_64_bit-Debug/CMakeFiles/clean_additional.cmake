# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Make2048_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Make2048_autogen.dir\\ParseCache.txt"
  "Make2048_autogen"
  )
endif()
