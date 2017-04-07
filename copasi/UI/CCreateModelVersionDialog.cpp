// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CCreateModelVersionDialog.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#include "CCreateModelVersionDialog.h"
#include "ui_CCreateModelVersionDialog.h"

#include "copasi.h"
#include "qtUtilities.h"

#include "commandline/CConfigurationFile.h"
#include "report/CCopasiRootContainer.h"

CCreateModelVersionDialog::CCreateModelVersionDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CCreateModelVersionDialog)
{
  ui->setupUi(this);

  mVersion = QString("");
  mComments = QString("");

  // Retrieve Author's information from Configuration
  CConfigurationFile * configFile = CCopasiRootContainer::getConfiguration();
  CCopasiParameter * pParameter = configFile->getParameter("Given Name");

  if (pParameter != NULL)
    {
      mGivenName = FROM_UTF8(pParameter->getValue< std::string >());
    }

  pParameter = configFile->getParameter("Famliy Name");

  if (pParameter != NULL)
    {
      mFamilyName = FROM_UTF8(pParameter->getValue< std::string >());
    }

  pParameter = configFile->getParameter("Organization");

  if (pParameter != NULL)
    {
      mOrganization = FROM_UTF8(pParameter->getValue< std::string >());
    }

  pParameter = configFile->getParameter("Email");

  if (pParameter != NULL)
    {
      mEmail = FROM_UTF8(pParameter->getValue< std::string >());
    }

  mDataCaptured = false;
  ui->CancelButton->setEnabled(true);
  ui->OkButton->setEnabled(false);
  ui->plainTextEdit->setEnabled(false);
  ui->lineEdit_2->setEnabled(true);
}

CCreateModelVersionDialog::~CCreateModelVersionDialog()
{
  delete ui;
}

QString CCreateModelVersionDialog::getVersion() const
{
  return mVersion;
}

QString CCreateModelVersionDialog::getComments() const
{
  return mComments;
}

bool CCreateModelVersionDialog::isDataCaptured() const
{
  return (mDataCaptured);
}

QString CCreateModelVersionDialog::getGivenName() const
{
  return mGivenName;
}

QString CCreateModelVersionDialog::getFamilyName() const
{
  return mFamilyName;
}

QString CCreateModelVersionDialog::getOrganization() const
{
  return mOrganization;
}

QString CCreateModelVersionDialog::getEmail() const
{
  return mEmail;
}

void CCreateModelVersionDialog::on_OkButton_clicked()
{

  mVersion  = ui->lineEdit_2->text();
  mComments = ui->plainTextEdit->toPlainText();
  mDataCaptured = true;
  close();
}

void CCreateModelVersionDialog::on_lineEdit_2_textEdited(const QString &arg1)
{
  if (arg1.isEmpty() == false)
    {
      ui->CancelButton->setEnabled(true);
      ui->OkButton->setEnabled(true);
      ui->plainTextEdit->setEnabled(true);
      ui->lineEdit_2->setEnabled(true);
    }
  else
    {
      ui->CancelButton->setEnabled(true);
      ui->OkButton->setEnabled(false);
      ui->plainTextEdit->setEnabled(false);
      ui->lineEdit_2->setEnabled(true);
    }
}
