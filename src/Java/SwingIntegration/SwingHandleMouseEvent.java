import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import vtk.*;

public class SwingHandleMouseEvent extends JFrame
{

  static
  {
    System.loadLibrary("vtkCommonJava");
    System.loadLibrary("vtkFilteringJava");
    System.loadLibrary("vtkIOJava");
    System.loadLibrary("vtkImagingJava");
    System.loadLibrary("vtkGraphicsJava");
    System.loadLibrary("vtkRenderingJava");
  }

  public SwingHandleMouseEvent()
  {
    // Create a sphere source
    vtkSphereSource sphere = new vtkSphereSource();
    sphere.SetRadius(10.0);

    // Create a sphere mapper
    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInputConnection(sphere.GetOutputPort());

    //create sphere actor
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);

    // Create a render window panel to display the sphere
    final vtkRenderWindowPanel renderWindowPanel = new vtkRenderWindowPanel();
    renderWindowPanel.setPreferredSize(new Dimension(600, 600));
    renderWindowPanel.setInteractorStyle(new vtkInteractorStyleTrackballCamera());

    add(renderWindowPanel, BorderLayout.CENTER);

    renderWindowPanel.GetRenderer().AddActor(sphereActor);

    // Create a status bar
    JPanel statusBar = new JPanel(new BorderLayout());
    final JLabel label = new JLabel(" ", SwingConstants.RIGHT);
    statusBar.add(label, BorderLayout.EAST);
    statusBar.setBorder(new BevelBorder(BevelBorder.LOWERED));

    add(statusBar, BorderLayout.SOUTH);

    final vtkCellPicker cellPicker = new vtkCellPicker();

    // Show the point on the sphere the mouse is hovering over in the status bar
    renderWindowPanel.addMouseMotionListener(new MouseMotionAdapter()
    {
      public void mouseMoved(MouseEvent e)
      {
        // The call to Pick needs to be surrounded by lock and unlock to prevent crashes.
        renderWindowPanel.lock();
        int pickSucceeded = cellPicker.Pick(e.getX(), renderWindowPanel.getHeight()-e.getY()-1,
            0.0, renderWindowPanel.GetRenderer());
        renderWindowPanel.unlock();

        if (pickSucceeded == 1)
        {
          double[] p = cellPicker.GetPickPosition();
          label.setText("Position: " + p[0] + ", " + p[1] + ", " + p[2]);
        }
        else
        {
          label.setText(" ");
        }
      }
    });
  }

  public static void main(String[] args)
  {
    try
    {
      javax.swing.SwingUtilities.invokeLater(new Runnable()
      {
        public void run()
        {
          JPopupMenu.setDefaultLightWeightPopupEnabled(false);
          ToolTipManager.sharedInstance().setLightWeightPopupEnabled(false);

          JFrame frame = new SwingHandleMouseEvent();
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.pack();
          frame.setVisible(true);
        }
      });    	
    }
    catch (Exception e)
    {
      e.printStackTrace();
    }
  }
}
