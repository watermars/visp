/****************************************************************************
 *
 * $Id: vp1394TwoGrabber.h,v 1.24 2008-11-19 16:55:38 nmelchio Exp $
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
 * Firewire cameras video capture.
 *
 * Authors:
 * Fabien Spindler
 *
 *****************************************************************************/

/*!
  \file vp1394TwoGrabber.h
  \brief class for firewire cameras video capture using libdc1394-2.x api

  \warning This class needs libdc1394-2 and
  libraw1394 (version greater than 1.1.0). These libraries are available from
  http://sourceforge.net/projects/libdc1394 and
  http://sourceforge.net/projects/libraw1394 .

  vp1394TwoGrabber was tested with libdc1394-2.0.0 (svn version) and
  with the following cameras:
  - Marlin F033C
  - Marlin F131B
  - PointGrey Dragonfly 2
  - APPLE iSight extern webcam

*/

#ifndef vp1394TwoGrabber_h
#define vp1394TwoGrabber_h

#include <visp/vpConfig.h>

#if defined(VISP_HAVE_DC1394_2)


/*!
  \class vp1394TwoGrabber

  \ingroup Framegrabber
  
  \brief Class for firewire ieee1394 video devices using libdc1394-2.x api.

 
  Needs libraw1394-1.2.0 and libdc1394-2.0.0 or more recent versions
  available on http://sourceforge.net.

  This class was tested with Marlin F033C and F131B cameras and with
  Point Grey Dragonfly 2 camera.

  \ingroup libdevice

  This grabber allows single or multi camera acquisition. An example
  of a single camera acquisition is given in vp1394TwoGrabber(). An
  example of multi camera acquisition is available in setCamera().

  - Here an example of single capture from the first camera found on the bus:
  \code
#include <visp/vpConfig.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vp1394TwoGrabber.h>

int main()
{
#if defined(VISP_HAVE_DC1394_2)
  vpImage<unsigned char> I; // Create a gray level image container
  vp1394TwoGrabber g;       // Create a grabber based on libdc1394-2.x third party lib
  g.setVideoMode(vp1394TwoGrabber::vpVIDEO_MODE_640x480_MONO8);
  g.setFramerate(vp1394TwoGrabber::vpFRAMERATE_60);

  g.acquire(I);                        // Acquire an image
  vpImageIo::writePGM(I, "image.pgm"); // Write image on the disk
#endif
}
  \endcode

  - Here an example of multi camera capture:
  \code
#include <visp/vpConfig.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vp1394TwoGrabber.h>

int main()
{
#if defined(VISP_HAVE_DC1394_2)
  unsigned int ncameras; // Number of cameras on the bus
  vp1394TwoGrabber g;    // Creation of a grabber instance based on libdc1394-2.x third party lib.
  g.getNumCameras(ncameras);
  vpImage<unsigned char> *I = new vpImage<unsigned char> [ncameras];
  char filename[FILENAME_MAX];

  // If the first camera supports vpVIDEO_MODE_640x480_YUV422 video mode
  g.setCamera(0);
  g.setVideoMode(vp1394TwoGrabber::vpVIDEO_MODE_640x480_YUV422);

  // If the second camera support 30 fps acquisition
  g.setCamera(1);
  g.setFramerate(vp1394TwoGrabber::vpFRAMERATE_30);

  // Acquire an image from each camera
  for (unsigned int camera=0; camera < ncameras; camera ++) {
    g.setCamera(camera);
    g.acquire(I[camera]);
    sprintf(filename, "image-cam%d.pgm", camera);
    vpImageIo::writePGM(I[camera], filename);
  }
  delete [] I;
#endif
}
  \endcode

  \author  Fabien Spindler (Fabien.Spindler@irisa.fr), Irisa / Inria Rennes

*/

/*
 * Interface with libdc1394 2.x
 */
#include <string.h>

#include <dc1394/control.h>
#include <dc1394/utils.h>

#include <visp/vpImage.h>
#include <visp/vpFrameGrabber.h>
#include <visp/vpRGBa.h>
#include <visp/vpList.h>


class VISP_EXPORT vp1394TwoGrabber : public vpFrameGrabber
{

 public:
  static const char * strVideoMode[DC1394_VIDEO_MODE_NUM];
  static const char * strFramerate[DC1394_FRAMERATE_NUM];
  static const char * strColorCoding[DC1394_COLOR_CODING_NUM];

