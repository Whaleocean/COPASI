/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingItemWidget.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/14 16:30:16 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Tue Mar 14 09:38:07 2006
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.cpp,v 1.11 2006/03/14 16:30:16 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQFittingItemWidget.h"

#include <qvariant.h>
 #include <qpushbutton.h>
 #include <qtable.h>
 #include <qcheckbox.h>
 #include <qlabel.h>
 #include <qtoolbutton.h>
 #include <qcombobox.h>
 #include <qlineedit.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include <qimage.h>
 #include <qpixmap.h>

#include "CQFittingItemWidget.ui.h"
static const unsigned char image0_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x2b, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x95, 0x92, 0xdf, 0x4b, 0x53,
    0x61, 0x18, 0xc7, 0x3f, 0xaf, 0x3b, 0x67, 0x9b, 0xd3, 0xc3, 0x4e, 0x4e,
    0x12, 0x5a, 0xe9, 0x91, 0xe1, 0xd4, 0x0c, 0x9b, 0xae, 0x2d, 0xba, 0x88,
    0x26, 0x5e, 0x76, 0x33, 0xfb, 0x07, 0x6c, 0x17, 0x29, 0xde, 0xd5, 0x7f,
    0x50, 0xb7, 0xfd, 0x07, 0x13, 0x42, 0x0c, 0xa2, 0x8b, 0xa0, 0x46, 0x10,
    0x04, 0xdd, 0x75, 0x97, 0x53, 0x1c, 0x79, 0x21, 0x2d, 0x24, 0x49, 0xf0,
    0xc7, 0x82, 0x3c, 0x6e, 0xed, 0x47, 0xf3, 0x9c, 0xf3, 0x76, 0xa1, 0x4e,
    0xad, 0x09, 0xf9, 0xc0, 0x17, 0xde, 0x87, 0xf7, 0x7d, 0x3e, 0xdf, 0x07,
    0xbe, 0xaf, 0x90, 0x52, 0x72, 0x56, 0x2d, 0x4d, 0xc7, 0xbf, 0x01, 0x44,
    0xd3, 0x0b, 0xbd, 0x67, 0xbd, 0x69, 0x39, 0xeb, 0x22, 0x3b, 0x15, 0x8f,
    0x04, 0x46, 0x63, 0x46, 0x60, 0x34, 0x66, 0x2c, 0xce, 0xc4, 0x12, 0xe7,
    0x06, 0x08, 0xc1, 0xa4, 0x3e, 0x30, 0x48, 0xe0, 0x5a, 0x18, 0x21, 0xc5,
    0xe4, 0xb9, 0x01, 0xaa, 0x6a, 0x25, 0xf5, 0x50, 0x10, 0x2d, 0x74, 0x15,
    0x4f, 0xbb, 0x9a, 0xcc, 0xa5, 0x46, 0xf4, 0xff, 0x06, 0x64, 0xa7, 0xe2,
    0x11, 0x7f, 0x5f, 0xc8, 0xc0, 0x2a, 0x43, 0x6d, 0x9b, 0xc0, 0xc0, 0x65,
    0xdd, 0x51, 0xd5, 0x64, 0xd3, 0x4d, 0x97, 0x1e, 0xc4, 0xee, 0x3b, 0x42,
    0x18, 0x07, 0xad, 0xf4, 0x0b, 0x49, 0xc4, 0xe5, 0xb6, 0x22, 0xa1, 0x7b,
    0xe3, 0xba, 0xd6, 0x7d, 0x11, 0x80, 0xfa, 0xde, 0x2f, 0xf2, 0x2f, 0xdf,
    0x9b, 0xbf, 0x8b, 0x32, 0xf7, 0x97, 0xfd, 0xba, 0xf8, 0xfc, 0x70, 0x58,
    0x5e, 0xb9, 0xdd, 0x89, 0xab, 0x2d, 0x00, 0x8a, 0x1f, 0xad, 0xb3, 0x08,
    0x8a, 0x1f, 0x54, 0x3f, 0x34, 0x12, 0x92, 0x07, 0xaa, 0x7e, 0x6f, 0x9c,
    0xed, 0x6a, 0x95, 0x95, 0x17, 0x05, 0x5a, 0xf6, 0xcb, 0x9e, 0xd4, 0x56,
    0xd6, 0xc4, 0xd7, 0xb1, 0x89, 0x16, 0x2c, 0x83, 0xd7, 0x03, 0x4a, 0x0d,
    0xe4, 0x36, 0x70, 0x28, 0x79, 0x28, 0xaf, 0x1b, 0xdc, 0x16, 0x76, 0xf5,
    0x2b, 0xf9, 0xb7, 0x3b, 0x38, 0x75, 0x57, 0x4a, 0x48, 0x29, 0x59, 0x9a,
    0xbe, 0x99, 0x74, 0xb9, 0xf7, 0xe7, 0xc2, 0x77, 0xbf, 0xe8, 0xbe, 0x2e,
    0x15, 0x94, 0x0e, 0x10, 0xca, 0xb1, 0xbb, 0x04, 0x64, 0x15, 0xec, 0x12,
    0x95, 0x1d, 0x8b, 0xfc, 0xbb, 0x7e, 0xd3, 0xae, 0xab, 0xa9, 0x68, 0xfa,
    0x53, 0x46, 0x1c, 0x7d, 0xa4, 0xec, 0x54, 0x3c, 0xe2, 0x6e, 0xb5, 0xde,
    0xf4, 0x8c, 0xaf, 0x1b, 0x7a, 0x68, 0xb7, 0x69, 0x32, 0x95, 0x1f, 0x3e,
    0xf2, 0xaf, 0xfb, 0xcd, 0xfd, 0x9a, 0x32, 0x16, 0x9b, 0x5d, 0xc8, 0x9d,
    0x4a, 0x21, 0x36, 0xbb, 0x90, 0x93, 0x75, 0xcf, 0x58, 0x61, 0xa5, 0x0b,
    0x7c, 0x34, 0xd5, 0xde, 0xc6, 0x05, 0x9c, 0x9a, 0xf2, 0xe8, 0x68, 0xf8,
    0x9f, 0x18, 0x2d, 0x2c, 0xa3, 0x35, 0x58, 0x81, 0x56, 0x0e, 0x24, 0x00,
    0x9b, 0x46, 0xdf, 0xde, 0x57, 0xc4, 0x11, 0x5c, 0x3f, 0x1d, 0xc4, 0xc9,
    0x72, 0x5a, 0x12, 0x5a, 0xb8, 0xd4, 0x18, 0xae, 0x17, 0x54, 0x2a, 0x9b,
    0x5e, 0xa8, 0x02, 0x5e, 0xd0, 0x06, 0x4b, 0x08, 0x48, 0x9e, 0x09, 0x10,
    0x52, 0xde, 0xd1, 0x86, 0x8a, 0xe0, 0x40, 0xe1, 0x63, 0x80, 0xd5, 0xe7,
    0xe1, 0xf5, 0xd5, 0xf9, 0x81, 0xcc, 0xda, 0xab, 0x1e, 0xec, 0x92, 0x0b,
    0xdc, 0xa0, 0x0f, 0xef, 0x1a, 0xb9, 0x99, 0x5b, 0x46, 0x53, 0x80, 0xaf,
    0xbb, 0x92, 0xc0, 0x81, 0xb5, 0xf9, 0x5e, 0x36, 0x3e, 0x18, 0x19, 0x59,
    0x56, 0x47, 0xa2, 0xcf, 0x96, 0x27, 0xcc, 0xb5, 0xce, 0x89, 0x95, 0xa7,
    0x43, 0xa6, 0xb9, 0xec, 0x47, 0x0b, 0x97, 0x70, 0x6c, 0x3b, 0x71, 0xc2,
    0xf4, 0x38, 0x85, 0xf6, 0x60, 0x79, 0xf9, 0xf7, 0x4f, 0xd5, 0xb4, 0x6b,
    0x4a, 0x2a, 0x9a, 0x5e, 0xcc, 0x9c, 0x84, 0xe7, 0x52, 0x23, 0xba, 0xad,
    0xba, 0xe6, 0x7c, 0x97, 0x2a, 0xc9, 0xf2, 0x56, 0xdb, 0x93, 0x1b, 0xe9,
    0xec, 0x63, 0x80, 0x3f, 0x01, 0x15, 0xd9, 0xe6, 0x21, 0xbb, 0xfb, 0x88,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
  };

