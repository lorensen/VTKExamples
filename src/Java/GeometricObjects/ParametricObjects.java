import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkParametricFunctionSource;
import vtk.vtkProperty;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPolyDataMapper;


import vtk.vtkParametricFigure8Klein;
//Uncomment one of the following includes that correspond
//import vtk.vtkParametricBoy;
//import vtk.vtkParametricConicSpiral;
//import vtk.vtkParametricCrossCap ;
//import vtk.vtkParametricDini ;
//import vtk.vtkParametricEllipsoid;
//import vtk.vtkParametricEnneper;
//import vtk.vtkParametricKlein;
//import vtk.vtkParametricMobius;
//import vtk.vtkParametricRandomHills;
//import vtk.vtkParametricRoman;
//import vtk.vtkParametricSpline;
//import vtk.vtkParametricSuperEllipsoid;
//import vtk.vtkParametricSuperToroid;
//import vtk.vtkParametricTorus;




 
public class ParametricObjects extends JPanel implements ActionListener 
{
	  private static final long serialVersionUID = 1L;
	  private vtkPanel renWin;
	  private JButton exitButton;

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
  
  
	  public ParametricObjects() 
	  {
		    super(new BorderLayout());
	    
		    vtkNamedColors Color = new vtkNamedColors();
	  
		    
		    //For Back Color
		    double BackColor[] = new double[4];
		    //For Diffuse Color
		    double DiffuseColor[] = new double[4];
		    //Renderer Background Color
		    double BgColor[] = new double[4];
		  
			   
		   
		    //Change Color Name to Use your own Color for Change Back Color
		    Color.GetColor("Navy",BackColor);
		    //Change Color Name to Use your own Color for Change Diffuse Color
		    Color.GetColor("Red",DiffuseColor);
		    //Change Color Name to Use your own Color for Renderer Background
		    Color.GetColor("Cornsilk",BgColor);

		    
		    vtkParametricFigure8Klein ParametricObject = new vtkParametricFigure8Klein();
		    
		    // Uncomment one of the following and
		    // ensure the matching include (above) is umcommented).
		    //vtkParametricBoy parametricObject = new vtkParametricBoy();
		    //vtkParametricConicSpiral parametricObject = new vtkParametricConicSpiral();
		    //vtkParametricCrossCap parametricObject = new vtkParametricCrossCap();
		    //vtkParametricDini parametricObject = new vtkParametricDini();
		    //vtkParametricEllipsoid parametricObject = new vtkParametricEllipsoid();
		    //vtkParametricEnneper parametricObject = new vtkParametricEnneper();
		    //vtkParametricKlein parametricObject = new vtkParametricKlein();
		    //vtkParametricMobius parametricObject = new vtkParametricMobius();
		    //vtkParametricRandomHills parametricObject = new vtkParametricRandomHills();
		    //vtkParametricRoman parametricObject = new vtkParametricRoman();
		    //vtkParametricSpline parametricObject = new vtkParametricSpline();
		    //vtkParametricSuperEllipsoid parametricObject = new vtkParametricSuperEllipsoid();
		    //vtkParametricSuperToroid parametricObject = new vtkParametricSuperToroid();
		    //vtkParametricToru parametricObject = new vtkParametricToru();
		    
		    
		    
		    vtkParametricFunctionSource parametricFunctionSource = new vtkParametricFunctionSource();
		    parametricFunctionSource.SetParametricFunction(ParametricObject);
		    parametricFunctionSource.Update();

		    
		    vtkProperty BackProperty = new vtkProperty();
		    BackProperty.SetColor(BackColor);
		    
		    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		    Mapper.SetInputConnection(parametricFunctionSource.GetOutputPort());
		    
		    vtkActor Actor = new vtkActor();
		    Actor.SetMapper(Mapper);
		    Actor.GetProperty().SetDiffuseColor(DiffuseColor);
		    Actor.GetProperty().SetSpecular(0.5);
		    Actor.GetProperty().SetSpecularPower(20);
		    Actor.SetBackfaceProperty(BackProperty);
		    

		    renWin = new vtkPanel();
		    renWin.GetRenderer().AddActor(Actor);
		    renWin.GetRenderer().SetBackground(BgColor);
		    renWin.resetCamera();
		  
		    // Add Java UI components
		    exitButton = new JButton("Exit");
		    exitButton.addActionListener(this);

		    add(renWin, BorderLayout.CENTER);
		    add(exitButton, BorderLayout.SOUTH);
	  }

	  /** An ActionListener that listens to the button. */
	  public void actionPerformed(ActionEvent e)
	  {
		  if (e.getSource().equals(exitButton)) 
		  {
			  	System.exit(0);
		  }
	  }

	  public static void main(String s[]) 
	  {
		  SwingUtilities.invokeLater(new Runnable() 
		  {
			  public void run() 
			  {
		        JFrame frame = new JFrame("Parametric Objects");
		        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		        frame.getContentPane().setLayout(new BorderLayout());
		        frame.getContentPane().add(new ParametricObjects(), BorderLayout.CENTER);
		        frame.setSize(400, 400);
		        frame.setLocationRelativeTo(null);
		        frame.setVisible(true);
			  }
		  });
	  }
}
