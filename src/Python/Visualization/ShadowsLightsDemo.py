"""
The scene consists of
 * Four actors: a rectangle, a box, a cone and a sphere.
     The box, the cone and the sphere are above the rectangle.
 * Two spotlights: one in the direction of the box, another one in the direction of the sphere.
     Both lights are above the box, the cone and the sphere.

"""

import vtk


def main():
    interactor = vtk.vtkRenderWindowInteractor()

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(400, 400)
    renderWindow.SetMultiSamples(0)

    renderWindow.SetAlphaBitPlanes(1)
    interactor.SetRenderWindow(renderWindow)

    renderer = vtk.vtkOpenGLRenderer()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(640, 480)

    rectangleSource = vtk.vtkPlaneSource()
    rectangleSource.SetOrigin(-5.0, 0.0, 5.0)
    rectangleSource.SetPoint1(5.0, 0.0, 5.0)
    rectangleSource.SetPoint2(-5.0, 0.0, -5.0)
    rectangleSource.SetResolution(100, 100)

    rectangleMapper = vtk.vtkPolyDataMapper()
    rectangleMapper.SetInputConnection(rectangleSource.GetOutputPort())

    rectangleMapper.SetScalarVisibility(0)

    shadows = vtk.vtkShadowMapPass()

    seq = vtk.vtkSequencePass()

    passes = vtk.vtkRenderPassCollection()
    passes.AddItem(shadows.GetShadowMapBakerPass())
    passes.AddItem(shadows)
    seq.SetPasses(passes)

    cameraP = vtk.vtkCameraPass()
    cameraP.SetDelegatePass(seq)

    # tell the renderer to use our render pass pipeline
    glrenderer = renderer
    glrenderer.SetPass(cameraP)

    colors = vtk.vtkNamedColors()
    boxColor = colors.GetColor3d("Tomato")
    rectangleColor = colors.GetColor3d("Beige")
    coneColor = colors.GetColor3d("Peacock")
    sphereColor = colors.GetColor3d("Banana")

    rectangleActor = vtk.vtkActor()
    rectangleActor.SetMapper(rectangleMapper)
    rectangleActor.VisibilityOn()
    rectangleActor.GetProperty().SetColor(rectangleColor)

    boxSource = vtk.vtkCubeSource()
    boxSource.SetXLength(2.0)

    boxNormals = vtk.vtkPolyDataNormals()
    boxNormals.SetInputConnection(boxSource.GetOutputPort())
    boxNormals.ComputePointNormalsOff()
    boxNormals.ComputeCellNormalsOn()
    boxNormals.Update()
    boxNormals.GetOutput().GetPointData().SetNormals(None)

    boxMapper = vtk.vtkPolyDataMapper()
    boxMapper.SetInputConnection(boxNormals.GetOutputPort())
    boxMapper.ScalarVisibilityOff()

    boxActor = vtk.vtkActor()
    boxActor.SetMapper(boxMapper)
    boxActor.VisibilityOn()
    boxActor.SetPosition(-2.0, 2.0, 0.0)
    boxActor.GetProperty().SetColor(boxColor)

    coneSource = vtk.vtkConeSource()
    coneSource.SetResolution(24)
    coneSource.SetDirection(1.0, 1.0, 1.0)

    coneMapper = vtk.vtkPolyDataMapper()
    coneMapper.SetInputConnection(coneSource.GetOutputPort())
    coneMapper.SetScalarVisibility(0)

    coneActor = vtk.vtkActor()
    coneActor.SetMapper(coneMapper)
    coneActor.VisibilityOn()
    coneActor.SetPosition(0.0, 1.0, 1.0)
    coneActor.GetProperty().SetColor(coneColor)

    sphereSource = vtk.vtkSphereSource()
    sphereSource.SetThetaResolution(32)
    sphereSource.SetPhiResolution(32)

    sphereMapper = vtk.vtkPolyDataMapper()
    sphereMapper.SetInputConnection(sphereSource.GetOutputPort())
    sphereMapper.ScalarVisibilityOff()

    sphereActor = vtk.vtkActor()
    sphereActor.SetMapper(sphereMapper)

    sphereActor.VisibilityOn()
    sphereActor.SetPosition(2.0, 2.0, -1.0)
    sphereActor.GetProperty().SetColor(sphereColor)

    renderer.AddViewProp(rectangleActor)
    renderer.AddViewProp(boxActor)
    renderer.AddViewProp(coneActor)
    renderer.AddViewProp(sphereActor)

    # Spotlights.

    # lighting the box.
    l1 = vtk.vtkLight()
    l1.SetPosition(-4.0, 4.0, -1.0)
    l1.SetFocalPoint(boxActor.GetPosition())
    l1.SetColor(1.0, 1.0, 1.0)
    l1.PositionalOn()
    renderer.AddLight(l1)
    l1.SwitchOn()

    # lighting the sphere
    l2 = vtk.vtkLight()
    l2.SetPosition(4.0, 5.0, 1.0)
    l2.SetFocalPoint(sphereActor.GetPosition())
    l2.SetColor(1.0, 0.0, 1.0)
    l2.PositionalOn()
    renderer.AddLight(l2)
    l2.SwitchOn()

    # For each spotlight, add a light frustum wireframe representation and a cone
    # wireframe representation, colored with the light color.
    angle = l1.GetConeAngle()
    if l1.LightTypeIsSceneLight() and l1.GetPositional() and angle < 180.0:  # spotlight
        la = vtk.vtkLightActor()
        la.SetLight(l1)
        renderer.AddViewProp(la)
    angle = l2.GetConeAngle()
    if l2.LightTypeIsSceneLight() and l2.GetPositional() and angle < 180.0:  # spotlight
        la = vtk.vtkLightActor()
        la.SetLight(l2)
        renderer.AddViewProp(la)

    renderer.SetBackground2(colors.GetColor3d("Silver"))
    renderer.SetBackground(colors.GetColor3d("LightGrey"))
    renderer.SetGradientBackground(True)

    renderWindow.Render()
    renderWindow.SetWindowName('ShadowsLightsDemo')

    renderer.ResetCamera()

    camera = renderer.GetActiveCamera()
    camera.Azimuth(40.0)
    camera.Elevation(10.0)

    renderWindow.Render()

    interactor.Start()


if __name__ == '__main__':
    main()