static const unsigned char image1_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x0e, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xc5, 0x93, 0xcf, 0x4b, 0x54,
    0x51, 0x14, 0xc7, 0x3f, 0x77, 0xde, 0x73, 0x1c, 0x1c, 0xa6, 0xb1, 0x92,
    0x4a, 0x0c, 0x2d, 0x6d, 0x15, 0x61, 0x2d, 0x6c, 0x13, 0xa1, 0x8b, 0x70,
    0xdd, 0x1f, 0x20, 0xd4, 0xa2, 0x5c, 0x94, 0x14, 0x2e, 0xaa, 0xcd, 0xb4,
    0x34, 0x88, 0x5a, 0x89, 0xd4, 0x22, 0x21, 0xfa, 0x45, 0x45, 0x9a, 0x11,
    0x82, 0x4b, 0x4d, 0xb3, 0x8d, 0x4a, 0x16, 0x86, 0x89, 0x13, 0x45, 0x85,
    0xd5, 0xe8, 0x4c, 0x6f, 0xc6, 0x52, 0x67, 0xde, 0x7b, 0xf7, 0x9e, 0x16,
    0x33, 0x86, 0x39, 0xb5, 0x72, 0xd1, 0x81, 0xbb, 0xb8, 0x97, 0xf3, 0xfd,
    0xdc, 0x2f, 0x9c, 0xef, 0x51, 0x22, 0xc2, 0x46, 0x2a, 0xb0, 0x21, 0x35,
    0xa0, 0xf6, 0x9c, 0x18, 0x3c, 0xed, 0x6a, 0xeb, 0xaa, 0xd6, 0x12, 0x10,
    0xcf, 0xc7, 0x78, 0x1e, 0xc6, 0xf5, 0xd1, 0xae, 0x87, 0xef, 0xfa, 0xe0,
    0x7a, 0x68, 0xd7, 0x47, 0x5c, 0x1f, 0xed, 0xf9, 0x18, 0xcf, 0x45, 0x7b,
    0x1a, 0x9d, 0x5e, 0x34, 0xa4, 0x9d, 0xf3, 0xaa, 0xe6, 0xe4, 0xe8, 0xb7,
    0xea, 0x86, 0xfa, 0xed, 0x75, 0x35, 0x11, 0x8c, 0x59, 0x8f, 0x5f, 0x77,
    0x55, 0xf9, 0x37, 0xdb, 0x86, 0xa9, 0xf1, 0x39, 0xc6, 0x2f, 0xdf, 0x4c,
    0xd8, 0x5e, 0xa0, 0xb4, 0xa2, 0xb9, 0x3e, 0xc2, 0xd1, 0x3a, 0xc8, 0xe4,
    0x8a, 0x34, 0x7f, 0x94, 0xa5, 0xf2, 0xa7, 0x2c, 0x08, 0x4f, 0xcb, 0xab,
    0x18, 0xef, 0xae, 0xa8, 0xb0, 0x55, 0x3a, 0x35, 0xd5, 0x3f, 0xfa, 0xf5,
    0x40, 0xc8, 0xaa, 0x24, 0x6c, 0x81, 0x5e, 0xef, 0xa2, 0x60, 0xc4, 0x0e,
    0xc0, 0xfc, 0x32, 0x38, 0x39, 0xd8, 0x14, 0x86, 0xbe, 0x47, 0x6f, 0x90,
    0xb9, 0x8f, 0x53, 0xb6, 0xad, 0xb3, 0xb1, 0x0f, 0x23, 0x13, 0x8f, 0xef,
    0x97, 0x34, 0x86, 0x1a, 0xf7, 0x45, 0x41, 0xc3, 0xda, 0xb9, 0x28, 0x95,
    0x87, 0xbe, 0x5e, 0x80, 0x99, 0x24, 0xac, 0x04, 0xa0, 0x24, 0x99, 0x22,
    0x7d, 0xa3, 0x27, 0x4b, 0x6e, 0x25, 0xa6, 0x44, 0x84, 0x9d, 0x47, 0xee,
    0x76, 0xfc, 0x2c, 0xaf, 0x8a, 0x55, 0x37, 0x37, 0xb1, 0x6b, 0x8b, 0x85,
    0x2e, 0x40, 0xa4, 0xf0, 0x7b, 0x3c, 0x0d, 0xef, 0x9c, 0x02, 0xd1, 0xf7,
    0xe1, 0xde, 0x2d, 0x88, 0x4f, 0x5e, 0x12, 0xb9, 0x76, 0x51, 0xad, 0xe6,
    0x60, 0xdb, 0xc1, 0xee, 0xdb, 0x6e, 0xed, 0xde, 0x63, 0x91, 0xc3, 0x87,
    0x08, 0xda, 0x0a, 0x0c, 0x88, 0xc0, 0x0f, 0x17, 0x92, 0x59, 0xc0, 0x02,
    0xc4, 0xc0, 0x93, 0x3e, 0x18, 0x1b, 0xbe, 0x23, 0xd2, 0x75, 0x1c, 0xc0,
    0x5e, 0xb5, 0xea, 0x86, 0xfc, 0xf6, 0xc0, 0xf4, 0x64, 0x4d, 0xd2, 0x2a,
    0x6d, 0xf2, 0xf7, 0x37, 0x20, 0x7e, 0xbe, 0xdf, 0x98, 0x82, 0x8d, 0x00,
    0x30, 0xf8, 0x0c, 0xc6, 0x5e, 0x0c, 0x83, 0x6e, 0x5f, 0xd5, 0xfd, 0x0e,
    0x52, 0xfa, 0xf9, 0x29, 0x47, 0x6b, 0xd3, 0x6a, 0x8f, 0x8d, 0xcc, 0x96,
    0xbc, 0x9d, 0xa1, 0x2c, 0x08, 0x21, 0x05, 0x61, 0x0b, 0x22, 0x61, 0x08,
    0xbe, 0x7c, 0x05, 0x43, 0x03, 0xb3, 0x60, 0x5a, 0x45, 0xae, 0x3b, 0x45,
    0x00, 0x80, 0xcc, 0xf4, 0xd9, 0xb8, 0x59, 0x5e, 0x69, 0x51, 0x43, 0xfd,
    0x89, 0xad, 0x89, 0x4f, 0xd4, 0xee, 0x80, 0xdd, 0x95, 0xb0, 0xf9, 0xf3,
    0x7b, 0xf4, 0x40, 0x4f, 0x02, 0x3f, 0xd7, 0x22, 0xd2, 0x19, 0x5f, 0xab,
    0x29, 0x8a, 0xf2, 0xd2, 0x97, 0xd8, 0x84, 0xff, 0x3d, 0xd3, 0x96, 0xea,
    0xed, 0xcd, 0x45, 0x9d, 0x79, 0xa2, 0xa9, 0x04, 0x0b, 0x0f, 0x1e, 0xe6,
    0xf4, 0xd2, 0x62, 0x9b, 0x48, 0xd7, 0x44, 0xd1, 0x88, 0xff, 0xb5, 0x4c,
    0xca, 0x3a, 0x77, 0x26, 0x14, 0x8d, 0x5c, 0xc1, 0x08, 0xd9, 0x8c, 0x73,
    0x41, 0xa4, 0xb3, 0xeb, 0xaf, 0x7d, 0xff, 0x7d, 0x1b, 0x7f, 0x01, 0xe5,
    0xff, 0xf8, 0x98, 0x20, 0x26, 0x1c, 0x32, 0x00, 0x00, 0x00, 0x00, 0x49,
    0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
  };

