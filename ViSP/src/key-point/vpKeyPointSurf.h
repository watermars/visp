/****************************************************************************
 *
 * $Id: vpBasicFeature.h,v 1.10 2008-02-26 10:32:10 asaunier Exp $
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
 * Key point Surf.
 *
 * Authors:
 * Nicolas Melchior
 *
 *****************************************************************************/


#ifndef vpKeyPointSurf_H
#define vpKeyPointSurf_H

/*!
  \file vpKeyPointSurf.h

  \brief Class that implements the SURF key points and technics thanks
  to the OpenCV library.
*/

#include <visp/vpConfig.h>
#include <visp/vpBasicKeyPoint.h>

#if (VISP_HAVE_OPENCV_VERSION >= 0x010100) // Require opencv >= 1.1.0 

#include <cxcore.h>
#include <cv.h>


/*!
  \class vpKeyPointSurf
  
  \brief Class that implements the SURF key points and technics thanks
  to the OpenCV library.

  The goal of this class is to provide a tool to match points from a
  model and points belonging to an image in which the model appears.
  The coordinates of the different reference points and matched points
  are given in pixel thanks to the class vpImagePoint. In this
  documentation we do not explain the SURF technics. So if you want to
  learn more about it you can refere to the following article :
  Herbert Bay, Tinne Tuytelaars and Luc Van Gool "SURF: Speeded Up
  Robust Features", Proceedings of the 9th European Conference on
  Computer Vision, Springer LNCS volume 3951, part 1, pp 404--417,
  2006.

  If you use this class the first things you have to do is to create
  the reference thanks to a refrence image which contains the
  interesting object to detect. Then you have to grab other images
  containing the object. After calling the specific method to match
  points you can access to the lists of matched points thanks to the
  methods getMatchedPointsInReferenceImage() and
  getMatchedPointsInCurrentImage(). These two methods return a list of
  matched points. The nth element of the first list is matched with
  the nth element of the second list. The following small example show
  how to use the class.

  \code
#include <visp/vpConfig.h>
#include <visp/vpImage.h>
#include <visp/vpKeyPointSurf.h>

#if VISP_HAVE_OPENCV_VERSION >= 0x010100 // Surf key-points only available since OpenCV-1.1.0
int main()
{
  vpImage<unsigned char> Irefrence;
  vpImage<unsigned char> Icurrent;
  vpKeyPointSurf surf;

  //First grab the reference image Irefrence

  //Build the reference SURF points.
  surf.buildReference(Irefrence);

  //Then grab another image which represents the current image Icurrent

  //Match points between the reference points and the SURF points computed in the current image.
  surf.matchPoint(Icurrent);

  //Display the matched points
  surf.display(Irefrence, Icurrent);

  return (0);
}
#else
int main() {}
#endif
  \endcode

  It is also possible to create the refernece thanks to only a part of the 
  reference image (not the whole image) and find points to match in only a 
  part of the current image. The small following example shows how to this

  \code
#include <visp/vpConfig.h>
#include <visp/vpImage.h>
#include <visp/vpDisplay.h>
#include <visp/vpKeyPointSurf.h>

#if VISP_HAVE_OPENCV_VERSION >= 0x010100 // Surf key-points only available since OpenCV-1.1.0
int main()
{
  vpImage<unsigned char> Ireference;
  vpImage<unsigned char> Icurrent;
  vpKeyPointSurf surf;

  //First grab the reference image Irefrence

  //Select a part of the image by clincking on two points which define a rectangle
  vpImagePoint corners[2];
  for (int i=0 ; i < 2 ; i++)
  {
    vpDisplay::getClick(Ireference, corners[i]);
  }

  //Build the reference SURF points.
  int nbrRef;
  unsigned int height, width;
  height = (unsigned int)(corners[1].get_i() - corners[0].get_i());
  width = (unsigned int)(corners[1].get_j() - corners[0].get_j());
  nbrRef = surf.buildReference(Ireference, corners[0], height, width);

  //Then grab another image which represents the current image Icurrent

  //Select a part of the image by clincking on two points which define a rectangle
  for (int i=0 ; i < 2 ; i++)
  {
    vpDisplay::getClick(Icurrent, corners[i]);
  }

  //Match points between the reference points and the SURF points computed in the current image.
  int nbrMatched;
  height = (unsigned int)(corners[1].get_i() - corners[0].get_i());
  width = (unsigned int)(corners[1].get_j() - corners[0].get_j());
  nbrMatched = surf.matchPoint(Icurrent, corners[0], height, width);

  //Display the matched points
  surf.display(Ireference, Icurrent);

  return(0);
}
#else
int main() {}
#endif
  \endcode
*/

