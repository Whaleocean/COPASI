// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidget.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEXPRESSIONMMLWIDGET_H
#define CQEXPRESSIONMMLWIDGET_H

#include <qvariant.h>

#include <Qt3Support/Q3WidgetStack>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>
#include <Qt3Support/Q3WidgetStack>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <QPixmap>
#include <Q3VBoxLayout>
#include "CQExpressionWidget.h"
#include "CQMmlScrollView.h"

QT_BEGIN_NAMESPACE

class Ui_CQExpressionMmlWidget
  {
  public:
    Q3GridLayout *gridLayout;
    Q3WidgetStack *mpWidgetStackExpressionMml;
    QWidget *mpExpressionPage;
    Q3GridLayout *gridLayout1;
    CQExpressionWidget *mpExpressionWidget;
    Q3VBoxLayout *vboxLayout;
    QToolButton *mpBtnExpressionObject;
    QToolButton *mpBtnViewExpression;
    QSpacerItem *mpSpacerExpressionObject;
    QWidget *mpMmlPage;
    Q3HBoxLayout *hboxLayout;
    CQMmlScrollView *mpMmlScrollView;
    Q3VBoxLayout *vboxLayout1;
    QToolButton *mpBtnEditExpression;
    QToolButton *mpBtnSaveExpression;
    QSpacerItem *mpSpacerMmlObject;

    void setupUi(QWidget *CQExpressionMmlWidget)
    {
      if (CQExpressionMmlWidget->objectName().isEmpty())
        CQExpressionMmlWidget->setObjectName(QString::fromUtf8("CQExpressionMmlWidget"));
      CQExpressionMmlWidget->resize(290, 125);
      gridLayout = new Q3GridLayout(CQExpressionMmlWidget);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(0);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      mpWidgetStackExpressionMml = new Q3WidgetStack(CQExpressionMmlWidget);
      mpWidgetStackExpressionMml->setObjectName(QString::fromUtf8("mpWidgetStackExpressionMml"));
      mpWidgetStackExpressionMml->setMinimumSize(QSize(0, 0));
      mpExpressionPage = new QWidget(mpWidgetStackExpressionMml);
      mpExpressionPage->setObjectName(QString::fromUtf8("mpExpressionPage"));
      gridLayout1 = new Q3GridLayout(mpExpressionPage);
      gridLayout1->setSpacing(6);
      gridLayout1->setMargin(0);
      gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
      gridLayout1->setContentsMargins(0, 0, 0, 0);
      mpExpressionWidget = new CQExpressionWidget(mpExpressionPage);
      mpExpressionWidget->setObjectName(QString::fromUtf8("mpExpressionWidget"));

      gridLayout1->addWidget(mpExpressionWidget, 0, 0, 1, 1);

      vboxLayout = new Q3VBoxLayout();
      vboxLayout->setSpacing(6);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      mpBtnExpressionObject = new QToolButton(mpExpressionPage);
      mpBtnExpressionObject->setObjectName(QString::fromUtf8("mpBtnExpressionObject"));
      mpBtnExpressionObject->setMaximumSize(QSize(20, 20));
      const QIcon icon = qt_get_icon(image0_ID);
      mpBtnExpressionObject->setIcon(icon);

      vboxLayout->addWidget(mpBtnExpressionObject);

      mpBtnViewExpression = new QToolButton(mpExpressionPage);
      mpBtnViewExpression->setObjectName(QString::fromUtf8("mpBtnViewExpression"));
      mpBtnViewExpression->setMaximumSize(QSize(20, 20));
      const QIcon icon1 = qt_get_icon(image1_ID);
      mpBtnViewExpression->setIcon(icon1);

      vboxLayout->addWidget(mpBtnViewExpression);

      mpSpacerExpressionObject = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout->addItem(mpSpacerExpressionObject);

      gridLayout1->addLayout(vboxLayout, 0, 1, 1, 1);

      mpWidgetStackExpressionMml->addWidget(mpExpressionPage, 0);
      mpMmlPage = new QWidget(mpWidgetStackExpressionMml);
      mpMmlPage->setObjectName(QString::fromUtf8("mpMmlPage"));
      hboxLayout = new Q3HBoxLayout(mpMmlPage);
      hboxLayout->setSpacing(6);
      hboxLayout->setMargin(0);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      hboxLayout->setContentsMargins(0, 0, 0, 0);
      mpMmlScrollView = new CQMmlScrollView(mpMmlPage);
      mpMmlScrollView->setObjectName(QString::fromUtf8("mpMmlScrollView"));

      hboxLayout->addWidget(mpMmlScrollView);

      vboxLayout1 = new Q3VBoxLayout();
      vboxLayout1->setSpacing(6);
      vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
      mpBtnEditExpression = new QToolButton(mpMmlPage);
      mpBtnEditExpression->setObjectName(QString::fromUtf8("mpBtnEditExpression"));
      mpBtnEditExpression->setMaximumSize(QSize(20, 20));
      const QIcon icon2 = qt_get_icon(image2_ID);
      mpBtnEditExpression->setIcon(icon2);

      vboxLayout1->addWidget(mpBtnEditExpression);

      mpBtnSaveExpression = new QToolButton(mpMmlPage);
      mpBtnSaveExpression->setObjectName(QString::fromUtf8("mpBtnSaveExpression"));
      mpBtnSaveExpression->setMaximumSize(QSize(20, 20));
      const QIcon icon3 = qt_get_icon(image3_ID);
      mpBtnSaveExpression->setIcon(icon3);

      vboxLayout1->addWidget(mpBtnSaveExpression);

      mpSpacerMmlObject = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout1->addItem(mpSpacerMmlObject);

      hboxLayout->addLayout(vboxLayout1);

      mpWidgetStackExpressionMml->addWidget(mpMmlPage, 1);

      gridLayout->addWidget(mpWidgetStackExpressionMml, 0, 0, 1, 1);

      retranslateUi(CQExpressionMmlWidget);
      QObject::connect(mpBtnEditExpression, SIGNAL(clicked()), CQExpressionMmlWidget, SLOT(slotGoExpressionWidget()));
      QObject::connect(mpBtnExpressionObject, SIGNAL(clicked()), mpExpressionWidget, SLOT(slotSelectObject()));
      QObject::connect(mpBtnViewExpression, SIGNAL(clicked()), CQExpressionMmlWidget, SLOT(updateWidget()));
      QObject::connect(mpExpressionWidget, SIGNAL(valid(bool)), mpBtnViewExpression, SLOT(setEnabled(bool)));
      QObject::connect(mpBtnSaveExpression, SIGNAL(clicked()), CQExpressionMmlWidget, SLOT(slotSaveExpression()));

      QMetaObject::connectSlotsByName(CQExpressionMmlWidget);
    } // setupUi

    void retranslateUi(QWidget *CQExpressionMmlWidget)
    {
      CQExpressionMmlWidget->setWindowTitle(QApplication::translate("CQExpressionMmlWidget", "Expression-Mml Widget", 0, QApplication::UnicodeUTF8));
      mpBtnExpressionObject->setText(QString());

#ifndef QT_NO_TOOLTIP
      mpBtnExpressionObject->setProperty("toolTip", QVariant(QApplication::translate("CQExpressionMmlWidget", "select object", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

      mpBtnViewExpression->setText(QString());

#ifndef QT_NO_TOOLTIP
      mpBtnViewExpression->setProperty("toolTip", QVariant(QApplication::translate("CQExpressionMmlWidget", "view expression", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

      mpBtnEditExpression->setText(QString());

#ifndef QT_NO_TOOLTIP
      mpBtnEditExpression->setProperty("toolTip", QVariant(QApplication::translate("CQExpressionMmlWidget", "edit expression", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

      mpBtnSaveExpression->setText(QString());

#ifndef QT_NO_TOOLTIP
      mpBtnSaveExpression->setProperty("toolTip", QVariant(QApplication::translate("CQExpressionMmlWidget", "save expression", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

      Q_UNUSED(CQExpressionMmlWidget);
    } // retranslateUi

  protected:
    enum IconID
    {
      image0_ID,
      image1_ID,
      image2_ID,
      image3_ID,
      image4_ID,
      image5_ID,
      unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
      static const unsigned char image0_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
          0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
          0x51, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x8d, 0x93, 0xdb, 0x53, 0x52,
          0x51, 0x14, 0x87, 0x7f, 0x1b, 0x37, 0x17, 0xe3, 0x2e, 0x8e, 0x98, 0x97,
          0x22, 0x01, 0x51, 0xb0, 0xcb, 0x28, 0x8c, 0x3a, 0xa6, 0x65, 0x4d, 0x33,
          0xdd, 0xa6, 0x9e, 0x7d, 0xe9, 0xef, 0xeb, 0xc5, 0xe9, 0xb1, 0x97, 0xa6,
          0x51, 0x31, 0x72, 0x72, 0x86, 0xd1, 0x20, 0x06, 0x27, 0x27, 0xec, 0x88,
          0xe0, 0x81, 0x40, 0xe0, 0x40, 0x9c, 0xa3, 0x70, 0x56, 0x0f, 0x8d, 0x34,
          0x27, 0xa3, 0xda, 0x8f, 0x7b, 0xad, 0xef, 0x9b, 0xbd, 0xd6, 0xda, 0x8b,
          0xc5, 0x62, 0x31, 0xfc, 0xcf, 0x29, 0x88, 0x97, 0x49, 0x91, 0x55, 0xd8,
          0x6c, 0x7a, 0xd8, 0x9d, 0x59, 0x76, 0x7e, 0xcf, 0xff, 0x06, 0x7d, 0xd9,
          0x1f, 0x20, 0xe1, 0xa0, 0x81, 0x7c, 0xae, 0x89, 0x62, 0x51, 0x00, 0xd3,
          0x31, 0x78, 0xbd, 0x66, 0x3c, 0x7e, 0xf6, 0x2b, 0xa7, 0xab, 0x60, 0xfd,
          0xad, 0x99, 0xd2, 0xa9, 0x1c, 0x0c, 0x06, 0x8e, 0xc9, 0x29, 0x07, 0x96,
          0xee, 0x98, 0x30, 0x7c, 0xf5, 0x98, 0x01, 0x8a, 0x26, 0xef, 0x8f, 0x82,
          0xd5, 0x97, 0x7a, 0x3a, 0x3a, 0xaa, 0xc2, 0xeb, 0xb3, 0xe0, 0xc9, 0x73,
          0x99, 0x01, 0x95, 0xae, 0xaf, 0xd4, 0x08, 0x92, 0xbb, 0x0e, 0xfa, 0xf0,
          0xfe, 0x04, 0x92, 0xd4, 0xc4, 0x74, 0xd8, 0x89, 0xc5, 0x65, 0x89, 0x75,
          0x03, 0x2f, 0x08, 0x76, 0xe3, 0x26, 0xda, 0x8c, 0x0a, 0x30, 0x1a, 0x2d,
          0x58, 0x5c, 0xee, 0xc7, 0x74, 0xb8, 0xf2, 0x4f, 0x58, 0x23, 0xd8, 0x8a,
          0x89, 0xb0, 0x5a, 0x55, 0xcc, 0x2f, 0x38, 0xe0, 0x0f, 0x5c, 0x84, 0xbd,
          0x8d, 0x0c, 0x29, 0xcd, 0x1a, 0x94, 0x96, 0x04, 0xa6, 0xd7, 0xa3, 0xe0,
          0x9a, 0x65, 0x1d, 0xc1, 0xab, 0xd5, 0x0a, 0xa9, 0x44, 0x88, 0xcc, 0x8e,
          0xc2, 0x1f, 0xa8, 0x69, 0xe0, 0xa1, 0xbd, 0x75, 0x2a, 0xa5, 0x13, 0x48,
          0x89, 0x39, 0x54, 0x65, 0x05, 0x27, 0x44, 0x60, 0x1c, 0x18, 0xf6, 0x44,
          0x69, 0xe2, 0xe1, 0x0a, 0x78, 0xee, 0x90, 0xd3, 0xe1, 0xd7, 0x1c, 0x66,
          0xc2, 0x7e, 0x4c, 0x86, 0xea, 0x1d, 0x78, 0xbc, 0x16, 0x27, 0x31, 0x16,
          0xc5, 0x5e, 0x3a, 0x8b, 0xfc, 0x99, 0x05, 0xad, 0xc1, 0x29, 0xb8, 0x6f,
          0x78, 0xe0, 0xeb, 0xb7, 0xe2, 0xb4, 0x94, 0xc1, 0x51, 0x72, 0x1b, 0x7d,
          0x87, 0x19, 0xf0, 0x5a, 0x59, 0xc4, 0x40, 0xdf, 0x19, 0x16, 0x96, 0xf4,
          0x1d, 0x78, 0xac, 0xbc, 0x45, 0xc2, 0xc6, 0x6b, 0x64, 0x04, 0xa0, 0x7d,
          0x65, 0x1e, 0x9e, 0xd0, 0x2d, 0x18, 0x02, 0x63, 0x9d, 0x78, 0x9b, 0x19,
          0xe9, 0x58, 0x4e, 0xc0, 0x5e, 0xd6, 0x81, 0xab, 0x6d, 0x05, 0x0e, 0xab,
          0xaa, 0xa9, 0xb7, 0x94, 0x58, 0xc7, 0x27, 0xc1, 0x08, 0x43, 0xe8, 0x01,
          0x46, 0xef, 0x47, 0x2e, 0xf4, 0x23, 0xba, 0x16, 0x47, 0x51, 0x54, 0xe0,
          0x33, 0xb9, 0xc0, 0x0d, 0x66, 0x2b, 0xc4, 0x92, 0xd0, 0x09, 0x06, 0x75,
          0x7b, 0x94, 0x3a, 0x29, 0x20, 0xab, 0x8b, 0x20, 0x12, 0xf0, 0x6b, 0xc0,
          0x6a, 0x2a, 0x4e, 0x3b, 0xef, 0xb6, 0x90, 0xfd, 0x9c, 0x87, 0x77, 0x2a,
          0x88, 0xc1, 0x60, 0x80, 0x71, 0xa7, 0xc3, 0x0e, 0x55, 0xd5, 0x61, 0x73,
          0xad, 0x44, 0xb7, 0xef, 0xba, 0x58, 0x93, 0xf7, 0xc3, 0x64, 0x33, 0xa3,
          0xb7, 0x95, 0x06, 0x09, 0x26, 0xd8, 0x64, 0x23, 0x49, 0x55, 0x09, 0x89,
          0x74, 0x01, 0xfb, 0xe9, 0x03, 0xc8, 0x0a, 0xc7, 0xa8, 0xef, 0x26, 0xee,
          0xbd, 0x58, 0xf9, 0x39, 0x05, 0x97, 0x5b, 0x65, 0x81, 0xe0, 0x35, 0x4a,
          0x7e, 0x14, 0x20, 0x35, 0x38, 0xcd, 0x5c, 0x77, 0xc2, 0xee, 0x7e, 0x04,
          0xa7, 0x6d, 0x03, 0x3b, 0x6f, 0x36, 0xb1, 0xad, 0xb4, 0xd1, 0x62, 0x3d,
          0xa8, 0xcb, 0x3d, 0x20, 0xdb, 0x08, 0x7c, 0xb3, 0x73, 0x08, 0x3f, 0x9d,
          0xeb, 0x94, 0xc5, 0xce, 0xb7, 0x31, 0xbe, 0xfd, 0x9d, 0x12, 0xc9, 0x6f,
          0x28, 0x8a, 0x15, 0xb0, 0xb3, 0x32, 0x5a, 0x8d, 0x3a, 0xea, 0xd5, 0x53,
          0xf0, 0x1e, 0x60, 0x68, 0xc4, 0x82, 0xf1, 0x80, 0x1b, 0x13, 0xa1, 0x11,
          0xb8, 0xc7, 0x5d, 0x9a, 0x9e, 0xb0, 0xdf, 0xd7, 0x39, 0x9f, 0x33, 0x52,
          0xa3, 0xde, 0x00, 0xb5, 0x75, 0xe0, 0x9c, 0xa3, 0xf7, 0x92, 0x01, 0x83,
          0xc3, 0x72, 0xd7, 0x5f, 0xf9, 0x03, 0x51, 0x05, 0xf9, 0xb7, 0x17, 0xf5,
          0x66, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
          0x60, 0x82
        };

      static const unsigned char image1_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
          0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x01,
          0xa2, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x9d, 0x93, 0x3b, 0x4b, 0x2b,
          0x41, 0x18, 0x86, 0x9f, 0x59, 0x76, 0x73, 0x8f, 0xd7, 0x28, 0x18, 0x05,
          0x51, 0x04, 0xe1, 0x80, 0x85, 0x1a, 0x2c, 0x16, 0x0b, 0x7f, 0x80, 0x17,
          0x30, 0x9d, 0x20, 0x08, 0x01, 0xb5, 0xb0, 0xb0, 0xf1, 0x57, 0x08, 0x36,
          0xda, 0x9c, 0x9c, 0x26, 0xa4, 0xb4, 0xb3, 0xb6, 0x10, 0x9b, 0xa9, 0x5c,
          0x41, 0x44, 0x10, 0x21, 0x95, 0x57, 0x10, 0xa3, 0x32, 0x12, 0x93, 0x78,
          0x59, 0x8b, 0x4d, 0x96, 0x4d, 0x34, 0xca, 0xf1, 0xab, 0x66, 0xbe, 0x99,
          0xe7, 0xfd, 0xde, 0x99, 0xf9, 0x46, 0x48, 0x29, 0xf9, 0x2e, 0xcc, 0x8c,
          0xcf, 0xf6, 0xce, 0xe5, 0x42, 0x59, 0x78, 0xe7, 0xfa, 0x4f, 0xe0, 0xf2,
          0xfc, 0x08, 0x00, 0xf7, 0xa5, 0x6a, 0xfe, 0xd0, 0xf6, 0x0a, 0x89, 0xaf,
          0x1c, 0x98, 0x19, 0x9f, 0xbd, 0xb5, 0x3a, 0xcc, 0x40, 0x54, 0xc3, 0xd0,
          0x20, 0x7b, 0x06, 0x47, 0x79, 0x50, 0x65, 0x78, 0xb5, 0x41, 0x17, 0x90,
          0xdb, 0xb3, 0x90, 0x0b, 0x65, 0xd1, 0xd0, 0x41, 0x8b, 0xa1, 0xd1, 0xea,
          0x83, 0xb1, 0x4e, 0xb8, 0x29, 0xc0, 0x76, 0xce, 0x81, 0xfd, 0x75, 0xc4,
          0x27, 0x81, 0x6a, 0xf5, 0x7c, 0x19, 0xce, 0x0b, 0xf0, 0x70, 0x09, 0x39,
          0x05, 0x83, 0xed, 0xd0, 0x11, 0x82, 0x80, 0x0e, 0xc5, 0x57, 0x20, 0x39,
          0x8a, 0x99, 0xb1, 0xec, 0x86, 0x0e, 0x2e, 0x9f, 0xe1, 0xb6, 0x04, 0x85,
          0x17, 0x67, 0x6c, 0x76, 0x43, 0x57, 0x18, 0x82, 0x06, 0x3c, 0xbf, 0x38,
          0x7b, 0x76, 0xbf, 0xbc, 0x44, 0xcb, 0xa2, 0x2b, 0x3c, 0xc2, 0xfd, 0x1b,
          0x5c, 0x3c, 0xc1, 0x5d, 0x11, 0xfa, 0x5a, 0xa0, 0xb7, 0x09, 0x7a, 0x22,
          0x10, 0xf5, 0x83, 0x2a, 0x81, 0x2a, 0xbc, 0x83, 0x65, 0x35, 0x7e, 0x85,
          0xb6, 0x00, 0xbc, 0x01, 0xcd, 0x41, 0x88, 0x87, 0xa1, 0x33, 0x04, 0xb1,
          0x10, 0xc4, 0x23, 0x70, 0xf5, 0x04, 0xb1, 0x90, 0x06, 0x80, 0x56, 0x0f,
          0xca, 0xcd, 0x21, 0x91, 0x9c, 0xfd, 0x87, 0xdf, 0x80, 0x9e, 0x28, 0x74,
          0x47, 0xa0, 0x3d, 0x08, 0x61, 0xc3, 0x59, 0xcf, 0x17, 0x9d, 0x7b, 0x18,
          0x9f, 0x48, 0x23, 0x37, 0x87, 0x6a, 0x5f, 0xe1, 0x38, 0x63, 0x56, 0x9a,
          0xe6, 0x2f, 0xa9, 0xde, 0x8a, 0xe0, 0x03, 0x3c, 0xbe, 0x3b, 0x50, 0xab,
          0x0e, 0x7f, 0x02, 0xb5, 0x05, 0x75, 0x2f, 0x3c, 0x99, 0x9c, 0x26, 0xde,
          0x3f, 0xc3, 0xd4, 0x69, 0x0a, 0x91, 0x70, 0xf2, 0xf6, 0xc1, 0x62, 0x0d,
          0x20, 0x12, 0x69, 0xd7, 0xa9, 0x2b, 0x50, 0x85, 0x63, 0x31, 0xc1, 0xf5,
          0x69, 0x0a, 0xa5, 0x60, 0x2e, 0xb0, 0xc4, 0xca, 0xba, 0x14, 0x22, 0x91,
          0xae, 0x6d, 0xe5, 0x0a, 0xe8, 0x3a, 0xf0, 0xc2, 0x77, 0x57, 0x3b, 0x28,
          0x05, 0x4a, 0x35, 0x06, 0xea, 0x43, 0x03, 0x3e, 0xc1, 0x1b, 0x59, 0x58,
          0x59, 0x97, 0xdf, 0x82, 0xae, 0xc0, 0xfe, 0x09, 0xbf, 0x86, 0xa1, 0xf2,
          0x99, 0xb6, 0xd6, 0x4c, 0xf7, 0x9c, 0xff, 0x03, 0x03, 0x7c, 0x00, 0x79,
          0x53, 0xa2, 0x24, 0xa1, 0xd8, 0xe8, 0xa2, 0x00, 0x00, 0x00, 0x00, 0x49,
          0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      static const unsigned char image2_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
          0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x01,
          0x5c, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x9d, 0xd0, 0xb1, 0x4b, 0x02,
          0x61, 0x18, 0xc7, 0xf1, 0xef, 0xab, 0x62, 0xa2, 0x83, 0xf4, 0x07, 0x24,
          0x95, 0x25, 0x14, 0x1a, 0x08, 0xde, 0xe2, 0xd8, 0x5e, 0x41, 0x82, 0xb7,
          0x44, 0xe1, 0xa6, 0xd1, 0xd2, 0xdc, 0x1c, 0x24, 0x04, 0x81, 0x41, 0xa5,
          0x43, 0x4a, 0x24, 0xe1, 0xd0, 0xdc, 0xe2, 0x24, 0x74, 0x53, 0x92, 0x0e,
          0x81, 0x38, 0x36, 0xb4, 0x99, 0x8b, 0x0e, 0x92, 0xf0, 0x36, 0x9c, 0x77,
          0x1a, 0x69, 0x77, 0xf4, 0x4c, 0xef, 0xf0, 0x7e, 0x7e, 0x3c, 0xcf, 0x4f,
          0x68, 0x9a, 0x86, 0xdd, 0x71, 0xa5, 0xe2, 0xd2, 0x78, 0x0f, 0x8b, 0x9a,
          0x00, 0x70, 0xd8, 0xc5, 0x6a, 0xc5, 0x23, 0x1d, 0x65, 0x89, 0xe2, 0x07,
          0xa5, 0x2c, 0xcd, 0x30, 0x5b, 0x01, 0x6a, 0xc5, 0x23, 0xcf, 0xd2, 0x21,
          0x0a, 0xf9, 0x3a, 0xf5, 0x2b, 0x09, 0x87, 0x02, 0xc5, 0xaf, 0x6f, 0x64,
          0x19, 0x90, 0x1c, 0xe1, 0xc8, 0x92, 0x0f, 0xbf, 0xba, 0x4c, 0x21, 0x5f,
          0xe7, 0x26, 0x65, 0x5e, 0x82, 0xcb, 0x0a, 0x67, 0xd3, 0x21, 0xa2, 0x41,
          0x1f, 0xc5, 0x5a, 0x17, 0xad, 0xdd, 0xa1, 0x11, 0x8b, 0xc0, 0x8b, 0x1e,
          0x32, 0xcc, 0x08, 0xc4, 0xac, 0x12, 0x27, 0x71, 0xa9, 0xd6, 0xe5, 0xb9,
          0xdd, 0xa1, 0xe1, 0x0c, 0xd0, 0x77, 0xb8, 0xf5, 0xc3, 0xaf, 0xef, 0xd0,
          0x72, 0xab, 0x62, 0xea, 0x06, 0xd3, 0x70, 0xd3, 0x19, 0xa0, 0xef, 0x72,
          0xeb, 0x1f, 0x46, 0x18, 0xa6, 0x94, 0x38, 0x0b, 0xf7, 0x0c, 0x5c, 0xb8,
          0x35, 0xf1, 0xaf, 0x0e, 0x92, 0x15, 0x9f, 0xcc, 0xa6, 0x57, 0x88, 0x06,
          0xbd, 0xb3, 0xf1, 0xc5, 0x9a, 0x98, 0x34, 0x66, 0x80, 0x5a, 0x99, 0x97,
          0xd9, 0x74, 0x80, 0x70, 0xd0, 0x6b, 0x16, 0x66, 0x85, 0xcd, 0x13, 0xea,
          0xf9, 0xb8, 0x7c, 0xdf, 0x3b, 0x21, 0x1c, 0xf4, 0x72, 0x5f, 0xeb, 0x52,
          0x6d, 0xf5, 0x68, 0xd8, 0xc0, 0x3f, 0x3b, 0x88, 0x3d, 0xb0, 0xd1, 0x4c,
          0x50, 0x6d, 0xf5, 0x78, 0x9d, 0x5b, 0xd0, 0xdb, 0xb6, 0xc0, 0x00, 0xe2,
          0xf2, 0x00, 0x79, 0x54, 0x1a, 0xc0, 0xd7, 0x27, 0x0c, 0x3e, 0xa0, 0x75,
          0x8a, 0x68, 0x3c, 0xea, 0xd1, 0x16, 0x78, 0xdc, 0x81, 0x81, 0x07, 0x1f,
          0xb0, 0xb8, 0x8b, 0x24, 0x81, 0xc8, 0xec, 0xa0, 0xe5, 0xfe, 0xc6, 0x00,
          0x62, 0x5d, 0xd9, 0x94, 0x00, 0x6f, 0x4f, 0xc7, 0x00, 0xec, 0x6f, 0x6f,
          0x01, 0x90, 0x39, 0xd7, 0x2c, 0xf1, 0x78, 0x83, 0x7f, 0x40, 0x63, 0xbe,
          0x01, 0xfa, 0x49, 0xa9, 0x02, 0xe4, 0x53, 0x67, 0x1d, 0x00, 0x00, 0x00,
          0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      static const unsigned char image3_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
          0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x01,
          0xd7, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x8d, 0x93, 0xbf, 0x6b, 0x93,
          0x51, 0x14, 0x86, 0x9f, 0x73, 0x73, 0xbf, 0xef, 0xcb, 0x8f, 0xa2, 0xd2,
          0x45, 0xb4, 0x36, 0x9b, 0x2e, 0x15, 0x04, 0x5d, 0xd2, 0x16, 0x3a, 0x54,
          0x1c, 0x5c, 0xdc, 0x8b, 0x8b, 0x83, 0x8a, 0x8b, 0x9b, 0x92, 0x51, 0xc5,
          0x49, 0x10, 0x17, 0xc1, 0x45, 0xfc, 0x13, 0x9c, 0x14, 0x3a, 0x74, 0xd5,
          0x50, 0x1a, 0x4b, 0x44, 0x70, 0x10, 0xa1, 0x56, 0xc1, 0x58, 0x15, 0x0b,
          0x36, 0xd5, 0xe4, 0x4b, 0x72, 0xef, 0x71, 0xb8, 0x29, 0x89, 0x41, 0x93,
          0xde, 0xed, 0x70, 0xcf, 0x79, 0xcf, 0xf3, 0x9e, 0x7b, 0xae, 0x70, 0xe5,
          0x95, 0xd2, 0xee, 0xf0, 0xf5, 0x68, 0x89, 0xdf, 0xca, 0xbe, 0x4e, 0x5e,
          0xe0, 0x70, 0x7d, 0x15, 0xe2, 0x08, 0x8b, 0xf3, 0x2c, 0x3f, 0x28, 0x91,
          0x9f, 0x84, 0xc6, 0xfe, 0xea, 0xc9, 0x03, 0xcb, 0xdb, 0x25, 0xce, 0xdf,
          0xac, 0x22, 0x5c, 0x5d, 0x57, 0x9e, 0xad, 0xa0, 0xf5, 0x32, 0x9d, 0x6e,
          0x07, 0x41, 0x46, 0x16, 0x2b, 0x4a, 0x64, 0x23, 0xe4, 0xc8, 0x3d, 0xb8,
          0x70, 0x0e, 0x8b, 0x73, 0x9c, 0x79, 0x5c, 0x06, 0xa0, 0xba, 0x16, 0x91,
          0x31, 0xa3, 0xbb, 0x3b, 0x0f, 0x73, 0x73, 0x70, 0xfd, 0x79, 0x99, 0x87,
          0x8f, 0xaa, 0x58, 0x54, 0xf1, 0x9d, 0x70, 0x79, 0xea, 0x74, 0x0b, 0x19,
          0x0d, 0x80, 0x2a, 0x40, 0x96, 0x77, 0x3f, 0x42, 0x60, 0x07, 0x2f, 0xdf,
          0xd4, 0xb2, 0x98, 0x31, 0x04, 0xde, 0xc3, 0xec, 0x2c, 0x6c, 0xfc, 0x04,
          0x84, 0xbf, 0x05, 0x8e, 0xcf, 0xec, 0x62, 0xc6, 0x20, 0x78, 0x55, 0x60,
          0x82, 0x8d, 0xc6, 0x80, 0xc0, 0x5e, 0xd3, 0x1c, 0x3a, 0x66, 0x84, 0x61,
          0x88, 0x00, 0xbe, 0x19, 0x62, 0x0b, 0x90, 0xb3, 0x90, 0x7d, 0x02, 0xe9,
          0xb6, 0x05, 0x9b, 0xe1, 0xbf, 0x3e, 0xbc, 0x07, 0x85, 0xe9, 0xad, 0xb7,
          0x30, 0x7d, 0x02, 0x44, 0x7a, 0x04, 0x02, 0x05, 0x0b, 0xa9, 0xb6, 0xe1,
          0xc5, 0x3a, 0xd4, 0x6a, 0x20, 0x43, 0x22, 0xaa, 0x70, 0x76, 0x01, 0xba,
          0x8e, 0xcb, 0x4b, 0x27, 0xb9, 0xf5, 0xba, 0xd9, 0x27, 0x80, 0xe0, 0x87,
          0x9d, 0x26, 0xfa, 0x74, 0x11, 0x58, 0xfc, 0x27, 0x80, 0x5c, 0xaa, 0x82,
          0x08, 0x33, 0xc5, 0x02, 0xac, 0x7e, 0x1b, 0x12, 0x00, 0x48, 0xd3, 0x90,
          0x38, 0x75, 0x1f, 0x2e, 0x2e, 0xf1, 0xe9, 0xda, 0x14, 0xf5, 0xef, 0x10,
          0x27, 0x9e, 0xc9, 0x83, 0xfd, 0x3d, 0xf7, 0x0a, 0xa4, 0xed, 0x9e, 0x05,
          0x63, 0x02, 0xad, 0x00, 0x69, 0x2b, 0x64, 0x14, 0x2c, 0xd0, 0x66, 0xb7,
          0x01, 0xb9, 0xbc, 0x27, 0x4a, 0x1c, 0x49, 0x76, 0xe8, 0xa3, 0xb4, 0x42,
          0xae, 0x91, 0x8f, 0x1f, 0xd8, 0xac, 0xbe, 0xc7, 0xd8, 0x40, 0xa0, 0x4d,
          0xa0, 0xdd, 0x85, 0x9d, 0x5f, 0x44, 0x31, 0x44, 0x89, 0x23, 0x8a, 0x1d,
          0x49, 0xd6, 0x0f, 0x78, 0xe9, 0x09, 0x88, 0x60, 0x5f, 0xde, 0x39, 0x26,
          0x0b, 0xb7, 0x6b, 0x9a, 0x74, 0x2c, 0xa8, 0xa7, 0xd1, 0x80, 0xcd, 0x95,
          0x1b, 0x24, 0x31, 0xb8, 0x0c, 0x4c, 0xc4, 0x86, 0x24, 0x81, 0x43, 0x07,
          0x3c, 0x64, 0x32, 0x60, 0x94, 0x38, 0x01, 0x5c, 0x17, 0x8c, 0x41, 0x2a,
          0x95, 0x0a, 0x00, 0xf3, 0x77, 0xbf, 0xa8, 0x7e, 0xde, 0x02, 0xa7, 0x7b,
          0xfb, 0xda, 0x9b, 0xbe, 0xf4, 0xbb, 0x46, 0xbd, 0x97, 0x71, 0x3e, 0x2c,
          0x4f, 0xb1, 0xc8, 0x1f, 0x9e, 0x09, 0xa8, 0x8c, 0xc0, 0x44, 0x13, 0x6b,
          0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      static const unsigned char image4_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
          0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x03,
          0x2e, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xb5, 0x95, 0x31, 0x68, 0x1c,
          0x47, 0x14, 0x86, 0x3f, 0x89, 0x2d, 0xde, 0x80, 0x04, 0xb3, 0x20, 0xc3,
          0x2e, 0x38, 0x70, 0x07, 0x32, 0xf8, 0x0a, 0x17, 0xd7, 0x1e, 0xa8, 0xb0,
          0x4a, 0x81, 0xc0, 0x16, 0xa8, 0x09, 0xa8, 0x71, 0x6b, 0x42, 0x20, 0x84,
          0x54, 0x09, 0x86, 0x04, 0xd2, 0xc4, 0x90, 0x4a, 0x69, 0x54, 0xa4, 0x10,
          0x51, 0x1a, 0xe7, 0x5c, 0x18, 0xac, 0x42, 0xb6, 0x12, 0x30, 0xdc, 0x35,
          0x22, 0x12, 0x44, 0xb0, 0x01, 0x19, 0xf6, 0x0a, 0xc1, 0x2e, 0xe8, 0x60,
          0x06, 0x2c, 0x98, 0x07, 0x19, 0x70, 0x8a, 0x95, 0xa2, 0x48, 0xf1, 0x29,
          0x45, 0x9c, 0xd7, 0xcc, 0xee, 0xcc, 0xf0, 0xed, 0xb7, 0x6f, 0xff, 0x61,
          0xa7, 0x06, 0x83, 0x01, 0xe7, 0xd5, 0xeb, 0xf5, 0xde, 0xf2, 0x1e, 0x6a,
          0x30, 0x18, 0x4c, 0x4d, 0x9d, 0x83, 0x5f, 0xee, 0xbc, 0x7c, 0xdb, 0x9e,
          0x6f, 0xe3, 0xbd, 0xa7, 0xaa, 0x2b, 0x9c, 0x77, 0x18, 0x0c, 0x81, 0x70,
          0xed, 0xe8, 0xbc, 0xa3, 0x38, 0x2a, 0x18, 0xee, 0x0d, 0x21, 0x5e, 0xc0,
          0x93, 0x73, 0xd3, 0x27, 0x3f, 0x3c, 0x21, 0xcd, 0x21, 0x6f, 0x43, 0x2b,
          0xea, 0xd9, 0xb2, 0x83, 0x44, 0x00, 0x87, 0x49, 0x04, 0x08, 0x17, 0xf3,
          0x5c, 0xdc, 0x17, 0x47, 0x02, 0xdf, 0x5b, 0x86, 0x2f, 0xfc, 0x65, 0x30,
          0x40, 0xed, 0x6b, 0xd2, 0x0f, 0xa0, 0x1c, 0xff, 0x84, 0xbe, 0x29, 0x09,
          0x51, 0x31, 0x06, 0xc2, 0x1f, 0xe0, 0x6b, 0xa1, 0xaa, 0x15, 0x41, 0x30,
          0x73, 0xd0, 0xbe, 0x05, 0x22, 0x0a, 0x11, 0x14, 0x90, 0x59, 0x48, 0x6f,
          0x28, 0x7f, 0xaf, 0xbf, 0xc0, 0xae, 0x76, 0x84, 0x3b, 0x1e, 0x7d, 0x53,
          0x13, 0xa2, 0xc7, 0xcc, 0x5a, 0xca, 0x7d, 0xd8, 0xdd, 0x56, 0xf6, 0xf7,
          0x6a, 0x24, 0x01, 0x8d, 0x8a, 0x24, 0x96, 0x6c, 0x5e, 0x58, 0x5a, 0x4d,
          0xe9, 0x2d, 0x04, 0x84, 0x66, 0xde, 0xce, 0x08, 0xcd, 0x63, 0xae, 0x80,
          0x2b, 0x5f, 0xd1, 0x45, 0x09, 0xb1, 0xc2, 0x18, 0xcb, 0x60, 0x47, 0xd9,
          0xda, 0xf0, 0x10, 0xc1, 0x5a, 0x21, 0x9f, 0x17, 0x44, 0xa0, 0x1a, 0x29,
          0xa3, 0xd7, 0xca, 0x77, 0x5f, 0x95, 0xd4, 0x6b, 0x19, 0x2b, 0x6b, 0x20,
          0xd2, 0xc0, 0xdf, 0x69, 0x6c, 0x12, 0x03, 0x28, 0x66, 0x56, 0x28, 0xf7,
          0xa1, 0x7f, 0x06, 0x5d, 0xba, 0x97, 0x71, 0x77, 0x19, 0xf2, 0xdc, 0x40,
          0x12, 0x50, 0x4d, 0xd9, 0xdd, 0x0e, 0xf4, 0x37, 0x3c, 0xfd, 0xcd, 0x11,
          0x59, 0xd6, 0x61, 0xf1, 0xbe, 0x41, 0x12, 0xbd, 0x64, 0x3c, 0x7d, 0x7e,
          0x11, 0x62, 0x00, 0x84, 0x10, 0xe0, 0xf9, 0x33, 0x8f, 0x46, 0x65, 0xe9,
          0x5e, 0xc6, 0xca, 0x03, 0x48, 0x73, 0x45, 0x93, 0x0a, 0x7f, 0x62, 0x78,
          0xfe, 0xd4, 0xb1, 0xb4, 0x9a, 0xf2, 0xe1, 0x47, 0x16, 0x12, 0x61, 0x6b,
          0xb3, 0x42, 0xc7, 0xff, 0x8c, 0xdc, 0x65, 0xe3, 0xc4, 0xe1, 0xeb, 0x94,
          0xe2, 0xa0, 0xc4, 0xda, 0xc6, 0x54, 0xa4, 0xb1, 0xf0, 0xa7, 0x39, 0xeb,
          0xdf, 0x38, 0xca, 0x43, 0x8f, 0x3b, 0x81, 0x87, 0x9f, 0xe5, 0x0c, 0x77,
          0x3c, 0xe5, 0xef, 0x4a, 0x51, 0x04, 0x44, 0x2e, 0x83, 0x2f, 0x19, 0x9b,
          0x44, 0xa8, 0x6a, 0x07, 0x09, 0xe4, 0x2d, 0x48, 0x6f, 0x80, 0xa2, 0x78,
          0x9f, 0xb2, 0xfe, 0x65, 0x45, 0x71, 0xe8, 0x11, 0x2b, 0xf4, 0x16, 0x52,
          0x98, 0x71, 0x74, 0xba, 0x16, 0x8d, 0x4a, 0x75, 0x0c, 0x1a, 0x27, 0x80,
          0x9b, 0x1e, 0x83, 0x20, 0x10, 0x15, 0x3b, 0x73, 0xf6, 0x51, 0x4e, 0x72,
          0xd6, 0xbf, 0x76, 0x94, 0x87, 0x4d, 0xbc, 0xec, 0x8c, 0x90, 0xdf, 0x84,
          0x54, 0x9a, 0xf7, 0x95, 0x44, 0xd0, 0x08, 0x72, 0x45, 0xf9, 0x4a, 0x8f,
          0xc1, 0xcc, 0x01, 0x89, 0xa5, 0x18, 0x29, 0xaa, 0x86, 0xdd, 0x17, 0xa1,
          0x31, 0x9d, 0x11, 0xb2, 0x9b, 0x96, 0xd1, 0xa8, 0xe6, 0xf1, 0xa3, 0x8a,
          0x62, 0x3f, 0xa5, 0x2a, 0x15, 0x8d, 0x4a, 0xbb, 0x65, 0xe0, 0xfa, 0x54,
          0x38, 0x3a, 0xb7, 0xa0, 0xd5, 0x12, 0xea, 0x91, 0xb2, 0xbb, 0x1d, 0x58,
          0x59, 0x4b, 0x71, 0x27, 0x4a, 0xef, 0x6e, 0x4a, 0x9e, 0xc1, 0xe3, 0x47,
          0x30, 0x7a, 0x5d, 0xf3, 0xf9, 0xc7, 0x15, 0x7a, 0xea, 0xc9, 0x32, 0x4b,
          0xa7, 0x0b, 0x55, 0x7d, 0x4d, 0x8f, 0x41, 0x40, 0x94, 0xa5, 0x55, 0x41,
          0xa3, 0xd2, 0xdf, 0xf0, 0xec, 0x6e, 0x3b, 0x1e, 0x7e, 0x92, 0xd3, 0x5d,
          0x08, 0xb4, 0xba, 0x81, 0x4f, 0xbf, 0xc8, 0xc9, 0x32, 0x8b, 0x1f, 0xd7,
          0x10, 0xa1, 0xb7, 0x6c, 0x69, 0xdf, 0xfe, 0xd7, 0x1c, 0x07, 0x88, 0x42,
          0x6f, 0x01, 0xea, 0xe3, 0x8c, 0xfe, 0xe6, 0x88, 0xad, 0x6f, 0x61, 0xb8,
          0xe3, 0xe9, 0xdc, 0xb1, 0x90, 0x40, 0x55, 0x3a, 0xfc, 0x58, 0x9b, 0xde,
          0xa2, 0x14, 0xaf, 0x94, 0xe2, 0xc0, 0x60, 0x65, 0xc2, 0xc9, 0x73, 0x63,
          0x77, 0x76, 0xf6, 0x15, 0x01, 0x56, 0xd6, 0x84, 0x2c, 0xeb, 0xd0, 0xff,
          0xb1, 0xa2, 0x38, 0x54, 0x8a, 0x83, 0x51, 0xb3, 0x3b, 0x82, 0x9d, 0xb3,
          0x2c, 0xde, 0xb7, 0xfc, 0xfa, 0xb3, 0x52, 0x9d, 0x7a, 0x34, 0xa6, 0xd4,
          0xe3, 0x09, 0xc6, 0xc5, 0x51, 0x41, 0x51, 0x0a, 0x92, 0x36, 0x26, 0x92,
          0xc0, 0xe2, 0x72, 0xa0, 0xb7, 0x90, 0x53, 0x14, 0x81, 0xea, 0xb8, 0x81,
          0xe6, 0x2d, 0x43, 0xa7, 0x0b, 0xed, 0xdb, 0x50, 0x2c, 0x1b, 0x88, 0x39,
          0x24, 0x8e, 0xf2, 0x37, 0xde, 0x0d, 0x1e, 0xee, 0x0d, 0x61, 0x43, 0x48,
          0xf3, 0x26, 0x52, 0xaa, 0xbe, 0xc9, 0x1b, 0x1e, 0x39, 0xdb, 0x25, 0x09,
          0x94, 0xc7, 0xbe, 0xc9, 0xed, 0xb3, 0xa6, 0x1d, 0xde, 0x43, 0xb1, 0xaf,
          0x54, 0xf5, 0x04, 0x63, 0x22, 0x0c, 0x7f, 0x39, 0x5f, 0xbc, 0x3a, 0x4e,
          0xaa, 0xc9, 0xeb, 0xd3, 0x13, 0x57, 0xfe, 0x63, 0x4d, 0x43, 0xf3, 0x8f,
          0xfa, 0x5f, 0xc0, 0xef, 0x1b, 0x3e, 0x18, 0x0c, 0xa6, 0xfe, 0x04, 0x09,
          0x39, 0x9b, 0xe1, 0x59, 0xe5, 0xea, 0x28, 0x00, 0x00, 0x00, 0x00, 0x49,
          0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      static const unsigned char image5_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
          0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x03,
          0xb1, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xad, 0x94, 0x5f, 0x4c, 0x5b,
          0x55, 0x1c, 0xc7, 0x3f, 0xe7, 0xdc, 0x4b, 0x7b, 0x4b, 0xcb, 0xa0, 0x76,
          0x2d, 0x45, 0xc4, 0x31, 0x14, 0x32, 0x35, 0x99, 0xee, 0x61, 0x92, 0x60,
          0x9c, 0x51, 0xd8, 0x83, 0x89, 0x2c, 0xe0, 0x83, 0xf1, 0x71, 0x8b, 0x3e,
          0xbb, 0x18, 0x5f, 0x8d, 0xc9, 0x1e, 0x97, 0x2c, 0xf3, 0x9d, 0x2d, 0x2a,
          0x2f, 0x1a, 0xf6, 0x64, 0xb6, 0xf1, 0xe0, 0xfe, 0x38, 0x63, 0xa0, 0x71,
          0x89, 0x69, 0x70, 0x0e, 0xb0, 0xc5, 0x21, 0x42, 0xda, 0x02, 0x42, 0xa1,
          0xbd, 0x6d, 0x69, 0x6f, 0x7b, 0xcf, 0xf1, 0x01, 0x58, 0x52, 0x03, 0xce,
          0xb8, 0xfd, 0x9e, 0xce, 0x39, 0xf9, 0x9d, 0xcf, 0xf9, 0xfe, 0x7e, 0xdf,
          0x93, 0x9f, 0x88, 0xc5, 0x62, 0xec, 0x46, 0x5f, 0x5f, 0x9f, 0xe6, 0x09,
          0x44, 0x2c, 0x16, 0x13, 0x62, 0x17, 0x3c, 0x3e, 0x3e, 0xae, 0x7b, 0x7a,
          0x7a, 0xc8, 0xe7, 0xf3, 0x64, 0x32, 0x19, 0x6c, 0xdb, 0xfe, 0x4f, 0x90,
          0x7c, 0x3e, 0x4f, 0x22, 0x91, 0x20, 0x1e, 0x8f, 0xe3, 0x38, 0xce, 0xc3,
          0x73, 0x73, 0x57, 0xe9, 0xe8, 0xe8, 0x28, 0xad, 0xed, 0x1e, 0x22, 0x9d,
          0x65, 0x0e, 0x1f, 0x2d, 0x51, 0x75, 0x4b, 0x08, 0x21, 0x10, 0x12, 0x4c,
          0x13, 0xa4, 0xdc, 0x5e, 0xa3, 0x41, 0xeb, 0x9d, 0xc2, 0x84, 0xc0, 0x55,
          0x8a, 0x85, 0x3f, 0x3c, 0xe8, 0xcb, 0x06, 0x77, 0xef, 0x50, 0x0f, 0xde,
          0x7d, 0x39, 0xd2, 0x59, 0x66, 0x79, 0xe3, 0x26, 0x59, 0x7b, 0x8e, 0x9a,
          0xbb, 0x85, 0xd7, 0xa7, 0x70, 0xab, 0x16, 0xab, 0x69, 0x83, 0xec, 0x5a,
          0x05, 0xb4, 0x87, 0xa7, 0x0e, 0x36, 0xf0, 0xf4, 0xe1, 0x0a, 0xfe, 0x40,
          0x8d, 0x6a, 0x55, 0x83, 0x10, 0x98, 0x01, 0x08, 0x47, 0x8d, 0xba, 0x4a,
          0x1e, 0x82, 0x33, 0x99, 0x0c, 0x5d, 0x47, 0x4b, 0x64, 0xed, 0x39, 0xaa,
          0x3a, 0x8f, 0xe5, 0xf3, 0x31, 0x7f, 0xbf, 0x81, 0xdb, 0xd7, 0x0b, 0xcc,
          0xfe, 0xb2, 0x05, 0x94, 0x76, 0x32, 0xfd, 0x74, 0xf6, 0x58, 0x9c, 0x1c,
          0x6e, 0xa2, 0xf7, 0x0d, 0x03, 0xa5, 0x8b, 0xa0, 0xc1, 0xf2, 0xc9, 0xbd,
          0xc1, 0xb6, 0x6d, 0xe3, 0xb8, 0x25, 0x6a, 0x6e, 0x11, 0xcb, 0xe7, 0xe3,
          0xee, 0x1d, 0x18, 0x1b, 0x59, 0x01, 0x24, 0xfe, 0x26, 0x93, 0xae, 0xee,
          0x08, 0xd2, 0x23, 0xc8, 0x2c, 0x3a, 0x2c, 0x24, 0xb7, 0xb8, 0x74, 0xbe,
          0xc8, 0xf2, 0x62, 0x88, 0x77, 0x4f, 0x7b, 0xd0, 0x54, 0x50, 0x4a, 0xef,
          0x0d, 0xde, 0x6e, 0x99, 0xc0, 0xeb, 0x83, 0xf9, 0xfb, 0x26, 0x63, 0x23,
          0xcb, 0x80, 0xa2, 0x7f, 0xb0, 0x95, 0x81, 0x41, 0x83, 0x60, 0x44, 0x60,
          0x5a, 0x2e, 0xe5, 0x52, 0x33, 0x93, 0x37, 0x1c, 0xc6, 0x46, 0xfe, 0xe2,
          0xda, 0x37, 0x19, 0x5a, 0xa3, 0x5d, 0x0c, 0x0c, 0x5b, 0x48, 0x59, 0xac,
          0x03, 0xd7, 0xe9, 0x17, 0x12, 0xdc, 0xaa, 0xc5, 0xad, 0xab, 0x36, 0x50,
          0xa3, 0xff, 0x9d, 0x08, 0xef, 0x7d, 0xd8, 0x40, 0x4b, 0xb4, 0x88, 0x69,
          0xe5, 0xd9, 0x58, 0xb5, 0xb8, 0x7d, 0xad, 0xc4, 0xc9, 0xa1, 0x46, 0x4e,
          0x9f, 0x0d, 0x03, 0x26, 0xdf, 0x7e, 0xbd, 0x86, 0xbd, 0x2e, 0x31, 0x0c,
          0xb1, 0xbf, 0x62, 0xd3, 0x84, 0xd5, 0x94, 0x41, 0xf2, 0xd7, 0x0a, 0x07,
          0x0e, 0x1c, 0x60, 0xe0, 0x94, 0x89, 0x92, 0x9b, 0x98, 0x86, 0x81, 0xbd,
          0xd9, 0xcc, 0x97, 0x17, 0x0b, 0xcc, 0x4c, 0x65, 0x59, 0x5f, 0x71, 0xf8,
          0xe0, 0xe3, 0x30, 0x13, 0x37, 0xfc, 0x24, 0xa7, 0x73, 0x24, 0x67, 0x83,
          0x18, 0x75, 0xa4, 0x7f, 0x28, 0x96, 0x52, 0xb0, 0xbe, 0x5e, 0x41, 0x51,
          0xe6, 0xd0, 0x73, 0x16, 0xc1, 0xb0, 0xc0, 0x34, 0x0d, 0x8a, 0xb9, 0x20,
          0x23, 0xe7, 0x6d, 0x66, 0xa6, 0xb2, 0x84, 0x0e, 0x36, 0xd2, 0xfb, 0x7a,
          0x13, 0xfe, 0xe6, 0x32, 0x47, 0x5e, 0x6e, 0xdc, 0x36, 0x7e, 0xa9, 0x8a,
          0x90, 0xfb, 0x98, 0xb7, 0xdd, 0x63, 0x10, 0xca, 0x03, 0x28, 0xa4, 0x47,
          0x61, 0x58, 0x2e, 0x1b, 0xab, 0x41, 0xbe, 0xfa, 0xbc, 0xc0, 0xec, 0x94,
          0x0d, 0x28, 0xbc, 0x5e, 0x93, 0xb6, 0x8e, 0x06, 0x4c, 0xab, 0x84, 0xe1,
          0xd9, 0xbe, 0xae, 0xb4, 0x89, 0x34, 0xea, 0xc1, 0xf5, 0x3b, 0x01, 0xc1,
          0xb0, 0x00, 0xfc, 0xa4, 0x96, 0xaa, 0x54, 0xb6, 0x1a, 0x99, 0xfc, 0xde,
          0x61, 0x66, 0x2a, 0x4b, 0x4b, 0x4b, 0x23, 0xd1, 0x68, 0x0b, 0xe9, 0xd4,
          0x26, 0x17, 0x3e, 0x4d, 0xf3, 0x60, 0x2a, 0x48, 0xea, 0x41, 0x19, 0x89,
          0xa4, 0xfd, 0x59, 0x0f, 0x52, 0xa8, 0xfd, 0x15, 0x6b, 0x05, 0xed, 0x9d,
          0x35, 0x0e, 0x3d, 0xef, 0xe3, 0xcf, 0xdf, 0x4b, 0x4c, 0x7c, 0xe7, 0x70,
          0xea, 0x7d, 0x3f, 0xb9, 0xf5, 0x20, 0xaf, 0xbe, 0x16, 0x20, 0xda, 0xee,
          0xe5, 0xc2, 0x67, 0x35, 0xd2, 0x0b, 0x9b, 0x9c, 0xfb, 0x68, 0x11, 0xa7,
          0x54, 0xa4, 0x39, 0xe4, 0xe5, 0xc5, 0x63, 0x9a, 0x4c, 0xaa, 0x1e, 0x5c,
          0xaf, 0x58, 0x6b, 0xfc, 0x01, 0x97, 0xb7, 0x87, 0x02, 0x00, 0x5c, 0xb9,
          0xb4, 0xca, 0xe4, 0xcd, 0x32, 0x67, 0xce, 0x86, 0x38, 0xfe, 0x96, 0x4b,
          0xd7, 0x2b, 0x39, 0x3e, 0x39, 0xd7, 0x49, 0x28, 0xd2, 0x42, 0x61, 0x73,
          0x03, 0xa7, 0x56, 0xa3, 0x7f, 0x28, 0x44, 0x47, 0x77, 0x0d, 0xcd, 0xbf,
          0xfc, 0x63, 0x84, 0xa0, 0x5a, 0x85, 0xde, 0x13, 0x06, 0xe9, 0xa5, 0x20,
          0x57, 0xc7, 0x52, 0x7c, 0x71, 0x31, 0xc3, 0xc4, 0x2d, 0x3f, 0x47, 0x5e,
          0xb2, 0x30, 0x3c, 0x82, 0xd4, 0xfc, 0x32, 0x76, 0xd6, 0x81, 0x1d, 0xb3,
          0x7e, 0xfe, 0xb1, 0x48, 0x72, 0x30, 0x82, 0xd9, 0xb0, 0x8f, 0x79, 0xf9,
          0x7c, 0x1e, 0x57, 0x29, 0x10, 0x9a, 0x9a, 0x28, 0x30, 0x7c, 0xc6, 0x22,
          0xd2, 0xd6, 0xcd, 0xf5, 0x2b, 0x2b, 0x24, 0xef, 0xe5, 0x48, 0xde, 0xdb,
          0x00, 0x14, 0x20, 0x09, 0x86, 0x2c, 0xfa, 0x87, 0x9e, 0xe1, 0xa7, 0x1f,
          0x6c, 0xec, 0x92, 0x83, 0x53, 0x51, 0x14, 0x72, 0xfb, 0xf4, 0x38, 0x91,
          0x48, 0xb0, 0xb0, 0xe0, 0xc1, 0x08, 0x08, 0x14, 0x12, 0x45, 0x8d, 0xfe,
          0x21, 0xc9, 0xf1, 0x13, 0x51, 0xe6, 0x7e, 0x73, 0x58, 0x59, 0x54, 0x68,
          0x24, 0x6d, 0x1d, 0x1e, 0x5e, 0x38, 0xa6, 0xe9, 0xe8, 0x51, 0xbc, 0x39,
          0xd8, 0x4a, 0xb5, 0x02, 0xa6, 0x69, 0x33, 0x1d, 0xaf, 0xec, 0x0d, 0x8e,
          0xc7, 0xe3, 0xe8, 0xcb, 0x06, 0xe1, 0xa8, 0x81, 0xd7, 0x27, 0xd1, 0xae,
          0x40, 0x18, 0x0a, 0x43, 0x4a, 0x8c, 0x9d, 0xb1, 0x29, 0xa5, 0x41, 0x26,
          0xad, 0x48, 0xa7, 0x35, 0x8c, 0x2b, 0x4c, 0x53, 0x52, 0xc8, 0xc3, 0x74,
          0xbc, 0xcc, 0xda, 0xb2, 0xbb, 0x37, 0xd8, 0x71, 0x9c, 0xba, 0x79, 0xfa,
          0xb8, 0x21, 0x1f, 0x9d, 0xf2, 0x18, 0xe0, 0x58, 0x2c, 0x26, 0x1e, 0x95,
          0xf8, 0xbf, 0xc0, 0x4f, 0x1a, 0x1e, 0x8b, 0xc5, 0xc4, 0xdf, 0xe0, 0xa1,
          0x90, 0x17, 0x2a, 0xf6, 0xa9, 0x69, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
          0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      switch (id)
        {
        case image0_ID: {QImage img; img.loadFromData(image0_data, sizeof(image0_data), "PNG"); return QPixmap::fromImage(img);}
        case image1_ID: {QImage img; img.loadFromData(image1_data, sizeof(image1_data), "PNG"); return QPixmap::fromImage(img);}
        case image2_ID: {QImage img; img.loadFromData(image2_data, sizeof(image2_data), "PNG"); return QPixmap::fromImage(img);}
        case image3_ID: {QImage img; img.loadFromData(image3_data, sizeof(image3_data), "PNG"); return QPixmap::fromImage(img);}
        case image4_ID: {QImage img; img.loadFromData(image4_data, sizeof(image4_data), "PNG"); return QPixmap::fromImage(img);}
        case image5_ID: {QImage img; img.loadFromData(image5_data, sizeof(image5_data), "PNG"); return QPixmap::fromImage(img);}
        default: return QPixmap();
        } // switch
    } // icon
  };

namespace Ui
  {
  class CQExpressionMmlWidget: public Ui_CQExpressionMmlWidget {};
} // namespace Ui

QT_END_NAMESPACE

class CQExpressionMmlWidget : public QWidget, public Ui::CQExpressionMmlWidget
  {
    Q_OBJECT

  public:
    CQExpressionMmlWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CQExpressionMmlWidget();

  public slots:
    void updateWidget();

  signals:
    void signalCheckValidity(bool);

  protected:
    void init();

  protected slots:
    virtual void languageChange();

    void slotGoExpressionWidget();
    void slotGoMmlWidget();

  private:
    QString MMLStr;

    void saveTeX(const QString filename);
    void saveMML(const QString filename);

  private slots:
    void slotSaveExpression();
  };

#endif // CQEXPRESSIONMMLWIDGET_H
