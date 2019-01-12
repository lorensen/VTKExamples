# Contributed by Eric E Monson

import vtk


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor('bkg', [0.2, 0.3, 0.7, 1.0])

    # create a rendering window and renderer
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)

    # create a renderwindowinteractor
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    cube = vtk.vtkCubeSource()
    cube.SetXLength(200)
    cube.SetYLength(200)
    cube.SetZLength(200)
    cube.Update()
    cm = vtk.vtkPolyDataMapper()
    cm.SetInputConnection(cube.GetOutputPort())
    ca = vtk.vtkActor()
    ca.SetMapper(cm)
    ca.GetProperty().SetColor(colors.GetColor3d("BurlyWood"))

    # assign actor to the renderer
    ren.AddActor(ca)
    ren.SetBackground(colors.GetColor3d('bkg'))

    axesActor = vtk.vtkAnnotatedCubeActor()
    axesActor.SetXPlusFaceText('R')
    axesActor.SetXMinusFaceText('L')
    axesActor.SetYMinusFaceText('H')
    axesActor.SetYPlusFaceText('F')
    axesActor.SetZMinusFaceText('P')
    axesActor.SetZPlusFaceText('A')
    axesActor.GetTextEdgesProperty().SetColor(colors.GetColor3d("Yellow"))
    axesActor.GetTextEdgesProperty().SetLineWidth(2)
    axesActor.GetCubeProperty().SetColor(colors.GetColor3d("Blue"))
    axes = vtk.vtkOrientationMarkerWidget()
    axes.SetOrientationMarker(axesActor)
    axes.SetInteractor(iren)
    axes.EnabledOn()
    axes.InteractiveOn()
    ren.ResetCamera()

    # enable user interface interactor
    iren.Initialize()
    renWin.Render()
    ren.GetActiveCamera().SetPosition(-151.5, 540.1, 364.0)
    ren.GetActiveCamera().SetViewUp(0.2, 0.6, -0.8)
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