static const unsigned char image2_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x3b, 0xd6, 0x95, 0x4a, 0x00, 0x00, 0x00,
    0xbf, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xad, 0x92, 0x41, 0x0a, 0xc2,
    0x30, 0x14, 0x44, 0xdf, 0x88, 0x7b, 0x11, 0x4f, 0x20, 0xb8, 0xa8, 0xb7,
    0x70, 0xe3, 0x41, 0x3c, 0x47, 0x8f, 0x96, 0x8d, 0x27, 0x70, 0xd9, 0xb4,
    0x10, 0xe8, 0x09, 0x8a, 0x78, 0x01, 0xbf, 0x1b, 0x53, 0x6c, 0x6c, 0xaa,
    0x54, 0x3f, 0x04, 0xc2, 0x64, 0x26, 0xc3, 0x4c, 0x22, 0x33, 0x63, 0xee,
    0x2c, 0x66, 0x2b, 0xff, 0x2a, 0xae, 0x25, 0xe7, 0xa5, 0x30, 0x25, 0xf0,
    0x52, 0xe8, 0x39, 0x66, 0x36, 0x58, 0x1e, 0xba, 0x0a, 0x42, 0x8a, 0xd7,
    0x50, 0x56, 0x10, 0x6a, 0x28, 0x23, 0xa6, 0xb4, 0xb0, 0x46, 0x2a, 0xef,
    0x70, 0x02, 0xd8, 0x9b, 0xed, 0xa2, 0x1b, 0x80, 0xa0, 0x2d, 0xcc, 0x8e,
    0x3d, 0x39, 0x75, 0x88, 0x2e, 0x1e, 0xba, 0xe8, 0x16, 0xf7, 0x29, 0xef,
    0xcd, 0xf9, 0x25, 0x7f, 0x07, 0xac, 0x80, 0x5b, 0x61, 0xb6, 0x19, 0xe3,
    0x2c, 0x33, 0x42, 0x67, 0x70, 0xd5, 0x54, 0x73, 0x30, 0x74, 0x8e, 0x79,
    0x05, 0x6b, 0xe0, 0x22, 0x38, 0x03, 0x3c, 0xb1, 0x61, 0xde, 0x54, 0xec,
    0xa5, 0x20, 0x68, 0x01, 0x22, 0xb1, 0x91, 0x4a, 0x83, 0x83, 0xc1, 0x36,
    0x5b, 0x98, 0x07, 0xe7, 0xc1, 0x8d, 0x15, 0x98, 0x7b, 0xaa, 0xfe, 0x60,
    0xac, 0xcd, 0xdc, 0x25, 0x1f, 0xdb, 0xfe, 0x66, 0x7e, 0xfa, 0xdb, 0x0f,
    0x18, 0xe8, 0xd7, 0x34, 0x08, 0xf9, 0x77, 0xe5, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
  };

