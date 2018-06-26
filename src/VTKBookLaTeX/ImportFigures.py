#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
from collections import defaultdict
from shutil import copy2

# Here we create a list of figure names and source names.
# When new/updated figures or test images become available, add them here.
# The key is Chapter Number, the subkey is figure number, the value is the test image.
figs = defaultdict(dict)
figs['3']['7'] = 'Rendering/TestFlatVersusGouraud'
figs['3']['12'] = 'Visualization/TestCameraModel1'
figs['3']['13'] = 'Visualization/TestCameraModel2'
figs['3']['26'] = 'GeometricObjects/TestSourceObjectsDemo'
figs['3']['27'] = 'Rendering/TestCone3'
figs['3']['28'] = 'Rendering/TestCone4'
figs['3']['32'] = 'Rendering/TestWalkCow'
figs['3']['33a'] = 'Rendering/TestWalkCowA'
figs['3']['33b'] = 'Rendering/TestWalkCowB'
figs['4']['1a'] = 'Visualization/TestQuadricVisualization'
figs['4']['13b'] = 'IO/Test3DSImporter'
figs['4']['19b'] = 'Rendering/TestColoredSphere'
figs['4']['20b'] = 'Rendering/TestTransformSphere'
figs['4']['21b'] = 'Rendering/TestMace'
figs['4']['22b'] = 'Visualization/TestLoopShrink'
figs['5']['17b'] = 'GeometricObjects/TestCube'
figs['5']['18b'] = 'StructuredPoints/TestVol'
figs['5']['19b'] = 'StructuredGrid/TestSGrid'
figs['5']['20b'] = 'RectilinearGrid/TestRGrid'
figs['5']['21b'] = 'UnstructuredGrid/TestUGrid'
figs['6']['6'] = 'VisualizationAlgorithms/TestMarchingCasesA'
figs['6']['10'] = 'VisualizationAlgorithms/TestMarchingCasesB'
figs['6']['11a'] = 'VisualizationAlgorithms/TestHeadSlice'
figs['6']['11b'] = 'VisualizationAlgorithms/TestHeadBone'
figs['6']['11c'] = 'VisualizationAlgorithms/TestCombustorIsosurface'
figs['6']['11d'] = 'VisualizationAlgorithms/TestIronIsoSurface'
figs['6']['12b'] = 'Visualization/TestHawaii'
figs['6']['13c'] = 'Visualization/TestComplexV'
figs['6']['14a'] = 'VisualizationAlgorithms/TestPlateVibration'
figs['6']['14b'] = 'VisualizationAlgorithms/TestVelocityProfile'
figs['6']['15b'] = 'VisualizationAlgorithms/TestDisplacementPlot'
figs['6']['18'] = 'Visualization/TestKitchen'
figs['6']['19'] = 'VisualizationAlgorithms/TestBluntStreamlines'
figs['6']['22a'] = 'VisualizationAlgorithms/TestTensorAxes'
figs['6']['22b'] = 'VisualizationAlgorithms/TestTensorEllipsoids'
figs['6']['23b'] = 'ImplicitFunctions/TestImplicitSphere'
figs['6']['23c'] = 'VisualizationAlgorithms/TestIceCream'
figs['6']['24b'] = 'VisualizationAlgorithms/TestExtractData'
figs['6']['25a'] = 'Visualization/TestLorenz'
figs['6']['28'] = 'VisualizationAlgorithms/TestHello'
figs['6']['30'] = 'VisualizationAlgorithms/TestSpikeFran'
figs['6']['31'] = 'VisualizationAlgorithms/TestCutStructuredGrid'
figs['6']['32b'] = 'VisualizationAlgorithms/TestCutStructuredGrid'
figs['6']['33'] = 'VisualizationAlgorithms/TestCutWithScalars'
figs['6']['39b'] = 'VisualizationAlgorithms/TestContourQuadric'
figs['7']['3'] = 'Texture/TestAnimateVectors'
figs['7']['33'] = 'Texture/TestTexturePlane'
figs['7']['34'] = 'VolumeRendering/TestSimpleRayCast'
figs['7']['36'] = 'Rendering/TestMotionBlur'
figs['7']['37'] = 'Rendering/TestCameraBlur'
figs['7']['39'] = 'VisualizationAlgorithms/TestStreamlinesWithLineWidget'
figs['8']['41a'] = 'Visualization/TestAlphaFrequency'
figs['8']['41b'] = 'Modelling/TestBottle'
figs['8']['41c'] = 'Modelling/TestSpring'
figs['9']['4a'] = 'VisualizationAlgorithms/TestExponentialCosine'
figs['9']['4b'] = 'VisualizationAlgorithms/TestWarpCombustor'
figs['9']['10c'] = 'VisualizationAlgorithms/TestCreateBFont'
figs['9']['12d'] = 'VisualizationAlgorithms/TestOfficeTube'
figs['9']['15'] = 'VisualizationAlgorithms/TestHyperStreamline'
figs['9']['19'] = 'VisualizationAlgorithms/TestProbeCombustor'
figs['9']['21'] = 'Rendering/TestStripFran'
figs['9']['24a'] = 'Visualization/TestNormalsDemo'
figs['9']['27a'] = 'VisualizationAlgorithms/TestDecimateFran'
figs['9']['27b'] = 'VisualizationAlgorithms/TestDecimateHawaii'
figs['9']['38b'] = 'VisualizationAlgorithms/TestSplatFace'
figs['9']['43a'] = 'Texture/TestTextureThreshold'
figs['9']['43b'] = 'Texture/TestTextureCutSphere'
figs['9']['45b'] = 'Texture/TestTextureCutQuadric'
figs['9']['47a'] = 'VisualizationAlgorithms/TestOfficeA'
figs['9']['47b'] = 'VisualizationAlgorithms/TestOffice'
figs['9']['48b'] = 'VisualizationAlgorithms/TestClipSphereCylinder'
figs['9']['50b'] = 'Modelling/TestFinance'
figs['9']['51a'] = 'VisualizationAlgorithms/TestPineRootConnectivityA'
figs['9']['51b'] = 'VisualizationAlgorithms/TestPineRootConnectivity'
figs['9']['52a'] = 'VisualizationAlgorithms/TestPineRootConnectivity'
figs['9']['52b'] = 'VisualizationAlgorithms/TestPineRootDecimation'
figs['9']['53b'] = 'VisualizationAlgorithms/TestMotor'
figs['9']['54b'] = 'Modelling/TestDelaunayMesh'
figs['10']['2b'] = 'ImageProcessing/TestGaussianSmooth'
figs['10']['3'] = 'ImageProcessing/TestMedianComparison'
figs['10']['4a'] = 'ImageProcessing/TestHybridMedianComparison'
figs['10']['5b'] = 'ImageProcessing/TestIsoSubsample'
figs['10']['6a'] = 'ImageProcessing/TestAttenuation'
figs['10']['9'] = 'ImageProcessing/TestEnhanceEdges'
figs['10']['10'] = 'ImageProcessing/TestVTKSpectrum'
figs['10']['11c'] = 'ImageProcessing/TestVTKSpectrum'
figs['10']['12'] = 'ImageProcessing/TestPad'
figs['10']['14'] = 'ImageProcessing/TestMorphologyComparison'
figs['10']['16a'] = 'VisualizationAlgorithms/TestImageGradient'
figs['10']['17b'] = 'Images/TestImageWarp'
figs['12']['2'] = 'Medical/TestMedicalDemo1'
figs['12']['3'] = 'Medical/TestMedicalDemo2'
figs['12']['4'] = 'Medical/TestMedicalDemo3'
figs['12']['6'] = 'Visualization/TestFrogSlice'
figs['12']['7'] = 'Visualization/TestViewFrogBoth'
figs['12']['9a'] = 'Visualization/TestViewFrogSkinAndTissue'
figs['12']['9b'] = 'Visualization/TestViewFrog'
figs['12']['9c'] = 'Visualization/TestViewFrogA'
figs['12']['11'] = 'VisualizationAlgorithms/TestStocks'
figs['12']['13b'] = 'Visualization/TestBlobbyLogo'
figs['12']['14b'] = 'VisualizationAlgorithms/TestLOxGrid'
figs['12']['15'] = 'VisualizationAlgorithms/TestLOxSeeds'
figs['12']['16'] = 'VisualizationAlgorithms/TestLOx'
figs['12']['17'] = 'Visualization/TestBlow'
figs['12']['20a'] = 'Visualization/TestHanoiInitial'
figs['12']['20b'] = 'Visualization/TestHanoiIntermediate'
figs['12']['20c'] = 'Visualization/TestHanoi'


