/****************************************************************************
 *
 * $Id: manGrabDirectShow.cpp,v 1.4 2008-05-25 07:29:17 fspindle Exp $
 *
 * Copyright (C) 1998-2008 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit
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
 * Images grabbing example.
 *
 * Authors:
 * Anthony Saunier
 * Fabien Spindler
 *
 *****************************************************************************/
/*!
  \file manGrabDirectShow.cpp

  \brief Images grabbing example with the vpDirectShowGrabber class.

 */
/*!
  \example manGrabDirectShow.cpp

  \brief Images grabbing example with the vpDirectShowGrabber class.
 
 */

#include <visp/vpConfig.h>

#include <visp/vpImage.h>
#include <visp/vpDirectShowGrabber.h>

int main()
{
  vpImage<unsigned char> I; // Grey level image
  
#ifdef VISP_HAVE_DIRECTSHOW
  vpDirectShowGrabber g; // Create the grabber
  if(g.getDeviceNumber() == 0) //test if a camera is connected
  {
    g.close();
    return -1;
  }
  
  g.open(); // Initialize the grabber
  
  g.setImageSize(640,480); // If the camera supports 640x480 image size
  g.setFramerate(30); // If the camera supports 30fps framerate
  
  while(1)
    g.acquire(I); // Acquire an image
#endif

  return 0;
}