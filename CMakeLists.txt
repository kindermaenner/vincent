cmake_minimum_required(VERSION 3.16)
project(Vincent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
  add_executable(Vincent
    src/ChangeUserNameDlg.cpp
    src/DgramSocket.cpp
    src/LogFile.cpp
    src/StdAfx.cpp
    src/trayicon.cpp
    src/Vincent.cpp
    src/VincentDlg.cpp
    Vincent.rc
  )

  target_compile_definitions(Vincent PRIVATE _WINDOWS _MBCS)
  target_compile_options(Vincent PRIVATE /W3)
  target_include_directories(Vincent PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_link_libraries(Vincent PRIVATE version)

  set_target_properties(Vincent PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
