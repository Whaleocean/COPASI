// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSpeciesDetail.h"
#include "CQMessageBox.h"
#include "CQNameSelectionDialog.h"  // for Copy button compartment options
#include "qtUtilities.h"

#include "model/CModel.h"
#include "model/CChemEqInterface.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModelExpansion.h"    //for Copy button and options

//UNDO framework classes
#include "model/CReactionInterface.h"
#include "undoFramework/DeleteSpeciesCommand.h"
#include "undoFramework/CreateNewSpeciesCommand.h"
#include "undoFramework/SpeciesTypeChangeCommand.h"
#include "undoFramework/SpeciesChangeCommand.h"
#include "undoFramework/SpeciesInitialValueLostFocusCommand.h"
#include "undoFramework/UndoSpeciesData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoEventAssignmentData.h"
#include "copasiui3window.h"

#include <copasi/UI/CQDependencyWidget.h>
#include <copasi/UI/CQDependenciesWidget.h>

/*
 *  Constructs a CQSpeciesDetail which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSpeciesDetail::CQSpeciesDetail(QWidget *parent, const char *name) :
  CopasiWidget(parent, name),
  mChanged(false),
  mpMetab(NULL),
  mpCurrentCompartment(NULL),
  mItemToType(),
  mInitialNumber(0.0),
  mInitialConcentration(0.0),
  mpDependencies(new CQDependenciesWidget(parent))
{
  setupUi(this);
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::REACTIONS]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));
  mItemToType.push_back(CModelEntity::REACTIONS);
  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);
  mpNoiseExpressionWidget->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);
  mpReactionTable->verticalHeader()->hide();
  mpReactionTable->horizontalHeader()->hide();
#if QT_VERSION >= 0x050000
  mpReactionTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  mpReactionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
  mpReactionTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpReactionTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
  CopasiUI3Window   *pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());
  // temporarily hide the reaction label / table
  mpLblReactions->setVisible(false);
  mpReactionTable->setVisible(false);
  // display dependency widget instead
  mpDependencies->setVisibleDependencies(REACTION | EVENT | SPECIES | PARAMETERS | COMPARTMENT);
  mpDependencies->setLabelWidth(mpLblValue->width() + 14);
  gridLayout->addWidget(mpDependencies, gridLayout->rowCount(), 0, 1, -1);
}

CQSpeciesDetail::~CQSpeciesDetail()
{
}

bool CQSpeciesDetail::leave()
{
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::FIXED &&
      (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::REACTIONS)
    {
      // -- Expression --
      mpExpressionEMW->updateWidget();
    }

  if (mpBoxUseInitialExpression->isChecked())
    {
      // -- Initial Expression --
      mpInitialExpressionEMW->updateWidget();
    }

  save();
  return true;
}

bool CQSpeciesDetail::update(ListViews::ObjectType objectType,
                             ListViews::Action action,
                             const std::string &key)
{
  switch (objectType)
    {
      case ListViews::MODEL:

        // For a new model we need to remove references to no longer existing metabolites
        if (action == ListViews::ADD)
          {
            mKey = "";
            mpObject = NULL;
            mpMetab = NULL;
          }

        break;

      case ListViews::METABOLITE:

        // If the currently displayed metabolite is deleted we need to remove its references.
        if (action == ListViews::DELETE && mKey == key)
          {
            mKey = "";
            mpObject = NULL;
            mpMetab = NULL;
          }

        break;

      case ListViews::STATE:
      case ListViews::COMPARTMENT:
        break;

      default:
        return true;
        break;
    }

  if (isVisible() && !mIgnoreUpdates)
    load();

  return true;
}

void CQSpeciesDetail::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  if (mpMetab == NULL) return;

  const CModel *pModel = mpMetab->getModel();
  QString ParticleNumberUnits = "[" + FROM_UTF8(CUnit::prettyPrint(mpMetab->getValueReference()->getUnits())) + "]";
  QString ParticleNumberRateUnits = "[" + FROM_UTF8(CUnit::prettyPrint(mpMetab->getRateReference()->getUnits())) + "]";
  // These depend on the current selected compartment's unit (which depends on it's dimentionality)
  std::string concUnitStdStr = "(" + pModel->getQuantityUnit() + ")/(" + mpCurrentCompartment->getUnits() + ")";
  QString ConcentrationUnits = "[" + FROM_UTF8(CUnit::prettyPrint(concUnitStdStr)) + "]";
  QString ConcentrationRateUnits = "[" + FROM_UTF8(CUnit::prettyPrint("(" + concUnitStdStr + ")/(" + pModel->getTimeUnit() + ")")) + "]";

  switch (mFramework)
    {
      case 0:
        mpLblInitialValue->setText("Initial Concentration\n" + ConcentrationUnits);
        mpLblInitialExpression->setText("Initial Expression\n" + ConcentrationUnits);

        if (mpMetab != NULL &&
            (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] == CModelEntity::ASSIGNMENT)
          mpLblExpression->setText("Expression " + ConcentrationUnits);
        else
          mpLblExpression->setText("Expression " + ConcentrationRateUnits);

        mpLblValue->setText("Concentration " + ConcentrationUnits);
        mpLblRate->setText("Rate " + ConcentrationRateUnits);
        mpEditInitialValue->setText(QString::number(mInitialConcentration, 'g', 10));
        mpEditInitialValue->setReadOnly(!mpMetab->isInitialConcentrationChangeAllowed());
        mpEditCurrentValue->setText(QString::number(mpMetab->getConcentration(), 'g', 10));
        mpEditRate->setText(QString::number(mpMetab->getConcentrationRate(), 'g', 10));
        break;

      case 1:
        mpLblInitialValue->setText("Initial Particle Number " + ParticleNumberUnits);
        mpLblInitialExpression->setText("Initial Expression " + ConcentrationUnits);

        if (mpMetab->getStatus() == CModelEntity::ASSIGNMENT)
          mpLblExpression->setText("Expression" + ConcentrationUnits);
        else
          mpLblExpression->setText("Expression" + ConcentrationRateUnits);

        mpLblValue->setText("Particle Number " + ParticleNumberUnits);
        mpLblRate->setText("Rate " + ParticleNumberRateUnits);
        mpEditInitialValue->setText(QString::number(mInitialNumber, 'g', 10));
        mpEditInitialValue->setReadOnly(false);
        mpEditCurrentValue->setText(QString::number(mpMetab->getValue(), 'g', 10));
        mpEditRate->setText(QString::number(mpMetab->getRate(), 'g', 10));
        break;
    }
}

bool CQSpeciesDetail::enterProtected()
{
  mpMetab = dynamic_cast< CMetab * >(mpObject);

  if (!mpMetab)
    {
      mpListView->switchToOtherWidget(112, "");
      return false;
    }

  load();
  return true;
}

void CQSpeciesDetail::load()
{
  if (mpMetab == NULL) return;

  const CModel *pModel = NULL;

  if (mpMetab)
    pModel = mpMetab->getModel();

  std::string TimeUnit = (pModel != NULL) ? CUnit::prettyPrint(pModel->getTimeUnit()) : "?";
  QString TimeUnits = " [" + FROM_UTF8(TimeUnit) + "]";
  // Update the labels to reflect the model units
  mpLblTransitionTime->setText("Transition Time " + TimeUnits);
  // Compartment
  const CCopasiVectorNS< CCompartment > &Compartments = pModel->getCompartments();
  const CCompartment *pCompartment;
  mpComboBoxCompartment->clear();
  mpComboBoxCompartment->setDuplicatesEnabled(false);
  size_t m;

  for (m = 0; m < Compartments.size(); m++)
    {
      pCompartment = &Compartments[m];
      mpComboBoxCompartment->insertItem(mpComboBoxCompartment->count(), FROM_UTF8(pCompartment->getObjectName()));
    }

  mpCurrentCompartment = mpMetab->getCompartment();
  mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(mpCurrentCompartment->getObjectName())));
  // Simulation Type
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mpMetab->getStatus()])));
  // Initial Concentration handled in slotTypeChanged
  mInitialConcentration = mpMetab->getInitialConcentration();
  // Initial Number handled in slotTypeChanged
  mInitialNumber = mpMetab->getInitialValue();
  // Transition Time
  mpEditTransitionTime->setText(QString::number(mpMetab->getTransitionTime(), 'g', 10));
  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpMetab->getExpression());
  mpExpressionEMW->updateWidget();
  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpMetab->getInitialExpression());
  mpInitialExpressionEMW->updateWidget();
  // Noise Expression
  mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpMetab->getNoiseExpression());
  mpNoiseExpressionWidget->updateWidget();
  mpBoxAddNoise->setChecked(mpMetab->hasNoise());
  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentIndex());

  // Use Initial Expression
  if (mpMetab->getStatus() == CModelEntity::ASSIGNMENT ||
      mpMetab->getInitialExpression() == "")
    {
      mpBoxUseInitialExpression->setChecked(false);
      // slotInitialTypeChanged(false);
    }
  else
    {
      mpBoxUseInitialExpression->setChecked(true);
      // slotInitialTypeChanged(true);
    }

  loadReactionTable();
  mpDependencies->loadFrom(mpObject);
  // Update the units and values accordingly
  setFramework(mFramework);
  mChanged = false;
  return;
}

void CQSpeciesDetail::save()
{
  if (mpMetab == NULL) return;

  CModel *pModel = const_cast< CModel * >(mpMetab->getModel());

  if (pModel == NULL) return;

  mIgnoreUpdates = true;

  // Compartment
  if (mpCurrentCompartment != mpMetab->getCompartment())
    {
      QString Compartment = mpComboBoxCompartment->currentText();;
      std::string CompartmentToRemove = mpMetab->getCompartment()->getObjectName();
      // SpeciesChangeCommand  -> compartment
      mpUndoStack->push(new SpeciesChangeCommand(
                          CCopasiUndoCommand::SPECIES_COMPARTMENT_CHANGE,
                          FROM_UTF8(CompartmentToRemove),
                          Compartment,
                          mpMetab,
                          this
                        ));

      mChanged = true;
    }

  // Type
  if (mpMetab->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()])
    {
      // SpeciesChangeCommand  -> simulation type
      mpUndoStack->push(new SpeciesChangeCommand(
                          CCopasiUndoCommand::SPECIES_SIMULATION_TYPE_CHANGE,
                          (int)mpMetab->getStatus(),
                          mItemToType[mpComboBoxType->currentIndex()],
                          mpMetab,
                          this
                        ));
      mChanged = true;
    }

  // Initial Concentration and Initial Number
  switch (mFramework)
    {
      case 0:
        if (mpMetab->getInitialConcentration() != mInitialConcentration)
          {
            // SpeciesChangeCommand  -> initial concentration
            mpUndoStack->push(new SpeciesChangeCommand(
                                CCopasiUndoCommand::SPECIES_INITAL_CONCENTRATION_CHANGE,
                                mpMetab->getInitialConcentration(),
                                mInitialConcentration,
                                mpMetab,
                                this
                              ));
            mChanged = true;
          }

        break;

      case 1:
        if (mpMetab->getInitialValue() != mInitialNumber)
          {
            // SpeciesChangeCommand  -> initial particle number
            mpUndoStack->push(new SpeciesChangeCommand(
                                CCopasiUndoCommand::SPECIES_INITAL_PARTICLENUMBER_CHANGE,
                                mpMetab->getInitialValue(),
                                mInitialNumber,
                                mpMetab,
                                this
                              ));
            mChanged = true;
          }

        break;
    }

  // Expression
  if (mpMetab->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      // SpeciesChangeCommand  -> expression
      mpUndoStack->push(new SpeciesChangeCommand(
                          CCopasiUndoCommand::SPECIES_EXPRESSION_CHANGE,
                          FROM_UTF8(mpMetab->getExpression()),
                          FROM_UTF8(mpExpressionEMW->mpExpressionWidget->getExpression()),
                          mpMetab,
                          this
                        ));
      mChanged = true;
    }

  // Initial Expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT)
    {
      if (mpBoxUseInitialExpression->isChecked() &&
          mpMetab->getInitialExpression() != (mpInitialExpressionEMW->mpExpressionWidget->getExpression()))
        {
          // SpeciesChangeCommand  -> initial expression
          mpUndoStack->push(new SpeciesChangeCommand(
                              CCopasiUndoCommand::SPECIES_INITIAL_EXPRESSION_CHANGE,
                              FROM_UTF8(mpMetab->getInitialExpression()),
                              FROM_UTF8(mpInitialExpressionEMW->mpExpressionWidget->getExpression()),
                              mpMetab,
                              this,
                              mpMetab->getInitialValue()
                            ));
          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpMetab->getInitialExpression() != "")
        {
          // SpeciesChangeCommand  -> initial expression
          mpUndoStack->push(new SpeciesChangeCommand(
                              CCopasiUndoCommand::SPECIES_INITIAL_EXPRESSION_CHANGE,
                              FROM_UTF8(mpMetab->getInitialExpression()),
                              QString(""),
                              mpMetab,
                              this,
                              mpMetab->getInitialValue()
                            ));
          mChanged = true;
        }
    }

  // Add Noise
  if (mpMetab->hasNoise() != mpBoxAddNoise->isChecked())
    {
      // SpeciesChangeCommand  -> noise
      mpUndoStack->push(new SpeciesChangeCommand(
                          CCopasiUndoCommand::SPECIES_ADD_NOISE_CHANGE,
                          mpMetab->hasNoise(),
                          mpBoxAddNoise->isChecked(),
                          mpMetab,
                          this
                        ));
      mChanged = true;
    }

  // Noise Expression
  if (mpMetab->getNoiseExpression() != mpNoiseExpressionWidget->mpExpressionWidget->getExpression())
    {
      // SpeciesChangeCommand  -> noise expression
      mpUndoStack->push(new SpeciesChangeCommand(
                          CCopasiUndoCommand::SPECIES_NOISE_EXPRESSION_CHANGE,
                          FROM_UTF8(mpMetab->getNoiseExpression()),
                          FROM_UTF8(mpNoiseExpressionWidget->mpExpressionWidget->getExpression()),
                          mpMetab,
                          this
                        ));
      mChanged = true;
    }

  mIgnoreUpdates = false;

  if (mChanged)
    {
      if (mpDataModel)
        mpDataModel->changed();

      protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, mKey);

      // Reload the initial value.
      mInitialConcentration = mpMetab->getInitialConcentration();
      mInitialNumber = mpMetab->getInitialValue();
    }

  mChanged = false;
}

void CQSpeciesDetail::loadReactionTable()
{
  if (mpMetab == NULL) return;

  CModel *pModel = const_cast< CModel * >(mpMetab->getModel());

  if (pModel == NULL) return;

  std::set< const CCopasiObject * > Reactions;
  pModel->appendDependentReactions(mpMetab->getDeletedObjects(), Reactions);
  mpReactionTable->setRowCount((int) Reactions.size());
  mpReactionTable->setSortingEnabled(false);
  std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
  std::set< const CCopasiObject * >::const_iterator end = Reactions.end();
  int i = 0;
  const CReaction *pReaction;

  for (; it != end; ++it, ++i)
    {
      pReaction = static_cast< const CReaction * >(*it);
      mpReactionTable->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(pReaction->getObjectName()) + ":"));
      mpReactionTable->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CChemEqInterface::getChemEqString(pModel, *pReaction, false))));
    }

  if (i == 0)
    mpReactionTable->setItem(i, 0, new QTableWidgetItem("none"));

  mpReactionTable->setSortingEnabled(true);
  // Provide count of reactions, in label.
  mpLblReactions->setText("Involved in \n" + QString::number(mpReactionTable->rowCount()) + " Reactions");
  return;
}

void CQSpeciesDetail::slotBtnDelete()
{
  mpUndoStack->push(new DeleteSpeciesCommand(this));
}

void CQSpeciesDetail::copy()
{
  if (mpMetab == NULL) return;

  CModel *pModel = NULL;

  if (mpMetab) pModel = mpDataModel->getModel();

  if (pModel == NULL) return; // for getting compartments and initializing cModelExpObj

  // Create and customize compartment choices dialog
  CQNameSelectionDialog *pDialog = new CQNameSelectionDialog(this);
  pDialog->setWindowTitle("Choose a compartment");
  pDialog->mpLblName->setText("compartment");
  pDialog->mpSelectionBox->clear();
  pDialog->mpSelectionBox->setDuplicatesEnabled(false);
  pDialog->mpSelectionBox->setEditable(false); // at least for now, unless we want to add new compartment creation here.
  // Use CModelExpansion for duplication
  CModelExpansion cModelExpObj = CModelExpansion(pModel);
  CModelExpansion::SetOfModelElements sourceObjects;
  CModelExpansion::ElementsMap origToCopyMapping;
  // for comboBox compartment list and setting compartment
  CCopasiVectorNS< CCompartment > &Compartments = pModel->getCompartments();
  CCopasiVectorN< CCompartment >::const_iterator it = Compartments.begin();
  CCopasiVectorN< CCompartment >::const_iterator end = Compartments.end();
  QStringList SelectionList;

  // Collect and load list of compartment names in comboBox
  for (; it != end; ++it)
    {
      SelectionList.append(FROM_UTF8(it->getObjectName()));
    }

  pDialog->setSelectionList(SelectionList);
  //Set the current compartment as the default
  mpCurrentCompartment = mpMetab->getCompartment();
  // to use here, and for testing if compartment changed after executing the dialog
  int origCompartmentIndex = pDialog->mpSelectionBox->findText(FROM_UTF8(mpCurrentCompartment->getObjectName()));
  pDialog->mpSelectionBox->setCurrentIndex(origCompartmentIndex);
  it = Compartments.begin(); // Reuse Compartments iterator to set compartment choice

  if (pDialog->exec() != QDialog::Rejected)
    {
      // Put species in different compartment (without name modification) by making
      // duplicateMetab think the other compartment was duplicated from the original
      if (origCompartmentIndex != pDialog->mpSelectionBox->currentIndex())
        {
          sourceObjects.addCompartment(mpMetab->getCompartment());
          origToCopyMapping.add(mpMetab->getCompartment(), (it + pDialog->mpSelectionBox->currentIndex()).constCast());
        }

      sourceObjects.addMetab(mpMetab);
      cModelExpObj.duplicateMetab(mpMetab, "_copy", sourceObjects, origToCopyMapping);
      protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");//Refresh all
      protectedNotify(ListViews::METABOLITE, ListViews::DELETE, ""); //Refresh all
      protectedNotify(ListViews::REACTION, ListViews::DELETE, "");   //Refresh all
      mpListView->switchToOtherWidget(C_INVALID_INDEX, origToCopyMapping.getDuplicateKey(mKey));
    }

  pdelete(pDialog);
}

CMetab * CQSpeciesDetail::getCurrentMetab()
{
  return mpMetab;
}

void CQSpeciesDetail::slotBtnNew()
{
  mpUndoStack->push(new CreateNewSpeciesCommand(this));
}

void CQSpeciesDetail::slotBtnCopy() {}

void CQSpeciesDetail::slotCompartmentChanged(int compartment)
{
  if (!mpMetab || !mpCurrentCompartment) return;

  const CModel *pModel = mpMetab->getModel();

  if (pModel == NULL)
    return;

  QString Compartment = mpComboBoxCompartment->itemText(compartment);
  const CCompartment *pNewCompartment =
    &pModel->getCompartments()[TO_UTF8(Compartment)];

  if (pNewCompartment == mpCurrentCompartment ||
      pNewCompartment == NULL) return;

  mInitialNumber *= pNewCompartment->getInitialValue() / mpCurrentCompartment->getInitialValue();

  if (mFramework == 1)
    mpEditInitialValue->setText(QString::number(mInitialNumber, 'g', 10));

  mpCurrentCompartment = pNewCompartment;
  // Update the units and values accordingly
  setFramework(mFramework);
}

void CQSpeciesDetail::slotInitialTypeChanged(bool useInitialExpression)
{
  if (useInitialExpression)
    {
      mpLblInitialExpression->show();
      mpInitialExpressionEMW->show();
      mpEditInitialValue->setEnabled(false);
      mpInitialExpressionEMW->updateWidget();
    }
  else
    {
      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();
      mpEditInitialValue->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT);
    }
}

void CQSpeciesDetail::slotAddNoiseChanged(bool hasNoise)
{
  if (hasNoise)
    {
      if (mpMetab != NULL &&
          mpMetab->getNoiseExpression().empty())
        {
          mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpMetab->getDefaultNoiseExpression());
        }

      mpLblNoiseExpression->show();
      mpNoiseExpressionWidget->show();
      mpNoiseExpressionWidget->updateWidget();
    }
  else
    {
      mpLblNoiseExpression->hide();
      mpNoiseExpressionWidget->hide();
    }
}

void CQSpeciesDetail::slotInitialValueLostFocus()
{
  // no need to track this for undo this is for display
  // purposes only
  speciesInitialValueLostFocus();
  //mpUndoStack->push(new SpeciesInitialValueLostFocusCommand(this));
}

void CQSpeciesDetail::slotNameLostFocus()
{}

void CQSpeciesDetail::slotSwitchToReaction(int row, int /* column */)
{
  if (mpMetab == NULL) return;

  const CModel *pModel = mpMetab->getModel();

  if (pModel == NULL) return;

  std::set< const CCopasiObject * > Reactions;
  pModel->appendDependentReactions(mpMetab->getDeletedObjects(), Reactions);
  std::string s1, s2;
  s1 = TO_UTF8(mpReactionTable->item(row, 0)->text());
  s1 = s1.substr(0, s1.length() - 1);
  C_INT32 i = 0;
  std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
  std::set< const CCopasiObject * >::const_iterator end = Reactions.end();
  const CReaction *pReaction;

  for (; it != end; ++it, ++i)
    {
      pReaction = static_cast< const CReaction * >(*it);
      s2 = pReaction->getObjectName();

      if (s1 == s2)
        mpListView->switchToOtherWidget(C_INVALID_INDEX, pReaction->getKey());
    }
}

