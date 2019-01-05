import vtk.vtkActor;
import vtk.vtkFloatArray;
import vtk.vtkLookupTable;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPlaneSource;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderer;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;

public class ColorCells {
  private static final long serialVersionUID = 1L;

  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
  static {
    if (!vtkNativeLibrary.LoadAllNativeLibraries()) {
      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) {
        if (!lib.IsLoaded()) {
          System.out.println(lib.GetLibraryName() + " not loaded");
        }
      }
    }
    vtkNativeLibrary.DisableOutputWindow(null);
  }
  // -----------------------------------------------------------------

  public static void main(String s[]) {
    // Provide some geometry
    int xResolution = 3;
    int yResolution = 3;

    vtkPlaneSource aPlane = new vtkPlaneSource();
    aPlane.SetXResolution(xResolution);
    aPlane.SetYResolution(yResolution);

    // Create cell data
    vtkFloatArray cellData = new vtkFloatArray();
    for (int i = 0; i < xResolution * yResolution; i++) {
      cellData.InsertNextValue(i + 1);
    }

    // Fill in a few known colors, the rest will be generated if needed
    vtkNamedColors color = new vtkNamedColors();

    //Renderer Background Color
    double BgColor[] = new double[4];
    color.GetColor("DarkGray", BgColor);

    // Assign some colors to an array
    double[][] tableColors = new double[11][4];
    color.GetColor("Black", tableColors[0]);
    color.GetColor("Banana", tableColors[1]);
    color.GetColor("Tomato", tableColors[2]);
    color.GetColor("Wheat", tableColors[3]);
    color.GetColor("Lavender", tableColors[4]);
    color.GetColor("Flesh", tableColors[5]);
    color.GetColor("Raspberry", tableColors[6]);
    color.GetColor("Salmon", tableColors[7]);
    color.GetColor("Mint", tableColors[8]);
    color.GetColor("Peacock", tableColors[9]);
    color.GetColor("DarkGray", tableColors[10]);

    // Create a lookup table to map cell data to colors
    vtkLookupTable lut = new vtkLookupTable();
    int tableSize = Math.max(xResolution * yResolution + 1, 10);
    lut.SetNumberOfTableValues(tableSize);
    lut.Build();

    for (int i = 0; i < tableSize; ++i) {
      lut.SetTableValue(i, tableColors[i]);
    }

    // Force an update so we can set cell data
    aPlane.Update();
    aPlane.GetOutput().GetCellData().SetScalars(cellData);

    // Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(aPlane.GetOutputPort());
    mapper.SetScalarRange(0, tableSize - 1);
    mapper.SetLookupTable(lut);

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the arrow
    ren.AddActor(actor);
    ren.SetBackground(BgColor);
    ren.ResetCamera();

    renWin.SetSize(600, 600);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
} 
