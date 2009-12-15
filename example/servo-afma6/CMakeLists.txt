#############################################################################
#
# $Id: CMakeLists.txt,v 1.5 2008-07-18 09:16:53 fspindle Exp $
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
# ViSP configuration file. 
#
# Authors:
# Fabien Spindler
#
#############################################################################

# SOURCE variable corresponds to the list of all the sources to build binaries.
# The generate binary comes by removing the .cpp extension to
# the source name.
#
# If you want to add/remove a source, modify here
SET (SOURCE
  servoAfma6Ellipse2DCamVelocity.cpp
  servoAfma6FourPoints2DArtVelocity.cpp
  servoAfma6FourPoints2DCamVelocityInteractionDesired.cpp
  servoAfma6FourPoints2DCamVelocityInteractionCurrent.cpp
  servoAfma6Line2DCamVelocity.cpp
  servoAfma6Point2DArtVelocity.cpp
  servoAfma6Point2DCamVelocity.cpp
  servoAfma6Points2DCamVelocityEyeToHand.cpp
  servoAfma6SquareLines2DCamVelocity.cpp
  servoAfma6TwoLines2DCamVelocity.cpp
  servoAfma62DhalfCamVelocity.cpp
  servoAfma6Cylinder2DCamVelocity.cpp
  servoAfma6Cylinder2DCamVelocitySecondaryTask.cpp
)

# rule for binary build
FOREACH(source ${SOURCE})
  # Compute the name of the binary to create
  GET_FILENAME_COMPONENT(binary ${source} NAME_WE)

  # From source compile the binary and add link rules
  ADD_EXECUTABLE(${binary} ${source})
  TARGET_LINK_LIBRARIES(${binary} ${VISP_INTERN_LIBS} ${VISP_EXTERN_LIBS})

  # Add test
  ADD_TEST(${binary} ${binary})
ENDFOREACH(source)

# customize clean target 
SET_DIRECTORY_PROPERTIES(PROPERTIES 
  ADDITIONAL_MAKE_CLEAN_FILES "core*;*~;gmon.out;DartTestfile.txt"
)