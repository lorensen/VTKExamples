#include <vtkSmartPointer.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkActorCollection.h>
#include <vtkXMLMultiBlockDataWriter.h>
#include <vtkActorCollection.h>
#include <vtkPolyData.h>

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkFieldData.h>
#include <vtkDoubleArray.h>
#include <vtkStringArray.h>
#include <vtkIntArray.h>
#include <vtkIdTypeArray.h>
#include <vtkLookupTable.h>
#include <vtkScalarsToColors.h>

#include <vtksys/SystemTools.hxx>
#include <vtkNamedColors.h>

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
void ExportMultiBlockScene(vtkRenderer *renderer, std::string fileName, bool binary = false);
void SaveCameraAsFieldData(std::string, vtkCamera *, vtkPolyData *);
void SavePropertyAsFieldData(std::string, vtkProperty *, vtkPolyData *);
void SaveMapperAsFieldData(std::string, vtkPolyDataMapper *, vtkPolyData *);
void SaveActorAsFieldData(std::string, vtkActor *, vtkPolyData *);
void SaveLookupTableAsFieldData(std::string, vtkScalarsToColors *, vtkPolyData *);
}

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData =
    ReadPolyData(argc > 1 ? argv[1] : "");

  // Visualize
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  double bounds[6];
  polyData->GetBounds(bounds);
  double delta[3];
  delta[0] = bounds[1] - bounds[0];
  for (int a = 0; a < 10; ++a)
  {
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    vtkSmartPointer<vtkProperty> backProperty =
      vtkSmartPointer<vtkProperty>::New();
    backProperty->SetColor(colors->GetColor3d("peacock").GetData());

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->SetBackfaceProperty(backProperty);
    actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Crimson").GetData());
    actor->GetProperty()->SetSpecular(.1 * a);
    actor->GetProperty()->SetSpecularPower(10.0 * a);
    if ((a % 3) == 0)
    {
      actor->GetProperty()->EdgeVisibilityOn();
      actor->GetProperty()->SetEdgeColor(colors->GetColor3d("SlateGray").GetData());
      actor->GetProperty()->SetLineWidth(1.5);
    }
    else
    {
      actor->GetProperty()->EdgeVisibilityOff();
    }
    if ((a % 4) == 0)
    {
      actor->GetProperty()->FrontfaceCullingOn();
    }
    if ((a % 3) == 0)
    {
      actor->GetProperty()->SetRepresentationToWireframe();
    }
    else
    {
      actor->GetProperty()->SetRepresentationToSurface();
    }
    actor->GetProperty()->SetInterpolationToFlat();
    actor->AddPosition(a * delta[0], 0.0, 0.0);
    renderer->AddActor(actor);
  }
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Yaw(10);
  renderer->ResetCamera();
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start();

  std::string prefix;
  if (argc < 2)
  {
    prefix = "Sphere";
  }
  else
  {
    prefix = "Export" +
      vtksys::SystemTools::GetFilenameWithoutExtension(argv[1]) + 
      ".vtp";
  }
  std::cout << "Scene is exported to " << vtksys::SystemTools::GetCurrentWorkingDirectory() + "/" + prefix << std::endl;
  ExportMultiBlockScene (renderer.GetPointer(), prefix, true);

  return EXIT_SUCCESS;
}

