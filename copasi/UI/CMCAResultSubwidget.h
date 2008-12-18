// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CMCAResultSubwidget.h,v $
//   $Revision: 1.12.4.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:55 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMCARESULTSUBWIDGET_H
#define CMCARESULTSUBWIDGET_H

#include <qvariant.h>
//Added by qt3to4:
#include <QPixmap>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>

class CMCAMethod;

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QComboBox>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>
#include "CQArrayAnnotationsWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CMCAResultSubwidget
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3HBoxLayout *hboxLayout;
    QLabel *mTopLabel;
    QComboBox *mComboScale;
    QPushButton *mSaveButton;
    QTabWidget *mTabWidget;
    QWidget *tab;
    Q3HBoxLayout *hboxLayout1;
    CQArrayAnnotationsWidget *mpArrayElasticities;
    QWidget *tab1;
    Q3GridLayout *gridLayout;
    CQArrayAnnotationsWidget *mpArrayFCC;
    QWidget *TabPage;
    Q3GridLayout *gridLayout1;
    CQArrayAnnotationsWidget *mpArrayCCC;

    void setupUi(QWidget *CMCAResultSubwidget)
    {
      if (CMCAResultSubwidget->objectName().isEmpty())
        CMCAResultSubwidget->setObjectName(QString::fromUtf8("CMCAResultSubwidget"));
      CMCAResultSubwidget->resize(580, 422);
      vboxLayout = new Q3VBoxLayout(CMCAResultSubwidget);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mTopLabel = new QLabel(CMCAResultSubwidget);
      mTopLabel->setObjectName(QString::fromUtf8("mTopLabel"));
      mTopLabel->setWordWrap(false);

      hboxLayout->addWidget(mTopLabel);

      mComboScale = new QComboBox(CMCAResultSubwidget);
      mComboScale->setObjectName(QString::fromUtf8("mComboScale"));
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(mComboScale->sizePolicy().hasHeightForWidth());
      mComboScale->setSizePolicy(sizePolicy);

      hboxLayout->addWidget(mComboScale);

      mSaveButton = new QPushButton(CMCAResultSubwidget);
      mSaveButton->setObjectName(QString::fromUtf8("mSaveButton"));
      sizePolicy.setHeightForWidth(mSaveButton->sizePolicy().hasHeightForWidth());
      mSaveButton->setSizePolicy(sizePolicy);

      hboxLayout->addWidget(mSaveButton);

      vboxLayout->addLayout(hboxLayout);

      mTabWidget = new QTabWidget(CMCAResultSubwidget);
      mTabWidget->setObjectName(QString::fromUtf8("mTabWidget"));
      tab = new QWidget();
      tab->setObjectName(QString::fromUtf8("tab"));
      hboxLayout1 = new Q3HBoxLayout(tab);
      hboxLayout1->setSpacing(6);
      hboxLayout1->setMargin(0);
      hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
      mpArrayElasticities = new CQArrayAnnotationsWidget(tab);
      mpArrayElasticities->setObjectName(QString::fromUtf8("mpArrayElasticities"));

      hboxLayout1->addWidget(mpArrayElasticities);

      mTabWidget->addTab(tab, QString());
      tab1 = new QWidget();
      tab1->setObjectName(QString::fromUtf8("tab1"));
      gridLayout = new Q3GridLayout(tab1);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(0);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      mpArrayFCC = new CQArrayAnnotationsWidget(tab1);
      mpArrayFCC->setObjectName(QString::fromUtf8("mpArrayFCC"));

      gridLayout->addWidget(mpArrayFCC, 0, 0, 1, 1);

      mTabWidget->addTab(tab1, QString());
      TabPage = new QWidget();
      TabPage->setObjectName(QString::fromUtf8("TabPage"));
      gridLayout1 = new Q3GridLayout(TabPage);
      gridLayout1->setSpacing(6);
      gridLayout1->setMargin(0);
      gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
      mpArrayCCC = new CQArrayAnnotationsWidget(TabPage);
      mpArrayCCC->setObjectName(QString::fromUtf8("mpArrayCCC"));

      gridLayout1->addWidget(mpArrayCCC, 0, 0, 1, 1);

      mTabWidget->addTab(TabPage, QString());

      vboxLayout->addWidget(mTabWidget);

      retranslateUi(CMCAResultSubwidget);
      QObject::connect(mComboScale, SIGNAL(activated(int)), CMCAResultSubwidget, SLOT(slotScaled()));
      QObject::connect(mSaveButton, SIGNAL(clicked()), CMCAResultSubwidget, SLOT(slotSave()));

      QMetaObject::connectSlotsByName(CMCAResultSubwidget);
    } // setupUi

    void retranslateUi(QWidget *CMCAResultSubwidget)
    {
      CMCAResultSubwidget->setWindowTitle(QApplication::translate("CMCAResultSubwidget", "Form1", 0, QApplication::UnicodeUTF8));
      mTopLabel->setText(QString());
      mComboScale->clear();
      mComboScale->insertItems(0, QStringList()
                               << QApplication::translate("CMCAResultSubwidget", "scaled", 0, QApplication::UnicodeUTF8)
                               << QApplication::translate("CMCAResultSubwidget", "unscaled", 0, QApplication::UnicodeUTF8)
);
      mSaveButton->setText(QApplication::translate("CMCAResultSubwidget", "Save data to file", 0, QApplication::UnicodeUTF8));
      mTabWidget->setTabText(mTabWidget->indexOf(tab), QApplication::translate("CMCAResultSubwidget", "Elasticities", 0, QApplication::UnicodeUTF8));
      mTabWidget->setTabText(mTabWidget->indexOf(tab1), QApplication::translate("CMCAResultSubwidget", "Flux Control Coefficients", 0, QApplication::UnicodeUTF8));
      mTabWidget->setTabText(mTabWidget->indexOf(TabPage), QApplication::translate("CMCAResultSubwidget", "Concentration Control Coefficients", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CMCAResultSubwidget);
    } // retranslateUi

  protected:
    enum IconID
    {
      image0_ID,
      unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
      static const unsigned char image0_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
          0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x04,
          0x2b, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xb5, 0x95, 0x4b, 0x6c, 0x54,
          0x55, 0x18, 0xc7, 0x7f, 0xe7, 0xdc, 0xdb, 0x3b, 0x77, 0x3a, 0xa5, 0xed,
          0x38, 0xcc, 0x30, 0x80, 0xa5, 0xa5, 0xf2, 0x52, 0x43, 0x90, 0x05, 0xb2,
          0x20, 0x62, 0xb4, 0xb0, 0x30, 0xb1, 0xa4, 0x75, 0xa1, 0x2e, 0x01, 0x5d,
          0xb0, 0x92, 0x18, 0x37, 0x2e, 0x0c, 0x49, 0x97, 0x18, 0x82, 0x89, 0xcb,
          0x82, 0x8f, 0x10, 0xc1, 0x94, 0x95, 0x01, 0x36, 0xf2, 0x10, 0x63, 0x20,
          0x91, 0xc4, 0x34, 0x15, 0x29, 0xd8, 0x01, 0x6a, 0x29, 0x99, 0xe9, 0x43,
          0x3a, 0xd3, 0xde, 0x3b, 0x8f, 0xce, 0x9d, 0x7b, 0xcf, 0x71, 0x31, 0x0f,
          0x9c, 0x44, 0x51, 0x17, 0x7e, 0xc9, 0x97, 0x7b, 0x4f, 0x72, 0xf3, 0x3b,
          0xff, 0xf3, 0x7d, 0xe7, 0xfe, 0x3f, 0xa1, 0xb5, 0xa6, 0x1e, 0x42, 0x08,
          0x09, 0x18, 0x80, 0x09, 0x48, 0x40, 0xd4, 0xf2, 0x49, 0xa1, 0x6b, 0xa9,
          0x00, 0x1f, 0x08, 0xb4, 0xd6, 0x4a, 0xd4, 0xc1, 0x43, 0x43, 0x43, 0xed,
          0xbd, 0xbd, 0xbd, 0x87, 0x1c, 0xc7, 0x39, 0x98, 0xc9, 0x64, 0x36, 0xbb,
          0xae, 0xfb, 0x0f, 0xbc, 0x6a, 0x38, 0x8e, 0xc3, 0xc4, 0xc4, 0xc4, 0xbd,
          0xd1, 0xd1, 0xd1, 0x33, 0x9e, 0xe7, 0x7d, 0x06, 0x2c, 0x00, 0x65, 0xb3,
          0xae, 0xf4, 0xd4, 0xa9, 0x53, 0x87, 0x12, 0x6b, 0x5a, 0x8e, 0xc6, 0xbb,
          0x4b, 0xf4, 0x6c, 0x2d, 0x52, 0x09, 0x8a, 0x08, 0x21, 0x10, 0x12, 0x4c,
          0x13, 0xa4, 0xac, 0xbe, 0xa3, 0xa1, 0x71, 0x4a, 0x21, 0x08, 0x94, 0x62,
          0xea, 0x37, 0x6b, 0x83, 0x3e, 0x69, 0x1c, 0xb9, 0x71, 0x95, 0x30, 0xf0,
          0x29, 0x90, 0x33, 0x6b, 0x1b, 0x1b, 0x8e, 0xe3, 0x1c, 0x8c, 0x77, 0x97,
          0x98, 0xcd, 0x5d, 0x22, 0xeb, 0xde, 0xc5, 0x0f, 0x4a, 0x84, 0xc2, 0x8a,
          0xa0, 0x62, 0x33, 0x9f, 0x31, 0xc8, 0x3e, 0x2a, 0x83, 0xb6, 0x78, 0x6a,
          0x65, 0x0b, 0x6b, 0xd6, 0x97, 0x89, 0xb4, 0xf9, 0x54, 0x2a, 0x1a, 0x84,
          0xc0, 0x6c, 0x83, 0x78, 0xd2, 0x00, 0x78, 0x0b, 0x38, 0xdd, 0x50, 0x0c,
          0x98, 0x99, 0x4c, 0x66, 0xf3, 0xfa, 0xad, 0x45, 0xb2, 0xee, 0x5d, 0x2a,
          0xda, 0xc1, 0x0e, 0x87, 0x99, 0xbc, 0xd5, 0xc2, 0x95, 0x0b, 0x79, 0xee,
          0xfc, 0x5c, 0x02, 0x8a, 0xb5, 0x4f, 0x23, 0xf4, 0x6c, 0xb2, 0xd9, 0x3b,
          0xb8, 0x82, 0x9d, 0x2f, 0x1b, 0x28, 0x5d, 0x00, 0x0d, 0x76, 0x58, 0x02,
          0xac, 0x03, 0xa2, 0x7f, 0x56, 0x2c, 0x5d, 0xd7, 0xc5, 0x0b, 0x8a, 0xf8,
          0x41, 0x01, 0x3b, 0x1c, 0xe6, 0xc6, 0x55, 0x18, 0x19, 0x9e, 0x03, 0x24,
          0x91, 0x15, 0x26, 0xbd, 0x1b, 0x13, 0x48, 0x4b, 0x30, 0x33, 0xed, 0x31,
          0x95, 0x2a, 0x71, 0xe2, 0x68, 0x81, 0xd9, 0xe9, 0x18, 0x6f, 0xec, 0xb7,
          0xd0, 0x94, 0x51, 0xaa, 0x71, 0x09, 0xc2, 0x80, 0x55, 0x07, 0x8b, 0x5a,
          0xad, 0x09, 0x85, 0x61, 0xf2, 0x96, 0xc9, 0xc8, 0xf0, 0x2c, 0xa0, 0xe8,
          0xeb, 0x5f, 0xc5, 0x9e, 0x7e, 0x83, 0x68, 0x42, 0x60, 0xda, 0x01, 0xcb,
          0xc5, 0x0e, 0xae, 0x5f, 0xf4, 0x18, 0x19, 0xfe, 0x9d, 0xf3, 0x5f, 0xcf,
          0xb0, 0x2a, 0xd9, 0xcb, 0x9e, 0x41, 0x1b, 0x29, 0x0b, 0x75, 0xb0, 0x01,
          0xd5, 0x76, 0x3c, 0x06, 0x4b, 0x08, 0x2a, 0x36, 0x97, 0xcf, 0xb9, 0x80,
          0x4f, 0xdf, 0xeb, 0x09, 0xde, 0x7c, 0xb7, 0x85, 0xce, 0x64, 0x01, 0xd3,
          0x76, 0xc8, 0xcd, 0xdb, 0x5c, 0x39, 0x5f, 0x64, 0xef, 0x40, 0x2b, 0xfb,
          0x0f, 0xc7, 0x01, 0x93, 0x6f, 0xce, 0x3c, 0xc2, 0x5d, 0x90, 0x18, 0x46,
          0xe3, 0x56, 0x0a, 0x40, 0xd4, 0x15, 0x57, 0x0b, 0x6d, 0xc2, 0x7c, 0xda,
          0x20, 0xf5, 0x4b, 0x99, 0xf6, 0xf6, 0x76, 0xf6, 0xec, 0x33, 0x51, 0x72,
          0x11, 0xd3, 0x30, 0x70, 0x17, 0x3b, 0xf8, 0xe2, 0x78, 0x9e, 0xdb, 0x63,
          0x59, 0x16, 0xe6, 0x3c, 0xde, 0x79, 0x3f, 0xce, 0xb5, 0x8b, 0x11, 0x52,
          0xe3, 0x4b, 0xa4, 0xee, 0x44, 0x31, 0x9a, 0x48, 0xd5, 0x9f, 0xe0, 0xf1,
          0x42, 0x0a, 0x16, 0x16, 0xca, 0x28, 0x96, 0xe9, 0x7e, 0xc6, 0x26, 0x1a,
          0x17, 0x98, 0xa6, 0x41, 0x61, 0x29, 0xca, 0xf0, 0x51, 0x97, 0xdb, 0x63,
          0x59, 0x62, 0x2b, 0x5b, 0xd9, 0xf9, 0xd2, 0x0a, 0x22, 0x1d, 0xcb, 0x6c,
          0xd9, 0xd6, 0x0a, 0xc0, 0xcc, 0xc3, 0x0a, 0x42, 0x36, 0xa1, 0x68, 0xda,
          0x47, 0x08, 0x10, 0xca, 0x02, 0x14, 0xd2, 0x52, 0x18, 0x76, 0x40, 0x6e,
          0x3e, 0xca, 0x97, 0x9f, 0xe4, 0xb9, 0x33, 0xe6, 0x02, 0x8a, 0x50, 0xc8,
          0x64, 0x75, 0x57, 0x0b, 0xa6, 0x5d, 0xc4, 0xa8, 0xb5, 0x48, 0x69, 0x13,
          0x69, 0x34, 0x83, 0x9b, 0x57, 0x02, 0xa2, 0x71, 0x01, 0x44, 0x48, 0x3f,
          0xac, 0x50, 0x2e, 0xb5, 0x72, 0xfd, 0x3b, 0x8f, 0xdb, 0x63, 0x59, 0x3a,
          0x3b, 0x5b, 0x49, 0x26, 0x3b, 0xc9, 0xa4, 0x17, 0x39, 0xf6, 0x51, 0x86,
          0xfb, 0x63, 0x51, 0xd2, 0xf7, 0x97, 0x91, 0x48, 0xd6, 0xae, 0xb3, 0x90,
          0x42, 0xfd, 0xbd, 0x62, 0xad, 0x60, 0x6d, 0x8f, 0x4f, 0xf7, 0x86, 0x30,
          0x0f, 0xee, 0x15, 0xb9, 0xf6, 0xad, 0xc7, 0xbe, 0xb7, 0x23, 0x2c, 0x2d,
          0x44, 0x79, 0x71, 0x57, 0x1b, 0xc9, 0xb5, 0x21, 0x8e, 0x1d, 0xf1, 0xc9,
          0x4c, 0x2d, 0x32, 0xf4, 0xde, 0x34, 0x5e, 0xb1, 0x40, 0x47, 0x2c, 0xc4,
          0x73, 0xdb, 0x35, 0x33, 0xe9, 0x66, 0x70, 0xb3, 0x62, 0xad, 0x89, 0xb4,
          0x05, 0xbc, 0x36, 0xd0, 0x06, 0xc0, 0xd9, 0x13, 0xf3, 0x5c, 0xbf, 0xb4,
          0xcc, 0x81, 0xc3, 0x31, 0x76, 0xbc, 0x1a, 0xd0, 0xfb, 0xc2, 0x12, 0x1f,
          0x0c, 0xf5, 0x10, 0x4b, 0x74, 0x92, 0x5f, 0xcc, 0xe1, 0xf9, 0x3e, 0x7d,
          0x03, 0x31, 0xba, 0x36, 0xfa, 0x68, 0x74, 0x13, 0xaa, 0xb9, 0x97, 0x42,
          0x50, 0xa9, 0xc0, 0xce, 0xdd, 0x06, 0x99, 0x87, 0x51, 0xce, 0x8d, 0xa4,
          0xf9, 0xfc, 0xf8, 0x0c, 0xd7, 0x2e, 0x47, 0xd8, 0xf2, 0xbc, 0x8d, 0x61,
          0x09, 0xd2, 0x93, 0xb3, 0xb8, 0x59, 0x0f, 0x6a, 0xcd, 0xfa, 0xe9, 0x87,
          0x02, 0xa9, 0xfe, 0x04, 0x66, 0xcb, 0x5f, 0x37, 0x4f, 0x3b, 0x8e, 0x43,
          0xa0, 0x14, 0x08, 0x8d, 0x2f, 0xf2, 0x0c, 0x1e, 0xb0, 0x49, 0xac, 0xde,
          0xc8, 0x85, 0xb3, 0x73, 0xa4, 0x6e, 0x2e, 0x91, 0xba, 0x99, 0xa3, 0xea,
          0x8c, 0x92, 0x68, 0xcc, 0xa6, 0x6f, 0xe0, 0x69, 0x7e, 0xfc, 0xde, 0xc5,
          0x2d, 0x7a, 0x78, 0x65, 0x45, 0x7e, 0xa9, 0x51, 0x0a, 0x0d, 0xe8, 0x06,
          0x78, 0x62, 0x62, 0xe2, 0xde, 0xd4, 0x94, 0xb5, 0xc1, 0x68, 0x13, 0x28,
          0x24, 0x0a, 0x9f, 0xbe, 0x01, 0xc9, 0x8e, 0xdd, 0x49, 0xee, 0xfe, 0xea,
          0x31, 0x37, 0xad, 0xd0, 0x48, 0x56, 0x77, 0x59, 0x3c, 0xbb, 0x5d, 0xd3,
          0xb5, 0x49, 0xf1, 0x4a, 0xff, 0x2a, 0x2a, 0x65, 0x30, 0x4d, 0x97, 0xf1,
          0xd1, 0x32, 0x40, 0x06, 0x08, 0x00, 0x2d, 0xb4, 0xd6, 0x08, 0x21, 0xc2,
          0x96, 0x65, 0x7d, 0xb8, 0x7d, 0x97, 0x71, 0x24, 0x9e, 0x34, 0x08, 0x85,
          0x25, 0x3a, 0x10, 0x08, 0x43, 0x61, 0x48, 0x89, 0x51, 0xb3, 0x4d, 0x29,
          0x0d, 0x84, 0x50, 0xb5, 0x7a, 0x2a, 0x4c, 0x53, 0x92, 0x77, 0x60, 0x7c,
          0x74, 0x99, 0x47, 0xb3, 0x3e, 0xf3, 0x33, 0xfe, 0x69, 0xe0, 0x24, 0x30,
          0x59, 0xf7, 0xd6, 0x16, 0xaa, 0xce, 0xf4, 0x31, 0xf0, 0x80, 0xc7, 0x53,
          0xe1, 0xdf, 0x66, 0x1a, 0xf8, 0x0a, 0x18, 0x04, 0xb6, 0x01, 0xf1, 0xba,
          0x62, 0x49, 0xd5, 0x95, 0xa2, 0x40, 0xac, 0xf6, 0x0c, 0x53, 0x33, 0x14,
          0x9e, 0x1c, 0xba, 0x76, 0xfc, 0x12, 0x90, 0xa3, 0x3a, 0x41, 0x72, 0x8d,
          0xd1, 0x24, 0x84, 0x30, 0x81, 0x10, 0xd0, 0x5a, 0x83, 0x5a, 0xfc, 0xb7,
          0x99, 0xe7, 0xd5, 0xe0, 0x45, 0xa0, 0x2c, 0xfe, 0xaf, 0x61, 0xfa, 0x07,
          0x19, 0xe5, 0xce, 0x0f, 0xc9, 0x40, 0x34, 0x0e, 0x00, 0x00, 0x00, 0x00,
          0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      switch (id)
        {
        case image0_ID: {QImage img; img.loadFromData(image0_data, sizeof(image0_data), "PNG"); return QPixmap::fromImage(img);}
        default: return QPixmap();
        } // switch
    } // icon
  };

namespace Ui
  {
  class CMCAResultSubwidget: public Ui_CMCAResultSubwidget {};
} // namespace Ui

QT_END_NAMESPACE

class CMCAResultSubwidget : public QWidget, public Ui::CMCAResultSubwidget
  {
    Q_OBJECT

  public:
    CMCAResultSubwidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CMCAResultSubwidget();

    virtual void loadAll(const CMCAMethod * mcaMethod);
    virtual void loadElasticities(const CMCAMethod * mcaMethod);
    virtual void loadConcentrationCCs(const CMCAMethod * mcaMethod);
    virtual void loadFluxCCs(const CMCAMethod * mcaMethod);
    virtual void clear();

  protected:
    virtual void init();

  protected slots:
    virtual void languageChange();

    virtual void slotSave();
    virtual void slotScaled();

  private:
    const CMCAMethod * mMCAMethod;
  };

#endif // CMCARESULTSUBWIDGET_H
