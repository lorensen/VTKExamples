import vtk.vtkRenderWindow;
import vtk.vtkAnnotatedCubeActor;
import vtk.vtkCamera;
import vtk.vtkProperty;
import vtk.vtkNativeLibrary;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;

public class AnnotatedCubeActor 
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
  // -------------------------------------------------------------------
   
  public static void main(String args[]) 
  {
    
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double renBgcolor[] = new double[4];

    //Renderer Background Color
     double Cubecolor[] = new double[4];

    //Renderer Cube Text Edge Color
    double CubeTextEdge[] = new double[4];

    //Renderer xText plus and Minus Color
    double Xplus[] = new double[4];
    double Xminus[] = new double[4];

    //Renderer yText plus and Minus Color
    double Yplus[] = new double[4];
    double Yminus[] = new double[4];

    //Renderer zText plus and Minus Color
    double Zplus[] = new double[4];
    double Zminus[] = new double[4];

    colors.GetColor("DeepPink", renBgcolor);
    colors.GetColor("Aquamarine", Cubecolor);
    colors.GetColor("Gold", CubeTextEdge);
    colors.GetColor("Turquoise", Xplus);
    colors.GetColor("Turquoise", Xminus);
    colors.GetColor("Mint", Yplus);
    colors.GetColor("Mint", Yminus);
    colors.GetColor("RoyalBlue", Yplus);
    colors.GetColor("RoyalBlue", Yminus);

    vtkAnnotatedCubeActor Cube = new vtkAnnotatedCubeActor();
    Cube.SetFaceTextScale(0.666667);
    Cube.GetCubeProperty().SetColor(Cubecolor);

    // set up the renderer, window, and interactor
    vtkRenderer ren = new vtkRenderer();
    ren.SetBackground(renBgcolor);
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.SetSize(300,300);

    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // anatomic labelling 
    Cube.SetXPlusFaceText("V");
    Cube.SetXMinusFaceText("T");
    Cube.SetYPlusFaceText("K");
    Cube.SetYMinusFaceText("V");
    Cube.SetZPlusFaceText("T");
    Cube.SetZMinusFaceText("K");

    // change the vector text colors
    Cube.GetTextEdgesProperty().SetColor(CubeTextEdge);
    Cube.GetTextEdgesProperty().SetLineWidth(4);

    vtkProperty Property = new vtkProperty();
    Property = Cube.GetXPlusFaceProperty();
    Property.SetColor(Xplus);
    Property = Cube.GetXMinusFaceProperty();
    Property.SetColor(Xminus);

    Property = Cube.GetYPlusFaceProperty();
    Property.SetColor(Yplus);
    Property = Cube.GetYMinusFaceProperty();
    Property.SetColor(Yminus);

    Property = Cube.GetZPlusFaceProperty();
    Property.SetColor(Zplus);
    Property = Cube.GetZMinusFaceProperty();
    Property.SetColor(Zminus);

    ren.AddActor(Cube);

    // set up an interesting view
    vtkCamera Camera = new vtkCamera();
    Camera.SetViewUp(0, 0, 1);
    Camera.SetFocalPoint(0, 0, 0);
    Camera.SetPosition(4.5, 4.5, 2.5);
    ren.ResetCamera();
    Camera.Dolly(1.4);

    ren.ResetCameraClippingRange();
    ren.GetActiveCamera().Azimuth(40);
    ren.GetActiveCamera().Elevation(30);
    iren.Initialize();
    iren.Start();

  }   
}
