#include <vtkActor.h>
#include <vtkActorCollection.h>
#include <vtkCamera.h>
#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkIdTypeArray.h>
#include <vtkIntArray.h>
#include <vtkLinearTransform.h>
#include <vtkLookupTable.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkScalarsToColors.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>
#include <vtkTransform.h>
#include <vtkXMLMultiBlockDataWriter.h>
#include <vtksys/SystemTools.hxx>

// Readers
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkPolyData.h>
#include <vtkSphereSource.h>

#include <algorithm> // For transform()
#include <cctype>    // For to_lower
#include <string>    // For find_last_of()

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName);
void ExportMultiBlockScene(vtkRenderer* renderer, std::string fileName,
                           bool binary = false);
void SaveCameraAsFieldData(std::string const&, vtkCamera*, vtkPolyData*);
void SavePropertyAsFieldData(std::string const&, vtkProperty*, vtkPolyData*);
void SaveMapperAsFieldData(std::string const&, vtkPolyDataMapper*,
                           vtkPolyData*);
void SaveActorAsFieldData(std::string const&, vtkActor*, vtkPolyData*);
void SaveLookupTableAsFieldData(std::string const&, vtkScalarsToColors*,
                                vtkPolyData*);
} // namespace

int main(int argc, char* argv[])
{
  auto polyData = ReadPolyData(argc > 1 ? argv[1] : "");

  // Visualize
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  double bounds[6];
  polyData->GetBounds(bounds);
  double delta[3];
  delta[0] = bounds[1] - bounds[0];
  delta[1] = bounds[3] - bounds[2];
  delta[2] = bounds[5] - bounds[4];
  for (int c = 0; c < 4; ++c)
  {
    for (int b = 0; b < 4; ++b)
    {
      for (int a = 0; a < 4; ++a)
      {
        auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(polyData);

        auto backProperty = vtkSmartPointer<vtkProperty>::New();
        backProperty->SetColor(colors->GetColor3d("peacock").GetData());

        auto actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actor->SetBackfaceProperty(backProperty);
        if (b == 1)
        {
          actor->GetProperty()->SetDiffuseColor(
              colors->GetColor3d("Orchid").GetData());
        }
        else if (b == 2)
        {
          actor->GetProperty()->SetDiffuseColor(
              colors->GetColor3d("Salmon").GetData());
        }
        else if (b == 3)
        {
          actor->GetProperty()->SetDiffuseColor(
              colors->GetColor3d("SandyBrown").GetData());
        }
        else
        {
          actor->GetProperty()->SetDiffuseColor(
              colors->GetColor3d("Crimson").GetData());
        }
        actor->GetProperty()->SetSpecular(.5);
        actor->GetProperty()->SetDiffuse(.5);
        actor->GetProperty()->SetSpecularPower(a * b * c);
        if ((a % 3) == 0)
        {
          actor->GetProperty()->EdgeVisibilityOn();
          actor->GetProperty()->SetEdgeColor(
              colors->GetColor3d("SlateGray").GetData());
          actor->GetProperty()->SetLineWidth(1.0);
        }
        else
        {
          actor->GetProperty()->EdgeVisibilityOff();
        }
        if ((a % 4) == 0)
        {
          actor->GetProperty()->FrontfaceCullingOn();
        }
        if ((a % 3) == 0 && (c & 3) == 0)
        {
          actor->GetProperty()->SetRepresentationToWireframe();
        }
        else
        {
          actor->GetProperty()->SetRepresentationToSurface();
        }
        if (c == 3)
        {
          auto rotateTransform = vtkSmartPointer<vtkTransform>::New();
          rotateTransform->RotateZ(30.0);
          actor->GetProperty()->SetInterpolationToGouraud();
          actor->SetUserTransform(rotateTransform);
        }
        else
        {
          actor->GetProperty()->SetInterpolationToFlat();
        }
        actor->AddPosition(1.5 * a * delta[0], 1.5 * b * delta[1],
                           1.5 * c * delta[2]);
        actor->SetScale((a + 1) * .5, (b + 1) * .5, (c + 1) * .5);

        renderer->AddActor(actor);
      }
    }
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
        vtksys::SystemTools::GetFilenameWithoutExtension(argv[1]) + ".vtp";
  }
  std::cout << "Scene is exported to "
            << vtksys::SystemTools::GetCurrentWorkingDirectory() + "/" + prefix
            << std::endl;
  ExportMultiBlockScene(renderer.GetPointer(), prefix, false);

  return EXIT_SUCCESS;
}

