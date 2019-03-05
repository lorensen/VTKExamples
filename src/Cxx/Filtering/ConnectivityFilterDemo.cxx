#include <vtkSmartPointer.h>
#include <vtkPolyDataConnectivityFilter.h>

#include <vtkSphereSource.h>
#include <vtkDataSetMapper.h>

#include <vtkLookupTable.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
#include <vtkScalarsToColors.h>
#include <vtkNamedColors.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtksys/SystemTools.hxx>

#include <random>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main(int argc, char*argv[])
{
  vtkSmartPointer<vtkPolyData> polyData =
    ReadPolyData(argc > 1 ? argv[1] : "");

  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter =
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  connectivityFilter->SetInputData(polyData);
  connectivityFilter->SetExtractionModeToAllRegions();
  connectivityFilter->ColorRegionsOn();
  connectivityFilter->Update();

  // Visualize
  int numberOfRegions = connectivityFilter->GetNumberOfExtractedRegions();
  if (argc > 1)
    {
      std::cout << argv[1] << " contains " << numberOfRegions << " regions" << std::endl;
    }
    else
    {
      std::cout << "Generated data" << " contains " << numberOfRegions << " regions" << std::endl;
    }
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetNumberOfTableValues(std::max(numberOfRegions, 10));
  lut->Build();

  // Fill in a few known colors, the rest will be generated if needed
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  lut->SetTableValue(0, colors->GetColor4d("Gold").GetData());
  lut->SetTableValue(1, colors->GetColor4d("Banana").GetData());
  lut->SetTableValue(2, colors->GetColor4d("Tomato").GetData());
  lut->SetTableValue(3, colors->GetColor4d("Wheat").GetData());
  lut->SetTableValue(4, colors->GetColor4d("Lavender").GetData());
  lut->SetTableValue(5, colors->GetColor4d("Flesh").GetData());
  lut->SetTableValue(6, colors->GetColor4d("Raspberry").GetData());
  lut->SetTableValue(7, colors->GetColor4d("Salmon").GetData());
  lut->SetTableValue(8, colors->GetColor4d("Mint").GetData());
  lut->SetTableValue(9, colors->GetColor4d("Peacock").GetData());

  // If the number of regions os larger than the number of specified colors,
  // generate some random colors.
  if (numberOfRegions > 9)
  {
    std::mt19937 mt(4355412); //Standard mersenne_twister_engine
    std::uniform_real_distribution<double> distribution(.6, 1.0);
    for (auto i = 10; i < numberOfRegions; ++i)
    {
      lut->SetTableValue(i, distribution(mt), distribution(mt), distribution(mt), 1.0);
    }
  }
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(connectivityFilter->GetOutputPort());
  mapper->SetScalarRange(0, connectivityFilter->GetNumberOfExtractedRegions() - 1);
  mapper->SetLookupTable(lut);
  mapper->Update();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->UseHiddenLineRemovalOn();
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  // Pick a good view
  renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
  renderer->GetActiveCamera()->SetPosition(0.0, 1.0, 0.0);
  renderer->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Elevation(45.0);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Dolly(1.25);
  renderer->ResetCameraClippingRange();
  renderWindow->Render();

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource1->Update();

    vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource2->SetCenter(5,0,0);
    sphereSource2->Update();

    vtkSmartPointer<vtkAppendPolyData> appendFilter =
      vtkSmartPointer<vtkAppendPolyData>::New();
    appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
    appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
    appendFilter->Update();
    polyData = appendFilter->GetOutput();
  }
  return polyData;
}
}