static const unsigned char image3_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x18, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x7d, 0x92, 0xcb, 0x4a, 0x5c,
    0x41, 0x10, 0x86, 0xbf, 0xea, 0xee, 0x39, 0x73, 0xc6, 0x11, 0x41, 0x72,
    0x11, 0x11, 0x02, 0x51, 0xb3, 0x90, 0x90, 0x59, 0x8a, 0xb8, 0xc8, 0x22,
    0x2f, 0x12, 0x12, 0x92, 0x07, 0x08, 0x24, 0x8b, 0x11, 0x02, 0x82, 0x1b,
    0x4d, 0xde, 0x20, 0x31, 0x97, 0x95, 0x1b, 0x1f, 0x20, 0xcc, 0xd2, 0x80,
    0x8a, 0x06, 0xc4, 0x45, 0x44, 0x54, 0x22, 0x51, 0x88, 0x59, 0xa8, 0xa8,
    0x73, 0xc6, 0xb9, 0x9e, 0xd3, 0x95, 0xc5, 0x78, 0xd7, 0x49, 0x41, 0x6d,
    0xaa, 0xe8, 0xbf, 0xff, 0xff, 0xeb, 0x96, 0xd9, 0xd9, 0xf5, 0x83, 0xce,
    0xce, 0x76, 0xa7, 0xea, 0x89, 0x63, 0x8f, 0xf7, 0x8a, 0x31, 0x96, 0x95,
    0x95, 0xcd, 0xf6, 0xe5, 0xe5, 0xb5, 0xe7, 0x13, 0x13, 0x2f, 0xbe, 0xf0,
    0xbf, 0x5a, 0x5a, 0xda, 0x6c, 0x78, 0xef, 0xf5, 0xb4, 0x6b, 0x35, 0xaf,
    0xfb, 0xfb, 0x15, 0x5d, 0x5d, 0xfd, 0xab, 0x53, 0x53, 0xdf, 0x75, 0x64,
    0xe4, 0xd3, 0x1b, 0x55, 0xa5, 0x55, 0x9b, 0xab, 0x82, 0xd6, 0x42, 0x10,
    0x04, 0x6c, 0x6c, 0xfc, 0x61, 0x6f, 0xef, 0x80, 0x30, 0x0c, 0xde, 0xe5,
    0xf3, 0x93, 0x6f, 0x5b, 0x19, 0xb8, 0x26, 0x20, 0x02, 0x49, 0x12, 0x93,
    0xcb, 0xf5, 0x33, 0x38, 0xf8, 0x90, 0x81, 0x81, 0x5e, 0x44, 0xcc, 0xfd,
    0x56, 0x02, 0xee, 0x26, 0x01, 0x6b, 0x2d, 0xc5, 0x62, 0x99, 0x4a, 0xa5,
    0x4e, 0x47, 0x47, 0x96, 0xe1, 0xe1, 0x47, 0x8f, 0x17, 0x16, 0x7e, 0x7d,
    0x88, 0xe3, 0x38, 0x53, 0x2c, 0x56, 0xb2, 0x33, 0x33, 0x3f, 0xbe, 0x8d,
    0x8f, 0xbf, 0xfc, 0x78, 0x23, 0x83, 0x28, 0xf2, 0xba, 0xbd, 0x7d, 0xa8,
    0x73, 0x73, 0xeb, 0x7a, 0x74, 0x54, 0xbd, 0x34, 0xdf, 0xd9, 0x89, 0x74,
    0x6b, 0xeb, 0x50, 0xa7, 0xa7, 0xe7, 0x74, 0x74, 0xf4, 0xeb, 0x6b, 0x55,
    0xbd, 0xec, 0xa0, 0x5a, 0x85, 0x72, 0xb9, 0x8a, 0x31, 0x16, 0x6b, 0x2d,
    0xe9, 0xf4, 0xf9, 0x3a, 0x9b, 0x05, 0xef, 0x33, 0xec, 0xee, 0x1e, 0x12,
    0x45, 0x11, 0xe9, 0x74, 0xf8, 0x3e, 0x9f, 0x9f, 0xbc, 0x7b, 0xc6, 0x40,
    0x15, 0xea, 0xf5, 0x06, 0xce, 0x19, 0xc2, 0xd0, 0x21, 0x22, 0xa8, 0x5e,
    0xc9, 0xeb, 0x84, 0x20, 0x48, 0xd1, 0xdd, 0x7d, 0x87, 0xfe, 0xfe, 0x7b,
    0xb4, 0xb5, 0x85, 0xaf, 0xce, 0x04, 0xea, 0x75, 0x10, 0xb1, 0x88, 0xb4,
    0xc2, 0x05, 0xc6, 0x08, 0xe9, 0x74, 0x8a, 0xae, 0xae, 0x5b, 0xf4, 0xf4,
    0xdc, 0xc6, 0xb9, 0x14, 0xce, 0x98, 0xf3, 0x87, 0x70, 0x4e, 0x30, 0xc6,
    0x91, 0x24, 0x70, 0x71, 0x7e, 0x5a, 0xe5, 0x72, 0x9d, 0x52, 0xa9, 0x8c,
    0xf7, 0x4a, 0x26, 0x93, 0x46, 0x44, 0x70, 0x51, 0x54, 0x21, 0x8a, 0x1a,
    0x44, 0x51, 0x15, 0xef, 0x15, 0xef, 0x3d, 0x49, 0xa2, 0xd4, 0xeb, 0x31,
    0x72, 0xc1, 0x4e, 0x14, 0x79, 0x8e, 0x8f, 0x6b, 0xa8, 0x0a, 0xd9, 0x6c,
    0x06, 0x6b, 0x2d, 0xce, 0x81, 0x2b, 0x14, 0xe6, 0xa7, 0x0a, 0x85, 0x79,
    0x73, 0xf9, 0xa6, 0x5a, 0x25, 0x97, 0x7b, 0xf0, 0x64, 0x68, 0xa8, 0xb7,
    0xef, 0x14, 0x6e, 0x1c, 0x37, 0x08, 0x02, 0x87, 0x31, 0x06, 0x63, 0xe4,
    0xc4, 0xa1, 0xe0, 0xc6, 0xc6, 0x9e, 0x3d, 0xbd, 0x29, 0x6f, 0xa1, 0xb0,
    0xfc, 0xd9, 0x7b, 0xfa, 0x8c, 0x81, 0x24, 0xf1, 0x58, 0x6b, 0x88, 0x63,
    0xc5, 0x5a, 0x83, 0xb5, 0x06, 0x11, 0xdb, 0xe4, 0xd2, 0x0a, 0x58, 0x18,
    0x86, 0x27, 0x51, 0x00, 0x9a, 0x51, 0xac, 0xbd, 0x4e, 0xf8, 0xda, 0x4f,
    0x3c, 0x27, 0xde, 0x3c, 0x98, 0x4a, 0x81, 0x88, 0xe0, 0x7d, 0x0a, 0x11,
    0x8f, 0x48, 0x0c, 0x80, 0x88, 0x69, 0x42, 0x6c, 0x25, 0xb0, 0xb8, 0xf8,
    0xb3, 0xb6, 0xb6, 0xf6, 0x1b, 0xa0, 0x04, 0xa0, 0xaa, 0x24, 0x49, 0x73,
    0xa7, 0x9a, 0x20, 0x02, 0xa5, 0x52, 0x25, 0xfe, 0x07, 0xd9, 0xbb, 0x1d,
    0xb5, 0x0b, 0x97, 0x87, 0x95, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e,
    0x44, 0xae, 0x42, 0x60, 0x82
  };

