import vtk.vtkActor;
import vtk.vtkCylinderSource;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderer;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;

// Then we define our class.
public class CylinderExample {
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

    // now the main program
    public static void main(String args[]) {
        vtkNamedColors colors = new vtkNamedColors();

        // Here is how you create your own named color.
        double bkgColor[];
        bkgColor = new double[]{0.1, 0.2, 0.4, 1.0};
        // This corresponds to the unsigned char array
        // {26, 51, 102, 255} seen in C++ code for setting
        // colors not in vtkNamedColors.
        colors.SetColor("BkgColor", bkgColor);

        // Now we use our own named color.
        double bkg[] = new double[4];
        colors.GetColor("BkgColor", bkg);

        //For Actor Color
        double actorColor[] = new double[4];
        colors.GetColor("Tomato", actorColor);
        //Renderer Background Color

        // This creates a polygonal cylinder model with eight circumferential facets
        // (i.e, in practice an octagonal prism).
        vtkCylinderSource cylinder = new vtkCylinderSource();
        cylinder.SetResolution(8);

        // The actor is a grouping mechanism: besides the geometry (mapper), it
        // also has a property, transformation matrix, and/or texture map.
        // Here we set its color and rotate it around the X and Y axes.
        vtkPolyDataMapper cylinderMapper = new vtkPolyDataMapper();
        cylinderMapper.SetInputConnection(cylinder.GetOutputPort());

        vtkActor cylinderActor = new vtkActor();
        cylinderActor.SetMapper(cylinderMapper);
        cylinderActor.GetProperty().SetColor(actorColor);
        cylinderActor.RotateX(30.0);
        cylinderActor.RotateY(-45.0);

        // The renderer generates the image
        // which is then displayed on the render window.
        // It can be thought of as a scene to which the actor is added
        vtkRenderer ren = new vtkRenderer();
        ren.AddActor(cylinderActor);
        ren.ResetCamera();
        ren.GetActiveCamera().Zoom(1.5);
        ren.SetBackground(bkg);

        // The render window is the actual GUI window
        // that appears on the computer screen
        vtkRenderWindow renWin = new vtkRenderWindow();
        renWin.AddRenderer(ren);
        renWin.SetSize(300, 300);
        renWin.SetWindowName("Cylinder");


        // The render window interactor captures mouse events
        // and will perform appropriate camera or actor manipulation
        // depending on the nature of the events.
        vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
        iren.SetRenderWindow(renWin);

        renWin.Render();

        iren.Initialize();
        // This starts the event loop and as a side effect causes an initial render.
        iren.Start();
    }
}
