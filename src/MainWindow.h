#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class VtkOccView;
class QVTKOpenGLWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  
  MainWindow( QWidget* parent = nullptr );
  void CreateMainView();
  ~MainWindow();

private:

  VtkOccView* m_view { nullptr };
};

#endif // MAINWINDOW_H