void CQSpeciesDetail::slotTypeChanged(int type)
{
  if (mItemToType[type] == mpMetab->getStatus())
    {
      speciesTypeChanged(type);
    }
  else
    {
      mpUndoStack->push(new SpeciesTypeChangeCommand(mItemToType[type], mpMetab->getStatus(), this));
    }
}

//Undo methods
void CQSpeciesDetail::createNewSpecies()
{
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();
  assert(pModel != NULL);
  leave();

  if (pModel->getCompartments().size() == 0)
    pModel->createCompartment("compartment");

  std::string name = "species_1";
  int i = 1;

  while (!(mpMetab = pModel->createMetabolite(name, "", 1.0, CModelEntity::REACTIONS)))
    {
      i++;
      name = "species_";
      name += TO_UTF8(QString::number(i));
    }

  switch (mFramework)
    {
      case 0:
        mpMetab->setInitialConcentration(1.0);
        break;

      case 1:
        mpMetab->setInitialValue(100.0);
        break;
    }

  std::string key = mpMetab->getKey();
  protectedNotify(ListViews::METABOLITE, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQSpeciesDetail::deleteSpecies()
{
  if (mpMetab == NULL) return;

  CModel *pModel = const_cast< CModel *>(mpMetab->getModel());

  if (pModel == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "species",
                                FROM_UTF8(mpMetab->getObjectName()),
                                mpMetab->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        pModel->removeMetabolite(mKey);
#undef DELETE
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, mKey);
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        //TODO notify about reactions
        break;
      }

      default:
        break;
    }

  mpListView->switchToOtherWidget(CCopasiUndoCommand::SPECIES, "");
}

