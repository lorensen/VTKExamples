reader = vtk.vtkXMLPolyDataReader()
path = os.path.join(constant.BASE_DIR, "archive.vtp") #Archive path
reader.SetFileName(path)
reader.Update()

mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(reader.GetOutput())

actor = vtk.vtkActor()
actor.SetMapper(mapper)
