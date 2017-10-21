import vtk


def main():
    '''One render window, multiple viewports'''
    rw = vtk.vtkRenderWindow()
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(rw)
    # Define viewport ranges
    xmins = [0, .5, 0, .5]
    xmaxs = [0.5, 1, 0.5, 1]
    ymins = [0, 0, .5, .5]
    ymaxs = [0.5, 0.5, 1, 1]
    for i in range(4):
        ren = vtk.vtkRenderer()
        rw.AddRenderer(ren)
        ren.SetViewport(xmins[i], ymins[i], xmaxs[i], ymaxs[i])

        # Create a sphere
        sphereSource = vtk.vtkSphereSource()
        sphereSource.SetCenter(0.0, 0.0, 0.0)
        sphereSource.SetRadius(5)

        # Create a mapper and actor
        mapper = vtk.vtkPolyDataMapper()
        mapper.SetInputConnection(sphereSource.GetOutputPort())
        actor = vtk.vtkActor()
        actor.SetMapper(mapper)
        ren.AddActor(actor)
        ren.ResetCamera()

    rw.Render()
    rw.SetWindowName('RW: Multiple ViewPorts')
    iren.Start()


if __name__ == '__main__':
    main()
