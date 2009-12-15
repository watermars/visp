/****************************************************************************
 *
 * $Id: vpFeatureException.h,v 1.6 2008-09-26 15:21:02 fspindle Exp $
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
 * Exception that can be emited by the vpFeature class and its derivates.
 *
 * Authors:
 * Eric Marchand
 *
 *****************************************************************************/


#ifndef __vpFeatureException_H
#define __vpFeatureException_H


/* ------------------------------------------------------------------------- */
/* --- INCLUDE ------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */


/* \file vpFeatureException.h
   \brief error that can be emited by the vpFeature class and its derivates
 */
/* Classes standards. */
#include <iostream>                /* Classe std::ostream.    */
#include <string>                  /* Classe string.     */
#include <visp/vpConfig.h>
#include <visp/vpException.h>



/* ------------------------------------------------------------------------- */
/* --- CLASS --------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

/*!
  \class vpFeatureException
  \ingroup Exception
  \brief Error that can be emited by the vpBasicFeature class and its derivates.
 */
class VISP_EXPORT vpFeatureException : public vpException
{
public:
  /*!
    \brief Lists the possible error than can be emmited while calling
    vpFeature member
   */
  enum errorFeatureCodeEnum
    {
      //! feature list or desired feature list is empty
      badErrorVectorError,
      sizeMismatchError,
      notInitializedError,
      badInitializationError
    } ;

public:
  vpFeatureException (const int code, const char * msg)
    : vpException(code, msg){ ; }
  vpFeatureException (const int code, const std::string & msg)
    : vpException(code, msg){ ; }
  vpFeatureException (const int code)
    : vpException(code){ ; }

};





#endif /* #ifndef __vpFeatureException_H */


/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */