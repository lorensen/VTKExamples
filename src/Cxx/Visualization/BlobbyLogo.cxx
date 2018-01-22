//
// use implicit modeller to create the VTK logo
//

#include <vtkActor.h>
#include <vtkAppendPolyData.h>
#include <vtkContourFilter.h>
#include <vtkImplicitModeller.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

int main( int argc, char *argv[] )
{
  if (argc < 4)
  {
    std::cout << "Usage: " << argv[0] << " v.vtk t.vtk k.vtk" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkRenderer> aRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> aRenderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  aRenderWindow->AddRenderer(aRenderer);
  vtkSmartPointer<vtkRenderWindowInteractor> anInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  anInteractor->SetRenderWindow(aRenderWindow);
  aRenderWindow->SetSize( 300, 300 );

  // read the geometry file containing the letter v
  vtkSmartPointer<vtkPolyDataReader> letterV =
    vtkSmartPointer<vtkPolyDataReader>::New();
  letterV->SetFileName (argv[1]);

  // read the geometry file containing the letter t
  vtkSmartPointer<vtkPolyDataReader> letterT =
    vtkSmartPointer<vtkPolyDataReader>::New();
  letterT->SetFileName (argv[2]);

  // read the geometry file containing the letter k
  vtkSmartPointer<vtkPolyDataReader> letterK =
    vtkSmartPointer<vtkPolyDataReader>::New();
  letterK->SetFileName (argv[3]);

  // create a transform and transform filter for each letter
  vtkSmartPointer<vtkTransform> VTransform =
    vtkSmartPointer<vtkTransform>::New();
  vtkSmartPointer<vtkTransformPolyDataFilter> VTransformFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  VTransformFilter->SetInputConnection(letterV->GetOutputPort());
  VTransformFilter->SetTransform (VTransform);

  vtkSmartPointer<vtkTransform> TTransform =
    vtkSmartPointer<vtkTransform>::New();
  vtkSmartPointer<vtkTransformPolyDataFilter> TTransformFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  TTransformFilter->SetInputConnection (letterT->GetOutputPort());
  TTransformFilter->SetTransform (TTransform);

  vtkSmartPointer<vtkTransform> KTransform =
    vtkSmartPointer<vtkTransform>::New();
  vtkSmartPointer<vtkTransformPolyDataFilter> KTransformFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  KTransformFilter->SetInputConnection(letterK->GetOutputPort());
  KTransformFilter->SetTransform (KTransform);

  // now append them all
  vtkSmartPointer<vtkAppendPolyData> appendAll =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendAll->AddInputConnection (VTransformFilter->GetOutputPort());
  appendAll->AddInputConnection (TTransformFilter->GetOutputPort());
  appendAll->AddInputConnection (KTransformFilter->GetOutputPort());

  // create normals
  vtkSmartPointer<vtkPolyDataNormals> logoNormals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  logoNormals->SetInputConnection (appendAll->GetOutputPort());
  logoNormals->SetFeatureAngle (60);

  // map to rendering primitives
  vtkSmartPointer<vtkPolyDataMapper> logoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  logoMapper->SetInputConnection (logoNormals->GetOutputPort());

  // now an actor
  vtkSmartPointer<vtkActor> logo =
    vtkSmartPointer<vtkActor>::New();
  logo->SetMapper (logoMapper);

  // now create an implicit model of the same letter
  vtkSmartPointer<vtkImplicitModeller> blobbyLogoImp =
    vtkSmartPointer<vtkImplicitModeller>::New();
  blobbyLogoImp->SetInputConnection(appendAll->GetOutputPort());
  blobbyLogoImp->SetMaximumDistance (.075);
  blobbyLogoImp->SetSampleDimensions (64,64,64); 
  blobbyLogoImp->SetAdjustDistance (0.05);

  // extract an iso surface
  vtkSmartPointer<vtkContourFilter> blobbyLogoIso =
    vtkSmartPointer<vtkContourFilter>::New();
  blobbyLogoIso->SetInputConnection (blobbyLogoImp->GetOutputPort());
  blobbyLogoIso->SetValue (1, 1.5);

  // map to rendering primitives
  vtkSmartPointer<vtkPolyDataMapper> blobbyLogoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  blobbyLogoMapper->SetInputConnection (blobbyLogoIso->GetOutputPort());
  blobbyLogoMapper->ScalarVisibilityOff ();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkProperty> tomato =
    vtkSmartPointer<vtkProperty>::New();
  tomato->SetDiffuseColor(colors->GetColor3d("tomato").GetData());
  tomato->SetSpecular(.3);
  tomato->SetSpecularPower(20);

  vtkSmartPointer<vtkProperty> banana =
    vtkSmartPointer<vtkProperty>::New();
  banana->SetDiffuseColor(colors->GetColor3d("banana").GetData());
  banana->SetDiffuse (.7);
  banana->SetSpecular(.4);
  banana->SetSpecularPower(20);

  // now an actor
  vtkSmartPointer<vtkActor> blobbyLogo =
    vtkSmartPointer<vtkActor>::New();
  blobbyLogo->SetMapper (blobbyLogoMapper);
  blobbyLogo->SetProperty (banana);

  // position the letters

  VTransform->Translate (-16.0,0.0,12.5);
  VTransform->RotateY (40);

  KTransform->Translate (14.0, 0.0, 0.0);
  KTransform->RotateY (-40);

  // move the polygonal letters to the front
  logo->SetProperty (tomato);
  logo->SetPosition(0,0,6);
  
  aRenderer->AddActor(logo);
  aRenderer->AddActor(blobbyLogo);

  aRenderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  aRenderWindow->Render();

  // interact with data
  anInteractor->Start();

  return EXIT_SUCCESS;
}
