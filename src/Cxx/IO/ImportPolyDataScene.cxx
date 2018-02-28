#include <vtkSmartPointer.h>

#include <vtkXMLMultiBlockDataReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkCompositeDataSet.h>
#include <vtkDataObjectTreeIterator.h>

#include <vtkPolyData.h>
#include <vtkFieldData.h>

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>
#include <vtksys/SystemTools.hxx>

namespace
{
void ImportMultiBlockScene(vtkRenderer *renderer, std::string fileName);
void RestoreCameraFromFieldData(std::string, vtkCamera *, vtkPolyData *);
void RestorePropertyFromFieldData(std::string, vtkProperty *, vtkPolyData *);
void RestoreActorFromFieldData(std::string, vtkActor *, vtkPolyData *);
//void RestoreMapperFromFieldData(std::string, vtkPolyDataMapper *, vtkPolyData *);
//void RestoreLookupTableFromFieldData(std::string, vtkScalarsToColors *, vtkPolyData *);
}

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " file.vtp" << std::endl;
    return EXIT_FAILURE;
  }

  // Visualization
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  ImportMultiBlockScene (renderer.GetPointer(),std::string(argv[1]));

  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start(); 

 return EXIT_SUCCESS;
}

namespace
{
void ImportMultiBlockScene(vtkRenderer *renderer, std::string fileName)
{
  vtkCamera *camera = renderer->GetActiveCamera();

  std::string prefix;
  prefix = vtksys::SystemTools::GetFilenameName(fileName);

  // Read the multiblock data
  vtkSmartPointer<vtkXMLMultiBlockDataReader> reader =
    vtkSmartPointer<vtkXMLMultiBlockDataReader>::New();
  reader->SetFileName(fileName.c_str());
  reader->Update();
  std::cout << "NumberOfBlocks: " << vtkMultiBlockDataSet::SafeDownCast(reader->GetOutput())->GetNumberOfBlocks() << std::endl;

  vtkCompositeDataSet *input =
    vtkCompositeDataSet::SafeDownCast(reader->GetOutput());

  vtkSmartPointer<vtkDataObjectTreeIterator> iter =
    vtkSmartPointer<vtkDataObjectTreeIterator>::New();
  iter->SetDataSet(input);
  iter->SkipEmptyNodesOn();
  iter->VisitOnlyLeavesOn();
  for (iter->InitTraversal(); !iter->IsDoneWithTraversal();
       iter->GoToNextItem())
  {
    vtkDataObject *dso = iter->GetCurrentDataObject();
    vtkPolyData *pd = vtkPolyData::SafeDownCast(dso);
    RestoreCameraFromFieldData("Camera",
                               camera,
                               pd);
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(pd);

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    RestorePropertyFromFieldData("Property",
                                 actor->GetProperty(),
                                 pd);
    vtkSmartPointer<vtkProperty> backProperty =
      vtkSmartPointer<vtkProperty>::New();
    actor->SetBackfaceProperty(backProperty);
    RestorePropertyFromFieldData("BackfaceProperty",
                                 actor->GetBackfaceProperty(),
                                 pd);
    RestoreActorFromFieldData("Actor",
                              actor,
                              pd);
    renderer->AddActor(actor);
  }
}
void RestoreCameraFromFieldData(std::string arrayPrefix,
                                vtkCamera *camera,
                                vtkPolyData *pd)
{
  vtkFieldData *fd = pd->GetFieldData();
  camera->SetFocalPoint(fd->GetArray(std::string(arrayPrefix + ":" + "FocalPoint").c_str())->GetTuple(0));
  camera->SetPosition(fd->GetArray(std::string(arrayPrefix + ":" + "Position").c_str())->GetTuple(0));
  camera->SetViewUp(fd->GetArray(std::string(arrayPrefix + ":" + "ViewUp").c_str())->GetTuple(0));
  camera->SetClippingRange(fd->GetArray(std::string(arrayPrefix + ":" + "ClippingRange").c_str())->GetTuple(0));
  camera->SetViewAngle(fd->GetArray(std::string(arrayPrefix + ":" + "ViewAngle").c_str())->GetTuple1(0));
}
void RestorePropertyFromFieldData(std::string arrayPrefix,
                                  vtkProperty *property,
                                  vtkPolyData *pd)
{
  if (property)
  {
    vtkFieldData *fd = pd->GetFieldData();

    property->SetAmbient(fd->GetArray(std::string(arrayPrefix + ":" + "Ambient").c_str())->GetTuple1(0));
    property->SetAmbientColor(fd->GetArray(std::string(arrayPrefix + ":" + "AmbientColor").c_str())->GetTuple(0));
    property->SetAmbientColor(fd->GetArray(std::string(arrayPrefix + ":" + "AmbientColor").c_str())->GetTuple(0));
    property->SetDiffuse(fd->GetArray(std::string(arrayPrefix + ":" + "Diffuse").c_str())->GetTuple1(0));
    property->SetDiffuseColor(fd->GetArray(std::string(arrayPrefix + ":" + "DiffuseColor").c_str())->GetTuple(0));
    property->SetSpecular(fd->GetArray(std::string(arrayPrefix + ":" + "Specular").c_str())->GetTuple1(0));
    property->SetSpecularColor(fd->GetArray(std::string(arrayPrefix + ":" + "SpecularColor").c_str())->GetTuple(0));
    property->SetSpecularPower(fd->GetArray(std::string(arrayPrefix + ":" + "SpecularPower").c_str())->GetTuple1(0));
    property->SetEdgeColor(fd->GetArray(std::string(arrayPrefix + ":" + "EdgeColor").c_str())->GetTuple(0));
    property->SetEdgeVisibility(fd->GetArray(std::string(arrayPrefix + ":" + "EdgeVisibility").c_str())->GetTuple1(0));
    property->SetVertexColor(fd->GetArray(std::string(arrayPrefix + ":" + "VertexColor").c_str())->GetTuple(0));
    property->SetVertexVisibility(fd->GetArray(std::string(arrayPrefix + ":" + "VertexVisibility").c_str())->GetTuple1(0));
    property->SetInterpolation(fd->GetArray(std::string(arrayPrefix + ":" + "Interpolation").c_str())->GetTuple1(0));
    property->SetOpacity(fd->GetArray(std::string(arrayPrefix + ":" + "Opacity").c_str())->GetTuple1(0));
    property->SetRepresentation(fd->GetArray(std::string(arrayPrefix + ":" + "Representation").c_str())->GetTuple1(0));
    property->SetBackfaceCulling(fd->GetArray(std::string(arrayPrefix + ":" + "BackfaceCulling").c_str())->GetTuple1(0));
    property->SetFrontfaceCulling(fd->GetArray(std::string(arrayPrefix + ":" + "FrontfaceCulling").c_str())->GetTuple1(0));
    property->SetPointSize(fd->GetArray(std::string(arrayPrefix + ":" + "PointSize").c_str())->GetTuple1(0));
    property->SetLineWidth(fd->GetArray(std::string(arrayPrefix + ":" + "LineWidth").c_str())->GetTuple1(0));
    property->SetLineStipplePattern(fd->GetArray(std::string(arrayPrefix + ":" + "LineStipplePattern").c_str())->GetTuple1(0));
    property->SetLineStippleRepeatFactor(fd->GetArray(std::string(arrayPrefix + ":" + "LineStippleRepeatFactor").c_str())->GetTuple1(0));
    property->SetLighting(fd->GetArray(std::string(arrayPrefix + ":" + "Lighting").c_str())->GetTuple1(0));
    property->SetRenderPointsAsSpheres(fd->GetArray(std::string(arrayPrefix + ":" + "RenderPointsAsSpheres").c_str())->GetTuple1(0));
    property->SetRenderLinesAsTubes(fd->GetArray(std::string(arrayPrefix + ":" + "RenderLinesAsTubes").c_str())->GetTuple1(0));
    property->SetShading(fd->GetArray(std::string(arrayPrefix + ":" + "Shading").c_str())->GetTuple1(0));
  }
}
void RestoreActorFromFieldData(std::string arrayPrefix,
                               vtkActor *actor,
                               vtkPolyData *pd)
{
  vtkFieldData *fd = pd->GetFieldData();

  actor->SetDragable(fd->GetArray(std::string(arrayPrefix + ":" + "Dragable").c_str())->GetTuple1(0));
  actor->SetPickable(fd->GetArray(std::string(arrayPrefix + ":" + "Pickable").c_str())->GetTuple1(0));
  actor->SetVisibility(fd->GetArray(std::string(arrayPrefix + ":" + "Visibility").c_str())->GetTuple1(0));
  actor->SetPosition(fd->GetArray(std::string(arrayPrefix + ":" + "Position").c_str())->GetTuple(0));
  actor->SetOrientation(fd->GetArray(std::string(arrayPrefix + ":" + "Orientation").c_str())->GetTuple(0));
  actor->SetOrigin(fd->GetArray(std::string(arrayPrefix + ":" + "Origin").c_str())->GetTuple(0));
  actor->SetScale(fd->GetArray(std::string(arrayPrefix + ":" + "Scale").c_str())->GetTuple(0));
  actor->SetForceOpaque(fd->GetArray(std::string(arrayPrefix + ":" + "ForceOpaque").c_str())->GetTuple1(0));
  actor->SetForceTranslucent(fd->GetArray(std::string(arrayPrefix + ":" + "ForceTranslucent").c_str())->GetTuple1(0));
}
}
