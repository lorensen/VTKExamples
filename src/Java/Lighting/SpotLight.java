import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkLight;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPolyDataMapper;
import vtk.vtkPlaneSource;
import vtk.vtkNamedColors;


public class SpotLight extends JPanel implements ActionListener {
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
	  
	  
  public SpotLight() {
    super(new BorderLayout());
	   
	   
    vtkNamedColors Color = new vtkNamedColors(); 
    //For greenLight 
    double greenLightColor[] = new double[4];
    //For PinkLight 
    double pinkLightColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
    //Renderer Background1 Color
    double BgColor2[] = new double[4];
	   
	   
    //Change Color Name to Use your own Color 
    Color.GetColor("Lawn_green",greenLightColor);
    //Change Color Name to Use your own Color 
    Color.GetColor("DeepPink",pinkLightColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("RoyalBlue",BgColor);
    //Change Color Name to Use your own Color for Renderer Background1
    Color.GetColor("SkyBlue",BgColor2);
	   
    vtkPlaneSource PlaneSource = new vtkPlaneSource();
    PlaneSource.SetOrigin(-5.0, 0.0, 5.0);
    PlaneSource.SetPoint1(5.0, 0.0, 5.0);
    PlaneSource.SetPoint2(-5.0, 0.0, -5.0);
    PlaneSource.SetResolution(100, 100);
	  
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(PlaneSource.GetOutputPort());
	  
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
	  
	  
	
	  
    vtkLight greenLight = new vtkLight();
    greenLight.PositionalOn();
    greenLight.SetPosition(-4.0, 4.0, -1.0);
    greenLight.SetColor(greenLightColor);
    greenLight.SetIntensity(0.5);
	  
	  
    vtkLight pinkLight = new vtkLight();
    pinkLight.PositionalOn();
    pinkLight.SetPosition(4.0, 5.0,1.0);
    pinkLight.SetColor(pinkLightColor);
    pinkLight.SetIntensity(0.6);
	

    renWin = new vtkPanel();
    renWin.GetRenderer().AddActor(Actor);
    renWin.GetRenderer().SetBackground(BgColor);
    renWin.GetRenderer().SetBackground2(BgColor2);
    renWin.GetRenderer().AddLight(greenLight);
    renWin.GetRenderer().AddLight(pinkLight);
    renWin.setSize(640,480);
    renWin.resetCamera();
    renWin.GetRenderer().GetActiveCamera().Azimuth(40);
    renWin.GetRenderer().GetActiveCamera().Elevation(30);
    renWin.resetCameraClippingRange();

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
          JFrame frame = new JFrame("Spot Light");
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.getContentPane().setLayout(new BorderLayout());
          frame.getContentPane().add(new SpotLight(), BorderLayout.CENTER);
          frame.setSize(400, 400);
          frame.setLocationRelativeTo(null);
          frame.setVisible(true);
        }
      });
  }
}  