  /*!
    Enumeration of video modes. See libdc1394 2.x header file
    dc1394/control.h
  */
  typedef enum {
    vpVIDEO_MODE_160x120_YUV444   = DC1394_VIDEO_MODE_160x120_YUV444,
    vpVIDEO_MODE_320x240_YUV422   = DC1394_VIDEO_MODE_320x240_YUV422,
    vpVIDEO_MODE_640x480_YUV411   = DC1394_VIDEO_MODE_640x480_YUV411,
    vpVIDEO_MODE_640x480_YUV422   = DC1394_VIDEO_MODE_640x480_YUV422,
    vpVIDEO_MODE_640x480_RGB8     = DC1394_VIDEO_MODE_640x480_RGB8,
    vpVIDEO_MODE_640x480_MONO8    = DC1394_VIDEO_MODE_640x480_MONO8,
    vpVIDEO_MODE_640x480_MONO16   = DC1394_VIDEO_MODE_640x480_MONO16,
    vpVIDEO_MODE_800x600_YUV422   = DC1394_VIDEO_MODE_800x600_YUV422,
    vpVIDEO_MODE_800x600_RGB8     = DC1394_VIDEO_MODE_800x600_RGB8,
    vpVIDEO_MODE_800x600_MONO8    = DC1394_VIDEO_MODE_800x600_MONO8,
    vpVIDEO_MODE_1024x768_YUV422  = DC1394_VIDEO_MODE_1024x768_YUV422,
    vpVIDEO_MODE_1024x768_RGB8    = DC1394_VIDEO_MODE_1024x768_RGB8,
    vpVIDEO_MODE_1024x768_MONO8   = DC1394_VIDEO_MODE_1024x768_MONO8,
    vpVIDEO_MODE_800x600_MONO16   = DC1394_VIDEO_MODE_800x600_MONO16,
    vpVIDEO_MODE_1024x768_MONO16  = DC1394_VIDEO_MODE_1024x768_MONO16,
    vpVIDEO_MODE_1280x960_YUV422  = DC1394_VIDEO_MODE_1280x960_YUV422,
    vpVIDEO_MODE_1280x960_RGB8    = DC1394_VIDEO_MODE_1280x960_RGB8,
    vpVIDEO_MODE_1280x960_MONO8   = DC1394_VIDEO_MODE_1280x960_MONO8,
    vpVIDEO_MODE_1600x1200_YUV422 = DC1394_VIDEO_MODE_1600x1200_YUV422,
    vpVIDEO_MODE_1600x1200_RGB8   = DC1394_VIDEO_MODE_1600x1200_RGB8,
    vpVIDEO_MODE_1600x1200_MONO8  = DC1394_VIDEO_MODE_1600x1200_MONO8,
    vpVIDEO_MODE_1280x960_MONO16  = DC1394_VIDEO_MODE_1280x960_MONO16,
    vpVIDEO_MODE_1600x1200_MONO16 = DC1394_VIDEO_MODE_1600x1200_MONO16,
    vpVIDEO_MODE_EXIF      = DC1394_VIDEO_MODE_EXIF,
    vpVIDEO_MODE_FORMAT7_0 = DC1394_VIDEO_MODE_FORMAT7_0,
    vpVIDEO_MODE_FORMAT7_1 = DC1394_VIDEO_MODE_FORMAT7_1,
    vpVIDEO_MODE_FORMAT7_2 = DC1394_VIDEO_MODE_FORMAT7_2,
    vpVIDEO_MODE_FORMAT7_3 = DC1394_VIDEO_MODE_FORMAT7_3,
    vpVIDEO_MODE_FORMAT7_4 = DC1394_VIDEO_MODE_FORMAT7_4,
    vpVIDEO_MODE_FORMAT7_5 = DC1394_VIDEO_MODE_FORMAT7_5,
    vpVIDEO_MODE_FORMAT7_6 = DC1394_VIDEO_MODE_FORMAT7_6,
    vpVIDEO_MODE_FORMAT7_7 = DC1394_VIDEO_MODE_FORMAT7_7
  } vp1394TwoVideoModeType;

  /*!
    Enumeration of framerates. See libdc1394 2.x header file
    dc1394/control.h
  */
  typedef enum {
    vpFRAMERATE_1_875 = DC1394_FRAMERATE_1_875,
    vpFRAMERATE_3_75  = DC1394_FRAMERATE_3_75,
    vpFRAMERATE_7_5   = DC1394_FRAMERATE_7_5,
    vpFRAMERATE_15    = DC1394_FRAMERATE_15,
    vpFRAMERATE_30    = DC1394_FRAMERATE_30,
    vpFRAMERATE_60    = DC1394_FRAMERATE_60,
    vpFRAMERATE_120   = DC1394_FRAMERATE_120,
    vpFRAMERATE_240   = DC1394_FRAMERATE_240
  } vp1394TwoFramerateType;

