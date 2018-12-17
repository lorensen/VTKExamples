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
import vtk.vtkSphereSource;
import vtk.vtkMultiBlockDataSet;
import vtk.vtkCompositePolyDataMapper2;
import vtk.vtkCompositeDataDisplayAttributes;
import vtk.vtkNamedColors;


public class CompositePolyDataMapper extends JPanel implements ActionListener {
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
	  
	  
	   public CompositePolyDataMapper() {
	    super(new BorderLayout());
	   
	    
	   vtkNamedColors Color = new vtkNamedColors(); 
	   //For Actor Color
	   double ActorColor[] = new double[4];
	   //For Renderer Background Color
	   double BgColor[] = new double[4];
	   
	   
	   //Change Color Name to Use your own Color for Change Actor Color
	   Color.GetColor("Red",ActorColor);
	   //Change Color Name to Use your own Color for Renderer Background
	   Color.GetColor("Black",BgColor);
	
	   
  	   vtkSphereSource Sphere1 = new vtkSphereSource();
	   Sphere1.SetRadius(3);
	   Sphere1.SetCenter(0, 0, 0);
	   Sphere1.Update();
	   
	   vtkSphereSource Sphere2 = new vtkSphereSource();
	   Sphere2.SetRadius(2);
	   Sphere2.SetCenter(2, 0, 0);
	   Sphere2.Update();
	   
	   vtkMultiBlockDataSet MBDS = new vtkMultiBlockDataSet();
	   MBDS.SetNumberOfBlocks(3);
	   MBDS.SetBlock(0, Sphere1.GetOutput());
	   // Leave block 1 NULL.  
	   //NULL blocks are valid and should be handled by algorithms that process multiblock datasets.  
	   //Especially when running in parallel where the blocks owned by other processes are NULL in this process
	   MBDS.SetBlock(2, Sphere2.GetOutput());
	   
	   vtkCompositePolyDataMapper2 Mapper = new vtkCompositePolyDataMapper2();
	   Mapper.SetInputDataObject(MBDS);
	   
	   
	   vtkCompositeDataDisplayAttributes CDSA = new vtkCompositeDataDisplayAttributes();
	   Mapper.SetCompositeDataDisplayAttributes(CDSA);
	   // You can use the vtkCompositeDataDisplayAttributes to set the color,
	   // opacity and visibiliy of individual blocks of the multiblock dataset.
	   // Attributes are mapped by block pointers (vtkDataObject*), so these can
	   // be queried by their flat index through a convenience function in the
	   // attribute class (vtkCompositeDataDisplayAttributes::DataObjectFromIndex).
	   // Alternatively, one can set attributes directly through the mapper using
	   // flat indices.
	   // This sets the block at flat index 3 red
	   // Note that the index is the flat index in the tree, so the whole multiblock
	   // is index 0 and the blocks are flat indexes 1, 2 and 3.  This affects
	   // the block returned by mbds->GetBlock(2)
	   Mapper.SetBlockColor(3, ActorColor);
	   
	   
	   vtkActor Actor = new vtkActor();
	   Actor.SetMapper(Mapper);

	  renWin = new vtkPanel();
	  renWin.GetRenderer().AddActor(Actor);
	  renWin.resetCamera();
	  renWin.GetRenderer().SetBackground(BgColor);
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
	        JFrame frame = new JFrame("CompositePolyDataMapper");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new CompositePolyDataMapper(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	} 
