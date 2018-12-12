#include <vtkSmartPointer.h>
#include <vtkColorSeries.h>

#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkLookupTable.h>
#include <vtkFloatArray.h>
#include <vtkCellData.h>
#include <vtkPolyData.h>
#include <vtkPlaneSource.h>

#include <map>
#include <vector>
#include <string>

namespace {
void CreateLookupTableVTKBlue(vtkSmartPointer<vtkLookupTable> &lut,
                              int tableSize = 0);
void CreateLookupTableVTKBrown(vtkSmartPointer<vtkLookupTable> &lut,
                               int tableSize = 0);
void CreateLookupTableVTKRed(vtkSmartPointer<vtkLookupTable> &lu,
                             int tableSize = 0);
void CreateLookupTableVTKOrange(vtkSmartPointer<vtkLookupTable> &lu,
                                int tableSize = 0);
void CreateLookupTableVTKWhite(vtkSmartPointer<vtkLookupTable> &lu,
                               int tableSize = 0);
void CreateLookupTableVTKGrey(vtkSmartPointer<vtkLookupTable> &lu,
                              int tableSize = 0);
void CreateLookupTableVTKMagenta(vtkSmartPointer<vtkLookupTable> &lu,
                                 int tableSize = 0);
void CreateLookupTableVTKCyan(vtkSmartPointer<vtkLookupTable> &lu,
                                 int tableSize = 0);
void CreateLookupTableVTKYellow(vtkSmartPointer<vtkLookupTable> &lu,
                                int tableSize = 0);
}

