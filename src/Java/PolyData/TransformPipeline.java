import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkCylinderSource;
import vtk.vtkTransform;

public class TransformPipeline
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
   vtkNamedColors colors = new vtkNamedColors();
   
   //For arm Color
   double armColor[] = new double[4];
   //For forearm Color
   double forearmColor[] = new double[4];
   //For hand Color
   double handColor[] = new double[4];
   //Renderer Background Color
   double Bgcolor[] = new double[4];
   
   colors.GetColor("DarkKhaki", armColor);
   colors.GetColor("Blue", forearmColor);
   colors.GetColor("GreenYellow", handColor);
   colors.GetColor("MidnightBlue", Bgcolor);
   
   //arm
   vtkCylinderSource arm = new vtkCylinderSource();
   arm.SetRadius(8);
   arm.SetHeight(20);
   arm.SetResolution(20);
   
   vtkPolyDataMapper armMapper = new vtkPolyDataMapper();
   armMapper.SetInputConnection(arm.GetOutputPort());

   vtkTransform armTransform = new vtkTransform();
        
   vtkActor armActor = new vtkActor();
   armActor.SetUserTransform(armTransform);
   armActor.SetMapper(armMapper);
   armActor.GetProperty().SetColor(armColor);
        
   //forearm
   vtkCylinderSource forearm = new vtkCylinderSource();
   forearm.SetRadius(6);
   forearm.SetHeight(15);
   forearm.SetResolution(20);
   forearm.SetCenter(0, 10.5, -2.5);;

   vtkPolyDataMapper forearmMapper = new vtkPolyDataMapper();
   forearmMapper.SetInputConnection(forearm.GetOutputPort());

   vtkTransform forearmTransform = new vtkTransform();
   forearmTransform.SetInput(armTransform);

   vtkActor forearmActor = new vtkActor();
   forearmActor.SetUserTransform(forearmTransform);
   forearmActor.SetMapper(forearmMapper);
   forearmActor.GetProperty().SetColor(forearmColor);
    
   //hand
   vtkCylinderSource hand = new vtkCylinderSource();
   hand.SetRadius(4);
   hand.SetHeight(10);
   hand.SetResolution(20);
   hand.SetCenter(0, 18.5, -2.5);

   vtkPolyDataMapper handMapper = new vtkPolyDataMapper();
   handMapper.SetInputConnection(hand.GetOutputPort());

   vtkTransform handTransform = new vtkTransform();
   handTransform.SetInput(forearmTransform);

   vtkActor handActor = new vtkActor();
   handActor.SetUserTransform(handTransform);
   handActor.SetMapper(handMapper);
   handActor.GetProperty().SetColor(handColor);
	    
   // Create the renderer, render window and interactor.
   vtkRenderer ren = new vtkRenderer();
   vtkRenderWindow renWin = new vtkRenderWindow();
   renWin.AddRenderer(ren);
   vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
   iren.SetRenderWindow(renWin);
        
   ren.AddActor(armActor);
   ren.AddActor(forearmActor);
   ren.AddActor(handActor);
   ren.SetBackground(Bgcolor);
   renWin.Render();
    
   //execution of robot arm motion
   for (int i = 0; i<45; i++)
   {
    armTransform.Identity();
    armTransform.RotateZ(-i);
    renWin.Render();
   }
   //execution of robot forearm motion
   for (int i = 0; i<45; i++)
   {
    forearmTransform.Identity();
    forearmTransform.RotateZ(i);
    renWin.Render();
   }
   iren.Start();
  }
}