void CQSpeciesDetail::deleteSpecies(UndoSpeciesData *pSData)
{
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();
  assert(pModel != NULL);
  switchToWidget(CCopasiUndoCommand::SPECIES);
  CMetab *pSpecies = dynamic_cast< CMetab * >(pSData->getObject(pModel));

  if (pSpecies == NULL) return;

  std::string key = pSpecies->getKey();
  pModel->removeMetabolite(key);
#undef DELETE
  protectedNotify(ListViews::METABOLITE, ListViews::DELETE, key); //mKey);
  protectedNotify(ListViews::METABOLITE, ListViews::DELETE, "");//Refresh all as there may be dependencies.
}

void CQSpeciesDetail::addSpecies(UndoSpeciesData *pSData)
{
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();
  assert(pModel != NULL);
  //reinsert the species
  CCopasiObject *pSpecies =  pSData->restoreObjectIn(pModel);

  if (pSpecies == NULL)
    return;

  std::string key = pSpecies->getKey();
  protectedNotify(ListViews::METABOLITE, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQSpeciesDetail::speciesTypeChanged(int type)
{
  switch ((CModelEntity::Status) mItemToType[type])
    {
      case CModelEntity::FIXED:
        mpLblExpression->hide();
        mpExpressionEMW->hide();
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);
        break;

      case CModelEntity::ASSIGNMENT:
        mpLblExpression->show();
        mpExpressionEMW->show();
        mpBoxUseInitialExpression->setEnabled(false);
        slotInitialTypeChanged(false);
        mpExpressionEMW->updateWidget();
        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);
        break;

      case CModelEntity::ODE:
        mpLblExpression->show();
        mpExpressionEMW->show();
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        mpExpressionEMW->updateWidget();
#ifdef WITH_SDE_SUPPORT
        mpBoxAddNoise->show();
        slotAddNoiseChanged(mpBoxAddNoise->isChecked());
#else
        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);
#endif
        break;

      case CModelEntity::REACTIONS:
        mpLblExpression->hide();
        mpExpressionEMW->hide();
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);
        break;

      default:
        break;
    }

  // This will update the unit display.
  setFramework(mFramework);
}