static const unsigned char image4_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x1b, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x93, 0x4b, 0x48, 0x94,
    0x51, 0x18, 0x86, 0x9f, 0xf3, 0xff, 0xff, 0x34, 0x5e, 0x12, 0x1d, 0x19,
    0x66, 0x5c, 0x18, 0xa6, 0xe6, 0x3d, 0xa5, 0x1a, 0x5b, 0x58, 0x90, 0x21,
    0x44, 0x25, 0x41, 0x17, 0xdb, 0x84, 0x69, 0x66, 0xbb, 0xa0, 0xa5, 0xad,
    0x5a, 0xb6, 0x88, 0xdc, 0x48, 0x6d, 0x24, 0x69, 0xd7, 0x2c, 0x0a, 0x84,
    0x56, 0x41, 0x23, 0x6d, 0xa2, 0x36, 0x2d, 0x8d, 0x48, 0x68, 0x11, 0x65,
    0x86, 0xe3, 0x8c, 0x93, 0x36, 0xf3, 0xcf, 0xcc, 0x7f, 0x39, 0xe7, 0xb4,
    0x98, 0x28, 0x6f, 0x2d, 0xc2, 0x0f, 0x9e, 0xc5, 0xe1, 0xbc, 0xef, 0xc7,
    0x39, 0xe7, 0xfd, 0x8e, 0xd0, 0x5a, 0xb3, 0x9b, 0x32, 0x76, 0xe5, 0x06,
    0xac, 0x7f, 0x6d, 0x1c, 0xb8, 0x9a, 0xb8, 0x55, 0x20, 0x70, 0x5f, 0x39,
    0x2e, 0x96, 0x9d, 0xbd, 0xbd, 0xf8, 0xe2, 0xf2, 0xc3, 0x9d, 0x74, 0x62,
    0xa7, 0x2b, 0x34, 0x8f, 0xbc, 0x1c, 0x72, 0xcc, 0xf2, 0xf8, 0x89, 0x33,
    0xb1, 0x20, 0x4a, 0x31, 0xf7, 0xf4, 0xb5, 0x63, 0xa4, 0xd3, 0xc3, 0xc9,
    0xb7, 0xd7, 0x66, 0xb7, 0x89, 0xb5, 0xd6, 0x9b, 0x68, 0x1b, 0x49, 0xf4,
    0x46, 0xaf, 0xbc, 0x5a, 0xbe, 0xf8, 0x38, 0xa3, 0xbf, 0xd9, 0x5a, 0x2f,
    0xe5, 0xb5, 0x3e, 0x3f, 0x9d, 0xd4, 0x95, 0xc7, 0x9e, 0x2c, 0x87, 0x0f,
    0x4f, 0xf7, 0x6e, 0xd5, 0x6f, 0x7a, 0x83, 0xe6, 0xeb, 0x73, 0x2d, 0xb6,
    0x14, 0xf1, 0xc6, 0x58, 0x67, 0x74, 0xec, 0x64, 0x88, 0xaf, 0x19, 0xf8,
    0xb2, 0x0a, 0x37, 0x4e, 0x47, 0x68, 0x3f, 0xd5, 0x17, 0x2d, 0xb8, 0x2a,
    0x5e, 0xdd, 0xf9, 0xa0, 0x65, 0xa3, 0xe7, 0x4f, 0x83, 0x9e, 0xe1, 0x37,
    0x21, 0x2d, 0x99, 0xa9, 0x68, 0x6a, 0x6e, 0x1d, 0xec, 0xab, 0xc3, 0xce,
    0xc3, 0x87, 0x54, 0x89, 0x9c, 0x0d, 0x17, 0xce, 0x36, 0x51, 0xdb, 0x77,
    0xb4, 0x55, 0x16, 0xdd, 0x99, 0x9a, 0x86, 0x7b, 0xa1, 0x6d, 0x0d, 0xf2,
    0x66, 0x7e, 0x4a, 0x86, 0xeb, 0xfb, 0x0f, 0xc5, 0xf6, 0xa3, 0x14, 0xcc,
    0xaf, 0xc0, 0x42, 0x06, 0x16, 0x56, 0x61, 0x3e, 0x09, 0xca, 0x87, 0xe3,
    0xe7, 0x8e, 0x10, 0xe8, 0xea, 0xe9, 0x2f, 0xd8, 0xce, 0xd4, 0xa6, 0x14,
    0xda, 0xc7, 0x13, 0x77, 0xf3, 0x55, 0x91, 0xd1, 0xba, 0x8e, 0x36, 0x84,
    0x16, 0xbc, 0x5f, 0x06, 0x4d, 0x09, 0xa9, 0xc0, 0x32, 0xc0, 0x57, 0xe0,
    0x6a, 0x83, 0xf2, 0x81, 0x01, 0xb2, 0x4b, 0xa9, 0xd1, 0x60, 0x70, 0x62,
    0xd1, 0x71, 0x26, 0xef, 0x88, 0xd6, 0xb1, 0xc4, 0xa0, 0x23, 0x82, 0xb3,
    0x6b, 0x8d, 0xbd, 0x65, 0x75, 0x91, 0x0a, 0x8c, 0x0d, 0xa1, 0x68, 0x40,
    0x68, 0x28, 0x7a, 0xb0, 0x62, 0x83, 0xed, 0x00, 0x01, 0x10, 0xc9, 0x15,
    0x88, 0x3f, 0x2a, 0xea, 0x4c, 0x6a, 0xc8, 0x0c, 0xc5, 0xc6, 0x9f, 0xe5,
    0xa2, 0x1d, 0xf5, 0x72, 0x6f, 0x0d, 0x59, 0x17, 0x7e, 0x14, 0x4b, 0x64,
    0x1d, 0xb0, 0xdd, 0x92, 0x69, 0xbd, 0x00, 0x5a, 0x43, 0xd0, 0x84, 0x3d,
    0x40, 0x20, 0x54, 0x89, 0x59, 0x5d, 0x6b, 0xc9, 0x4f, 0x1f, 0xbb, 0x2c,
    0x51, 0x56, 0xd5, 0x1d, 0xde, 0x17, 0x41, 0x4b, 0x50, 0x0a, 0x7c, 0x40,
    0x69, 0x30, 0x45, 0x09, 0x03, 0x10, 0x62, 0x4b, 0xf6, 0x06, 0x18, 0xfd,
    0x07, 0xf9, 0xfc, 0xae, 0xa1, 0xdb, 0x22, 0xb7, 0x9e, 0x0e, 0xfb, 0xeb,
    0xd1, 0xaa, 0x48, 0x35, 0x28, 0x40, 0x80, 0xf8, 0x7d, 0xfc, 0xbf, 0xe3,
    0xb6, 0xc5, 0x6f, 0x41, 0x6a, 0xe1, 0x3b, 0x32, 0x9d, 0x4e, 0x8b, 0x86,
    0x4b, 0xcf, 0x6f, 0x9a, 0x86, 0x39, 0x29, 0xc0, 0x90, 0x8e, 0x44, 0x7b,
    0x2e, 0xd2, 0xf5, 0x51, 0xae, 0x8f, 0xf2, 0x7c, 0x94, 0xeb, 0x21, 0x5d,
    0xaf, 0xb4, 0x76, 0x7d, 0x94, 0xe7, 0x01, 0xe0, 0xe6, 0x0a, 0xca, 0xf9,
    0x99, 0x9d, 0xd8, 0x71, 0x94, 0xff, 0xa7, 0x76, 0xfd, 0x1b, 0x7f, 0x01,
    0x3c, 0x66, 0x02, 0xb5, 0xb8, 0x0c, 0x75, 0xeb, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
  };

