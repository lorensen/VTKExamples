#!/usr/bin/env python

import vtk


def main():
    mc_cases, rotation, label = get_program_parameters()
    if not mc_cases:
        mc_cases = [7]
    else:
        # Ensure that they are unique.
        mc_cases = list(set(mc_cases))
        # Check that they lie in the correct range.
        badCases = []
        for item in mc_cases:
            if abs(int(item) > 14):
                badCases.append(item)
        if badCases:
            print('Bad case number(s)', ','.join(map(str, badCases)))
            for item in badCases:
                mc_cases.remove(item)
            if not mc_cases:
                print('No cases.')
                return
    marching_cubes(mc_cases, rotation, label)


def get_program_parameters():
    import argparse
    description = 'Marching cubes cases for 3D isosurface generation.'
    epilogue = '''
    Marching cubes cases for 3D isosurface generation.
    The 256 possible cases have been reduced to 15 cases using symmetry.
    Dark vertices are greater than the selected isosurface value.
    
    For the cases, enter them as integers separated by a space e.g: 1 2 3  
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('cases', nargs='*', type=int, default=[],
                        help='A list of integers i such that 0 <= abs(i) < 14,  corresponding to the cases desired.')
    parser.add_argument('-r', '--rotation', type=int, default=0,
                        help='Rotate camera around the cube, for i such that 0 <= abs(i) < 4,\
                          corresponding to 0, 90, 180, 270 degrees.')
    # Use a mutually exclusive group.
    label_parser = parser.add_mutually_exclusive_group(required=False)
    label_parser.add_argument('-l', '--label', action='store_true', dest='label',
                              help='Display a label, true by default.')
    label_parser.add_argument('-n', '--no_label', action='store_false', dest='label',
                              help='Supress diaplaying a label.')
    parser.set_defaults(label=True)
    args = parser.parse_args()
    return args.cases, args.rotation, args.label


def marching_cubes(mcCases, rotation=0, label=True):
    color = vtk.vtkNamedColors()

    # Rotate the final figure 0, 90, 180, 270 degrees.
    rotation = abs(int(rotation))
    if rotation > 3:
        rotation = 0

    if len(mcCases) > 1:
        print('Cases', ', '.join(map(str, mcCases)))
    else:
        print('Cases', ','.join(map(str, mcCases)))
    print('Rotated', rotation * 90, 'degrees.')

    renWin = vtk.vtkRenderWindow()
    renWin.SetSize(640, 480)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Always use a grid of four columns unless number of cases < 4.
    renderers = list()
    gridSize = ((len(mcCases) + 3) // 4) * 4
    if len(mcCases) < 4:
        gridSize = len(mcCases)
    for i in range(0, gridSize):
        # Create the Renderer
        renderer = vtk.vtkRenderer()
        renderers.append(renderer)
        # Set the background color.
        renderers[i].SetBackground(color.GetColor3d("slate_grey"))
        renWin.AddRenderer(renderer)

    for i in range(0, len(mcCases)):
        # Define a Single Cube
        Scalars = vtk.vtkFloatArray()
        Scalars.InsertNextValue(1.0)
        Scalars.InsertNextValue(0.0)
        Scalars.InsertNextValue(0.0)
        Scalars.InsertNextValue(1.0)
        Scalars.InsertNextValue(0.0)
        Scalars.InsertNextValue(0.0)
        Scalars.InsertNextValue(0.0)
        Scalars.InsertNextValue(0.0)

        Points = vtk.vtkPoints()
        Points.InsertNextPoint(0, 0, 0)
        Points.InsertNextPoint(1, 0, 0)
        Points.InsertNextPoint(1, 1, 0)
        Points.InsertNextPoint(0, 1, 0)
        Points.InsertNextPoint(0, 0, 1)
        Points.InsertNextPoint(1, 0, 1)
        Points.InsertNextPoint(1, 1, 1)
        Points.InsertNextPoint(0, 1, 1)

        Ids = vtk.vtkIdList()
        Ids.InsertNextId(0)
        Ids.InsertNextId(1)
        Ids.InsertNextId(2)
        Ids.InsertNextId(3)
        Ids.InsertNextId(4)
        Ids.InsertNextId(5)
        Ids.InsertNextId(6)
        Ids.InsertNextId(7)

        Grid = vtk.vtkUnstructuredGrid()
        Grid.Allocate(10, 10)
        Grid.InsertNextCell(12, Ids)
        Grid.SetPoints(Points)
        Grid.GetPointData().SetScalars(Scalars)

        # Find the triangles that lie along the 0.5 contour in this cube.
        Marching = vtk.vtkContourFilter()
        Marching.SetInputData(Grid)
        Marching.SetValue(0, 0.5)
        Marching.Update()

        # Extract the edges of the triangles just found.
        triangleEdges = vtk.vtkExtractEdges()
        triangleEdges.SetInputConnection(Marching.GetOutputPort())

        # Draw the edges as tubes instead of lines.  Also create the associated
        # mapper and actor to display the tubes.
        triangleEdgeTubes = vtk.vtkTubeFilter()
        triangleEdgeTubes.SetInputConnection(triangleEdges.GetOutputPort())
        triangleEdgeTubes.SetRadius(.005)
        triangleEdgeTubes.SetNumberOfSides(6)
        triangleEdgeTubes.UseDefaultNormalOn()
        triangleEdgeTubes.SetDefaultNormal(.577, .577, .577)

        triangleEdgeMapper = vtk.vtkPolyDataMapper()
        triangleEdgeMapper.SetInputConnection(triangleEdgeTubes.GetOutputPort())
        triangleEdgeMapper.ScalarVisibilityOff()

        triangleEdgeActor = vtk.vtkActor()
        triangleEdgeActor.SetMapper(triangleEdgeMapper)
        triangleEdgeActor.GetProperty().SetDiffuseColor(
            color.GetColor3d("lamp_black"))
        triangleEdgeActor.GetProperty().SetSpecular(.4)
        triangleEdgeActor.GetProperty().SetSpecularPower(10)

        # Shrink the triangles we found earlier.  Create the associated mapper
        # and actor.  Set the opacity of the shrunken triangles.
        aShrinker = vtk.vtkShrinkPolyData()
        aShrinker.SetShrinkFactor(1)
        aShrinker.SetInputConnection(Marching.GetOutputPort())

        aMapper = vtk.vtkPolyDataMapper()
        aMapper.ScalarVisibilityOff()
        aMapper.SetInputConnection(aShrinker.GetOutputPort())

        Triangles = vtk.vtkActor()
        Triangles.SetMapper(aMapper)
        Triangles.GetProperty().SetDiffuseColor(
            color.GetColor3d("banana"))
        Triangles.GetProperty().SetOpacity(.6)

        # Draw a cube the same size and at the same position as the one
        # created previously.  Extract the edges because we only want to see
        # the outline of the cube.  Pass the edges through a vtkTubeFilter so
        # they are displayed as tubes rather than lines.
        CubeModel = vtk.vtkCubeSource()
        CubeModel.SetCenter(.5, .5, .5)

        Edges = vtk.vtkExtractEdges()
        Edges.SetInputConnection(CubeModel.GetOutputPort())

        Tubes = vtk.vtkTubeFilter()
        Tubes.SetInputConnection(Edges.GetOutputPort())
        Tubes.SetRadius(.01)
        Tubes.SetNumberOfSides(6)
        Tubes.UseDefaultNormalOn()
        Tubes.SetDefaultNormal(.577, .577, .577)
        # Create the mapper and actor to display the cube edges.
        TubeMapper = vtk.vtkPolyDataMapper()
        TubeMapper.SetInputConnection(Tubes.GetOutputPort())
        CubeEdges = vtk.vtkActor()
        CubeEdges.SetMapper(TubeMapper)
        CubeEdges.GetProperty().SetDiffuseColor(
            color.GetColor3d("khaki"))
        CubeEdges.GetProperty().SetSpecular(.4)
        CubeEdges.GetProperty().SetSpecularPower(10)

        # Create a sphere to use as a glyph source for vtkGlyph3D.
        Sphere = vtk.vtkSphereSource()
        Sphere.SetRadius(0.04)
        Sphere.SetPhiResolution(20)
        Sphere.SetThetaResolution(20)
        # Remove the part of the cube with data values below 0.5.
        ThresholdIn = vtk.vtkThresholdPoints()
        ThresholdIn.SetInputData(Grid)
        ThresholdIn.ThresholdByUpper(.5)
        # Display spheres at the vertices remaining in the cube data set after
        # it was passed through vtkThresholdPoints.
        Vertices = vtk.vtkGlyph3D()
        Vertices.SetInputConnection(ThresholdIn.GetOutputPort())
        Vertices.SetSourceConnection(Sphere.GetOutputPort())
        # Create a mapper and actor to display the glyphs.
        SphereMapper = vtk.vtkPolyDataMapper()
        SphereMapper.SetInputConnection(Vertices.GetOutputPort())
        SphereMapper.ScalarVisibilityOff()

        CubeVertices = vtk.vtkActor()
        CubeVertices.SetMapper(SphereMapper)
        CubeVertices.GetProperty().SetDiffuseColor(
            color.GetColor3d("tomato"))

        # Define the text for the label
        caseLabel = vtk.vtkVectorText()
        caseLabel.SetText("Case 1")

        if label:
            # Set up a transform to move the label to a new position.
            aLabelTransform = vtk.vtkTransform()
            aLabelTransform.Identity()
            # Position the label according to the rotation of the figure.
            if rotation == 0:
                aLabelTransform.Translate(-0.2, 0, 1.25)
                aLabelTransform.Scale(.05, .05, .05)
            elif rotation == 1:
                aLabelTransform.RotateY(90)
                aLabelTransform.Translate(-1.25, 0, 1.25)
                aLabelTransform.Scale(.05, .05, .05)
            elif rotation == 2:
                aLabelTransform.RotateY(180)
                aLabelTransform.Translate(-1.25, 0, 0.2)
                aLabelTransform.Scale(.05, .05, .05)
            else:
                aLabelTransform.RotateY(270)
                aLabelTransform.Translate(-0.2, 0, 0.2)
                aLabelTransform.Scale(.05, .05, .05)

            # Move the label to a new position.
            labelTransform = vtk.vtkTransformPolyDataFilter()
            labelTransform.SetTransform(aLabelTransform)
            labelTransform.SetInputConnection(caseLabel.GetOutputPort())

            # Create a mapper and actor to display the text.
            labelMapper = vtk.vtkPolyDataMapper()
            labelMapper.SetInputConnection(labelTransform.GetOutputPort())

            labelActor = vtk.vtkActor()
            labelActor.SetMapper(labelMapper)

        # Define the base that the cube sits on.  Create its associated mapper
        # and actor.  Set the position of the actor.
        baseModel = vtk.vtkCubeSource()
        baseModel.SetXLength(1.5)
        baseModel.SetYLength(.01)
        baseModel.SetZLength(1.5)

        baseMapper = vtk.vtkPolyDataMapper()
        baseMapper.SetInputConnection(baseModel.GetOutputPort())

        base = vtk.vtkActor()
        base.SetMapper(baseMapper)
        base.SetPosition(.5, -0.09, .5)

        # Set the scalar values for this case of marching cubes.
        # A negative case number will generate a complementary case
        mcCase = mcCases[i]
        if mcCase < 0:
            cases[-mcCase](Scalars, caseLabel, 0, 1)
        else:
            cases[mcCase](Scalars, caseLabel, 1, 0)
        # Force the grid to update.
        Grid.Modified()

        # Add the actors to the renderer
        renderers[i].AddActor(triangleEdgeActor)
        renderers[i].AddActor(base)
        if label:
            renderers[i].AddActor(labelActor)
        renderers[i].AddActor(CubeEdges)
        renderers[i].AddActor(CubeVertices)
        renderers[i].AddActor(Triangles)

        # Position the camera.
        renderers[i].GetActiveCamera().Dolly(1.2)
        # Rotate the camera an extra 30 degrees so the cube is not face on.
        if rotation == 0:
            renderers[i].GetActiveCamera().Azimuth(30)
        elif rotation == 1:
            renderers[i].GetActiveCamera().Azimuth(30 + 90)
        elif rotation == 2:
            renderers[i].GetActiveCamera().Azimuth(30 + 180)
        else:
            renderers[i].GetActiveCamera().Azimuth(30 + 270)

        renderers[i].GetActiveCamera().Elevation(20)
        renderers[i].ResetCamera()
        renderers[i].ResetCameraClippingRange()
        if i > 0:
            renderers[i].SetActiveCamera(renderers[0].GetActiveCamera())

    # Setup viewports for the renderers
    rendererSize = 300
    xGridDimensions = 4
    if len(mcCases) < 4:
        xGridDimensions = len(mcCases)
    yGridDimensions = (len(mcCases) - 1) // 4 + 1
    print("Grid dimensions, (x, y): ({:d}, {:d})".format(xGridDimensions, yGridDimensions))
    renWin.SetSize(
        rendererSize * xGridDimensions, rendererSize * yGridDimensions)
    for row in range(0, yGridDimensions):
        for col in range(0, xGridDimensions):
            index = row * xGridDimensions + col

            # (xmin, ymin, xmax, ymax)
            viewport = [
                float(col) / xGridDimensions,
                float(yGridDimensions - (row + 1)) / yGridDimensions,
                float(col + 1) / xGridDimensions,
                float(yGridDimensions - row) / yGridDimensions]

            renderers[index].SetViewport(viewport)

    iren.Initialize()
    renWin.Render()
    iren.Start()


def case0(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, OUT)
    scalars.InsertValue(1, OUT)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, OUT)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 0 - 00000000")
    else:
        caseLabel.SetText("Case 0c - 11111111")


def case1(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, OUT)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, OUT)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 1 - 00000001")
    else:
        caseLabel.SetText("Case 1c - 11111110")


def case2(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, IN)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, OUT)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 2 - 00000011")
    else:
        caseLabel.SetText("Case 2c - 11111100")


def case3(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, OUT)
    scalars.InsertValue(2, IN)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, OUT)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 3 - 00000101")
    else:
        caseLabel.SetText("Case 3c - 11111010")


def case4(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, OUT)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, IN)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 4 - 01000001")
    else:
        caseLabel.SetText("Case 4c - 10111110")


def case5(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, OUT)
    scalars.InsertValue(1, IN)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, IN)
    scalars.InsertValue(5, IN)
    scalars.InsertValue(6, OUT)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 5 - 00110010")
    else:
        caseLabel.SetText("Case 5c - 11001101")


def case6(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, OUT)
    scalars.InsertValue(1, IN)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, IN)
    scalars.InsertValue(4, IN)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, OUT)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 6 - 00011010")
    else:
        caseLabel.SetText("Case 6c - 11100101")


def case7(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, IN)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, IN)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 7 - 01000011")
    else:
        caseLabel.SetText("Case 7c - 10111100")


def case8(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, IN)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, IN)
    scalars.InsertValue(5, IN)
    scalars.InsertValue(6, OUT)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 8 - 00110011")
    else:
        caseLabel.SetText("Case 8c - 11001100")


def case9(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, OUT)
    scalars.InsertValue(1, IN)
    scalars.InsertValue(2, IN)
    scalars.InsertValue(3, IN)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, IN)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 9 - 01001110")
    else:
        caseLabel.SetText("Case 9c - 10110001")


def case10(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, OUT)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, IN)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, IN)
    scalars.InsertValue(6, IN)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 10 - 01101001")
    else:
        caseLabel.SetText("Case 10c - 10010110")


def case11(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, OUT)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, OUT)
    scalars.InsertValue(4, IN)
    scalars.InsertValue(5, IN)
    scalars.InsertValue(6, IN)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 11 - 01110001")
    else:
        caseLabel.SetText("Case 11c - 10001110")


def case12(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, OUT)
    scalars.InsertValue(1, IN)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, IN)
    scalars.InsertValue(4, IN)
    scalars.InsertValue(5, IN)
    scalars.InsertValue(6, OUT)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 12 - 00111010")
    else:
        caseLabel.SetText("Case 12c - 11000101")


def case13(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, OUT)
    scalars.InsertValue(1, IN)
    scalars.InsertValue(2, OUT)
    scalars.InsertValue(3, IN)
    scalars.InsertValue(4, IN)
    scalars.InsertValue(5, OUT)
    scalars.InsertValue(6, IN)
    scalars.InsertValue(7, OUT)
    if IN == 1:
        caseLabel.SetText("Case 13 - 01011010")
    else:
        caseLabel.SetText("Case 13c - 10100101")


def case14(scalars, caseLabel, IN, OUT):
    scalars.InsertValue(0, IN)
    scalars.InsertValue(1, OUT)
    scalars.InsertValue(2, IN)
    scalars.InsertValue(3, IN)
    scalars.InsertValue(4, OUT)
    scalars.InsertValue(5, IN)
    scalars.InsertValue(6, IN)
    scalars.InsertValue(7, IN)
    if IN == 1:
        caseLabel.SetText("Case 14 - 11101101")
    else:
        caseLabel.SetText("Case 14c - 00010010")


cases = [case0, case1, case2, case3, case4, case5, case6, case7, case8, case9, case10, case11, case12, case13, case14]

if __name__ == '__main__':
    main()
