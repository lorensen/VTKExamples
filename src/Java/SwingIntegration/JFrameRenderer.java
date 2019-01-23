import java.awt.*;
import javax.swing.*;

import vtk.*;

public class JFrameRenderer extends JFrame {

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

  private vtkRenderWindowPanel renderWindowPanel;

  public JFrameRenderer() {
    vtkNamedColors colors = new vtkNamedColors();

    double bkg[] = new double[4];
    double actorColor[] = new double[4];
    colors.GetColor("RoyalBlue", bkg);
    colors.GetColor("LemonChiffon", actorColor);

    // Create a sphere source
    vtkSphereSource sphere = new vtkSphereSource();
    sphere.SetRadius(10.0);

    // Create a sphere mapper
    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInputConnection(sphere.GetOutputPort());

    //create sphere actor
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);
    sphereActor.GetProperty().SetColor(actorColor);

    // Create a render window panel to display the sphere
    renderWindowPanel = new vtkRenderWindowPanel();
    renderWindowPanel.setPreferredSize(new Dimension(600, 600));
    renderWindowPanel.setInteractorStyle(new vtkInteractorStyleTrackballCamera());

    add(renderWindowPanel, BorderLayout.CENTER);

    renderWindowPanel.GetRenderer().AddActor(sphereActor);
    renderWindowPanel.GetRenderer().SetBackground(bkg);
  }

  public static void main(String[] args) {
    try {
      SwingUtilities.invokeLater(new Runnable() {
        public void run() {
          JPopupMenu.setDefaultLightWeightPopupEnabled(false);
          ToolTipManager.sharedInstance().setLightWeightPopupEnabled(false);

          JFrame frame = new JFrameRenderer();
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.pack();
          frame.setVisible(true);
          ((JFrameRenderer) frame).render();
        }
      });
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public void render() {
    renderWindowPanel.Render();
  }
}
