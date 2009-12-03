/****************************************************************************
 *
 * $Id: vpBasicFeature.cpp,v 1.5 2007-06-27 14:38:31 fspindle Exp $
 *
 * Copyright (C) 1998-2006 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit.
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * Key point used in matching algorithm.
 *
 * Authors:
 * Nicolas Melchior
 *
 *****************************************************************************/


#include <visp/vpBasicKeyPoint.h>

/*!
  Basic constructor.
*/
vpBasicKeyPoint::vpBasicKeyPoint()
{
  referenceImagePointsList = NULL;
  currentImagePointsList = NULL;
  matchedReferencePoints = NULL;
  nbReferencePoints = 0;
  nbMatchedPoints = 0;
}


/*
 * Local variables:
 * c-basic-offset: 4
 * End:
 */
