#ifndef VTKOCCVIEW_H
#define VTKOCCVIEW_H

#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>

#include <vtkSmartPointer.h>

class TopoDS_Shape;

class vtkRenderer;
class vtkGenericOpenGLRenderWindow;
class vtkOrientationMarkerWidget;

class VtkOccView : public QVTKOpenGLNativeWidget
{
    Q_OBJECT

public:
    explicit VtkOccView( QWidget*parent = nullptr);
    ~VtkOccView();

    void displayShape(const TopoDS_Shape &shape);

    QSize minimumSizeHint() const override; 


public slots:
    bool readVTKFile();

private:
    void initialize();
    void createTestCube();
    
    //QVTKOpenGLWidget* m_vtkWidget;  
    vtkSmartPointer<vtkRenderer> m_pRenderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
    //vtkSmartPointer<vtkOrientationMarkerWidget> widget;

};

#endif // VTKOCCVIEW_H