static const unsigned char image5_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x00,
    0x8f, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x52, 0x49, 0x12, 0xc0,
    0x20, 0x08, 0x8b, 0x4e, 0x1f, 0xc6, 0xd3, 0x7c, 0x1a, 0x3f, 0xb3, 0x07,
    0x6d, 0x59, 0x9a, 0xee, 0x78, 0x10, 0x42, 0x58, 0x26, 0x5a, 0x00, 0x85,
    0x99, 0xe0, 0x3a, 0xce, 0x26, 0x28, 0x80, 0xa2, 0x25, 0x52, 0x9b, 0x27,
    0x62, 0x42, 0x79, 0x35, 0x12, 0xb6, 0x22, 0x75, 0x8d, 0x84, 0x34, 0x32,
    0xac, 0x62, 0x0f, 0x3c, 0x91, 0xf9, 0xfe, 0xb6, 0xfc, 0x32, 0xa6, 0x69,
    0x5a, 0xf9, 0x29, 0xe6, 0xd6, 0xfd, 0x7a, 0x9f, 0x88, 0xc8, 0x04, 0xe3,
    0x22, 0x46, 0xc7, 0xf9, 0x47, 0x4c, 0x29, 0xaf, 0xc6, 0x95, 0xd8, 0x9a,
    0x71, 0x6a, 0xc6, 0x16, 0xeb, 0xe8, 0x89, 0x32, 0x67, 0xe4, 0xe2, 0xcc,
    0xd3, 0xa1, 0x41, 0x2c, 0x7c, 0x17, 0x17, 0x00, 0x87, 0xa7, 0xe1, 0x3f,
    0x91, 0x63, 0x70, 0xe2, 0x74, 0x00, 0x3d, 0x09, 0x76, 0x83, 0xc1, 0xbe,
    0xf2, 0x57, 0x73, 0x22, 0xb6, 0x92, 0x93, 0x4f, 0xb1, 0x5f, 0xb6, 0x02,
    0x6f, 0x3b, 0x53, 0x57, 0x71, 0xe6, 0x68, 0xdf, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
  };

static const unsigned char image6_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x5c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x93, 0x4d, 0x4f, 0x13,
    0x71, 0x10, 0x87, 0x9f, 0xff, 0xee, 0xd6, 0xd6, 0xb6, 0xdb, 0x52, 0x5a,
    0x40, 0x81, 0x16, 0x85, 0x5a, 0x5e, 0x04, 0xa2, 0xa9, 0x26, 0x26, 0x98,
    0x88, 0x89, 0x07, 0xaf, 0xc6, 0x0f, 0xe8, 0x47, 0xc0, 0x98, 0x78, 0x30,
    0x6a, 0x0c, 0x97, 0x62, 0xc4, 0x82, 0xc8, 0x6b, 0x63, 0x43, 0xaa, 0xa0,
    0xad, 0x5d, 0xe8, 0xf2, 0x62, 0x29, 0xdd, 0x6d, 0x3b, 0x1e, 0x10, 0x22,
    0x41, 0xf4, 0xe0, 0x9c, 0x26, 0x33, 0xf3, 0xfc, 0x0e, 0xbf, 0x99, 0x51,
    0x99, 0x4c, 0x86, 0xff, 0x09, 0xe3, 0x6f, 0x4d, 0x9f, 0xaf, 0x2c, 0xae,
    0xab, 0x61, 0xdb, 0x65, 0xb6, 0xb6, 0x2a, 0x78, 0xbd, 0x06, 0x3d, 0x3d,
    0x77, 0xd4, 0x3f, 0x05, 0x4c, 0xd3, 0x96, 0x4a, 0xe5, 0x80, 0x6c, 0xb6,
    0x40, 0xa1, 0x50, 0xc7, 0xeb, 0x15, 0x62, 0x31, 0x61, 0x60, 0x20, 0x4a,
    0x38, 0x5c, 0x91, 0xdd, 0xdd, 0x76, 0x75, 0xae, 0x80, 0xcf, 0x57, 0x97,
    0xf9, 0xf9, 0x0d, 0xe6, 0xe6, 0x2c, 0x82, 0x41, 0xc5, 0xc4, 0x44, 0x37,
    0x89, 0x44, 0x02, 0x91, 0x1f, 0x18, 0x86, 0xf0, 0x3b, 0x7c, 0x46, 0xc0,
    0xb6, 0xbf, 0xca, 0xcc, 0xcc, 0x67, 0x2c, 0xeb, 0x80, 0x64, 0xd2, 0xc3,
    0xe8, 0x68, 0x2f, 0xe1, 0xf0, 0x80, 0x72, 0x1c, 0x00, 0x3f, 0xae, 0xfb,
    0x17, 0x0f, 0xf2, 0xf9, 0x9c, 0x64, 0xe7, 0x4a, 0x04, 0xfc, 0x1a, 0x93,
    0x93, 0x7d, 0xf4, 0xf5, 0x5d, 0x53, 0x67, 0xc7, 0xcf, 0x11, 0xc8, 0xe7,
    0xd7, 0x64, 0x61, 0xe1, 0x3b, 0x83, 0xa9, 0x20, 0xe9, 0xf4, 0x75, 0x9a,
    0x4d, 0xdf, 0x29, 0x38, 0xac, 0xd6, 0x44, 0x73, 0x04, 0x6b, 0x7d, 0x95,
    0xda, 0x4e, 0x85, 0x50, 0x7b, 0x94, 0xee, 0xe1, 0x34, 0x5f, 0x1b, 0x09,
    0x65, 0x94, 0x4a, 0x39, 0xc9, 0x66, 0xbf, 0x91, 0x4c, 0x06, 0x19, 0x1b,
    0xeb, 0x3a, 0x05, 0x07, 0xdc, 0x05, 0xd9, 0x2f, 0x16, 0x59, 0x5a, 0x5a,
    0xa2, 0xb4, 0xd1, 0xc4, 0xda, 0x0f, 0x50, 0x6f, 0x18, 0xb4, 0x7b, 0x3e,
    0x71, 0x75, 0x3e, 0xc7, 0xed, 0xc7, 0x0f, 0xc4, 0x98, 0x9d, 0x9d, 0xc7,
    0x34, 0x03, 0xa4, 0x52, 0x09, 0x74, 0xbd, 0xf7, 0x04, 0xbe, 0xb0, 0xf1,
    0x42, 0x16, 0x3f, 0xac, 0x91, 0x2b, 0x18, 0x78, 0xc2, 0x31, 0xe2, 0x63,
    0x6d, 0xdc, 0x1c, 0xe9, 0xc7, 0x17, 0x08, 0x52, 0xdb, 0xb6, 0xc9, 0x3e,
    0x7f, 0x49, 0x7e, 0xe6, 0x15, 0x86, 0x65, 0xd9, 0x8c, 0x8f, 0xb7, 0x61,
    0x9a, 0xc9, 0x13, 0x58, 0xcf, 0x3f, 0x93, 0x77, 0xaf, 0x57, 0xd8, 0xb9,
    0x18, 0x65, 0xf0, 0x5e, 0x92, 0xc1, 0xf1, 0x1b, 0xb8, 0x44, 0x14, 0x40,
    0x03, 0xd0, 0xcd, 0x4d, 0xb1, 0x1b, 0x21, 0x76, 0xec, 0x6f, 0x67, 0xd7,
    0x98, 0x08, 0x94, 0xe5, 0xcd, 0xdb, 0x45, 0x0e, 0x82, 0x31, 0x26, 0x1f,
    0x3d, 0x04, 0x7f, 0x5c, 0xfd, 0x6e, 0xbe, 0x6e, 0xbd, 0x97, 0xcc, 0xf4,
    0x3a, 0x5e, 0xd1, 0xb8, 0x9c, 0x7e, 0x88, 0xd1, 0xd1, 0x11, 0xa1, 0x54,
    0x72, 0xb0, 0xac, 0x15, 0xe9, 0xe8, 0x18, 0x51, 0xf5, 0xba, 0xcd, 0x8f,
    0xea, 0x01, 0xa1, 0x78, 0x83, 0x20, 0x45, 0xcc, 0xe6, 0xb6, 0xb4, 0x9a,
    0x0d, 0xaa, 0xd5, 0x2a, 0x85, 0x8f, 0xab, 0x7c, 0x59, 0x2c, 0x72, 0xa8,
    0x5d, 0x62, 0xfc, 0xfe, 0x18, 0x46, 0xf7, 0x5d, 0xa5, 0xa6, 0xa6, 0x9e,
    0xc8, 0xf4, 0xf4, 0x17, 0xa2, 0x51, 0x97, 0x91, 0xe1, 0x5e, 0xa2, 0xa1,
    0x06, 0x9b, 0xb3, 0x4f, 0x29, 0xe7, 0xca, 0x38, 0xc5, 0x0b, 0x38, 0x7b,
    0xa0, 0xeb, 0x1a, 0x8e, 0x3f, 0x42, 0x35, 0x10, 0xa3, 0x2b, 0xd5, 0xc6,
    0xc8, 0xad, 0x21, 0x22, 0xf1, 0xb4, 0x02, 0x50, 0x99, 0x4c, 0x86, 0x5a,
    0xad, 0x20, 0xcb, 0xcb, 0x6b, 0x2c, 0x2f, 0x7b, 0xa8, 0x1f, 0x2a, 0xdc,
    0x9a, 0x8d, 0xb3, 0x5f, 0xa7, 0xbe, 0x27, 0xe8, 0x2d, 0xa1, 0x27, 0x2e,
    0xa4, 0x46, 0x4d, 0xae, 0x0c, 0xc5, 0x69, 0xef, 0x8a, 0xa0, 0x79, 0xfa,
    0x4f, 0xfc, 0x52, 0xc7, 0xdf, 0xe8, 0xf1, 0x6c, 0x8a, 0xeb, 0x7a, 0x68,
    0xb5, 0xe4, 0xa8, 0xd3, 0x82, 0x96, 0x80, 0xae, 0x0c, 0xfc, 0xc1, 0x10,
    0xd2, 0xda, 0xe1, 0xd0, 0xe9, 0x3c, 0x73, 0x5c, 0x27, 0x26, 0xba, 0xee,
    0xd1, 0x0a, 0x35, 0xed, 0x57, 0x41, 0x83, 0xe3, 0xb4, 0x76, 0x08, 0xd0,
    0xf9, 0xc7, 0x4b, 0xfc, 0x09, 0x52, 0xcb, 0x07, 0x62, 0x36, 0x43, 0x92,
    0xc6, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
    0x82
  };

