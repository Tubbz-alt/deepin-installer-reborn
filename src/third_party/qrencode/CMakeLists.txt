CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

PROJECT(QREncodingLibrary VERSION 4.0.0 LANGUAGES C)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

ADD_DEFINITIONS(-DMAJOR_VERSION=${PROJECT_VERSION_MAJOR})
ADD_DEFINITIONS(-DMINOR_VERSION=${PROJECT_VERSION_MINOR})
ADD_DEFINITIONS(-DMICRO_VERSION=${PROJECT_VERSION_PATCH})
ADD_DEFINITIONS(-DVERSION="${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
ADD_DEFINITIONS(-D__STATIC=)
ADD_DEFINITIONS(-DSTATIC_IN_RELEASE=static)

SET(LIB_FILES qrencode.c
              qrinput.c
              bitstream.c
              qrspec.c
              rsecc.c
              split.c
              mask.c
              mqrspec.c
              mmask.c)
ADD_LIBRARY(qrencode ${LIB_FILES})
