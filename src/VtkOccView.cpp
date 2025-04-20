#include "VtkOccView.h"
#include <QVBoxLayout>

#include <STEPControl_Reader.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <Poly_Triangulation.hxx>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkDataSet.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkCubeSource.h>
#include <vtkCellArray.h>

#include <qaction.h>


#include <vtkCaptionActor2D.h>
#include <vtkTextRepresentation.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkDataSetReader.h>


VtkOccView::VtkOccView( QWidget* parent )
  :QVTKOpenGLNativeWidget( parent )
{
  vtkNew<vtkGenericOpenGLRenderWindow> window;
  QVTKOpenGLNativeWidget::setRenderWindow( window );

  m_pRenderer = vtkSmartPointer<vtkRenderer>::New();
  m_pRenderer->SetGradientBackground( true );
  m_pRenderer->SetBackground2( 0.4, 0.5, 0.6 );
  m_pRenderer->SetBackground( 0.2, 0.3, 0.4 );

  QVTKOpenGLNativeWidget::renderWindow()->AddRenderer( m_pRenderer );
  vtkMapper::SetResolveCoincidentTopologyToPolygonOffset();

  createTestCube(); 
}

VtkOccView::~VtkOccView()
{

}

void VtkOccView::initialize()
{
  m_pRenderer->SetBackground( 0.2, 0.3, 0.4 );
  m_pRenderer->ResetCamera();
}

void VtkOccView::createTestCube()
{
  //vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
  //cubeSource->SetXLength( 10.0 );
  //cubeSource->SetYLength( 10.0 );
  //cubeSource->SetZLength( 10.0 );
  //cubeSource->Update();

  auto reader = vtkSmartPointer<vtkDataSetReader>::New();
  reader->SetFileName(R"(C:\Download\Data\Data\Data\fran_cut.vtk)");
  
  reader->Update();
  

  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( reader->GetOutputPort() );


  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );


  m_pRenderer->AddActor( actor );
  m_pRenderer->ResetCamera();

  //TopoDS_Shape cube1 = BRepPrimAPI_MakeBox( { -20 ,-20, -10 }, 10.0, 10.0, 10.0 ).Shape();
  //TopoDS_Shape cube2 = BRepPrimAPI_MakeBox( { 20 ,20, 20 }, 10.0, 20, 10.0 ).Shape();
  //displayShape( cube1 );
  //displayShape( cube2 );

  STEPControl_Reader stepReader;
  IFSelect_ReturnStatus status = stepReader.ReadFile( R"(C:\Libs\OCCT-7.7.0-vc14-64\opencascade-7.7.0\data\step\linkrods.step)" );

  if ( status == IFSelect_RetDone ) {
    bool fail = false;

    if ( stepReader.TransferRoots() == 0 ) {
      std::cerr << "\n";
      fail = true;
    }

    if ( !fail ) {
      TopoDS_Shape importedShape = stepReader.OneShape();
      displayShape( importedShape );
    }
  }
  else {
    std::cerr << "\n";
}



}

#if 0
void VtkOccView::displayShape( const TopoDS_Shape& shape )
{
  auto occSource = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
  occSource->SetShape( new IVtkOCC_Shape( shape ) );

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( occSource->GetOutputPort() );

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );
  //actor->GetProperty()->SetColor( 0.8, 0.5, 0.3 );

  m_pRenderer->AddActor( actor );
  m_pRenderer->ResetCamera();
  m_renderWindow->Render();
}
#endif

void VtkOccView::displayShape( const TopoDS_Shape& shape )
{
  BRepMesh_IncrementalMesh mesher( shape, 0.1 ); 

  auto points = vtkSmartPointer<vtkPoints>::New();
  auto polys = vtkSmartPointer<vtkCellArray>::New();

  std::map<gp_Pnt, vtkIdType, bool( * )( const gp_Pnt&, const gp_Pnt& )> pointMap(
    []( const gp_Pnt& a, const gp_Pnt& b ) {
    if ( a.X() != b.X() ) return a.X() < b.X();
    if ( a.Y() != b.Y() ) return a.Y() < b.Y();
    return a.Z() < b.Z();
  }
  );

  for ( TopExp_Explorer faceExp( shape, TopAbs_FACE ); faceExp.More(); faceExp.Next() ) {
    TopoDS_Face face = TopoDS::Face( faceExp.Current() );
    TopLoc_Location loc;
    Handle( Poly_Triangulation ) triangulation = BRep_Tool::Triangulation( face, loc );

    if ( triangulation.IsNull() ) continue;

    Standard_Integer nbNodes = triangulation->NbNodes();
    Standard_Integer nbTriangles = triangulation->NbTriangles();
    std::vector<vtkIdType> pointIds( nbNodes + 1 ); // OCC index starts from 1

    for ( Standard_Integer i = 1; i <= nbNodes; ++i ) {
      gp_Pnt pnt = triangulation->Node( i ).Transformed( loc.Transformation() );

      auto it = pointMap.find( pnt );
      if ( it == pointMap.end() ) {
        vtkIdType id = points->InsertNextPoint( pnt.X(), pnt.Y(), pnt.Z() );
        pointMap[pnt] = id;
        pointIds[i] = id;
      }
      else {
        pointIds[i] = it->second;
      }
    }

    for ( Standard_Integer i = 1; i <= nbTriangles; ++i ) {
      Standard_Integer n1, n2, n3;
      triangulation->Triangle( i ).Get( n1, n2, n3 );
      vtkIdType ids[3] = { pointIds[n1], pointIds[n2], pointIds[n3] };
      polys->InsertNextCell( 3, ids );
    }
  }

  auto polyData = vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints( points );
  polyData->SetPolys( polys );

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData( polyData );

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );
  // actor->GetProperty()->SetColor(1.0, 0.5, 0.2); 

  m_pRenderer->AddActor( actor );
  m_pRenderer->ResetCamera();
  //m_renderWindow->Render();
}

QSize VtkOccView::minimumSizeHint() const
{
  return {500, 500};
}

bool VtkOccView::readVTKFile()
{
  return true;
}
