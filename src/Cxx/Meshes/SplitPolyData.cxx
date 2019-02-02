#include <vtkSmartPointer.h>

#include <vtkOBBDicer.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkThreshold.h>
#include <vtkGeometryFilter.h>

#include <vtkNamedColors.h>
#include <vtkColorSeries.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>

#include <vtksys/SystemTools.hxx>
#include <sstream>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  std::string filename;
  std::string extension;

  vtkSmartPointer<vtkPolyData> inputPolyData = ReadPolyData(argc > 1 ? argv[1] : "");;
  if(argc > 1)
  {
    filename = vtksys::SystemTools::GetFilenameWithoutExtension(std::string(argv[1]));
    extension = vtksys::SystemTools::GetFilenameExtension(std::string(argv[1]));
  }
  else
  {
    filename = "sphere";
    extension = ".vtp";
  }

  // Create pipeline
  vtkSmartPointer<vtkOBBDicer> dicer =
  vtkSmartPointer<vtkOBBDicer>::New();
  dicer->SetInputData(inputPolyData);
  dicer->SetNumberOfPieces(4);
  dicer->SetDiceModeToSpecifiedNumberOfPieces();
  dicer->Update();

  vtkSmartPointer<vtkThreshold> selector =
    vtkSmartPointer<vtkThreshold>::New();
  selector->SetInputArrayToProcess(0, 0, 0, 0, "vtkOBBDicer_GroupIds");
  selector->SetInputConnection(dicer->GetOutputPort());
  selector->AllScalarsOff();

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(namedColors->GetColor3d("NavajoWhite").GetData());

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);
  renWin->SetSize(512, 512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Use a color series to create a transfer function
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_DIVERGING_SPECTRAL_11);

  // Create an actor for each piece
  for (int i = 0; i < dicer->GetNumberOfActualPieces(); ++i)
  {
    selector->ThresholdBetween(i, i);
    vtkSmartPointer<vtkGeometryFilter> geometry =
      vtkSmartPointer<vtkGeometryFilter>::New();
    geometry->SetInputConnection(selector->GetOutputPort());
    geometry->Update();

    vtkSmartPointer<vtkDataSetMapper> mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(geometry->GetOutput());
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkColor3ub color = colorSeries->GetColor(i);
    double dColor[3];
    dColor[0] = static_cast<double> (color[0]) / 255.0;
    dColor[1] = static_cast<double> (color[1]) / 255.0;
    dColor[2] = static_cast<double> (color[2]) / 255.0;
    actor->GetProperty()->SetColor(dColor);
    renderer->AddActor(actor);
  }
  renWin->Render();
  iren->Initialize();
  iren->Start();

  vtkSmartPointer<vtkGeometryFilter> geometry =
    vtkSmartPointer<vtkGeometryFilter>::New();
  geometry->SetInputConnection(selector->GetOutputPort());

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(geometry->GetOutputPort());
  for (int i = 0; i < dicer->GetNumberOfActualPieces(); ++i)
  {
    std::stringstream pieceName;
    pieceName << filename << "_" << i + 1 << extension;
    selector->ThresholdBetween(i, i);
    writer->SetFileName(pieceName.str().c_str());
    writer->Write();
  }
  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
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
    vtkSmartPointer<vtkSphereSource> source =
      vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
}
