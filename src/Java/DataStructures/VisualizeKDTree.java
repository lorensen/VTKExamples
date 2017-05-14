import vtk.*;

public class VisualizeKDTree
{

  static
  {
    System.loadLibrary("vtkCommonJava");
    System.loadLibrary("vtkFilteringJava");
    System.loadLibrary("vtkIOJava");
    System.loadLibrary("vtkImagingJava");
    System.loadLibrary("vtkGraphicsJava");
    System.loadLibrary("vtkRenderingJava");
    System.loadLibrary("vtkWidgetsJava");
  }

  static class vtkSliderCallback
  {
    void Execute()
    {
      this.Level = (int)Math.round(((vtkSliderRepresentation)SliderWidget.GetRepresentation()).GetValue());
      this.KdTree.GenerateRepresentation(this.Level, this.PolyData);
      this.Renderer.Render();
    }

    vtkKdTreePointLocator KdTree;
    int Level = 0;
    vtkPolyData PolyData;
    vtkRenderer Renderer;
    vtkSliderWidget SliderWidget;
  }

  public static void main(String[] args)
  {
    // Create a point cloud
    vtkPointSource pointSource = new vtkPointSource();
    pointSource.SetRadius(4);
    pointSource.SetNumberOfPoints(1000);
    pointSource.Update();

    vtkPolyDataMapper pointsMapper = new vtkPolyDataMapper();
    pointsMapper.SetInputConnection(pointSource.GetOutputPort());

    vtkActor pointsActor = new vtkActor();
    pointsActor.SetMapper(pointsMapper);
    pointsActor.GetProperty().SetInterpolationToFlat();

    int maxLevel = 20;
    // Create the tree
    vtkKdTreePointLocator kdTree = new vtkKdTreePointLocator();
    kdTree.SetDataSet(pointSource.GetOutput());
    kdTree.AutomaticOff();
    kdTree.SetMaxLevel(maxLevel);
    kdTree.BuildLocator();

    // Initialize the representation
    vtkPolyData polydata = new vtkPolyData();
    kdTree.GenerateRepresentation(0, polydata);

    vtkPolyDataMapper octreeMapper = new vtkPolyDataMapper();
    octreeMapper.SetInputConnection(polydata.GetProducerPort());

    vtkActor octreeActor = new vtkActor();
    octreeActor.SetMapper(octreeMapper);
    octreeActor.GetProperty().SetInterpolationToFlat();
    octreeActor.GetProperty().SetRepresentationToWireframe();

    // A renderer and render window
    vtkRenderer renderer = new vtkRenderer();
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.AddRenderer(renderer);

    // An interactor
    vtkRenderWindowInteractor renderWindowInteractor =
      new vtkRenderWindowInteractor();
    renderWindowInteractor.SetRenderWindow(renderWindow);

    // Add the actors to the scene
    renderer.AddActor(pointsActor);
    renderer.AddActor(octreeActor);

    // Render an image (lights and cameras are created automatically)
    renderWindow.Render();

    vtkSliderRepresentation2D sliderRep = new vtkSliderRepresentation2D();
    sliderRep.SetMinimumValue(0);
    sliderRep.SetMaximumValue(kdTree.GetLevel());
    sliderRep.SetValue(0);
    sliderRep.SetTitleText("Level");
    sliderRep.GetPoint1Coordinate().SetCoordinateSystemToNormalizedDisplay();
    sliderRep.GetPoint1Coordinate().SetValue(.2, .2);
    sliderRep.GetPoint2Coordinate().SetCoordinateSystemToNormalizedDisplay();
    sliderRep.GetPoint2Coordinate().SetValue(.8, .2);
    sliderRep.SetSliderLength(0.075);
    sliderRep.SetSliderWidth(0.05);
    sliderRep.SetEndCapLength(0.05);

    vtkSliderWidget sliderWidget = new vtkSliderWidget();
    sliderWidget.SetInteractor(renderWindowInteractor);
    sliderWidget.SetRepresentation(sliderRep);
    sliderWidget.SetAnimationModeToAnimate();
    sliderWidget.EnabledOn();

    vtkSliderCallback callback = new vtkSliderCallback();
    callback.KdTree = kdTree;
    callback.PolyData = polydata;
    callback.Renderer = renderer;
    callback.SliderWidget = sliderWidget;

    sliderWidget.AddObserver("InteractionEvent", callback, "Execute");

    renderWindowInteractor.Initialize();
    renderWindow.Render();

    renderWindowInteractor.Start();
  }
}