namespace {
void ExportMultiBlockScene(vtkRenderer* renderer, std::string fileName,
                           bool binary)
{
  // Iterate over all actors in the renderer
  auto actors = renderer->GetActors();
  std::cout << "There are " << actors->GetNumberOfItems() << " actors"
            << std::endl;
  actors->InitTraversal();
  // Initialize dataset to write
  auto multiBlockDataset = vtkSmartPointer<vtkMultiBlockDataSet>::New();
  multiBlockDataset->SetNumberOfBlocks(actors->GetNumberOfItems());

  for (vtkIdType a = 0; a < actors->GetNumberOfItems(); ++a)
  {
    vtkActor* actor = actors->GetNextActor();

    // Deep copy the polydata because it may be shared with other actors
    auto pd = vtkSmartPointer<vtkPolyData>::New();
    pd->DeepCopy(dynamic_cast<vtkPolyData*>(actor->GetMapper()->GetInput()));

    // Set metadata for block
    multiBlockDataset->SetBlock(a, pd);

    // Save Camera
    SaveCameraAsFieldData("Camera", renderer->GetActiveCamera(), pd);

    // Save Property
    SavePropertyAsFieldData("Property", actor->GetProperty(), pd);
    SavePropertyAsFieldData("BackfaceProperty", actor->GetBackfaceProperty(),
                            pd);
    // Save Mapper
    SaveMapperAsFieldData("PolyDataMapper",
                          dynamic_cast<vtkPolyDataMapper*>(actor->GetMapper()),
                          pd);
    // Save Actor
    SaveActorAsFieldData("Actor", actor, pd);
  }

  // Write multiblock dataset to disk
  auto writer = vtkSmartPointer<vtkXMLMultiBlockDataWriter>::New();
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

#define SAVE_SCALAR(arrayPrefix, instance, pd, name, T)                        \
  vtkSmartPointer<T> name = vtkSmartPointer<T>::New();                         \
  name->SetNumberOfComponents(1);                                              \
  name->SetNumberOfTuples(1);                                                  \
  name->SetValue(0, instance->Get##name());                                    \
  name->SetName(std::string(arrayPrefix + ":" + "#name").c_str());             \
  pd->GetFieldData()->AddArray(name)

#define SAVE_VECTOR(arrayPrefix, instance, pd, name, T, components, tuples)    \
  vtkSmartPointer<T> name = vtkSmartPointer<T>::New();                         \
  name->SetNumberOfComponents(components);                                     \
  name->SetNumberOfTuples(tuples);                                             \
  name->SetTuple(0, instance->Get##name());                                    \
  name->SetName(std::string(arrayPrefix + ":" + "#name").c_str());             \
  pd->GetFieldData()->AddArray(name)

void SaveCameraAsFieldData(std::string const& arrayPrefix, vtkCamera* camera,
                           vtkPolyData* pd)
{
  SAVE_VECTOR(arrayPrefix, camera, pd, ViewUp, vtkDoubleArray, 3, 1);
  SAVE_VECTOR(arrayPrefix, camera, pd, Position, vtkDoubleArray, 3, 1);
  SAVE_VECTOR(arrayPrefix, camera, pd, FocalPoint, vtkDoubleArray, 3, 1);
  SAVE_VECTOR(arrayPrefix, camera, pd, ClippingRange, vtkDoubleArray, 2, 1);
  SAVE_SCALAR(arrayPrefix, camera, pd, ViewAngle, vtkDoubleArray);
}
void SavePropertyAsFieldData(std::string const& arrayPrefix,
                             vtkProperty* property, vtkPolyData* pd)
{
  if (property)
  {
    SAVE_SCALAR(arrayPrefix, property, pd, Ambient, vtkDoubleArray);
    SAVE_VECTOR(arrayPrefix, property, pd, AmbientColor, vtkDoubleArray, 3, 1);
    SAVE_SCALAR(arrayPrefix, property, pd, Diffuse, vtkDoubleArray);
    SAVE_VECTOR(arrayPrefix, property, pd, DiffuseColor, vtkDoubleArray, 3, 1);
    SAVE_SCALAR(arrayPrefix, property, pd, Specular, vtkDoubleArray);
    SAVE_VECTOR(arrayPrefix, property, pd, SpecularColor, vtkDoubleArray, 3, 1);
    SAVE_SCALAR(arrayPrefix, property, pd, SpecularPower, vtkDoubleArray);
    SAVE_VECTOR(arrayPrefix, property, pd, EdgeColor, vtkDoubleArray, 3, 1);
    SAVE_SCALAR(arrayPrefix, property, pd, EdgeVisibility, vtkIntArray);
    SAVE_VECTOR(arrayPrefix, property, pd, VertexColor, vtkDoubleArray, 3, 1);
    SAVE_SCALAR(arrayPrefix, property, pd, Interpolation, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, Opacity, vtkDoubleArray);
    SAVE_SCALAR(arrayPrefix, property, pd, Representation, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, BackfaceCulling, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, FrontfaceCulling, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, PointSize, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, LineWidth, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, LineStipplePattern, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, LineStippleRepeatFactor,
                vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, Lighting, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, RenderPointsAsSpheres, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, property, pd, Shading, vtkIntArray);

    if (property->GetMaterialName())
    {
      SAVE_SCALAR(arrayPrefix, property, pd, MaterialName, vtkStringArray);
    }
  }
}
void SaveMapperAsFieldData(std::string const& arrayPrefix,
                           vtkPolyDataMapper* mapper, vtkPolyData* pd)
{
  if (mapper->GetLookupTable())
  {
    std::string prefix = arrayPrefix + "LookupTable:";
    vtkScalarsToColors* scalarsToColors = mapper->GetLookupTable();

    SAVE_SCALAR(prefix, scalarsToColors, pd, Alpha, vtkDoubleArray);
    SAVE_SCALAR(prefix, scalarsToColors, pd, VectorMode, vtkIntArray);
    SAVE_SCALAR(prefix, scalarsToColors, pd, VectorComponent, vtkIntArray);
    SAVE_SCALAR(prefix, scalarsToColors, pd, VectorSize, vtkIntArray);
    SAVE_SCALAR(prefix, scalarsToColors, pd, IndexedLookup, vtkIntArray);

    vtkLookupTable* lut =
        dynamic_cast<vtkLookupTable*>(mapper->GetLookupTable());
    SAVE_VECTOR(prefix, lut, pd, TableRange, vtkDoubleArray, 2, 1);
    SAVE_SCALAR(prefix, lut, pd, Scale, vtkIntArray);
    SAVE_VECTOR(prefix, lut, pd, HueRange, vtkDoubleArray, 2, 1);
    SAVE_VECTOR(prefix, lut, pd, SaturationRange, vtkDoubleArray, 2, 1);
    SAVE_VECTOR(prefix, lut, pd, ValueRange, vtkDoubleArray, 2, 1);
    SAVE_VECTOR(prefix, lut, pd, AlphaRange, vtkDoubleArray, 2, 1);
    SAVE_VECTOR(prefix, lut, pd, NanColor, vtkDoubleArray, 4, 1);
    SAVE_VECTOR(prefix, lut, pd, BelowRangeColor, vtkDoubleArray, 4, 1);
    SAVE_SCALAR(prefix, lut, pd, UseBelowRangeColor, vtkIntArray);
    SAVE_VECTOR(prefix, lut, pd, AboveRangeColor, vtkDoubleArray, 4, 1);
    SAVE_SCALAR(prefix, lut, pd, UseAboveRangeColor, vtkIntArray);
    SAVE_SCALAR(prefix, lut, pd, NumberOfTableValues, vtkIntArray);
    SAVE_SCALAR(prefix, lut, pd, Ramp, vtkIntArray);
    SAVE_SCALAR(prefix, lut, pd, NumberOfColors, vtkIntArray);

    auto Table = vtkSmartPointer<vtkUnsignedCharArray>::New();
    //    Table->SetNumberOfComponents(4);
    //    Table->SetNumberOfTuples(dynamic_cast<vtkLookupTable*>(lut)->GetTable()->GetNumberOfTuples());
    Table->DeepCopy(dynamic_cast<vtkLookupTable*>(lut)->GetTable());
    Table->SetName(
        std::string(arrayPrefix + ":LookupTable:" + "Table").c_str());
    pd->GetFieldData()->AddArray(Table);

    SAVE_SCALAR(arrayPrefix, mapper, pd, ScalarVisibility, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, mapper, pd, Static, vtkIntArray);
    SAVE_VECTOR(arrayPrefix, mapper, pd, ScalarRange, vtkDoubleArray, 2, 1);
    SAVE_SCALAR(arrayPrefix, mapper, pd, UseLookupTableScalarRange,
                vtkIntArray);
    SAVE_SCALAR(arrayPrefix, mapper, pd, ColorMode, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, mapper, pd, InterpolateScalarsBeforeMapping,
                vtkIntArray);
    SAVE_SCALAR(arrayPrefix, mapper, pd, ScalarMode, vtkIntArray);
    SAVE_SCALAR(arrayPrefix, mapper, pd, ResolveCoincidentTopology,
                vtkIntArray);
  }
}

void SaveActorAsFieldData(std::string const& arrayPrefix, vtkActor* actor,
                          vtkPolyData* pd)
{
  SAVE_SCALAR(arrayPrefix, actor, pd, Dragable, vtkIntArray);
  SAVE_SCALAR(arrayPrefix, actor, pd, Pickable, vtkIntArray);
  SAVE_SCALAR(arrayPrefix, actor, pd, Visibility, vtkIntArray);
  SAVE_VECTOR(arrayPrefix, actor, pd, Orientation, vtkDoubleArray, 3, 1);
  SAVE_VECTOR(arrayPrefix, actor, pd, Origin, vtkDoubleArray, 3, 1);
  SAVE_VECTOR(arrayPrefix, actor, pd, Scale, vtkDoubleArray, 3, 1);
  SAVE_SCALAR(arrayPrefix, actor, pd, ForceOpaque, vtkIntArray);
  SAVE_SCALAR(arrayPrefix, actor, pd, ForceTranslucent, vtkIntArray);

  if (actor->GetUserTransform())
  {
    vtkLinearTransform* userTransform = actor->GetUserTransform();
    userTransform->Print(std::cout);
  }

#if 0
UserTransform
UserMatrix
Texture
#endif
}

vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = "";
  if (fileName.find_last_of(".") != std::string::npos)
  {
    extension = fileName.substr(fileName.find_last_of("."));
  }
  // Make the extension lowercase
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);
  if (extension == ".ply")
  {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    // Return a polydata sphere if the extension is unknown.
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->SetThetaResolution(20);
    source->SetPhiResolution(11);
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
} // namespace
