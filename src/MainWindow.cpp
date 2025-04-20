#include "MainWindow.h"

#include <QVBoxLayout>
#include <QGuiApplication>
#include <QScreen>
#include "VtkOccView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  const QScreen* pScreen = QGuiApplication::primaryScreen();
  const QRect rectScreen = pScreen->geometry();
  const int nAppWidth = rectScreen.width() / 2;
  const int nAppHeight = rectScreen.height() / 2;
  const int nAppLocationX = ( rectScreen.width() - nAppWidth ) / 2;
  const int nAppLocationY = ( rectScreen.height() - nAppHeight ) / 2;
  resize( nAppWidth, nAppHeight );
  move( nAppLocationX, nAppLocationY );

  CreateMainView();
}

void MainWindow::CreateMainView()
{
  QWidget* pContainerWidget = new QWidget( this );
  pContainerWidget->setObjectName( "ParasolidSceneWidget" );
  pContainerWidget->setContentsMargins( 2, 2, 2, 2 );
  pContainerWidget->setMinimumWidth( 1 );

  QHBoxLayout* pLayout = new QHBoxLayout( pContainerWidget );
  pLayout->setContentsMargins( 0, 0, 0, 0 );
  pLayout->setSpacing( 0 );

  VtkOccView* pVtkView = new VtkOccView( pContainerWidget );
  pVtkView->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding ); 

  pLayout->addWidget( pVtkView );

  setCentralWidget( pContainerWidget );
}

MainWindow::~MainWindow()
= default;