  /*!
    Enumeration of color codings. See libdc1394 2.x header file
    dc1394/control.h
  */
  typedef enum {
    vpCOLOR_CODING_MONO8   = DC1394_COLOR_CODING_MONO8,
    vpCOLOR_CODING_YUV411  = DC1394_COLOR_CODING_YUV411,
    vpCOLOR_CODING_YUV422  = DC1394_COLOR_CODING_YUV422,
    vpCOLOR_CODING_YUV444  = DC1394_COLOR_CODING_YUV444,
    vpCOLOR_CODING_RGB8    = DC1394_COLOR_CODING_RGB8,
    vpCOLOR_CODING_MONO16  = DC1394_COLOR_CODING_MONO16,
    vpCOLOR_CODING_RGB16   = DC1394_COLOR_CODING_RGB16,
    vpCOLOR_CODING_MONO16S = DC1394_COLOR_CODING_MONO16S,
    vpCOLOR_CODING_RGB16S  = DC1394_COLOR_CODING_RGB16S,
    vpCOLOR_CODING_RAW8    = DC1394_COLOR_CODING_RAW8,
    vpCOLOR_CODING_RAW16   = DC1394_COLOR_CODING_RAW16
  } vp1394TwoColorCodingType;


 public:
  vp1394TwoGrabber(bool reset=true);
  virtual ~vp1394TwoGrabber();


  void getCamera(unsigned int &camera);
  void getColorCoding(vp1394TwoColorCodingType & coding);
  int  getColorCodingSupported(vp1394TwoVideoModeType videomode,
			       vpList<vp1394TwoColorCodingType> & codings);
  void getFramerate(vp1394TwoFramerateType & fps);
  int  getFramerateSupported(vp1394TwoVideoModeType videomode,
			     vpList<vp1394TwoFramerateType> & fps);
  void getHeight(unsigned int &height);
  void getNumCameras(unsigned int &ncameras);
  unsigned int getRingBufferSize();
  void getVideoMode(vp1394TwoVideoModeType & videomode);
  int  getVideoModeSupported(vpList<vp1394TwoVideoModeType> & videomodes);
  void getWidth(unsigned int &width);

  bool isColor();
  bool isColorCodingSupported(vp1394TwoVideoModeType videomode,
                              vp1394TwoColorCodingType coding);
  bool isFramerateSupported(vp1394TwoVideoModeType videomode,
                            vp1394TwoFramerateType fps);
  bool isVideoModeSupported(vp1394TwoVideoModeType videomode) ;
  bool isVideoModeFormat7(vp1394TwoVideoModeType videomode);


  void setCamera(unsigned int camera);
  void setColorCoding(vp1394TwoColorCodingType coding);
  void setFormat7ROI(unsigned int left=0, unsigned int top=0,
		     unsigned int width=0, unsigned int height=0);
  void setFramerate(vp1394TwoFramerateType fps);
  void setRingBufferSize(unsigned int size);
  void setVideoMode(vp1394TwoVideoModeType videomode);
  void setPanControl(int panControlValue);

  void open(vpImage<unsigned char> &I);
  void open(vpImage<vpRGBa> &I);

  void printCameraInfo();


  dc1394video_frame_t *dequeue();
  dc1394video_frame_t *dequeue(vpImage<unsigned char> &I);
  dc1394video_frame_t *dequeue(vpImage<unsigned char> &I, uint64_t &timestamp, uint32_t &id);
  dc1394video_frame_t *dequeue(vpImage<vpRGBa> &I);
  dc1394video_frame_t *dequeue(vpImage<vpRGBa> &I, uint64_t &timestamp, uint32_t &id);
  void enqueue(dc1394video_frame_t *frame);

  void acquire(vpImage<unsigned char> &I);
  void acquire(vpImage<unsigned char> &I, uint64_t &timestamp, uint32_t &id);
  void acquire(vpImage<vpRGBa> &I);
  void acquire(vpImage<vpRGBa> &I, uint64_t &timestamp, uint32_t &id);


  void close();
  void resetBus();

public:
  static std::string videoMode2string(vp1394TwoVideoModeType videomode);
  static std::string framerate2string(vp1394TwoFramerateType fps);
  static std::string colorCoding2string(vp1394TwoColorCodingType colorcoding);
  static vp1394TwoVideoModeType string2videoMode(std::string videomode);
  static vp1394TwoFramerateType string2framerate(std::string fps);
  static vp1394TwoColorCodingType string2colorCoding(std::string colorcoding);

 private:
  void open();
  void initialize(bool reset); 
  void setCapture(dc1394switch_t _switch);
  void setTransmission(dc1394switch_t _switch);
  void setIsoSpeed(dc1394speed_t speed);

 private:
  dc1394camera_t *camera, **cameras;
  unsigned int num_cameras;
  unsigned int camera_id;

  bool verbose;
  bool *camIsOpen;
  unsigned int num_buffers;

#ifdef VISP_HAVE_DC1394_2_CAMERA_ENUMERATE
  dc1394_t * d;
  dc1394camera_list_t * list;
#endif
};


#endif
#endif
