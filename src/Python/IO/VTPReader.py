import vtk

filename = "archive.vtp"

reader = vtk.vtkXMLPolyDataReader()
reader.SetFileName(filename)
reader.Update()

mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(reader.GetOutput())

actor = vtk.vtkActor()
actor.SetMapper(mapper)
