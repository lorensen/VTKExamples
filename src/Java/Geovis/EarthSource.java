import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkEarthSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;

//Author: Bharatesh Chakravarthi
//Affiliation: VELab, Chung Ang University, Seoul, South Korea. 
 
public class EarthSource extends JPanel implements ActionListener 
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
  
  
	  public EarthSource() 
	  {
		    super(new BorderLayout());
		    
		    double MyColors[] = new double[4];
		    vtkNamedColors Colors = new vtkNamedColors();
		    Colors.GetColor("Banana",MyColors);
		    
		    vtkEarthSource EarthSource = new vtkEarthSource();
		    EarthSource.OutlineOff();
		    //EarthSource.OutlineOn();
		    EarthSource.Update();
		    
		    
		    //Create a Mapper and Actor
		    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		    Mapper.SetInputConnection(EarthSource.GetOutputPort());
		
		    vtkActor Actor = new vtkActor();
		    Actor.SetMapper(Mapper);
		     Actor.GetProperty().SetColor(MyColors);
		    renWin = new vtkPanel();
		    renWin.GetRenderer().AddActor(Actor);
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
		          JFrame frame = new JFrame("EarthSource");
		          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		          frame.getContentPane().setLayout(new BorderLayout());
		          frame.getContentPane().add(new EarthSource(), BorderLayout.CENTER);
		          frame.setSize(400, 400);
		          frame.setLocationRelativeTo(null);
		          frame.setVisible(true);
		        }
		      });
		}
}