namespace
{
void ExportMultiBlockScene (vtkRenderer *renderer,
                            std::string fileName,
                            bool binary)
{
  // Iterate over all actors in the renderer
  vtkSmartPointer<vtkActorCollection> actors =
    vtkSmartPointer<vtkActorCollection>::New();
  actors = renderer->GetActors();
  std::cout << "There are " << actors->GetNumberOfItems() << " actors" << std::endl;
  actors->InitTraversal();
  // Initialize dataset to write
  vtkSmartPointer<vtkMultiBlockDataSet> multiBlockDataset =
    vtkSmartPointer<vtkMultiBlockDataSet>::New();
  multiBlockDataset->SetNumberOfBlocks(actors->GetNumberOfItems());

  for (vtkIdType a = 0; a < actors->GetNumberOfItems(); ++a)
  {
    vtkActor * actor = actors->GetNextActor();

    // Deep copy the polydata because it may be shared with other actors
    vtkSmartPointer<vtkPolyData> pd =
      vtkSmartPointer<vtkPolyData>::New();
    pd->DeepCopy(vtkPolyData::SafeDownCast(actor->GetMapper()->GetInput()));

    // Set metadata for block
    multiBlockDataset->SetBlock(a, pd);

    // Save Camera
    SaveCameraAsFieldData("Camera",
                          renderer->GetActiveCamera(),
                          pd);
                                                   
    // Save Property
    SavePropertyAsFieldData("Property",
                            actor->GetProperty(),
                            pd);
    SavePropertyAsFieldData("BackfaceProperty",
                            actor->GetBackfaceProperty(),
                            pd);
    // Save Mapper
    SaveMapperAsFieldData("PolyDataMapper",
                          vtkPolyDataMapper::SafeDownCast(actor->GetMapper()),
                          pd);
    // Save Actor
    SaveActorAsFieldData("Actor",
                          actor,
                          pd);
  }

  // Write multiblock dataset to disk
  vtkSmartPointer<vtkXMLMultiBlockDataWriter> writer =
    vtkSmartPointer<vtkXMLMultiBlockDataWriter>::New();
  if (binary)
  {
    writer->SetDataModeToBinary();
    writer->SetCompressorTypeToZLib();
  }
  else
  {
    writer->SetDataModeToAscii();
  }
  writer->SetInputData(multiBlockDataset);
  writer->SetFileName(fileName.c_str());
  writer->Update();
  return;
}

void SaveCameraAsFieldData(std::string arrayPrefix,
                           vtkCamera *camera,
                           vtkPolyData *pd)
{
  vtkSmartPointer<vtkDoubleArray> viewUp =
    vtkSmartPointer<vtkDoubleArray>::New();
  viewUp->SetNumberOfComponents(3);
  viewUp->SetNumberOfTuples(1);
  viewUp->SetTuple(0, camera->GetViewUp());
  viewUp->SetName(std::string(arrayPrefix + ":" + "ViewUp").c_str());
  pd->GetFieldData()->AddArray(viewUp);

  vtkSmartPointer<vtkDoubleArray> position =
    vtkSmartPointer<vtkDoubleArray>::New();
  position->SetNumberOfComponents(3);
  position->SetNumberOfTuples(1);
  position->SetTuple(0, camera->GetPosition());
  position->SetName(std::string(arrayPrefix + ":" + "Position").c_str());
  pd->GetFieldData()->AddArray(position);

  vtkSmartPointer<vtkDoubleArray> focalPoint =
    vtkSmartPointer<vtkDoubleArray>::New();
  focalPoint->SetNumberOfComponents(3);
  focalPoint->SetNumberOfTuples(1);
  focalPoint->SetTuple(0, camera->GetFocalPoint());
  focalPoint->SetName(std::string(arrayPrefix + ":" + "FocalPoint").c_str());
  pd->GetFieldData()->AddArray(focalPoint);

  vtkSmartPointer<vtkDoubleArray> clippingRange =
    vtkSmartPointer<vtkDoubleArray>::New();
  clippingRange->SetNumberOfComponents(2);
  clippingRange->SetNumberOfTuples(1);
  clippingRange->SetTuple(0, camera->GetClippingRange());
  clippingRange->SetName(std::string(arrayPrefix + ":" + "ClippingRange").c_str());
  pd->GetFieldData()->AddArray(clippingRange);

  vtkSmartPointer<vtkDoubleArray> viewAngle =
    vtkSmartPointer<vtkDoubleArray>::New();
  viewAngle->SetNumberOfComponents(1);
  viewAngle->SetNumberOfTuples(1);
  viewAngle->SetValue(0, camera->GetViewAngle());
  viewAngle->SetName(std::string(arrayPrefix + ":" + "ViewAngle").c_str());
  pd->GetFieldData()->AddArray(viewAngle);
}
void SavePropertyAsFieldData(std::string arrayPrefix,
                             vtkProperty * property,
                             vtkPolyData *pd)
{
  if (property)
  {
    vtkSmartPointer<vtkDoubleArray> ambient =
      vtkSmartPointer<vtkDoubleArray>::New();
    ambient->SetNumberOfComponents(1);
    ambient->SetNumberOfTuples(1);
    ambient->SetValue(0, property->GetAmbient());
    ambient->SetName(std::string(arrayPrefix + ":" + "Ambient").c_str());
    pd->GetFieldData()->AddArray(ambient);

    vtkSmartPointer<vtkDoubleArray> ambientColor =
      vtkSmartPointer<vtkDoubleArray>::New();
    ambientColor->SetNumberOfComponents(3);
    ambientColor->SetNumberOfTuples(1);
    ambientColor->SetTuple(0, property->GetAmbientColor());
    ambientColor->SetName(std::string(arrayPrefix + ":" + "AmbientColor").c_str());
    pd->GetFieldData()->AddArray(ambientColor);

    vtkSmartPointer<vtkDoubleArray> diffuse =
      vtkSmartPointer<vtkDoubleArray>::New();
    diffuse->SetNumberOfComponents(1);
    diffuse->SetNumberOfTuples(1);
    diffuse->SetValue(0, property->GetDiffuse());
    diffuse->SetName(std::string(arrayPrefix + ":" + "Diffuse").c_str());
    pd->GetFieldData()->AddArray(diffuse);

    vtkSmartPointer<vtkDoubleArray> diffuseColor =
      vtkSmartPointer<vtkDoubleArray>::New();
    diffuseColor->SetNumberOfComponents(3);
    diffuseColor->SetNumberOfTuples(1);
    diffuseColor->SetTuple(0, property->GetDiffuseColor());
    diffuseColor->SetName(std::string(arrayPrefix + ":" + "DiffuseColor").c_str());
    pd->GetFieldData()->AddArray(diffuseColor);

    vtkSmartPointer<vtkDoubleArray> EdgeColor =
      vtkSmartPointer<vtkDoubleArray>::New();
    EdgeColor->SetNumberOfComponents(3);
    EdgeColor->SetNumberOfTuples(1);
    EdgeColor->SetTuple(0, property->GetEdgeColor());
    EdgeColor->SetName(std::string(arrayPrefix + ":" + "EdgeColor").c_str());
    pd->GetFieldData()->AddArray(EdgeColor);

    vtkSmartPointer<vtkIntArray> EdgeVisibility =
      vtkSmartPointer<vtkIntArray>::New();
    EdgeVisibility->SetNumberOfComponents(1);
    EdgeVisibility->SetNumberOfTuples(1);
    EdgeVisibility->SetValue(0, property->GetEdgeVisibility());
    EdgeVisibility->SetName(std::string(arrayPrefix + ":" + "EdgeVisibility").c_str());
    pd->GetFieldData()->AddArray(EdgeVisibility);

    vtkSmartPointer<vtkDoubleArray> VertexColor =
      vtkSmartPointer<vtkDoubleArray>::New();
    VertexColor->SetNumberOfComponents(3);
    VertexColor->SetNumberOfTuples(1);
    VertexColor->SetTuple(0, property->GetVertexColor());
    VertexColor->SetName(std::string(arrayPrefix + ":" + "VertexColor").c_str());
    pd->GetFieldData()->AddArray(VertexColor);

    vtkSmartPointer<vtkIntArray> VertexVisibility =
      vtkSmartPointer<vtkIntArray>::New();
    VertexVisibility->SetNumberOfComponents(1);
    VertexVisibility->SetNumberOfTuples(1);
    VertexVisibility->SetValue(0, property->GetVertexVisibility());
    VertexVisibility->SetName(std::string(arrayPrefix + ":" + "VertexVisibility").c_str());
    pd->GetFieldData()->AddArray(VertexVisibility);

    vtkSmartPointer<vtkIntArray> Interpolation =
      vtkSmartPointer<vtkIntArray>::New();
    Interpolation->SetNumberOfComponents(1);
    Interpolation->SetNumberOfTuples(1);
    Interpolation->SetValue(0, property->GetInterpolation());
    Interpolation->SetName(std::string(arrayPrefix + ":" + "Interpolation").c_str());
    pd->GetFieldData()->AddArray(Interpolation);

    vtkSmartPointer<vtkDoubleArray> Opacity =
      vtkSmartPointer<vtkDoubleArray>::New();
    Opacity->SetNumberOfComponents(1);
    Opacity->SetNumberOfTuples(1);
    Opacity->SetValue(0, property->GetOpacity());
    Opacity->SetName(std::string(arrayPrefix + ":" + "Opacity").c_str());
    pd->GetFieldData()->AddArray(Opacity);

    vtkSmartPointer<vtkIntArray> Representation =
      vtkSmartPointer<vtkIntArray>::New();
    Representation->SetNumberOfComponents(1);
    Representation->SetNumberOfTuples(1);
    Representation->SetValue(0, property->GetRepresentation());
    Representation->SetName(std::string(arrayPrefix + ":" + "Representation").c_str());
    pd->GetFieldData()->AddArray(Representation);

    vtkSmartPointer<vtkDoubleArray> Specular =
      vtkSmartPointer<vtkDoubleArray>::New();
    Specular->SetNumberOfComponents(1);
    Specular->SetNumberOfTuples(1);
    Specular->SetValue(0, property->GetSpecular());
    Specular->SetName(std::string(arrayPrefix + ":" + "Specular").c_str());
    pd->GetFieldData()->AddArray(Specular);

    vtkSmartPointer<vtkDoubleArray> SpecularColor =
      vtkSmartPointer<vtkDoubleArray>::New();
    SpecularColor->SetNumberOfComponents(3);
    SpecularColor->SetNumberOfTuples(1);
    SpecularColor->SetTuple(0, property->GetSpecularColor());
    SpecularColor->SetName(std::string(arrayPrefix + ":" + "SpecularColor").c_str());
    pd->GetFieldData()->AddArray(SpecularColor);

    vtkSmartPointer<vtkDoubleArray> SpecularPower =
      vtkSmartPointer<vtkDoubleArray>::New();
    SpecularPower->SetNumberOfComponents(1);
    SpecularPower->SetNumberOfTuples(1);
    SpecularPower->SetValue(0, property->GetSpecularPower());
    SpecularPower->SetName(std::string(arrayPrefix + ":" + "SpecularPower").c_str());
    pd->GetFieldData()->AddArray(SpecularPower);

    vtkSmartPointer<vtkIntArray> BackfaceCulling =
      vtkSmartPointer<vtkIntArray>::New();
    BackfaceCulling->SetNumberOfComponents(1);
    BackfaceCulling->SetNumberOfTuples(1);
    BackfaceCulling->SetValue(0, property->GetBackfaceCulling());
    BackfaceCulling->SetName(std::string(arrayPrefix + ":" + "BackfaceCulling").c_str());
    pd->GetFieldData()->AddArray(BackfaceCulling);

    vtkSmartPointer<vtkIntArray> FrontfaceCulling =
      vtkSmartPointer<vtkIntArray>::New();
    FrontfaceCulling->SetNumberOfComponents(1);
    FrontfaceCulling->SetNumberOfTuples(1);
    FrontfaceCulling->SetValue(0, property->GetFrontfaceCulling());
    FrontfaceCulling->SetName(std::string(arrayPrefix + ":" + "FrontfaceCulling").c_str());
    pd->GetFieldData()->AddArray(FrontfaceCulling);

    vtkSmartPointer<vtkDoubleArray> PointSize =
      vtkSmartPointer<vtkDoubleArray>::New();
    PointSize->SetNumberOfComponents(1);
    PointSize->SetNumberOfTuples(1);
    PointSize->SetValue(0, property->GetPointSize());
    PointSize->SetName(std::string(arrayPrefix + ":" + "PointSize").c_str());
    pd->GetFieldData()->AddArray(PointSize);

    vtkSmartPointer<vtkDoubleArray> LineWidth =
      vtkSmartPointer<vtkDoubleArray>::New();
    LineWidth->SetNumberOfComponents(1);
    LineWidth->SetNumberOfTuples(1);
    LineWidth->SetValue(0, property->GetLineWidth());
    LineWidth->SetName(std::string(arrayPrefix + ":" + "LineWidth").c_str());
    pd->GetFieldData()->AddArray(LineWidth);

    vtkSmartPointer<vtkIntArray> LineStipplePattern =
      vtkSmartPointer<vtkIntArray>::New();
    LineStipplePattern->SetNumberOfComponents(1);
    LineStipplePattern->SetNumberOfTuples(1);
    LineStipplePattern->SetValue(0, property->GetLineStipplePattern());
    LineStipplePattern->SetName(std::string(arrayPrefix + ":" + "LineStipplePattern").c_str());
    pd->GetFieldData()->AddArray(LineStipplePattern);

    vtkSmartPointer<vtkIntArray> LineStippleRepeatFactor =
      vtkSmartPointer<vtkIntArray>::New();
    LineStippleRepeatFactor->SetNumberOfComponents(1);
    LineStippleRepeatFactor->SetNumberOfTuples(1);
    LineStippleRepeatFactor->SetValue(0, property->GetLineStippleRepeatFactor());
    LineStippleRepeatFactor->SetName(std::string(arrayPrefix + ":" + "LineStippleRepeatFactor").c_str());
    pd->GetFieldData()->AddArray(LineStippleRepeatFactor);

    vtkSmartPointer<vtkIntArray> Lighting =
      vtkSmartPointer<vtkIntArray>::New();
    Lighting->SetNumberOfComponents(1);
    Lighting->SetNumberOfTuples(1);
    Lighting->SetValue(0, property->GetLighting());
    Lighting->SetName(std::string(arrayPrefix + ":" + "Lighting").c_str());
    pd->GetFieldData()->AddArray(Lighting);

    vtkSmartPointer<vtkIntArray> RenderPointsAsSpheres =
      vtkSmartPointer<vtkIntArray>::New();
    RenderPointsAsSpheres->SetNumberOfComponents(1);
    RenderPointsAsSpheres->SetNumberOfTuples(1);
    RenderPointsAsSpheres->SetValue(0, property->GetRenderPointsAsSpheres());
    RenderPointsAsSpheres->SetName(std::string(arrayPrefix + ":" + "RenderPointsAsSpheres").c_str());
    pd->GetFieldData()->AddArray(RenderPointsAsSpheres);

    vtkSmartPointer<vtkIntArray> RenderLinesAsTubes =
      vtkSmartPointer<vtkIntArray>::New();
    RenderLinesAsTubes->SetNumberOfComponents(1);
    RenderLinesAsTubes->SetNumberOfTuples(1);
    RenderLinesAsTubes->SetValue(0, property->GetRenderLinesAsTubes());
    RenderLinesAsTubes->SetName(std::string(arrayPrefix + ":" + "RenderLinesAsTubes").c_str());
    pd->GetFieldData()->AddArray(RenderLinesAsTubes);

    vtkSmartPointer<vtkIntArray> Shading =
      vtkSmartPointer<vtkIntArray>::New();
    Shading->SetNumberOfComponents(1);
    Shading->SetNumberOfTuples(1);
    Shading->SetValue(0, property->GetShading());
    Shading->SetName(std::string(arrayPrefix + ":" + "Shading").c_str());
    pd->GetFieldData()->AddArray(Shading);

    if (property->GetMaterialName())
    {
      vtkSmartPointer<vtkStringArray> MaterialName =
        vtkSmartPointer<vtkStringArray>::New();
      MaterialName->SetNumberOfComponents(1);
      MaterialName->SetNumberOfTuples(1);
      MaterialName->SetValue(0, property->GetMaterialName());
      MaterialName->SetName(std::string(arrayPrefix + ":" + "MaterialName").c_str());
      pd->GetFieldData()->AddArray(MaterialName);
    }
  }
}
void SaveMapperAsFieldData(std::string arrayPrefix,
                           vtkPolyDataMapper *mapper,
                           vtkPolyData *pd)
{
  if (mapper->GetLookupTable())
  {
    vtkScalarsToColors *lut = mapper->GetLookupTable();
    vtkSmartPointer<vtkDoubleArray> Alpha =
      vtkSmartPointer<vtkDoubleArray>::New();
    Alpha->SetNumberOfComponents(1);
    Alpha->SetNumberOfTuples(1);
    Alpha->SetValue(0, lut->GetAlpha());
    Alpha->SetName(std::string(arrayPrefix + ":LookupTable:" + "Alpha").c_str());
    pd->GetFieldData()->AddArray(Alpha);

    vtkSmartPointer<vtkDoubleArray> VectorMode =
      vtkSmartPointer<vtkDoubleArray>::New();
    VectorMode->SetNumberOfComponents(1);
    VectorMode->SetNumberOfTuples(1);
    VectorMode->SetValue(0, lut->GetVectorMode());
    VectorMode->SetName(std::string(arrayPrefix + ":LookupTable:" + "VectorMode").c_str());
    pd->GetFieldData()->AddArray(VectorMode);

    vtkSmartPointer<vtkDoubleArray> VectorComponent =
      vtkSmartPointer<vtkDoubleArray>::New();
    VectorComponent->SetNumberOfComponents(1);
    VectorComponent->SetNumberOfTuples(1);
    VectorComponent->SetValue(0, lut->GetVectorComponent());
    VectorComponent->SetName(std::string(arrayPrefix + ":LookupTable:" + "VectorComponent").c_str());
    pd->GetFieldData()->AddArray(VectorComponent);

    vtkSmartPointer<vtkDoubleArray> VectorSize =
      vtkSmartPointer<vtkDoubleArray>::New();
    VectorSize->SetNumberOfComponents(1);
    VectorSize->SetNumberOfTuples(1);
    VectorSize->SetValue(0, lut->GetVectorSize());
    VectorSize->SetName(std::string(arrayPrefix + ":LookupTable:" + "VectorSize").c_str());
    pd->GetFieldData()->AddArray(VectorSize);

    vtkSmartPointer<vtkIntArray> IndexedLookup =
      vtkSmartPointer<vtkIntArray>::New();
    IndexedLookup->SetNumberOfComponents(1);
    IndexedLookup->SetNumberOfTuples(1);
    IndexedLookup->SetValue(0, lut->GetIndexedLookup());
    IndexedLookup->SetName(std::string(arrayPrefix + ":LookupTable:" + "IndexedLookup").c_str());
    pd->GetFieldData()->AddArray(IndexedLookup);

    vtkSmartPointer<vtkDoubleArray> TableRange =
      vtkSmartPointer<vtkDoubleArray>::New();
    TableRange->SetNumberOfComponents(2);
    TableRange->SetNumberOfTuples(1);
    TableRange->SetTuple(0, vtkLookupTable::SafeDownCast(lut)->GetTableRange());
    TableRange->SetName(std::string(arrayPrefix + ":LookupTable:" + "TableRange").c_str());
    pd->GetFieldData()->AddArray(TableRange);

    vtkSmartPointer<vtkIntArray> Scale =
      vtkSmartPointer<vtkIntArray>::New();
    Scale->SetNumberOfComponents(1);
    Scale->SetNumberOfTuples(1);
    Scale->SetValue(0, vtkLookupTable::SafeDownCast(lut)->GetScale());
    Scale->SetName(std::string(arrayPrefix + ":LookupTable:" + "Scale").c_str());
    pd->GetFieldData()->AddArray(Scale);

    vtkSmartPointer<vtkDoubleArray> HueRange =
      vtkSmartPointer<vtkDoubleArray>::New();
    HueRange->SetNumberOfComponents(2);
    HueRange->SetNumberOfTuples(1);
    HueRange->SetTuple(0, vtkLookupTable::SafeDownCast(lut)->GetHueRange());
    HueRange->SetName(std::string(arrayPrefix + ":LookupTable:" + "HueRange").c_str());
    pd->GetFieldData()->AddArray(HueRange);

    vtkSmartPointer<vtkDoubleArray> SaturationRange =
      vtkSmartPointer<vtkDoubleArray>::New();
    SaturationRange->SetNumberOfComponents(2);
    SaturationRange->SetNumberOfTuples(1);
    SaturationRange->SetTuple(0, vtkLookupTable::SafeDownCast(lut)->GetSaturationRange());
    SaturationRange->SetName(std::string(arrayPrefix + ":LookupTable:" + "SaturationRange").c_str());
    pd->GetFieldData()->AddArray(SaturationRange);

    vtkSmartPointer<vtkDoubleArray> ValueRange =
      vtkSmartPointer<vtkDoubleArray>::New();
    ValueRange->SetNumberOfComponents(2);
    ValueRange->SetNumberOfTuples(1);
    ValueRange->SetTuple(0, vtkLookupTable::SafeDownCast(lut)->GetValueRange());
    ValueRange->SetName(std::string(arrayPrefix + ":LookupTable:" + "ValueRange").c_str());
    pd->GetFieldData()->AddArray(ValueRange);

    vtkSmartPointer<vtkDoubleArray> AlphaRange =
      vtkSmartPointer<vtkDoubleArray>::New();
    AlphaRange->SetNumberOfComponents(2);
    AlphaRange->SetNumberOfTuples(1);
    AlphaRange->SetTuple(0, vtkLookupTable::SafeDownCast(lut)->GetAlphaRange());
    AlphaRange->SetName(std::string(arrayPrefix + ":LookupTable:" + "AlphaRange").c_str());
    pd->GetFieldData()->AddArray(AlphaRange);

    vtkSmartPointer<vtkDoubleArray> NanColor =
      vtkSmartPointer<vtkDoubleArray>::New();
    NanColor->SetNumberOfComponents(4);
    NanColor->SetNumberOfTuples(1);
    NanColor->SetTuple(0, vtkLookupTable::SafeDownCast(lut)->GetNanColor());
    NanColor->SetName(std::string(arrayPrefix + ":LookupTable:" + "NanColor").c_str());
    pd->GetFieldData()->AddArray(NanColor);

    vtkSmartPointer<vtkDoubleArray> BelowRangeColor =
      vtkSmartPointer<vtkDoubleArray>::New();
    BelowRangeColor->SetNumberOfComponents(4);
    BelowRangeColor->SetNumberOfTuples(1);
    BelowRangeColor->SetTuple(0, vtkLookupTable::SafeDownCast(lut)->GetBelowRangeColor());
    BelowRangeColor->SetName(std::string(arrayPrefix + ":LookupTable:" + "BelowRangeColor").c_str());
    pd->GetFieldData()->AddArray(BelowRangeColor);

    vtkSmartPointer<vtkIntArray> UseBelowRangeColor =
      vtkSmartPointer<vtkIntArray>::New();
    UseBelowRangeColor->SetNumberOfComponents(1);
    UseBelowRangeColor->SetNumberOfTuples(1);
    UseBelowRangeColor->SetValue(0, vtkLookupTable::SafeDownCast(lut)->GetUseBelowRangeColor());
    UseBelowRangeColor->SetName(std::string(arrayPrefix + ":LookupTable:" + "UseBelowRangeColor").c_str());
    pd->GetFieldData()->AddArray(UseBelowRangeColor);

    vtkSmartPointer<vtkDoubleArray> AboveRangeColor =
      vtkSmartPointer<vtkDoubleArray>::New();
    AboveRangeColor->SetNumberOfComponents(4);
    AboveRangeColor->SetNumberOfTuples(1);
    AboveRangeColor->SetTuple(0, vtkLookupTable::SafeDownCast(lut)->GetAboveRangeColor());
    AboveRangeColor->SetName(std::string(arrayPrefix + ":LookupTable:" + "AboveRangeColor").c_str());
    pd->GetFieldData()->AddArray(AboveRangeColor);

    vtkSmartPointer<vtkIntArray> UseAboveRangeColor =
      vtkSmartPointer<vtkIntArray>::New();
    UseAboveRangeColor->SetNumberOfComponents(1);
    UseAboveRangeColor->SetNumberOfTuples(1);
    UseAboveRangeColor->SetValue(0, vtkLookupTable::SafeDownCast(lut)->GetUseAboveRangeColor());
    UseAboveRangeColor->SetName(std::string(arrayPrefix + ":LookupTable:" + "UseAboveRangeColor").c_str());
    pd->GetFieldData()->AddArray(UseAboveRangeColor);

    vtkSmartPointer<vtkIdTypeArray> NumberOfTableValues =
      vtkSmartPointer<vtkIdTypeArray>::New();
    NumberOfTableValues->SetNumberOfComponents(1);
    NumberOfTableValues->SetNumberOfTuples(1);
    NumberOfTableValues->SetValue(0, vtkLookupTable::SafeDownCast(lut)->GetNumberOfTableValues());
    NumberOfTableValues->SetName(std::string(arrayPrefix + ":LookupTable:" + "NumberOfTableValues").c_str());
    pd->GetFieldData()->AddArray(NumberOfTableValues);

    vtkSmartPointer<vtkIdTypeArray> NumberOfColors =
      vtkSmartPointer<vtkIdTypeArray>::New();
    NumberOfColors->SetNumberOfComponents(1);
    NumberOfColors->SetNumberOfTuples(1);
    NumberOfColors->SetValue(0, vtkLookupTable::SafeDownCast(lut)->GetNumberOfColors());
    NumberOfColors->SetName(std::string(arrayPrefix + ":LookupTable:" + "NumberOfColors").c_str());
    pd->GetFieldData()->AddArray(NumberOfColors);

    vtkSmartPointer<vtkIntArray> Ramp =
      vtkSmartPointer<vtkIntArray>::New();
    Ramp->SetNumberOfComponents(1);
    Ramp->SetNumberOfTuples(1);
    Ramp->SetValue(0, vtkLookupTable::SafeDownCast(lut)->GetRamp());
    Ramp->SetName(std::string(arrayPrefix + ":LookupTable:" + "Ramp").c_str());
    pd->GetFieldData()->AddArray(Ramp);

    vtkSmartPointer<vtkUnsignedCharArray> Table =
      vtkSmartPointer<vtkUnsignedCharArray>::New();
//    Table->SetNumberOfComponents(4);
//    Table->SetNumberOfTuples(vtkLookupTable::SafeDownCast(lut)->GetTable()->GetNumberOfTuples());
    Table->DeepCopy(vtkLookupTable::SafeDownCast(lut)->GetTable());
    Table->SetName(std::string(arrayPrefix + ":LookupTable:" + "Table").c_str());
    pd->GetFieldData()->AddArray(Table);

    vtkSmartPointer<vtkIntArray> ScalarVisibility =
      vtkSmartPointer<vtkIntArray>::New();
    ScalarVisibility->SetNumberOfComponents(1);
    ScalarVisibility->SetNumberOfTuples(1);
    ScalarVisibility->SetValue(0, mapper->GetScalarVisibility());
    ScalarVisibility->SetName(std::string(arrayPrefix + ":" + "ScalarVisibility").c_str());
    pd->GetFieldData()->AddArray(ScalarVisibility);

    vtkSmartPointer<vtkIntArray> Static =
      vtkSmartPointer<vtkIntArray>::New();
    Static->SetNumberOfComponents(1);
    Static->SetNumberOfTuples(1);
    Static->SetValue(0, mapper->GetStatic());
    Static->SetName(std::string(arrayPrefix + ":" + "Static").c_str());
    pd->GetFieldData()->AddArray(Static);

    vtkSmartPointer<vtkDoubleArray> ScalarRange =
      vtkSmartPointer<vtkDoubleArray>::New();
    ScalarRange->SetNumberOfComponents(2);
    ScalarRange->SetNumberOfTuples(1);
    ScalarRange->SetTuple(0, mapper->GetScalarRange());
    ScalarRange->SetName(std::string(arrayPrefix + ":" + "ScalarRange").c_str());
    pd->GetFieldData()->AddArray(ScalarRange);

    vtkSmartPointer<vtkIntArray> UseLookupTableScalarRange =
      vtkSmartPointer<vtkIntArray>::New();
    UseLookupTableScalarRange->SetNumberOfComponents(1);
    UseLookupTableScalarRange->SetNumberOfTuples(1);
    UseLookupTableScalarRange->SetValue(0, mapper->GetUseLookupTableScalarRange());
    UseLookupTableScalarRange->SetName(std::string(arrayPrefix + ":" + "UseLookupTableScalarRange").c_str());
    pd->GetFieldData()->AddArray(UseLookupTableScalarRange);

    vtkSmartPointer<vtkIntArray> ColorMode =
      vtkSmartPointer<vtkIntArray>::New();
    ColorMode->SetNumberOfComponents(1);
    ColorMode->SetNumberOfTuples(1);
    ColorMode->SetValue(0, mapper->GetColorMode());
    ColorMode->SetName(std::string(arrayPrefix + ":" + "ColorMode").c_str());
    pd->GetFieldData()->AddArray(ColorMode);

    vtkSmartPointer<vtkIntArray> InterpolateScalarsBeforeMapping =
      vtkSmartPointer<vtkIntArray>::New();
    InterpolateScalarsBeforeMapping->SetNumberOfComponents(1);
    InterpolateScalarsBeforeMapping->SetNumberOfTuples(1);
    InterpolateScalarsBeforeMapping->SetValue(0, mapper->GetInterpolateScalarsBeforeMapping());
    InterpolateScalarsBeforeMapping->SetName(std::string(arrayPrefix + ":" + "InterpolateScalarsBeforeMapping").c_str());
    pd->GetFieldData()->AddArray(InterpolateScalarsBeforeMapping);

    vtkSmartPointer<vtkIntArray> ScalarMode =
      vtkSmartPointer<vtkIntArray>::New();
    ScalarMode->SetNumberOfComponents(1);
    ScalarMode->SetNumberOfTuples(1);
    ScalarMode->SetValue(0, mapper->GetScalarMode());
    ScalarMode->SetName(std::string(arrayPrefix + ":" + "ScalarMode").c_str());
    pd->GetFieldData()->AddArray(ScalarMode);

    vtkSmartPointer<vtkIntArray> ResolveCoincidentTopology =
      vtkSmartPointer<vtkIntArray>::New();
    ResolveCoincidentTopology->SetNumberOfComponents(1);
    ResolveCoincidentTopology->SetNumberOfTuples(1);
    ResolveCoincidentTopology->SetValue(0, mapper->GetResolveCoincidentTopology());
    ResolveCoincidentTopology->SetName(std::string(arrayPrefix + ":" + "ResolveCoincidentTopology").c_str());
    pd->GetFieldData()->AddArray(ResolveCoincidentTopology);

#if 0
    vtkSmartPointer<vtkDoubleArray> CoincidentPointOffset =
      vtkSmartPointer<vtkDoubleArray>::New();
    CoincidentPointOffset->SetNumberOfComponents(1);
    CoincidentPointOffset->SetNumberOfTuples(1);
    CoincidentPointOffset->SetValue(0, mapper->GetCoincidentPointOffset());
    CoincidentPointOffset->SetName(std::string(arrayPrefix + ":" + "CoincidentPointOffset").c_str());
    pd->GetFieldData()->AddArray(CoincidentPointOffset);

    vtkSmartPointer<vtkDoubleArray> CoincidentLineOffset =
      vtkSmartPointer<vtkDoubleArray>::New();
    CoincidentLineOffset->SetNumberOfComponents(1);
    CoincidentLineOffset->SetNumberOfTuples(1);
    CoincidentLineOffset->SetValue(0, mapper->GetCoincidentLineOffset());
    CoincidentLineOffset->SetName(std::string(arrayPrefix + ":" + "CoincidentLineOffset").c_str());
    pd->GetFieldData()->AddArray(CoincidentLineOffset);

    vtkSmartPointer<vtkDoubleArray> CoincidentPolygonOffset =
      vtkSmartPointer<vtkDoubleArray>::New();
    CoincidentPolygonOffset->SetNumberOfComponents(1);
    CoincidentPolygonOffset->SetNumberOfTuples(1);
    CoincidentPolygonOffset->SetValue(0, mapper->GetCoincidentPolygonOffset());
    CoincidentPolygonOffset->SetName(std::string(arrayPrefix + ":" + "CoincidentPolygonOffset").c_str());
    pd->GetFieldData()->AddArray(CoincidentPolygonOffset);

    vtkSmartPointer<vtkDoubleArray> CoincidentLineFactor =
      vtkSmartPointer<vtkDoubleArray>::New();
    CoincidentLineFactor->SetNumberOfComponents(1);
    CoincidentLineFactor->SetNumberOfTuples(1);
    CoincidentLineFactor->SetValue(0, mapper->GetCoincidentLineFactor());
    CoincidentLineFactor->SetName(std::string(arrayPrefix + ":" + "CoincidentLineFactor").c_str());
    pd->GetFieldData()->AddArray(CoincidentLineFactor);

    vtkSmartPointer<vtkDoubleArray> CoincidentPolygonFactor =
      vtkSmartPointer<vtkDoubleArray>::New();
    CoincidentPolygonFactor->SetNumberOfComponents(1);
    CoincidentPolygonFactor->SetNumberOfTuples(1);
    CoincidentPolygonFactor->SetValue(0, mapper->GetCoincidentPolygonFactor());
    CoincidentPolygonFactor->SetName(std::string(arrayPrefix + ":" + "CoincidentPolygonFactor").c_str());
    pd->GetFieldData()->AddArray(CoincidentPolygonFactor);
#endif
  }
}

void SaveActorAsFieldData(std::string arrayPrefix,
                          vtkActor *actor,
                          vtkPolyData *pd)
{
  vtkSmartPointer<vtkIntArray> dragable =
    vtkSmartPointer<vtkIntArray>::New();
  dragable->SetNumberOfComponents(1);
  dragable->SetNumberOfTuples(1);
  dragable->SetValue(0, actor->GetDragable());
  dragable->SetName(std::string(arrayPrefix + ":" + "Dragable").c_str());
  pd->GetFieldData()->AddArray(dragable);

  vtkSmartPointer<vtkIntArray> pickable =
    vtkSmartPointer<vtkIntArray>::New();
  pickable->SetNumberOfComponents(1);
  pickable->SetNumberOfTuples(1);
  pickable->SetValue(0, actor->GetPickable());
  pickable->SetName(std::string(arrayPrefix + ":" + "Pickable").c_str());
  pd->GetFieldData()->AddArray(pickable);

  vtkSmartPointer<vtkIntArray> visibility =
    vtkSmartPointer<vtkIntArray>::New();
  visibility->SetNumberOfComponents(1);
  visibility->SetNumberOfTuples(1);
  visibility->SetValue(0, actor->GetVisibility());
  visibility->SetName(std::string(arrayPrefix + ":" + "Visibility").c_str());
  pd->GetFieldData()->AddArray(visibility);

  vtkSmartPointer<vtkDoubleArray> position =
    vtkSmartPointer<vtkDoubleArray>::New();
  position->SetNumberOfComponents(3);
  position->SetNumberOfTuples(1);
  position->SetTuple(0, actor->GetPosition());
  position->SetName(std::string(arrayPrefix + ":" + "Position").c_str());
  pd->GetFieldData()->AddArray(position);

  vtkSmartPointer<vtkDoubleArray> orientation =
    vtkSmartPointer<vtkDoubleArray>::New();
  orientation->SetNumberOfComponents(3);
  orientation->SetNumberOfTuples(1);
  orientation->SetTuple(0, actor->GetOrientation());
  orientation->SetName(std::string(arrayPrefix + ":" + "Orientation").c_str());
  pd->GetFieldData()->AddArray(orientation);

  vtkSmartPointer<vtkDoubleArray> origin =
    vtkSmartPointer<vtkDoubleArray>::New();
  origin->SetNumberOfComponents(3);
  origin->SetNumberOfTuples(1);
  origin->SetTuple(0, actor->GetOrigin());
  origin->SetName(std::string(arrayPrefix + ":" + "Origin").c_str());
  pd->GetFieldData()->AddArray(origin);

  vtkSmartPointer<vtkDoubleArray> scale =
    vtkSmartPointer<vtkDoubleArray>::New();
  scale->SetNumberOfComponents(3);
  scale->SetNumberOfTuples(1);
  scale->SetTuple(0, actor->GetScale());
  scale->SetName(std::string(arrayPrefix + ":" + "Scale").c_str());
  pd->GetFieldData()->AddArray(scale);

  vtkSmartPointer<vtkIntArray> forceOpaque =
    vtkSmartPointer<vtkIntArray>::New();
  forceOpaque->SetNumberOfComponents(1);
  forceOpaque->SetNumberOfTuples(1);
  forceOpaque->SetValue(0, actor->GetForceOpaque());
  forceOpaque->SetName(std::string(arrayPrefix + ":" + "ForceOpaque").c_str());
  pd->GetFieldData()->AddArray(forceOpaque);

  vtkSmartPointer<vtkIntArray> forceTranslucent =
    vtkSmartPointer<vtkIntArray>::New();
  forceTranslucent->SetNumberOfComponents(1);
  forceTranslucent->SetNumberOfTuples(1);
  forceTranslucent->SetValue(0, actor->GetForceTranslucent());
  forceTranslucent->SetName(std::string(arrayPrefix + ":" + "ForceTranslucent").c_str());
  pd->GetFieldData()->AddArray(forceTranslucent);
#if 0
UserTransform
UserMatrix
Texture
#endif
}
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
