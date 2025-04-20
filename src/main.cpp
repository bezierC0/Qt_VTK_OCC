#include "MainWindow.h"
#include <QVTKOpenGLNativeWidget.h>
#include <QApplication>
#include <QVBoxLayout>
#include <QtWidgets>
#include "VtkOccView.h"


int main( int argc, char* argv[] )
{
  QSurfaceFormat::setDefaultFormat( QVTKOpenGLNativeWidget::defaultFormat() );

  QApplication application( argc, argv );

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