void CQSpeciesDetail::speciesTypeChanged(UndoSpeciesData *pSData, int type)
{
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();
  assert(pModel != NULL);
  //find the species of interest and switch to its widget
  CMetab *pSpecie = pModel->findMetabByName(pSData->getName());

  if (pSpecie != NULL)
    {
      std::string key = pSpecie->getKey();
      mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
    }

  //set the species index
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[type])));
  mpMetab->setStatus((CModelEntity::Status)mItemToType[mpComboBoxType->currentIndex()]);
  speciesTypeChanged(mpComboBoxType->currentIndex());
}

void CQSpeciesDetail::speciesInitialValueLostFocus()
{
  if (!mpMetab || !mpCurrentCompartment) return;

  const CModel *pModel = mpMetab->getModel();

  if (pModel == NULL)
    return;

  switch (mFramework)
    {
      case 0:
        if (QString::number(mInitialConcentration, 'g', 10) == mpEditInitialValue->text())
          return;

        mInitialConcentration = mpEditInitialValue->text().toDouble();
        mInitialNumber = CMetab::convertToNumber(mInitialConcentration,
                         *mpCurrentCompartment,
                         *pModel);
        break;

      case 1:
        if (QString::number(mInitialNumber, 'g', 10) == mpEditInitialValue->text())
          return;

        mInitialNumber = mpEditInitialValue->text().toDouble();
        mInitialConcentration = CMetab::convertToConcentration(mInitialNumber,
                                *mpCurrentCompartment,
                                *pModel);
        break;
    }
}

