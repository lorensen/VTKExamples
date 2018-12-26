import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkSphereSource;
import vtk.vtkTriangleFilter;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyData;
import vtk.vtkMeshQuality;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkDoubleArray;

public class MeshQuality 
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
    vtkNamedColors Color = new vtkNamedColors();

    //Renderer Background Color
    double BgColor[] = new double[4];
		  
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("NavajoWhite",BgColor);

    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    //Sphere.SetCenter(0.0,0.0,0.0);
    phere.SetRadius(5.0);
    Sphere.Update();
		  
    //Change Phi and Theta Value for Smooth Surface
    Sphere.SetPhiResolution(12);
    Sphere.SetThetaResolution(14);
		    	  
    vtkTriangleFilter triangleFilter = new vtkTriangleFilter();
    triangleFilter.SetInputConnection(Sphere.GetOutputPort());
    triangleFilter.Update();
		        
    vtkPolyData Mesh = triangleFilter.GetOutput();
    System.out.println("There are" + " " +  Mesh.GetNumberOfCells() +" "  + "Cells");
		    
		  
    vtkMeshQuality QualityFilter = new vtkMeshQuality();
    QualityFilter.SetInputData(Mesh);
    QualityFilter.SetTriangleQualityMeasureToArea();
    QualityFilter.Update();
		    
	    
    vtkDoubleArray QualityArray = new vtkDoubleArray().FastDownCast(QualityFilter.GetOutput().GetCellData().GetArray("Quality"));
    System.out.println("There are" + QualityArray.GetNumberOfTuples() + "values");
		   
		   
    for(int i=0;i<QualityArray.GetNumberOfTuples();i++)
    {
      double val = QualityArray.GetValue(i);
      System.out.println("Value" + " "+i + " " + val);
			  
    }
		   
    vtkPolyData PolyData = new vtkPolyData();
    PolyData.ShallowCopy(QualityFilter.GetOutput());

    //Create a Mapper and Actor for Sphere
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(PolyData);
		    
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