def main():
    base_path = get_program_parameters()
    figure_path = os.path.join(base_path, 'src/VTKBookLaTeX/Figures')
    example_path = os.path.join(base_path, 'src/Testing/Baseline/Cxx')
    ext = '.png'
    files_to_copy = list()
    ok_to_copy = True
    for chap, v in figs.items():
        for num, src in v.items():
            fig_name = 'Figure{}-{}{}'.format(chap, num, ext)
            dest = os.path.join(figure_path, fig_name)
            src = os.path.join(example_path, src + ext)
            if os.path.isfile(src):
                files_to_copy.append([src, dest])
            else:
                print('This source file does not exist.')
                print('Source: ', src)
                print('Destination:', dest)
                ok_to_copy = False
    if not ok_to_copy:
        print('Some test file names were not found.')
        print('Please fix and run again.')
        return
    files_copied = 0
    for f in files_to_copy:
        try:
            copy2(f[0], f[1])
            files_copied += 1
        except IOError:
            print('Unable to copy: ', f[0])
            print('to:             ', f[1])
            break
    print('Total number of files:      ', len(files_to_copy))
    print('Number of files copied:     ', files_copied)
    print('Number of files not copied: ', len(files_to_copy) - files_copied)


def get_program_parameters():
    import argparse
    description = 'Copy and rename images.'
    epilogue = '''
The program takes one parameter, the path to VTKExamples.

It then takes relevant images from VTKExamples/src/Testing/Baseline/Cxx/*,
   renames them, and places them into VTKExamples/src/VTKBookLaTeX/Figures.
'''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('base_path', help='The path to the VTKExamples folder.')

    args = parser.parse_args()
    return args.base_path


if __name__ == '__main__':
    main()
