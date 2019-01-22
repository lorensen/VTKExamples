# Check if user has specified C++ 11 or newer
# using the old style flags.
# (this does not check Compiler's capability)

string(FIND "${CMAKE_CXX_FLAGS}" "c++11" FLAG_FOUND)

if (NOT FLAG_FOUND EQUAL -1)
  MESSAGE(STATUS "CXX_STANDARD: Found c++11 in CMAKE_CXX_FLAGS")
  string(REPLACE "-std=c++11" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  string(REPLACE "-std=gnu++11" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  set(CMAKE_CXX_STANDARD 11)
  set(USING_CPP11 1)

elseif ((CMAKE_CXX_STANDARD EQUAL 11) OR (CMAKE_CXX_STANDARD GREATER 11))
  MESSAGE(STATUS "CXX_STANDARD: User specified CMAKE_CXX_STANDARD " ${CMAKE_CXX_STANDARD})
  set(USING_CPP11 1)

else()
  MESSAGE(STATUS "CXX_STANDARD: default (C++98)")
endif()