class VISP_EXPORT vpKeyPointSurf : public vpBasicKeyPoint
{
  public:
    /*!  
      This enumerate enables to set the detail level of the
      descriptors.
    */
    typedef enum 
    {
      basicDescriptor,   /*<! basicDescriptor means that the descriptors are
			   composed by 64 elements floating-point vector. */
      extendedDescriptor /*<! Means that the descriptors are composed by
			   128 elements floating-point vector. */
    } vpDescriptorType;

  public:
    vpKeyPointSurf();

    //! Basic destructor
    virtual ~vpKeyPointSurf() {cvReleaseMemStorage(&storage);} ;

    int buildReference(const vpImage<unsigned char> &I);
    int buildReference(const vpImage<unsigned char> &I, 
		       vpImagePoint &iP,
		       unsigned int height, unsigned int width);
    int buildReference(const vpImage<unsigned char> &I,
		       const vpRect rectangle);
    int matchPoint(const vpImage<unsigned char> &I);
    int matchPoint(const vpImage<unsigned char> &I, 
		   vpImagePoint &iP, unsigned int height, unsigned int width);
    int matchPoint(const vpImage<unsigned char> &I, const vpRect rectangle);
    void display(vpImage<unsigned char> &Iref, 
		 vpImage<unsigned char> &Icurrent);
    void display(vpImage<unsigned char> &Icurrent);

    /*!

      Sets the value of the hessian threhold.  Note that during the
      computation of the hessian for each potential points, only the
      points which have a hessian value higher than the threshold are
      keeped.  Fore more details about the threshold see the article
      Herbert Bay, Tinne Tuytelaars and Luc Van Gool "SURF: Speeded Up
      Robust Features", Proceedings of the 9th European Conference on
      Computer Vision, Springer LNCS volume 3951, part 1, pp 404--417,
      2006.

      \param hessianThreshold : Desired hessian threshold value.
    */
    void setHessianThreshold (double hessianThreshold) {
	this->hessianThreshold = hessianThreshold;
	params = cvSURFParams(this->hessianThreshold, this->descriptorType);
    } ;

    /*!

      Sets the type of descriptors to use.

      \param descriptorType : Type of descriptor to use.
    */
    void setDescriptorType (vpDescriptorType descriptorType) {
	this->descriptorType = descriptorType; 
	params = cvSURFParams(this->hessianThreshold, this->descriptorType);
    } ;

    /*!
      Gets the value of the hessian threhold.

      \return the hessian threshold value.
    */
    double getHessianThreshold () {return hessianThreshold;} ;

    /*!
      Gets the type of descriptor used.

      \return the type of descriptor used.
    */
    vpDescriptorType getDescriptorType () {return descriptorType;} ;


  private:
    void init();

  private:
    //OpenCV Parameters
    CvMemStorage* storage;
    CvSURFParams params;

    CvSeq* image_keypoints;
    CvSeq* image_descriptors;

    CvSeq* ref_keypoints;
    CvSeq* ref_descriptors;

    /*!
      only features with keypoint.hessian larger than that are extracted.
      Good default value is ~300-500 (can depend on the average
      local contrast and sharpness of the image).
      User can further filter out some features based on their hessian values
      and other characteristics.
    */
    double hessianThreshold;
    vpDescriptorType descriptorType;

};


#endif 

#endif

/*
 * Local variables:
 * c-basic-offset: 4
 * End:
 */
