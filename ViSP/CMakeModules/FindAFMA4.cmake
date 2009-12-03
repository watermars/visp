#############################################################################
#
# $Id$
#
# Copyright (C) 1998-2006 Inria. All rights reserved.
#
# This software was developed at:
# IRISA/INRIA Rennes
# Projet Lagadic
# Campus Universitaire de Beaulieu
# 35042 Rennes Cedex
# http://www.irisa.fr/lagadic
#
# This file is part of the ViSP toolkit
#
# This file may be distributed under the terms of the Q Public License
# as defined by Trolltech AS of Norway and appearing in the file
# LICENSE included in the packaging of this file.
#
# Licensees holding valid ViSP Professional Edition licenses may
# use this file in accordance with the ViSP Commercial License
# Agreement provided with the Software.
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# Contact visp@irisa.fr if any conditions of this licensing are
# not clear to you.
#
# Description:
# Try to find libraries for Irisa's Afma 4 ddl cylindrical robot 
# Once run this will define: 
#
# AFMA4_FOUND
# AFMA4_INCLUDE_DIR
# AFMA4_LIBRARIES
#
# Authors:
# Fabien Spindler
#
#############################################################################

IF(NOT UNIX)
  # MESSAGE("FindAFMA4.cmake: Afma4 only available for Unix.")
  SET(AFMA4_FOUND FALSE)
ELSE(NOT UNIX)
  
  FIND_PATH(AFMA4_INCLUDE_DIR main_Afma4.h
    $ENV{AFMA4_HOME}/include
    /udd/fspindle/robot/Afma4/current/include
    /local/soft/Afma4/current/include 
    )
  #MESSAGE("DBG AFMA4_INCLUDE_DIR=${AFMA4_INCLUDE_DIR}")  
  
  FIND_LIBRARY(AFMA4_ROBOT_LIBRARY
    NAMES robotAfma4
    PATHS 
    $ENV{AFMA4_HOME}/lib
    /udd/fspindle/robot/Afma4/current/lib
    /local/soft/Afma4/current/lib
    )
  FIND_LIBRARY(AFMA4_TOOLS_LIBRARY
    NAMES toolsAfma4
    PATHS 
    $ENV{AFMA4_HOME}/lib
    /udd/fspindle/robot/Afma4/current/lib
    /local/soft/Afma4/current/lib
    )
  FIND_LIBRARY(AFMA4_UPRIM_LIBRARY
    NAMES uprimAfma4
    PATHS 
    $ENV{AFMA4_HOME}/lib
    /udd/fspindle/robot/Afma4/current/lib
    /local/soft/Afma4/current/lib
    )
  FIND_LIBRARY(AFMA4_BIT3_LIBRARY
    NAMES bit3Afma4
    PATHS 
    $ENV{AFMA4_HOME}/lib
    /udd/fspindle/robot/Afma4/current/lib
    /local/soft/Afma4/current/lib
    )
  FIND_LIBRARY(AFMA4_SERVOLENS_LIBRARY
    NAMES servolensAfma4
    PATHS 
    $ENV{AFMA4_HOME}/lib
    /udd/fspindle/robot/Afma4/current/lib
    /local/soft/Afma4/current/lib
    )
  #MESSAGE("DBG AFMA4_LIBRARY=${AFMA4_LIBRARY}")
  
  ## --------------------------------
  
  IF(AFMA4_ROBOT_LIBRARY AND AFMA4_TOOLS_LIBRARY AND AFMA4_UPRIM_LIBRARY 
      AND AFMA4_BIT3_LIBRARY AND AFMA4_SERVOLENS_LIBRARY)
    SET(AFMA4_LIBRARIES ${AFMA4_ROBOT_LIBRARY} ${AFMA4_TOOLS_LIBRARY}
      ${AFMA4_UPRIM_LIBRARY} ${AFMA4_BIT3_LIBRARY} ${AFMA4_SERVOLENS_LIBRARY})
  ELSE(AFMA4_ROBOT_LIBRARY AND AFMA4_TOOLS_LIBRARY AND AFMA4_UPRIM_LIBRARY 
      AND AFMA4_BIT3_LIBRARY AND AFMA4_SERVOLENS_LIBRARY)
    MESSAGE(SEND_ERROR "Afma4 library not found.")
  ENDIF(AFMA4_ROBOT_LIBRARY AND AFMA4_TOOLS_LIBRARY AND AFMA4_UPRIM_LIBRARY 
      AND AFMA4_BIT3_LIBRARY AND AFMA4_SERVOLENS_LIBRARY)
  
  IF(NOT AFMA4_INCLUDE_DIR)
    MESSAGE(SEND_ERROR "Afma4 include dir not found.")
  ENDIF(NOT AFMA4_INCLUDE_DIR)
  
  IF(AFMA4_LIBRARIES AND AFMA4_INCLUDE_DIR)
    SET(AFMA4_FOUND TRUE)
  ELSE(AFMA4_LIBRARIES AND AFMA4_INCLUDE_DIR)
    SET(AFMA4_FOUND FALSE)
  ENDIF(AFMA4_LIBRARIES AND AFMA4_INCLUDE_DIR)
  
  MARK_AS_ADVANCED(
    AFMA4_INCLUDE_DIR
    AFMA4_LIBRARIES
    AFMA4_ROBOT_LIBRARY
    AFMA4_TOOLS_LIBRARY
    AFMA4_UPRIM_LIBRARY
    AFMA4_BIT3_LIBRARY
    AFMA4_SERVOLENS_LIBRARY
    )
ENDIF(NOT UNIX)