int main (int argc, char *argv[])
{
  std::string seriesName = "Red";
  if (argc > 1)
  {
    seriesName = argv[1];
  }

  // Provide some geometry
  int resolution = 6;
  vtkSmartPointer<vtkPlaneSource> aPlane =
    vtkSmartPointer<vtkPlaneSource>::New();
  aPlane->SetXResolution(resolution);
  aPlane->SetYResolution(resolution);

  // Create cell data
  vtkSmartPointer<vtkFloatArray> cellData =
    vtkSmartPointer<vtkFloatArray>::New();
  for (int i = 0; i < resolution * resolution; i++)
  {
    cellData->InsertNextValue(i);
  }
  aPlane->Update(); // Force an update so we can set cell data
  aPlane->GetOutput()->GetCellData()->SetScalars(cellData);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  if (seriesName == "Blue")
    {
      CreateLookupTableVTKBlue(lut, resolution * resolution + 1);
    }
  else if (seriesName == "Brown")
  {
    CreateLookupTableVTKBrown(lut, resolution * resolution + 1);
  }
  else if (seriesName == "Red")
  {
    CreateLookupTableVTKRed(lut, resolution * resolution + 1);

  }
  else if (seriesName == "Orange")
  {
    CreateLookupTableVTKOrange(lut, resolution * resolution + 1);

  }
  else if (seriesName == "White")
  {
    CreateLookupTableVTKWhite(lut, resolution * resolution + 1);

  }
  else if (seriesName == "Grey")
  {
    CreateLookupTableVTKGrey(lut, resolution * resolution + 1);

  }
  else if (seriesName == "Magenta")
  {
    CreateLookupTableVTKMagenta(lut, resolution * resolution + 1);

  }
  else if (seriesName == "Cyan")
  {
    CreateLookupTableVTKCyan(lut, resolution * resolution + 1);

  }
  else if (seriesName == "Yellow")
  {
    CreateLookupTableVTKYellow(lut, resolution * resolution + 1);

  }
  else
  {
    std::cout << "Bad series name: " << seriesName << std::endl;
    return EXIT_FAILURE;
  }

  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetLookupTable(lut);
  mapper->SetInputConnection(aPlane->GetOutputPort());
  mapper->SetScalarModeToUseCellData();
  mapper->SetScalarRange(0, resolution * resolution + 1);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOn();

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace {
void CreateLookupTableVTKBlue(vtkSmartPointer<vtkLookupTable> &lut,
                              int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKBlueColors");

  myColors->AddColor(vtkColor3ub(240,  248,  255)); // alice_blue
  myColors->AddColor(vtkColor3ub(  0,    0,  255)); // blue 
  myColors->AddColor(vtkColor3ub(173,  216,  230)); // blue_light 
  myColors->AddColor(vtkColor3ub( 0,    0,  205)); // blue_medium 
  myColors->AddColor(vtkColor3ub(95,  158,  160)); // cadet 
  myColors->AddColor(vtkColor3ub(61,   89,  171)); // cobalt 
  myColors->AddColor(vtkColor3ub(100,  149,  237)); // cornflower 
  myColors->AddColor(vtkColor3ub( 5,  184,  204)); // cerulean 
  myColors->AddColor(vtkColor3ub(30,  144,  255)); // dodger_blue 
  myColors->AddColor(vtkColor3ub(75,    0,  130)); // indigo 
  myColors->AddColor(vtkColor3ub( 3,  168,  158)); // manganese_blue 
  myColors->AddColor(vtkColor3ub(25,   25,  112)); // midnight_blue 
  myColors->AddColor(vtkColor3ub( 0,    0,  128)); // navy 
  myColors->AddColor(vtkColor3ub(51,  161,  201)); // peacock 
  myColors->AddColor(vtkColor3ub(176,  224,  230)); // powder_blue 
  myColors->AddColor(vtkColor3ub(65,  105,  225)); // royal_blue 
  myColors->AddColor(vtkColor3ub(106,   90,  205)); // slate_blue 
  myColors->AddColor(vtkColor3ub(72,   61,  139)); // slate_blue_dark 
  myColors->AddColor(vtkColor3ub(132,  112,  255)); // slate_blue_light 
  myColors->AddColor(vtkColor3ub(123,  104,  238)); // slate_blue_medium 
  myColors->AddColor(vtkColor3ub(135,  206,  235)); // sky_blue 
  myColors->AddColor(vtkColor3ub(0,  191,  255)); // sky_blue_deep 
  myColors->AddColor(vtkColor3ub(135,  206,  250)); // sky_blue_light 
  myColors->AddColor(vtkColor3ub(70,  130,  180)); // steel_blue 
  myColors->AddColor(vtkColor3ub(176,  196,  222)); // steel_blue_light 
  myColors->AddColor(vtkColor3ub(0,  199,  140)); // turquoise_blue 
  myColors->AddColor(vtkColor3ub(18,   10,  143)); // ultramarine 
  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}

void CreateLookupTableVTKBrown(vtkSmartPointer<vtkLookupTable> &lut,
                               int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKBrownColors");

  myColors->AddColor(vtkColor3ub( 245, 245, 220)); // beige 
  myColors->AddColor(vtkColor3ub( 165, 42, 42)); // brown 
  myColors->AddColor(vtkColor3ub( 219, 41, 41)); // brown_madder 
  myColors->AddColor(vtkColor3ub( 135, 66, 31)); // brown_ochre 
  myColors->AddColor(vtkColor3ub( 222, 184, 135)); // burlywood 
  myColors->AddColor(vtkColor3ub( 138, 54, 15)); // burnt_sienna 
  myColors->AddColor(vtkColor3ub( 138, 51, 36)); // burnt_umber 
  myColors->AddColor(vtkColor3ub( 210, 105, 30)); // chocolate 
  myColors->AddColor(vtkColor3ub( 115, 61, 26)); // deep_ochre 
  myColors->AddColor(vtkColor3ub( 255, 125, 64)); // flesh 
  myColors->AddColor(vtkColor3ub( 255, 87, 33)); // flesh_ochre 
  myColors->AddColor(vtkColor3ub( 199, 120, 38)); // gold_ochre 
  myColors->AddColor(vtkColor3ub( 255, 61, 13)); // greenish_umber 
  myColors->AddColor(vtkColor3ub( 240, 230, 140)); // khaki 
  myColors->AddColor(vtkColor3ub( 189, 183, 107)); // khaki_dark 
  myColors->AddColor(vtkColor3ub( 245, 245, 220)); // light_beige 
  myColors->AddColor(vtkColor3ub(  205, 133, 63)); // peru 
  myColors->AddColor(vtkColor3ub( 188, 143, 143)); // rosy_brown 
  myColors->AddColor(vtkColor3ub( 199, 97, 20)); // raw_sienna 
  myColors->AddColor(vtkColor3ub( 115, 74, 18)); // raw_umber 
  myColors->AddColor(vtkColor3ub( 94, 38, 18)); // sepia 
  myColors->AddColor(vtkColor3ub( 160, 82, 45)); // sienna 
  myColors->AddColor(vtkColor3ub( 139, 69, 19)); // saddle_brown 
  myColors->AddColor(vtkColor3ub( 244, 164, 96)); // sandy_brown 
  myColors->AddColor(vtkColor3ub( 210, 180, 140)); // tan 
  myColors->AddColor(vtkColor3ub( 94, 38, 5)); // van_dyke_brown 
  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}

void CreateLookupTableVTKRed(vtkSmartPointer<vtkLookupTable> &lut,
                             int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKRedColors");

  myColors->AddColor(vtkColor3ub(227, 38, 54)); // alizarin_crimson 
  myColors->AddColor(vtkColor3ub( 156, 102, 31)); // brick 
  myColors->AddColor(vtkColor3ub( 227, 23, 13)); // cadmium_red_deep 
  myColors->AddColor(vtkColor3ub( 255, 127, 80)); // coral 
  myColors->AddColor(vtkColor3ub( 240, 128, 128)); // coral_light 
  myColors->AddColor(vtkColor3ub( 255, 20, 147)); // deep_pink 
  myColors->AddColor(vtkColor3ub( 212, 61, 26)); // english_red 
  myColors->AddColor(vtkColor3ub( 178, 34, 34)); // firebrick 
  myColors->AddColor(vtkColor3ub( 227, 18, 48)); // geranium_lake 
  myColors->AddColor(vtkColor3ub( 255, 105, 180)); // hot_pink 
  myColors->AddColor(vtkColor3ub( 176, 23, 31)); // indian_red 
  myColors->AddColor(vtkColor3ub( 255, 160, 122)); // light_salmon 
  myColors->AddColor(vtkColor3ub( 227, 46, 48)); // madder_lake_deep 
  myColors->AddColor(vtkColor3ub( 128, 0, 0)); // maroon 
  myColors->AddColor(vtkColor3ub( 255, 192, 203)); // pink 
  myColors->AddColor(vtkColor3ub( 255, 182, 193)); // pink_light 
  myColors->AddColor(vtkColor3ub( 135, 38, 87)); // raspberry 
  myColors->AddColor(vtkColor3ub( 255, 0, 0)); // red 
  myColors->AddColor(vtkColor3ub( 227, 54, 56)); // rose_madder 
  myColors->AddColor(vtkColor3ub( 250, 128, 114)); // salmon 
  myColors->AddColor(vtkColor3ub( 255, 99, 71)); // tomato 
  myColors->AddColor(vtkColor3ub( 212, 26, 31)); // venetian_red 
  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}

void CreateLookupTableVTKGrey(vtkSmartPointer<vtkLookupTable> &lut,
                             int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKGreyColors");
  myColors->AddColor(vtkColor3ub( 128, 138, 135)); // cold_grey
  myColors->AddColor(vtkColor3ub( 105, 105, 105)); // dim_grey
  myColors->AddColor(vtkColor3ub( 192, 192, 192)); // grey
  myColors->AddColor(vtkColor3ub( 211, 211, 211)); // light_grey
  myColors->AddColor(vtkColor3ub( 112, 128, 144)); // slate_grey
  myColors->AddColor(vtkColor3ub( 47, 79, 79)); // slate_grey_dark
  myColors->AddColor(vtkColor3ub( 119, 136, 153)); // slate_grey_light
  myColors->AddColor(vtkColor3ub( 128, 128, 105)); // warm_grey

  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}

void CreateLookupTableVTKWhite(vtkSmartPointer<vtkLookupTable> &lut,
                             int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKWhiteColors");
  myColors->AddColor(vtkColor3ub( 250, 235, 215)); // antique_white
  myColors->AddColor(vtkColor3ub( 240, 255, 255)); // azure
  myColors->AddColor(vtkColor3ub( 255, 228, 196)); // bisque
  myColors->AddColor(vtkColor3ub( 255, 235, 205)); // blanched_almond
  myColors->AddColor(vtkColor3ub( 255, 248, 220)); // cornsilk
  myColors->AddColor(vtkColor3ub( 252, 230, 201)); // eggshell
  myColors->AddColor(vtkColor3ub( 255, 250, 240)); // floral_white
  myColors->AddColor(vtkColor3ub( 220, 220, 220)); // gainsboro
  myColors->AddColor(vtkColor3ub( 248, 248, 255)); // ghost_white
  myColors->AddColor(vtkColor3ub( 240, 255, 240)); // honeydew
  myColors->AddColor(vtkColor3ub( 255, 255, 240)); // ivory
  myColors->AddColor(vtkColor3ub( 230, 230, 250)); // lavender
  myColors->AddColor(vtkColor3ub( 255, 240, 245)); // lavender_blush
  myColors->AddColor(vtkColor3ub( 255, 250, 205)); // lemon_chiffon
  myColors->AddColor(vtkColor3ub( 250, 240, 230)); // linen
  myColors->AddColor(vtkColor3ub( 245, 255, 250)); // mint_cream
  myColors->AddColor(vtkColor3ub( 255, 228, 225)); // misty_rose
  myColors->AddColor(vtkColor3ub( 255, 228, 181)); // moccasin
  myColors->AddColor(vtkColor3ub( 255, 222, 173)); // navajo_white
  myColors->AddColor(vtkColor3ub( 253, 245, 230)); // old_lace
  myColors->AddColor(vtkColor3ub( 255, 239, 213)); // papaya_whip
  myColors->AddColor(vtkColor3ub( 255, 218, 185)); // peach_puff
  myColors->AddColor(vtkColor3ub( 255, 245, 238)); // seashell
  myColors->AddColor(vtkColor3ub( 255, 250, 250)); // snow
  myColors->AddColor(vtkColor3ub( 216, 191, 216)); // thistle
  myColors->AddColor(vtkColor3ub( 252, 255, 240)); // titanium_white
  myColors->AddColor(vtkColor3ub( 245, 222, 179)); // wheat
  myColors->AddColor(vtkColor3ub( 255, 255, 255)); // white
  myColors->AddColor(vtkColor3ub( 245, 245, 245)); // white_smoke
  myColors->AddColor(vtkColor3ub( 252, 247, 255)); // zinc_white

  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}

void CreateLookupTableVTKOrange(vtkSmartPointer<vtkLookupTable> &lut,
                             int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKOrangeColors");

  myColors->AddColor(vtkColor3ub( 255, 97, 3)); // admium_orange
  myColors->AddColor(vtkColor3ub( 255, 3, 13)); // cadmium_red_light
  myColors->AddColor(vtkColor3ub( 237, 145, 33)); // carrot
  myColors->AddColor(vtkColor3ub( 255, 140, 0)); // dark_orange
  myColors->AddColor(vtkColor3ub( 150, 69, 20)); // mars_orange
  myColors->AddColor(vtkColor3ub( 227, 112, 26)); // mars_yellow
  myColors->AddColor(vtkColor3ub( 255, 165, 0)); // orange
  myColors->AddColor(vtkColor3ub( 255, 69, 0)); // orange_red
  myColors->AddColor(vtkColor3ub( 227, 130, 23)); // yellow_ochre
  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}

void CreateLookupTableVTKMagenta(vtkSmartPointer<vtkLookupTable> &lut,
                             int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKMagentaColors");

  myColors->AddColor(vtkColor3ub( 138, 43, 226)); // blue_violet
  myColors->AddColor(vtkColor3ub( 145, 33, 158)); // cobalt_violet_deep
  myColors->AddColor(vtkColor3ub( 255, 0, 255)); // magenta
  myColors->AddColor(vtkColor3ub( 218, 112, 214)); // orchid
  myColors->AddColor(vtkColor3ub( 153, 50, 204)); // orchid_dark
  myColors->AddColor(vtkColor3ub( 186, 85, 211)); // orchid_medium
  myColors->AddColor(vtkColor3ub( 219, 38, 69)); // permanent_red_violet
  myColors->AddColor(vtkColor3ub( 221, 160, 221)); // plum
  myColors->AddColor(vtkColor3ub( 128, 0, 128)); // purple
  myColors->AddColor(vtkColor3ub( 147, 112, 219)); // purple_medium
  myColors->AddColor(vtkColor3ub( 92, 36, 110)); // ultramarine_violet
  myColors->AddColor(vtkColor3ub( 238, 130, 238)); // violet
  myColors->AddColor(vtkColor3ub( 148, 0, 211)); // violet_dark
  myColors->AddColor(vtkColor3ub( 208, 32, 144)); // violet_red
  myColors->AddColor(vtkColor3ub( 199, 21, 133)); // violet_red_medium
  myColors->AddColor(vtkColor3ub( 219, 112, 147)); // violet_red_pale

  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}

void CreateLookupTableVTKCyan(vtkSmartPointer<vtkLookupTable> &lut,
                             int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKCyanColors");

  myColors->AddColor(vtkColor3ub( 127, 255, 212)); // aquamarine
  myColors->AddColor(vtkColor3ub( 102, 205, 170)); // aquamarine_medium
  myColors->AddColor(vtkColor3ub(  0, 255, 255)); // cyan
  myColors->AddColor(vtkColor3ub( 224, 255, 255)); // cyan_white
  myColors->AddColor(vtkColor3ub( 64, 224, 208)); // turquoise
  myColors->AddColor(vtkColor3ub( 0, 206, 209)); // turquoise_dark
  myColors->AddColor(vtkColor3ub( 72, 209, 204)); // turquoise_medium
  myColors->AddColor(vtkColor3ub( 175, 238, 238)); // turquoise_pale

  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}

void CreateLookupTableVTKYellow(vtkSmartPointer<vtkLookupTable> &lut,
                             int size)
{
  vtkSmartPointer<vtkColorSeries> myColors =
    vtkSmartPointer<vtkColorSeries>::New();
  myColors->SetColorSchemeByName("VTKYellowColors");

  myColors->AddColor(vtkColor3ub( 255, 168, 36)); // ureoline_yellow
  myColors->AddColor(vtkColor3ub( 227, 207, 87)); // banana
  myColors->AddColor(vtkColor3ub( 255, 227, 3)); // cadmium_lemon
  myColors->AddColor(vtkColor3ub( 255, 153, 18)); // cadmium_yellow
  myColors->AddColor(vtkColor3ub( 255, 176, 15)); // cadmium_yellow_light
  myColors->AddColor(vtkColor3ub( 255, 215, 0)); // gold
  myColors->AddColor(vtkColor3ub( 218, 165, 32)); // goldenrod
  myColors->AddColor(vtkColor3ub( 184, 134, 11)); // goldenrod_dark
  myColors->AddColor(vtkColor3ub( 250, 250, 210)); // goldenrod_light
  myColors->AddColor(vtkColor3ub( 238, 232, 170)); // goldenrod_pale
  myColors->AddColor(vtkColor3ub( 238, 221, 130)); // 
  myColors->AddColor(vtkColor3ub( 227, 168, 105)); // melon
  myColors->AddColor(vtkColor3ub( 255, 168, 18)); // naples_yellow_deep
  myColors->AddColor(vtkColor3ub( 255, 255, 0)); // yellow
  myColors->AddColor(vtkColor3ub( 255, 255, 224)); // yellow_light

  int numberOfColors = myColors->GetNumberOfColors();
  std::cout << "Number of colors: " << numberOfColors << std::endl;  
  lut->SetNumberOfTableValues (size == 0 ? numberOfColors : size);
  lut->SetTableRange(0, lut->GetNumberOfTableValues());
  for (int i = 0; i < lut->GetNumberOfTableValues(); ++i)
  {
    vtkColor3ub color = myColors->GetColorRepeating(i);
    lut->SetTableValue(
      i, color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
  }
}
}

