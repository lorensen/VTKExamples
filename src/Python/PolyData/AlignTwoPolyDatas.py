#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def get_program_parameters():
    import argparse
    description = 'How to align two vtkPolyData\'s.'
    epilogue = '''

    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('src_fn', help='The polydata source file name,e.g. Grey_Nurse_Shark.stl.')
    parser.add_argument('tgt_fn', help='The polydata target file name, e.g. shark.ply.')

    args = parser.parse_args()

    return args.src_fn, args.tgt_fn


def main():
    colors = vtk.vtkNamedColors()

    src_fn, tgt_fn = get_program_parameters()
    print('Loading source:', src_fn)
    sourcePolyData = ReadPolyData(src_fn)
    # Save the source polydata in case the align does not improve
    # segmentation
    originalSourcePolyData = vtk.vtkPolyData()
    originalSourcePolyData.DeepCopy(sourcePolyData)

    print('Loading target:', tgt_fn)
    targetPolyData = ReadPolyData(tgt_fn)

    # If the target orientation is markedly different,
    # you may need to apply a transform to orient the
    # target with the source.
    # For example, when using Grey_Nurse_Shark.stl as the source and
    # greatWhite.stl as the target, you need to uncomment the following
    # two rotations.
    trnf = vtk.vtkTransform()
    # trnf.RotateX(90)
    # trnf.RotateY(-90)
    tpd = vtk.vtkTransformPolyDataFilter()
    tpd.SetTransform(trnf)
    tpd.SetInputData(targetPolyData)
    tpd.Update()

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    distance = vtk.vtkHausdorffDistancePointSetFilter()
    distance.SetInputData(0, tpd.GetOutput())
    distance.SetInputData(1, sourcePolyData)
    distance.Update()

    distanceBeforeAlign = distance.GetOutput(0).GetFieldData().GetArray('HausdorffDistance').GetComponent(0, 0)

    # Get initial alignment using oriented bounding boxes
    AlignBoundingBoxes(sourcePolyData, tpd.GetOutput())

    distance.SetInputData(0, tpd.GetOutput())
    distance.SetInputData(1, sourcePolyData)
    distance.Modified()
    distance.Update()
    distanceAfterAlign = distance.GetOutput(0).GetFieldData().GetArray('HausdorffDistance').GetComponent(0, 0)

    bestDistance = min(distanceBeforeAlign, distanceAfterAlign)

    if distanceAfterAlign > distanceBeforeAlign:
        sourcePolyData.DeepCopy(originalSourcePolyData)

    # Refine the alignment using IterativeClosestPoint
    icp = vtk.vtkIterativeClosestPointTransform()
    icp.SetSource(sourcePolyData)
    icp.SetTarget(tpd.GetOutput())
    icp.GetLandmarkTransform().SetModeToRigidBody()
    icp.SetMaximumNumberOfLandmarks(100)
    icp.SetMaximumMeanDistance(.00001)
    icp.SetMaximumNumberOfIterations(500)
    icp.CheckMeanDistanceOn()
    icp.StartByMatchingCentroidsOn()
    icp.Update()

    #  print(icp)

    lmTransform = icp.GetLandmarkTransform()
    transform = vtk.vtkTransformPolyDataFilter()
    transform.SetInputData(sourcePolyData)
    transform.SetTransform(lmTransform)
    transform.SetTransform(icp)
    transform.Update()

    distance.SetInputData(0, tpd.GetOutput())
    distance.SetInputData(1, transform.GetOutput())
    distance.Update()

    distanceAfterICP = distance.GetOutput(0).GetFieldData().GetArray('HausdorffDistance').GetComponent(0, 0)

    if distanceAfterICP < bestDistance:
        bestDistance = distanceAfterICP

    print(
        'Distance before, after align, after ICP, min: {:0.5f}, {:0.5f}, {:0.5f}, {:0.5f}'.format(distanceBeforeAlign,
                                                                                                  distanceAfterAlign,
                                                                                                  distanceAfterICP,
                                                                                                  bestDistance))
    # Select
    sourceMapper = vtk.vtkDataSetMapper()
    if bestDistance == distanceBeforeAlign:
        sourceMapper.SetInputData(originalSourcePolyData)
        print('Using original alignment')
    elif bestDistance == distanceAfterAlign:
        sourceMapper.SetInputData(sourcePolyData)
        print('Using alignment by OBB')
    else:
        sourceMapper.SetInputConnection(transform.GetOutputPort())
        print('Using alignment by ICP')
    sourceMapper.ScalarVisibilityOff()

    sourceActor = vtk.vtkActor()
    sourceActor.SetMapper(sourceMapper)
    sourceActor.GetProperty().SetOpacity(.6)
    sourceActor.GetProperty().SetDiffuseColor(
        colors.GetColor3d('White'))
    renderer.AddActor(sourceActor)

    targetMapper = vtk.vtkDataSetMapper()
    targetMapper.SetInputData(tpd.GetOutput())
    targetMapper.ScalarVisibilityOff()

    targetActor = vtk.vtkActor()
    targetActor.SetMapper(targetMapper)
    targetActor.GetProperty().SetDiffuseColor(
        colors.GetColor3d('Tomato'))
    renderer.AddActor(targetActor)

    renderWindow.AddRenderer(renderer)
    renderer.SetBackground(colors.GetColor3d("sea_green_light"))
    renderer.UseHiddenLineRemovalOn()

    renderWindow.SetSize(640, 480)
    renderWindow.Render()
    renderWindow.SetWindowName('AlignTwoPolyDatas')
    renderWindow.Render()
    interactor.Start()


def ReadPolyData(file_name):
    import os
    path, extension = os.path.splitext(file_name)
    extension = extension.lower()
    if extension == ".ply":
        reader = vtk.vtkPLYReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".vtp":
        reader = vtk.vtkXMLpoly_dataReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".obj":
        reader = vtk.vtkOBJReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".stl":
        reader = vtk.vtkSTLReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".vtk":
        reader = vtk.vtkpoly_dataReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".g":
        reader = vtk.vtkBYUReader()
        reader.SetGeometryFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    else:
        # Return a None if the extension is unknown.
        poly_data = None
    return poly_data


def AlignBoundingBoxes(source, target):
    # Use OBBTree to create an oriented bounding box for target and source
    sourceOBBTree = vtk.vtkOBBTree()
    sourceOBBTree.SetDataSet(source)
    sourceOBBTree.SetMaxLevel(1)
    sourceOBBTree.BuildLocator()

    targetOBBTree = vtk.vtkOBBTree()
    targetOBBTree.SetDataSet(target)
    targetOBBTree.SetMaxLevel(1)
    targetOBBTree.BuildLocator()

    sourceLandmarks = vtk.vtkPolyData()
    sourceOBBTree.GenerateRepresentation(0, sourceLandmarks)

    targetLandmarks = vtk.vtkPolyData()
    targetOBBTree.GenerateRepresentation(0, targetLandmarks)

    lmTransform = vtk.vtkLandmarkTransform()
    lmTransform.SetModeToSimilarity()
    lmTransform.SetTargetLandmarks(targetLandmarks.GetPoints())
    # lmTransformPD = vtk.vtkTransformPolyDataFilter()
    bestDistance = vtk.VTK_DOUBLE_MAX
    bestPoints = vtk.vtkPoints()
    bestDistance = BestBoundingBox(
        "X",
        target,
        source,
        targetLandmarks,
        sourceLandmarks,
        bestDistance,
        bestPoints)
    bestDistance = BestBoundingBox(
        "Y",
        target,
        source,
        targetLandmarks,
        sourceLandmarks,
        bestDistance,
        bestPoints)
    bestDistance = BestBoundingBox(
        "Z",
        target,
        source,
        targetLandmarks,
        sourceLandmarks,
        bestDistance,
        bestPoints)

    lmTransform.SetSourceLandmarks(bestPoints)
    lmTransform.Modified()

    transformPD = vtk.vtkTransformPolyDataFilter()
    transformPD.SetInputData(source)
    transformPD.SetTransform(lmTransform)
    transformPD.Update()

    source.DeepCopy(transformPD.GetOutput())

    return


def BestBoundingBox(axis, target, source, targetLandmarks, sourceLandmarks, bestDistance, bestPoints):
    distance = vtk.vtkHausdorffDistancePointSetFilter()
    testTransform = vtk.vtkTransform()
    testTransformPD = vtk.vtkTransformPolyDataFilter()
    lmTransform = vtk.vtkLandmarkTransform()
    lmTransformPD = vtk.vtkTransformPolyDataFilter()

    lmTransform.SetModeToSimilarity()
    lmTransform.SetTargetLandmarks(targetLandmarks.GetPoints())

    sourceCenter = sourceLandmarks.GetCenter()

    delta = 90.0
    for i in range(0, 4):
        angle = delta * i
        # Rotate about center
        testTransform.Identity()
        testTransform.Translate(sourceCenter[0], sourceCenter[1], sourceCenter[2])
        if axis == "X":
            testTransform.RotateX(angle)
        elif axis == "Y":
            testTransform.RotateY(angle)
        else:
            testTransform.RotateZ(angle)
        testTransform.Translate(-sourceCenter[0], -sourceCenter[1], -sourceCenter[2])

        testTransformPD.SetTransform(testTransform)
        testTransformPD.SetInputData(sourceLandmarks)
        testTransformPD.Update()

        lmTransform.SetSourceLandmarks(testTransformPD.GetOutput().GetPoints())
        lmTransform.Modified()

        lmTransformPD.SetInputData(source)
        lmTransformPD.SetTransform(lmTransform)
        lmTransformPD.Update()

        distance.SetInputData(0, target)
        distance.SetInputData(1, lmTransformPD.GetOutput())
        distance.Update()

        testDistance = distance.GetOutput(0).GetFieldData().GetArray("HausdorffDistance").GetComponent(0, 0)
        if testDistance < bestDistance:
            bestDistance = testDistance
            bestPoints.DeepCopy(testTransformPD.GetOutput().GetPoints())

    return bestDistance


if __name__ == '__main__':
    main()