/*
 *  Constructs a CQFittingItemWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQFittingItemWidget::CQFittingItemWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  QImage img;
  img.loadFromData(image0_data, sizeof(image0_data), "PNG");
  image0 = img;
  img.loadFromData(image1_data, sizeof(image1_data), "PNG");
  image1 = img;
  img.loadFromData(image2_data, sizeof(image2_data), "PNG");
  image2 = img;
  img.loadFromData(image3_data, sizeof(image3_data), "PNG");
  image3 = img;
  img.loadFromData(image4_data, sizeof(image4_data), "PNG");
  image4 = img;
  img.loadFromData(image5_data, sizeof(image5_data), "PNG");
  image5 = img;
  img.loadFromData(image6_data, sizeof(image6_data), "PNG");
  image6 = img;
  if (!name)
    setName("CQFittingItemWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, sizePolicy().hasHeightForWidth()));
  CQFittingItemWidgetLayout = new QVBoxLayout(this, 1, 6, "CQFittingItemWidgetLayout");

  mpTable = new QTable(this, "mpTable");
  mpTable->setNumRows(0);
  mpTable->setNumCols(1);
  mpTable->setShowGrid(FALSE);
  mpTable->setReadOnly(TRUE);
  mpTable->setSelectionMode(QTable::SingleRow);
  mpTable->setFocusStyle(QTable::FollowStyle);
  CQFittingItemWidgetLayout->addWidget(mpTable);

  mpLayout = new QGridLayout(0, 1, 1, 0, 1, "mpLayout");

  mpBtnPerExperiment = new QPushButton(this, "mpBtnPerExperiment");

  mpLayout->addMultiCellWidget(mpBtnPerExperiment, 5, 5, 0, 3);
  mpSpacer1 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  mpLayout->addMultiCell(mpSpacer1, 0, 1, 4, 4);

  mpCheckLowerInf = new QCheckBox(this, "mpCheckLowerInf");
  mpCheckLowerInf->setChecked(TRUE);

  mpLayout->addWidget(mpCheckLowerInf, 2, 2);

  mpLblExperiments = new QLabel(this, "mpLblExperiments");

  mpLayout->addMultiCellWidget(mpLblExperiments, 4, 4, 0, 2);

  mpBtnNew = new QToolButton(this, "mpBtnNew");
  mpBtnNew->setMaximumSize(QSize(20, 20));
  mpBtnNew->setIconSet(QIconSet(image0));

  mpLayout->addMultiCellWidget(mpBtnNew, 0, 1, 5, 5);

  mpBtnDown = new QToolButton(this, "mpBtnDown");
  mpBtnDown->setMaximumSize(QSize(20, 20));
  mpBtnDown->setIconSet(QIconSet(image1));

  mpLayout->addWidget(mpBtnDown, 2, 6);
  mpSpacerLeft = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  mpLayout->addItem(mpSpacerLeft, 2, 1);

  mpBtnDel = new QToolButton(this, "mpBtnDel");
  mpBtnDel->setMaximumSize(QSize(20, 20));
  mpBtnDel->setIconSet(QIconSet(image2));

  mpLayout->addWidget(mpBtnDel, 2, 5);

  mpBtnCopy = new QToolButton(this, "mpBtnCopy");
  mpBtnCopy->setMaximumSize(QSize(20, 20));
  mpBtnCopy->setIconSet(QIconSet(image3));

  mpLayout->addWidget(mpBtnCopy, 3, 5);

  mpBtnUp = new QToolButton(this, "mpBtnUp");
  mpBtnUp->setMaximumSize(QSize(20, 20));
  mpBtnUp->setIconSet(QIconSet(image4));

  mpLayout->addMultiCellWidget(mpBtnUp, 0, 1, 6, 6);

  mpLayoutExperiments = new QHBoxLayout(0, 0, 6, "mpLayoutExperiments");

  mpCheckAll = new QCheckBox(this, "mpCheckAll");
  mpCheckAll->setChecked(TRUE);
  mpLayoutExperiments->addWidget(mpCheckAll);

  mpBoxExperiments = new QComboBox(FALSE, this, "mpBoxExperiments");
  mpBoxExperiments->setEnabled(TRUE);
  mpBoxExperiments->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, mpBoxExperiments->sizePolicy().hasHeightForWidth()));
  mpBoxExperiments->setDuplicatesEnabled(FALSE);
  mpLayoutExperiments->addWidget(mpBoxExperiments);

  mpBtnExperiments = new QToolButton(this, "mpBtnExperiments");
  mpBtnExperiments->setMaximumSize(QSize(20, 20));
  mpBtnExperiments->setIconSet(QIconSet(image5));
  mpLayoutExperiments->addWidget(mpBtnExperiments);

  mpLayout->addLayout(mpLayoutExperiments, 4, 3);

  mpLblObject = new QLabel(this, "mpLblObject");

  mpLayout->addWidget(mpLblObject, 0, 0);

  mpLblUpper = new QLabel(this, "mpLblUpper");

  mpLayout->addWidget(mpLblUpper, 3, 0);

  mpCheckUpperInf = new QCheckBox(this, "mpCheckUpperInf");
  mpCheckUpperInf->setChecked(TRUE);

  mpLayout->addWidget(mpCheckUpperInf, 3, 2);

  mpLblLower = new QLabel(this, "mpLblLower");

  mpLayout->addMultiCellWidget(mpLblLower, 1, 2, 0, 0);

  mpLayoutLower = new QHBoxLayout(0, 0, 6, "mpLayoutLower");

  mpEditLower = new QLineEdit(this, "mpEditLower");
  mpEditLower->setEnabled(FALSE);
  mpEditLower->setFrameShape(QLineEdit::LineEditPanel);
  mpEditLower->setFrameShadow(QLineEdit::Sunken);
  mpLayoutLower->addWidget(mpEditLower);

  mpBtnLowerEdit = new QToolButton(this, "mpBtnLowerEdit");
  mpBtnLowerEdit->setMaximumSize(QSize(20, 20));
  mpBtnLowerEdit->setIconSet(QIconSet(image6));
  mpLayoutLower->addWidget(mpBtnLowerEdit);

  mpLayout->addLayout(mpLayoutLower, 2, 3);

  mpLayoutUpper = new QHBoxLayout(0, 0, 6, "mpLayoutUpper");

  mpEditUpper = new QLineEdit(this, "mpEditUpper");
  mpEditUpper->setEnabled(FALSE);
  mpEditUpper->setFrameShape(QLineEdit::LineEditPanel);
  mpEditUpper->setFrameShadow(QLineEdit::Sunken);
  mpLayoutUpper->addWidget(mpEditUpper);

  mpBtnUpperEdit = new QToolButton(this, "mpBtnUpperEdit");
  mpBtnUpperEdit->setMaximumSize(QSize(20, 20));
  mpBtnUpperEdit->setIconSet(QIconSet(image6));
  mpLayoutUpper->addWidget(mpBtnUpperEdit);

  mpLayout->addLayout(mpLayoutUpper, 3, 3);

  mpLayoutObject = new QHBoxLayout(0, 0, 6, "mpLayoutObject");

  mpEditObject = new QLineEdit(this, "mpEditObject");
  mpEditObject->setEnabled(TRUE);
  mpEditObject->setReadOnly(TRUE);
  mpLayoutObject->addWidget(mpEditObject);

  mpBtnObject = new QToolButton(this, "mpBtnObject");
  mpBtnObject->setMaximumSize(QSize(20, 20));
  mpBtnObject->setIconSet(QIconSet(image6));
  mpLayoutObject->addWidget(mpBtnObject);

  mpLayout->addMultiCellLayout(mpLayoutObject, 0, 1, 3, 3);
  mpSpacer2 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  mpLayout->addItem(mpSpacer2, 2, 4);
  mpSpacer3 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  mpLayout->addItem(mpSpacer3, 3, 4);
  CQFittingItemWidgetLayout->addLayout(mpLayout);
  languageChange();
  resize(QSize(349, 241).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpCheckLowerInf, SIGNAL(toggled(bool)), this, SLOT(slotCheckLowerInf(bool)));
  connect(mpCheckUpperInf, SIGNAL(toggled(bool)), this, SLOT(slotCheckUpperInf(bool)));
  connect(mpBtnLowerEdit, SIGNAL(clicked()), this, SLOT(slotLowerEdit()));
  connect(mpBtnUpperEdit, SIGNAL(clicked()), this, SLOT(slotUpperEdit()));
  connect(mpBtnObject, SIGNAL(clicked()), this, SLOT(slotParamEdit()));
  connect(mpBtnExperiments, SIGNAL(clicked()), this, SLOT(slotExperiments()));
  connect(mpBtnDel, SIGNAL(clicked()), this, SLOT(slotDelete()));
  connect(mpCheckAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckAll(bool)));
  connect(mpBtnDown, SIGNAL(clicked()), this, SLOT(slotDown()));
  connect(mpBtnPerExperiment, SIGNAL(clicked()), this, SLOT(slotDuplicatePerExperiment()));
  connect(mpBtnUp, SIGNAL(clicked()), this, SLOT(slotUp()));
  connect(mpBtnCopy, SIGNAL(clicked()), this, SLOT(slotCopy()));
  connect(mpBtnNew, SIGNAL(clicked()), this, SLOT(slotNew()));
  connect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingItemWidget::~CQFittingItemWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingItemWidget::languageChange()
{
  setCaption(tr("CQFittingItemWidget"));
  mpBtnPerExperiment->setText(tr("Duplicate for each Experiment"));
  mpCheckLowerInf->setText(tr("- Infinity"));
  mpLblExperiments->setText(tr("Affected Experiments"));
  mpBtnNew->setText(QString::null);
  mpBtnNew->setTextLabel(tr("new"));
  mpBtnDown->setText(QString::null);
  mpBtnDown->setTextLabel(tr("move down"));
  mpBtnDel->setText(QString::null);
  mpBtnDel->setTextLabel(tr("delete"));
  mpBtnCopy->setText(QString::null);
  mpBtnCopy->setTextLabel(tr("copy"));
  mpBtnUp->setText(QString::null);
  mpBtnUp->setTextLabel(tr("move up"));
  mpCheckAll->setText(tr("all"));
  mpBtnExperiments->setText(QString::null);
  mpLblObject->setText(tr("Object"));
  mpLblUpper->setText(tr("Upper Bound"));
  mpCheckUpperInf->setText(tr("+ Infinity"));
  mpLblLower->setText(tr("Lower Bound"));
  mpBtnLowerEdit->setText(QString::null);
  mpBtnLowerEdit->setTextLabel(tr("select"));
  mpBtnUpperEdit->setText(QString::null);
  mpBtnUpperEdit->setTextLabel(tr("select"));
  mpBtnObject->setText(QString::null);
  mpBtnObject->setTextLabel(tr("select"));
}
