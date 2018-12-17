import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;


import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkActor;
import vtk.vtkAxes;
import vtk.vtkVectorText;
import vtk.vtkPolyDataMapper;
import vtk.vtkFollower;
import vtk.vtkNamedColors;


public class TextOrigin extends JPanel implements ActionListener {
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
	  
	  
	   public TextOrigin() {
	    super(new BorderLayout());
	   
	    
	   vtkNamedColors Color = new vtkNamedColors(); 
	   //For Text Actor Color
	   double TextActorColor[] = new double[4];
	   //For Renderer Background Color
	   double BgColor[] = new double[4];
	   
	   
	   //Change Color Name to Use your own Color for Change Actor Color
	   Color.GetColor("IndianRed",TextActorColor);
	   //Change Color Name to Use your own Color for Renderer Background
	   Color.GetColor("LightGrey",BgColor);
	
	   
	   // Create the axes and the associated mapper and actor.
	   vtkAxes Axes = new vtkAxes();
	   Axes.SetOrigin(0, 0, 0);
	   
	   vtkPolyDataMapper AxesMapper = new vtkPolyDataMapper();
	   AxesMapper.SetInputConnection(Axes.GetOutputPort());
	   
	   vtkActor AxesActor = new vtkActor();
	   AxesActor.SetMapper(AxesMapper);
	  
	  // Create the 3D text and the associated mapper and follower (a type of actor).  
	  //Position the text so it is displayed over the origin of the axes.
	  vtkVectorText aText = new vtkVectorText();
	  aText.SetText("Origin");
	  
	  
	  vtkPolyDataMapper TextMapper = new vtkPolyDataMapper();
	  TextMapper.SetInputConnection(aText.GetOutputPort());
	  
	  
	  vtkFollower TextActor = new vtkFollower();
	  TextActor.SetMapper(TextMapper);
	  TextActor.SetScale(0.2, 0.2, 0.2);
	  TextActor.AddPosition(0, -0.1, 0);
	  TextActor.GetProperty().SetColor(TextActorColor);

  
	  renWin = new vtkPanel();
	  renWin.GetRenderer().AddActor(TextActor);
	  renWin.GetRenderer().AddActor(AxesActor);
	  renWin.resetCamera();
	  renWin.GetRenderer().SetBackground(BgColor);
	  renWin.setSize(640, 480);
	  renWin.GetRenderer().ResetCamera();
	  renWin.GetRenderer().GetActiveCamera().Zoom(1.6);
	  renWin.GetRenderer().ResetCameraClippingRange();
  
	  
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
	        JFrame frame = new JFrame("Text Origin");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new TextOrigin(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	} 
