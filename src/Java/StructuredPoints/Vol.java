import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkStructuredPoints;
import vtk.vtkDoubleArray;
import vtk.vtkContourFilter;

public class Vol 
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
  
	
  public static void main(String args[]) 
  {
    
    int i, j, k, kOffset, jOffset, offset;
    double x, y, z, sp;
    double s;
    
    vtkNamedColors colors = new vtkNamedColors();

    //For Actor Color
    double actorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Salmon", actorColor);
    colors.GetColor("SlateGray", Bgcolor);
    
    vtkStructuredPoints vol = new vtkStructuredPoints();
    vol.SetDimensions(26,26,26);
    vol.SetOrigin(-0.5,-0.5,-0.5);
    sp = 1.0/25.0;
    vol.SetSpacing(sp, sp, sp);
    
    vtkDoubleArray scalars = new vtkDoubleArray();
    scalars.SetNumberOfComponents(1);
    scalars.SetNumberOfTuples(26*26*26);
    for (k=0; k<26; k++)
    {
     z = -0.5 + k*sp;
     kOffset = k * 26 * 26;
     for (j=0; j<26; j++) 
     {
      y = -0.5 + j*sp;
      jOffset = j * 26;
      for (i=0; i<26; i++) 
      {
       x = -0.5 + i*sp;
       s = x*x + y*y + z*z - (0.4*0.4);
       offset = i + jOffset + kOffset;
       scalars.InsertTuple1(offset, s);
      }
     }
    }
    
    vol.GetPointData().SetScalars(scalars);
    vtkContourFilter contour = new vtkContourFilter();
    contour.SetInputData(vol);
    contour.SetValue(0,0.0);
    
    vtkPolyDataMapper volMapper = new vtkPolyDataMapper();
    volMapper.SetInputConnection(contour.GetOutputPort());
    volMapper.ScalarVisibilityOff();
    
    vtkActor volActor = new vtkActor();
    volActor.SetMapper(volMapper);
    volActor.GetProperty().EdgeVisibilityOn();
    volActor.GetProperty().SetColor(actorColor);
	    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(volActor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
