import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPlaneSource;
import vtk.vtkFloatArray;
import vtk.vtkLookupTable;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;

public class ColorCells 
{
  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
  static 
  {
    if (!vtkNativeLibrary.LoadAllNativeLibraries()) 
    {
      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) 
      {
        if (!lib.IsLoaded()) 
        {
          System.out.println(lib.GetLibraryName() + " not loaded");
        }
      }
    }
    vtkNativeLibrary.DisableOutputWindow(null);
  }
  // -----------------------------------------------------------------

  public static void main(String s[]) 
  {
    // Provide some geometry
    int resolution = 3;
		   
    vtkPlaneSource aPlane = new vtkPlaneSource();
    aPlane.SetXResolution(resolution);
    aPlane.SetYResolution(resolution);
		   
    // Create cell data
    vtkFloatArray cellData = new vtkFloatArray();
    for (int i = 0; i < resolution * resolution; i++)
    {
      cellData.InsertNextValue(i+1);
    }

    // Create a lookup table to map cell data to colors 
    vtkLookupTable LUT = new vtkLookupTable();
    int tableSize = Math.max(resolution*resolution+1, 10);
    LUT.SetNumberOfTableValues(tableSize);
    LUT.Build();
		   
    // Fill in a few known colors, the rest will be generated if needed
    vtkNamedColors Color = new vtkNamedColors(); 
		   
    //For Tablevalue 0
    double Table0Color[] = new double[4];
		   
    //For Tablevalue 1
    double Table1Color[] = new double[4];
		   
    //For Tablevalue 2
    double Table2Color[] = new double[4];
		   
    //For Tablevalue 3
    double Table3Color[] = new double[4];
		   
    //For Tablevalue 4
    double Table4Color[] = new double[4];
		   
    //For Tablevalue 5
    double Table5Color[] = new double[4];
		   
    //For Tablevalue 6
    double Table6Color[] = new double[4];
		   
    //For Tablevalue 7
    double Table7Color[] = new double[4];
		   
    //For Tablevalue 8
    double Table8Color[] = new double[4];
		   
    //For Tablevalue 9
    double Table9Color[] = new double[4];
		   
    //Renderer Background Color
    double BgColor[] = new double[4];
		   
    //Change Color Name to Use your own Color for Table 0
    Color.GetColor("Black",Table0Color);
		   
    //Change Color Name to Use your own Color for Table 1
    Color.GetColor("Banana",Table1Color);
		   
    //Change Color Name to Use your own Color for Table 2
    Color.GetColor("Tomato",Table2Color);
		   
    //Change Color Name to Use your own Color for Table 3
    Color.GetColor("Wheat",Table3Color);
		   
    //Change Color Name to Use your own Color for Table 4
    Color.GetColor("Lavender",Table4Color);
		   
    //Change Color Name to Use your own Color for Table 5
    Color.GetColor("Flesh",Table5Color);
		   
    //Change Color Name to Use your own Color for Table 6
    Color.GetColor("Raspberry",Table6Color);
		   
    //Change Color Name to Use your own Color for Table 7
    Color.GetColor("Salmon",Table7Color);
		   
    //Change Color Name to Use your own Color for Table 8
    Color.GetColor("Mint",Table8Color);
		   
    //Change Color Name to Use your own Color for Table 9
    Color.GetColor("Peacock",Table9Color);
		   
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("DarkGray",BgColor);
		     
    LUT.SetTableValue(0, Table0Color);
    LUT.SetTableValue(1, Table1Color);
    LUT.SetTableValue(2, Table2Color);
    LUT.SetTableValue(3, Table3Color);
    LUT.SetTableValue(4, Table4Color);
    LUT.SetTableValue(5, Table5Color);
    LUT.SetTableValue(6, Table6Color);
    LUT.SetTableValue(7, Table7Color);
    LUT.SetTableValue(8, Table8Color);
		   
    // Force an update so we can set cell data
    aPlane.Update();
    aPlane.GetOutput().GetCellData().SetScalars(cellData);

    // Create a mapper and actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(aPlane.GetOutputPort());
    Mapper.SetScalarRange(0, tableSize-1);
    Mapper.SetLookupTable(LUT);

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);

		 	  
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
		    
    // Visualise the arrow
    ren.AddActor(Actor);
    ren.SetBackground(BgColor);
    ren.ResetCamera();
	      
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
 
  }
} 
