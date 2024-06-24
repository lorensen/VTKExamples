import vtk

def main():
    # Generate  some random points
    numberOfPoints = 8
    pointSource = vtk.vtkPointSource()
    pointSource.SetNumberOfPoints(numberOfPoints)
    pointSource.Update()

    points = pointSource.GetOutput().GetPoints()

    spline = vtk.vtkParametricSpline()
    spline.SetPoints(points)

    functionSource = vtk.vtkParametricFunctionSource()
    functionSource.SetParametricFunction(spline)
    functionSource.SetUResolution(10 * numberOfPoints)
    functionSource.SetVResolution(10 * numberOfPoints)
    functionSource.SetWResolution(10 * numberOfPoints)

    # Create the frame
    frame = vtk.vtkFrenetSerretFrame()
    frame.SetInputConnection(functionSource.GetOutputPort())
    frame.ConsistentNormalsOn()
    frame.Update()

    # Setup renderer
    renderer =  vtk.vtkRenderer()
    renderer.SetBackground(.4, .5, .7)
    
    # for each vector, create a Glyph3D and DeepCopy the output
    arrow_radius = .05
    
    for vector, color in zip(["FSNormals", "FSTangents","FSBinormals"], [(0.8900, 0.8100, 0.3400), (1.0000, 0.3882, 0.2784), (0.1804,0.5451,0.3412)]):
        polyData = MakeGlyphs(frame, arrow_radius, vector)
    
        # Setup actors and mappers
        glyphMapper = vtk.vtkPolyDataMapper()
        glyphMapper.SetInputData(normalsPolyData)

        glyphActor = vtk.vtkActor()
        glyphActor.SetMapper(mapper)
        glyphActor.GetProperty().SetColor(color)
        
        renderer.AddActor(glyphActor)

    # Display spline
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(functionSource.GetOutputPort())
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    renderer.AddActor(actor)

    # Setup render window, and interactor
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Pick a good view
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(120)
    renderer.GetActiveCamera().Elevation(30)
    renderer.GetActiveCamera().Dolly(1.8)
    renderer.ResetCameraClippingRange()

    renderWindow.SetSize(640, 480)
    renderWindow.Render()
    renderWindowInteractor.Start()

def MakeGlyphs(frame, arrow_size, vector_name)
    frame.GetOutput().GetPointData().SetActiveVectors(vector_name)
    srcPolyData = frame.GetOutput()
    
    arrow = vtk.vtkArrowSource()
    arrow.SetTipResolution(16)
    arrow.SetTipLength(.3)
    arrow.SetTipRadius(.1)

    glyph = vtk.vtkGlyph3D()
    glyph.SetSourceConnection(arrow.GetOutputPort())
    glyph.SetInputData(srcPolyData)
    glyph.SetVectorModeToUseVector()
    glyph.SetScaleModeToScaleByVector()
    glyph.SetScaleFactor(size)
    glyph.OrientOn()
    glyph.Update()

    normalsPolyData = vtk.vtkPolyData()
    normalsPolyData.DeepCopy(glyph.GetOutput())

    return normalsPolyData
