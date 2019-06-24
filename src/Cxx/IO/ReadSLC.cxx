#include <vtkSmartPointer.h>
#include <vtkSLCReader.h>

#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContourFilter.h>
#include <vtkProperty.h>
#include <vtkExtractVOI.h>
#include <vtkOutlineFilter.h>
#include <vtkNamedColors.h>


//Author: Bharatesh Chakravarthi 
//Affiliation: Virtual Environment Lab, Chung-Ang University, Seoul, South Korea

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    //Pass the filename (<filename>.slc) as parameter to read .slc file 
    std::cout << "Required parameters: Filename(.slc) e.g vw_knee.slc" << std::endl;
    return EXIT_FAILURE;
  }

  double isoValue = 72.0;
  if (argc < 3)
  {
    isoValue = 72.0;
  }
  else
  {
    isoValue = std::atof(argv[2]);
  }
  std::string inputFilename = argv[1];
 	
  //Using vtkSLCReader to read Volumetric file format(<filename.slc>) 
  vtkSmartPointer<vtkSLCReader> reader =
    vtkSmartPointer<vtkSLCReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
 	
  // Implementing Marching Cubes Algorithm to create the surface using
  // vtkContourFilter object 
  vtkSmartPointer<vtkContourFilter> cFilter =
    vtkSmartPointer<vtkContourFilter>::New();
  cFilter->SetInputConnection(reader->GetOutputPort());
	
  // Change the range(2nd and 3rd Paramater) based on your
  // requirement. recomended value for 1st parameter is above 1
//  cFilter->GenerateValues(5, 80.0, 100.0); 
  cFilter->SetValue(0, isoValue);
  cFilter->Update();
 	
  //Adding the outliner using vtkOutlineFilter object
  vtkSmartPointer<vtkOutlineFilter> outliner =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outliner->SetInputConnection(reader->GetOutputPort());
  outliner->Update();
 	
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cFilter->GetOutputPort());
  mapper->SetScalarVisibility(0);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuse(.8);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Ivory").GetData());
  actor->GetProperty()->SetSpecular(.8);
  actor->GetProperty()->SetSpecularPower(120.0);

  //extractVOI is used to fix the problem of subsampling of data and reduce slow interaction and increase loading speed
  vtkSmartPointer<vtkExtractVOI> extractVOI =
    vtkSmartPointer<vtkExtractVOI>::New();
  extractVOI->SetInputConnection(reader->GetOutputPort());
  extractVOI->SetSampleRate(2, 2, 2);
  extractVOI->Update();
 	
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 512);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor
    = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderWindow->Render();

  // Pick a good view
  vtkCamera *cam1 = renderer->GetActiveCamera();
  cam1->SetFocalPoint(0.0, 0.0, 0.0);
  cam1->SetPosition(0.0, -1.0, 0.0);
  cam1->SetViewUp(0.0, 0.0, -1.0);
  cam1->Azimuth(30.0);
  renderer->ResetCamera();
  renderer->ResetCameraClippingRange();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