void CQSpeciesDetail::speciesInitialValueLostFocus(UndoSpeciesData *pSData)
{
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();
  assert(pModel != NULL);
  //find the species of interest and switch to its widget
  CMetab *pSpecie = pModel->findMetabByName(pSData->getName());

  if (pSpecie != NULL)
    {
      std::string key = pSpecie->getKey();
      mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
    }

  switch (mFramework)
    {
      case 0:
        mInitialConcentration = pSData->getIConc();
        pSData->setIConc(mpEditInitialValue->text().toDouble());
        mpEditInitialValue->setText(QString::number(mInitialConcentration, 'g', 10));
        break;

      case 1:
        mInitialNumber = pSData->getINumber();
        pSData->setINumber(mpEditInitialValue->text().toDouble());
        mpEditInitialValue->setText(QString::number(mInitialNumber, 'g', 10));
        break;
    }
}

bool CQSpeciesDetail::changeValue(
  const std::string & key,
  CCopasiUndoCommand::Type type,
  const QVariant & newValue,
  double iValue)
{
  if (!mIgnoreUpdates)
    {
      mpObject = CCopasiRootContainer::getKeyFactory()->get(key);
      mpMetab = dynamic_cast<CMetab*>(mpObject);
      load();
    }

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);

  CModel* pModel = mpMetab->getModel();

  switch (type)
    {
      case CCopasiUndoCommand::SPECIES_COMPARTMENT_CHANGE:
      {
        QString Compartment = newValue.toString();
        std::string CompartmentToRemove = mpMetab->getCompartment()->getObjectName();

        if (!pModel->getCompartments()[TO_UTF8(Compartment)].addMetabolite(mpMetab))
          {
            QString msg;
            msg = "Unable to move species '" + FROM_UTF8(mpMetab->getObjectName()) + "'\n"
                  + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + Compartment + "'\n"
                  + "since a species with that name already exist in the target compartment.";
            CQMessageBox::information(this,
                                      "Unable to move Species",
                                      msg,
                                      QMessageBox::Ok, QMessageBox::Ok);
            // Revert the changes
            mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(CompartmentToRemove)));
            slotCompartmentChanged(mpComboBoxCompartment->currentIndex());
          }
        else
          {
            pModel->getCompartments()[CompartmentToRemove].getMetabolites().remove(mpMetab->getObjectName());
            pModel->setCompileFlag();
            pModel->initializeMetabolites();
            protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
          }

        break;
      }

      case CCopasiUndoCommand::SPECIES_EXPRESSION_CHANGE:
        mpMetab->setExpression(TO_UTF8(newValue.toString()));
        break;

      case CCopasiUndoCommand::SPECIES_INITAL_PARTICLENUMBER_CHANGE:
        mpMetab->setInitialValue(newValue.toDouble());
        break;

      case CCopasiUndoCommand::SPECIES_INITAL_CONCENTRATION_CHANGE:
        mpMetab->setInitialConcentration(newValue.toDouble());
        break;

      case CCopasiUndoCommand::SPECIES_INITIAL_EXPRESSION_CHANGE:
        mpMetab->setInitialExpression(TO_UTF8(newValue.toString()));

        if (newValue.toString().isEmpty())
          mpMetab->setInitialValue(iValue);

        break;

      case CCopasiUndoCommand::SPECIES_SIMULATION_TYPE_CHANGE:
        mpMetab->setStatus((CModelEntity::Status) newValue.toInt());
        break;

      case CCopasiUndoCommand::SPECIES_ADD_NOISE_CHANGE:
        mpMetab->setHasNoise(newValue.toBool());
        break;

      case CCopasiUndoCommand::SPECIES_NOISE_EXPRESSION_CHANGE:
        mpMetab->setNoiseExpression(TO_UTF8(newValue.toString()));
        break;

      default:
        return false;
    }

  if (mIgnoreUpdates) return true;

  assert(mpDataModel != NULL);
  mpDataModel->changed();
  protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, mKey);

  load();

  return true;
}
