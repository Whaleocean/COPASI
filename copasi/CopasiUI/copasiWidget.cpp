// copasiWidget.cpp: implementation of the CopasiWidget class.
//
//////////////////////////////////////////////////////////////////////

#include "copasiWidget.h"
#include "listviews.h"
#include "qvaluelist.h" 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction of CopasiWidget
//////////////////////////////////////////////////////////////////////
int CopasiWidget::realMinHeight = 0;
int CopasiWidget::realMinWidth = 0;

DataModel* CopasiWidget::dataModel = NULL;

CopasiWidget::CopasiWidget(QWidget * parent, const char * name, WFlags f)
    : QWidget (parent, name, f)
{
  pListView = (ListViews*)parent;
  dataModel = ListViews::getDataModel();
  bInitialized = false;
  bSetMinSize = false;
}

void CopasiWidget::resize (int w, int h)
{
  if (!bInitialized)
    {
      bInitialized = true;
      int tmpW = realMinWidth;
      int tmpH = realMinHeight;
      if (minimumSizeHint().width() > realMinWidth)
        realMinWidth = minimumSizeHint().width();
      if (minimumSizeHint().height() > realMinHeight)
        realMinHeight = minimumSizeHint().height();
      if ((tmpW != realMinWidth) || (tmpH != realMinHeight))
        {
          //   ListViews* qParent=(ListViews*)topLevelWidget();
          QValueList<int> list = pListView->sizes();
          pListView->setMinimumSize(realMinWidth + list[0], realMinHeight);
          //   qParent->resize(realMinWidth, realMinHeight);
        }
      return;
    }
  if (!bSetMinSize)
    {
      setMinimumSize(realMinWidth, realMinHeight);
      bSetMinSize = true;
    }
  //after initialization
  //realMinWidth and realMinHeight are set,
  QWidget::resize(w, h);
}

void CopasiWidget::resizeEvent (QResizeEvent * event)
{
  int w = event->size().width();
  int h = event->size().height();
  // ListViews* qParent = (ListViews*)topLevelWidget();
  // QValueList<int> list = pListView->sizes();
  // pListView->setMinimumSize(realMinWidth+list[0], realMinHeight);
  // if ((qParent->size().width()<realMinWidth || qParent->size().height()<realMinHeight))
  //  qParent->setMinimumSize(realMinWidth, realMinHeight);
  resize(w, h);
  // QWidget::resizeEvent (event);
}

bool CopasiWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{return true;}

bool CopasiWidget::leave()
{return true;}

bool CopasiWidget::enter(const std::string & C_UNUSED(key))
{return true;}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction of CopasiParametersWidget
//////////////////////////////////////////////////////////////////////
CopasiParametersWidget::CopasiParametersWidget(QWidget * parent, const char * name, WFlags f)
    : CopasiWidget (parent, name, f)
{}
