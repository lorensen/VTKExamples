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
import vtk.vtkPolyDataMapper;
import vtk.vtkDiskSource;



//Author: Bharatesh Chakravarthi
//Affiliation: VE Lab, Chung Ang University, Seoul, South Korea. 


public class Disk extends JPanel implements ActionListener 
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
	  
	  
	  public Disk() 
	  {
	    
			super(new BorderLayout());

		  //Create a Disk
		  vtkDiskSource Disk = new vtkDiskSource();
		  
	 
		  //Create a Mapper and Actor
		  vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		  Mapper.SetInputConnection(Disk.GetOutputPort());

		  vtkActor Actor = new vtkActor();
		  Actor.SetMapper(Mapper);
		  Actor.GetProperty().SetColor(1.0, 1.0, 0.5);  
		   
		  renWin = new vtkPanel();
		  renWin.GetRenderer().AddActor(Actor);
		  renWin.GetRenderer().SetBackground(0.1, 0.0, 0.1);
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
	        JFrame frame = new JFrame("Disk");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new Disk(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
}
