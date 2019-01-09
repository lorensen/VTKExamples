import vtk


def main():
    # setup sphere
    sphereSource = vtk.vtkSphereSource()
    sphereSource.Update()

    polydata = vtk.vtkPolyData()
    polydata.ShallowCopy(sphereSource.GetOutput())

    normals = polydata.GetPointData().GetNormals()
    normals.SetName("TestN")

    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName("Test.vtp")
    writer.SetInput(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
