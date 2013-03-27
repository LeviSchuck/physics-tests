cmake_minimum_required (VERSION 2.6)
project(phys)
IF(APPLE)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(GLUT_LIBRARY GLUT )
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
   MARK_AS_ADVANCED (COCOA_LIBRARY
                     GLUT_LIBRARY
                     OpenGL_LIBRARY)
   set(EXTRA_LIBS ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
   #set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
   set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
   #set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
   #set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
   set(CMAKE_CXX_FLAGS "-std=c++11")
ENDIF (APPLE)
set(CMAKE_XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN "YES")
set(CMAKE_CXX_LINK_FLAGS " -framework IOKit ")
set(CMAKE_EXE_LINKER_FLAGS "-fvisibility=hidden")
include_directories(/usr/local/include ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(/usr/local/lib)

list(APPEND main_sources 
   lib/math.cpp lib/math.hpp
	lib/enums.hpp
	lib/gentity.cpp lib/gentity.hpp
	lib/graphics.cpp lib/graphics.hpp
	lib/object.cpp lib/object.hpp
	lib/pentity.cpp lib/pentity.hpp
	lib/test.cpp lib/test.hpp
	lib/vec.hpp
	lib/world.cpp lib/world.hpp
)
list(APPEND engine_sources
   null/nworld.cpp null/nworld.hpp
)
list(APPEND test_sources
   tests/basic/test.cpp tests/basic/test.hpp
)

add_executable(phys MACOSX_BUNDLE main.cpp apple.cpp ${main_sources} ${engine_sources} ${test_sources})
target_link_libraries(phys Irrlicht ${EXTRA_LIBS})
