#!/usr/bin/env python

import os
import sys

import vtk


def get_program_parameters():
    import argparse
    description = 'Demonstrates physically based rendering, image based lighting and a skybox.'
    epilogue = '''
Physically based rendering sets color, metallicity and roughness of the object.
Image based lighting uses a cubemap texture to specify the environment.
A Skybox is used to create the illusion of distant three-dimensional surroundings.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('path', help='The path to the cubemap files e.g. skyboxes/skybox2/')
    parser.add_argument('surface', nargs='?', default='Boy', help="The surface to use. Boy's surface is the default.")
    args = parser.parse_args()
    return args.path, args.surface


def main():
    if not vtk_version_ok(8, 90, 0):
        print('You need VTK version 8.90 or greater to run this program.')
        return
    cube_path, surface = get_program_parameters()
    if not os.path.isdir(cube_path):
        print('This path does not exist:', cube_path)
        return
    surface = surface.lower()
    available_surfaces = {'boy', 'mobius', 'randomhills', 'torus', 'sphere', 'cube'}
    if surface not in available_surfaces:
        surface = 'boy'
    if surface == 'mobius':
        source = GetMobius()
    elif surface == 'randomhills':
        source = GetRandomHills()
    elif surface == 'torus':
        source = GetTorus()
    elif surface == 'sphere':
        source = GetSphere()
    elif surface == 'cube':
        source = GetCube()
    else:
        source = GetBoy()

    # Load the cube map
    # cubemap = ReadCubeMap(cube_path, '/', '.jpg', 0)
    cubemap = ReadCubeMap(cube_path, '/', '.jpg', 1)
    # cubemap = ReadCubeMap(cube_path, '/skybox', '.jpg', 2)

    # Load the skybox
    # Read it again as there is no deep copy for vtkTexture
    # skybox = ReadCubeMap(cube_path, '/', '.jpg', 0)
    skybox = ReadCubeMap(cube_path, '/', '.jpg', 1)
    # skybox = ReadCubeMap(cube_path, '/skybox', '.jpg', 2)
    skybox.InterpolateOn()
    skybox.RepeatOff()
    skybox.EdgeClampOn()

    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor('BkgColor', [26, 51, 102, 255])

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    # Lets use a smooth metallic surface
    metallicCoefficient = 1.0
    roughnessCoefficient = 0.05

    slwP = SliderProperties()
    slwP.initialValue = metallicCoefficient
    slwP.title = 'Metallicity'

    sliderWidgetMetallic = MakeSliderWidget(slwP)
    sliderWidgetMetallic.SetInteractor(interactor)
    sliderWidgetMetallic.SetAnimationModeToAnimate()
    sliderWidgetMetallic.EnabledOn()

    slwP.initialValue = roughnessCoefficient
    slwP.title = 'Roughness'
    slwP.p1 = [0.1, 0.9]
    slwP.p2 = [0.9, 0.9]

    sliderWidgetRoughness = MakeSliderWidget(slwP)
    sliderWidgetRoughness.SetInteractor(interactor)
    sliderWidgetRoughness.SetAnimationModeToAnimate()
    sliderWidgetRoughness.EnabledOn()

    # Build the pipeline
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(source)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer.UseImageBasedLightingOn()
    renderer.SetEnvironmentCubeMap(cubemap)
    actor.GetProperty().SetInterpolationToPBR()

    # configure the basic properties
    actor.GetProperty().SetColor(colors.GetColor3d('White'))
    actor.GetProperty().SetMetallic(metallicCoefficient)
    actor.GetProperty().SetRoughness(roughnessCoefficient)

    # Create the slider callbacks to manipulate metallicity and roughness
    sliderWidgetMetallic.AddObserver(vtk.vtkCommand.InteractionEvent, SliderCallbackMetallic(actor.GetProperty()))
    sliderWidgetRoughness.AddObserver(vtk.vtkCommand.InteractionEvent, SliderCallbackRoughness(actor.GetProperty()))

    renderer.SetBackground(colors.GetColor3d("BkgColor"))
    renderer.AddActor(actor)

    skyboxActor = vtk.vtkSkybox()
    skyboxActor.SetTexture(skybox)
    renderer.AddActor(skyboxActor)

    renderWindow.SetSize(640, 480)
    renderWindow.Render()
    renderWindow.SetWindowName("Skybox-PBR")

    axes = vtk.vtkAxesActor()

    widget = vtk.vtkOrientationMarkerWidget()
    rgba = [0.0, 0.0, 0.0, 0.0]
    colors.GetColor("Carrot", rgba)
    widget.SetOutlineColor(rgba[0], rgba[1], rgba[2])
    widget.SetOrientationMarker(axes)
    widget.SetInteractor(interactor)
    widget.SetViewport(0.0, 0.2, 0.2, 0.4)
    widget.SetEnabled(1)
    widget.InteractiveOn()

    interactor.SetRenderWindow(renderWindow)

    renderWindow.Render()
    interactor.Start()


def vtk_version_ok(major, minor, build):
    """
    Check the VTK version.

    :param major: Major version.
    :param minor: Minor version.
    :param build: Build version.
    :return: True if the requested VTK version is greater or equal to the actual VTK version.
    """
    needed_version = 10000000000 * int(major) + 100000000 * int(minor) + int(build)
    try:
        vtk_version_number = vtk.VTK_VERSION_NUMBER
    except AttributeError:  # as error:
        ver = vtk.vtkVersion()
        vtk_version_number = 10000000000 * ver.GetVTKMajorVersion() + 100000000 * ver.GetVTKMinorVersion() \
                             + ver.GetVTKBuildVersion()
    if vtk_version_number <= needed_version:
        return True
    else:
        return False


def ReadCubeMap(folderRoot, fileRoot, ext, key):
    """
    Read the cube map.
    :param folderRoot: The folder where the cube maps are stored.
    :param fileRoot: The root of the individual cube map file names.
    :param ext: The extension of the cube map files.
    :param key: The key to data used to build the full file name.
    :return: The cubemap texture.
    """
    # A map of cube map naming conventions and the corresponding file name
    # components.
    fileNames = {
        0: ['right', 'left', 'top', 'bottom', 'front', 'back'],
        1: ['posx', 'negx', 'posy', 'negy', 'posz', 'negz'],
        2: ['-px', '-nx', '-py', '-ny', '-pz', '-nz'],
        3: ['0', '1', '2', '3', '4', '5']}
    if key in fileNames:
        fns = fileNames[key]
    else:
        print('ReadCubeMap(): invalid key, unable to continue.')
        sys.exit()
    texture = vtk.vtkTexture()
    texture.CubeMapOn()
    # Build the file names.
    for i in range(0, len(fns)):
        fns[i] = folderRoot + fileRoot + fns[i] + ext
        if not os.path.isfile(fns[i]):
            print('Nonexistent texture file:', fns[i])
            return texture
    i = 0
    for fn in fns:
        # Read the images
        readerFactory = vtk.vtkImageReader2Factory()
        imgReader = readerFactory.CreateImageReader2(fn)
        imgReader.SetFileName(fn)

        flip = vtk.vtkImageFlip()
        flip.SetInputConnection(imgReader.GetOutputPort())
        flip.SetFilteredAxis(1)  # flip y axis
        texture.SetInputConnection(i, flip.GetOutputPort(0))
        i += 1
    return texture


def GetBoy():
    uResolution = 51
    vResolution = 51
    surface = vtk.vtkParametricBoy()

    source = vtk.vtkParametricFunctionSource()
    source.SetUResolution(uResolution)
    source.SetVResolution(vResolution)
    source.SetParametricFunction(surface)
    source.Update()

    # Build the tcoords
    pd = UVTcoords(uResolution, vResolution, source.GetOutput())
    # Now the tangents
    tangents = vtk.vtkPolyDataTangents()
    tangents.SetInputData(pd)
    tangents.Update()
    return tangents.GetOutput()


def GetMobius():
    uResolution = 51
    vResolution = 51
    surface = vtk.vtkParametricMobius()
    surface.SetMinimumV(-0.25)
    surface.SetMaximumV(0.25)

    source = vtk.vtkParametricFunctionSource()
    source.SetUResolution(uResolution)
    source.SetVResolution(vResolution)
    source.SetParametricFunction(surface)
    source.Update()

    # Build the tcoords
    pd = UVTcoords(uResolution, vResolution, source.GetOutput())
    # Now the tangents
    tangents = vtk.vtkPolyDataTangents()
    tangents.SetInputData(pd)
    tangents.Update()

    transform = vtk.vtkTransform()
    transform.RotateX(90.0)
    transformFilter = vtk.vtkTransformPolyDataFilter()
    transformFilter.SetInputConnection(tangents.GetOutputPort())
    transformFilter.SetTransform(transform)
    transformFilter.Update()

    return transformFilter.GetOutput()


def GetRandomHills():
    uResolution = 51
    vResolution = 51
    surface = vtk.vtkParametricRandomHills()
    surface.SetRandomSeed(1)
    surface.SetNumberOfHills(30)
    # If you want a plane
    # surface.SetHillAmplitude(0)

    source = vtk.vtkParametricFunctionSource()
    source.SetUResolution(uResolution)
    source.SetVResolution(vResolution)
    source.SetParametricFunction(surface)
    source.Update()

    # Build the tcoords
    pd = UVTcoords(uResolution, vResolution, source.GetOutput())
    # Now the tangents
    tangents = vtk.vtkPolyDataTangents()
    tangents.SetInputData(pd)
    tangents.Update()

    transform = vtk.vtkTransform()
    transform.RotateZ(180.0)
    transform.RotateX(90.0)
    transformFilter = vtk.vtkTransformPolyDataFilter()
    transformFilter.SetInputConnection(tangents.GetOutputPort())
    transformFilter.SetTransform(transform)
    transformFilter.Update()

    return transformFilter.GetOutput()


def GetTorus():
    uResolution = 51
    vResolution = 51
    surface = vtk.vtkParametricTorus()

    source = vtk.vtkParametricFunctionSource()
    source.SetUResolution(uResolution)
    source.SetVResolution(vResolution)
    source.SetParametricFunction(surface)
    source.Update()

    # Build the tcoords
    pd = UVTcoords(uResolution, vResolution, source.GetOutput())
    # Now the tangents
    tangents = vtk.vtkPolyDataTangents()
    tangents.SetInputData(pd)
    tangents.Update()

    transform = vtk.vtkTransform()
    transform.RotateX(90.0)
    transformFilter = vtk.vtkTransformPolyDataFilter()
    transformFilter.SetInputConnection(tangents.GetOutputPort())
    transformFilter.SetTransform(transform)
    transformFilter.Update()

    return transformFilter.GetOutput()


def GetSphere():
    thetaResolution = 32
    phiResolution = 32
    surface = vtk.vtkTexturedSphereSource()
    surface.SetThetaResolution(thetaResolution)
    surface.SetPhiResolution(phiResolution)

    # Now the tangents
    tangents = vtk.vtkPolyDataTangents()
    tangents.SetInputConnection(surface.GetOutputPort())
    tangents.Update()
    return tangents.GetOutput()


def GetCube():
    surface = vtk.vtkCubeSource()

    # Triangulate
    triangulation = vtk.vtkTriangleFilter()
    triangulation.SetInputConnection(surface.GetOutputPort())
    # Subdivide the triangles
    subdivide = vtk.vtkLinearSubdivisionFilter()
    subdivide.SetInputConnection(triangulation.GetOutputPort())
    subdivide.SetNumberOfSubdivisions(3)
    # Now the tangents
    tangents = vtk.vtkPolyDataTangents()
    tangents.SetInputConnection(subdivide.GetOutputPort())
    tangents.Update()
    return tangents.GetOutput()


def UVTcoords(uResolution, vResolution, pd):
    """
    Generate u, v texture coordinates on a parametric surface.
    :param uResolution: u resolution
    :param vResolution: v resolution
    :param pd: The polydata representing the surface.
    :return: The polydata with the texture coordinates added.
    """
    u0 = 1.0
    v0 = 0.0
    du = 1.0 / (uResolution - 1)
    dv = 1.0 / (vResolution - 1)
    numPts = pd.GetNumberOfPoints()
    tCoords = vtk.vtkFloatArray()
    tCoords.SetNumberOfComponents(2)
    tCoords.SetNumberOfTuples(numPts)
    tCoords.SetName('Texture Coordinates')
    ptId = 0
    u = u0
    for i in range(0, uResolution):
        v = v0
        for j in range(0, vResolution):
            tc = [u, v]
            tCoords.SetTuple(ptId, tc)
            v += dv
            ptId += 1
        u -= du
    pd.GetPointData().SetTCoords(tCoords)
    return pd


class SliderProperties:
    tubeWidth = 0.008
    sliderLength = 0.008
    titleHeight = 0.02
    labelHeight = 0.02

    minimumValue = 0.0
    maximumValue = 1.0
    initialValue = 1.0

    p1 = [0.1, 0.1]
    p2 = [0.9, 0.1]

    title = None


def MakeSliderWidget(properties):
    slider = vtk.vtkSliderRepresentation2D()

    slider.SetMinimumValue(properties.minimumValue)
    slider.SetMaximumValue(properties.maximumValue)
    slider.SetValue(properties.initialValue)
    slider.SetTitleText(properties.title)

    slider.GetPoint1Coordinate().SetCoordinateSystemToNormalizedDisplay()
    slider.GetPoint1Coordinate().SetValue(properties.p1[0], properties.p1[1])
    slider.GetPoint2Coordinate().SetCoordinateSystemToNormalizedDisplay()
    slider.GetPoint2Coordinate().SetValue(properties.p2[0], properties.p2[1])

    slider.SetTubeWidth(properties.tubeWidth)
    slider.SetSliderLength(properties.sliderLength)
    slider.SetTitleHeight(properties.titleHeight)
    slider.SetLabelHeight(properties.labelHeight)

    sliderWidget = vtk.vtkSliderWidget()
    sliderWidget.SetRepresentation(slider)

    return sliderWidget


class SliderCallbackMetallic:
    def __init__(self, actorProperty):
        self.actorProperty = actorProperty

    def __call__(self, caller, ev):
        sliderWidget = caller
        value = sliderWidget.GetRepresentation().GetValue()
        self.actorProperty.SetMetallic(value)


class SliderCallbackRoughness:
    def __init__(self, actorProperty):
        self.actorProperty = actorProperty

    def __call__(self, caller, ev):
        sliderWidget = caller
        value = sliderWidget.GetRepresentation().GetValue()
        self.actorProperty.SetRoughness(value)


if __name__ == '__main__':
    main()
