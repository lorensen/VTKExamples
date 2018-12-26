import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkDataSetMapper;
import vtk.vtkPlanes;
import vtk.vtkFrustumSource;
import vtk.vtkShrinkFilter;
import vtk.vtkProperty;
import vtk.vtkCamera;
import vtk.vtkNamedColors;

public class Frustum extends JPanel implements ActionListener {
  private static final long serialVersionUID = 1L;
  private vtkPanel renWin;
  private JButton exitButton;

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
	  
	  
  public Frustum() {
    super(new BorderLayout());
	  
	   
	    
    vtkNamedColors Color = new vtkNamedColors(); 
    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
    //BackFace color 
    double BackColor[] = new double[4];
	   
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("GreenYellow",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("RoyalBlue",BgColor);
    //Change Color Name to Use your own Color for BackFace Color
    Color.GetColor("PeachPuff",BackColor);
	   
	 
	  
    // A virtual camera for 3D rendering
    vtkCamera Camera = new vtkCamera();
    Camera.SetClippingRange(0.1,0.4);
    double PlanesArray[] = new double[24];
	  
    Camera.GetFrustumPlanes(1.0, PlanesArray);
	  
    vtkPlanes Planes = new vtkPlanes();
    Planes.SetFrustumPlanes(PlanesArray);
	  
    //To create a frustum defined by a set of planes. 
    vtkFrustumSource FrustumSource = new vtkFrustumSource();
    FrustumSource.ShowLinesOff();
    FrustumSource.SetPlanes(Planes);
	  
    //shrink cells composing an arbitrary data set
    vtkShrinkFilter shrink = new vtkShrinkFilter();
    shrink.SetInputConnection(FrustumSource.GetOutputPort());
    shrink.SetShrinkFactor(.9);
	  
    //Create a Mapper and Actor
    vtkDataSetMapper Mapper = new vtkDataSetMapper();
    Mapper.SetInputConnection(shrink.GetOutputPort());
	  
    vtkProperty Back = new vtkProperty();
    Back.SetColor(BackColor);
	  
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().EdgeVisibilityOn();
    Actor.GetProperty().SetColor(ActorColor);
    Actor.SetBackfaceProperty(Back);
	   
  
    renWin = new vtkPanel();
    renWin.GetRenderer().AddActor(Actor);
    renWin.resetCamera();
    renWin.GetRenderer().SetBackground(BgColor);
    renWin.resetCamera();
    renWin.GetRenderer().GetActiveCamera().SetPosition(1.0, 0.0,0.0);;
    renWin.GetRenderer().GetActiveCamera().SetFocalPoint(0,0,0);
    renWin.GetRenderer().GetActiveCamera().SetViewUp(0.0,1.0,0.0);;
    renWin.GetRenderer().GetActiveCamera().Azimuth(30);
    renWin.GetRenderer().GetActiveCamera().Elevation(30);
    renWin.GetRenderer().ResetCamera();


    // Add Java UI components
    exitButton = new JButton("Exit");
    exitButton.addActionListener(this);

    add(renWin, BorderLayout.CENTER);
    add(exitButton, BorderLayout.SOUTH);
  }


  /** An ActionListener that listens to the button. */
  public void actionPerformed(ActionEvent e) {
    if (e.getSource().equals(exitButton)) {
      System.exit(0);
    }
  }

  public static void main(String s[]) {
    SwingUtilities.invokeLater(new Runnable() {
        public void run() {
          JFrame frame = new JFrame("Frustum");
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.getContentPane().setLayout(new BorderLayout());
          frame.getContentPane().add(new Frustum(), BorderLayout.CENTER);
          frame.setSize(400, 400);
          frame.setLocationRelativeTo(null);
          frame.setVisible(true);
        }
      });
  }
}  
