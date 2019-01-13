# !/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function

import os
import re
from collections import defaultdict

# These examples do not produce an image for testing.
# A dictionary consisting of [example type][directory name][example name ...]
no_image = defaultdict(lambda: defaultdict(set))
no_image['Cxx']['Cxx/CompositeData'] = {'Generate2DAMRDataSetWithPulse', 'Generate3DAMRDataSetWithPulse'}
no_image['Cxx']['Cxx/DataStructures'] = {'BuildLocatorFromKClosestPoints', 'BuildOctree',
                                         'IncrementalOctreePointLocator', 'KDTreeAccessPoints',
                                         'KDTreeFindPointsWithinRadius', 'KdTree', 'KdTreePointLocatorClosestPoint',
                                         'ModifiedBSPTreeIntersectWithLine', 'OBBTreeIntersectWithLine',
                                         'OctreeClosestPoint', 'OctreeFindPointsWithinRadius',
                                         'OctreeKClosestPoints'}
no_image['Cxx']['Cxx/DataStructures/KdTreePointLocator'] = {'ClosestNPoints'}
no_image['Cxx']['Cxx/Databases/SQL/MySQL'] = {'ConnectAndRead', 'CreateDatabase', 'WriteToDatabase'}
no_image['Cxx']['Cxx/Demos'] = {'VisualDebugging', 'vtkTestFilter'}
no_image['Cxx']['Cxx/Filtering'] = {'SelectionSource', 'VectorFieldNonZeroExtraction'}
no_image['Cxx']['Cxx/GeometricObjects'] = {'PlanesIntersection', 'PolygonIntersection'}
no_image['Cxx']['Cxx/Graphs'] = {'AdjacencyMatrixToEdgeTable', 'BreadthFirstDistance', 'ConnectedComponents',
                                 'DepthFirstSearchIterator', 'EdgeListIterator', 'InEdgeIterator',
                                 'MinimumSpanningTree', 'NOVCAGraph', 'OutEdgeIterator', 'RemoveIsolatedVertices',
                                 'TreeBFSIterator'}
no_image['Cxx']['Cxx/Graphs/Conversions'] = {'DirectedGraphToMutableDirectedGraph',
                                             'MutableDirectedGraphToDirectedGraph', 'TreeToMutableDirectedGraph'}
no_image['Cxx']['Cxx/IO'] = {'ConvertFile', 'DumpXMLFile', 'FindAllArrayNames', 'GenericDataObjectReader', 'JPEGWriter',
                             'PNGWriter', 'ReadPlainTextTriangles', 'SimplePointsWriter', 'WriteLegacyLinearCells',
                             'WriteVTP', 'WriteXMLLinearCells', 'XMLPImageDataWriter', 'XMLPUnstructuredGridWriter',
                             'XMLStructuredGridWriter'}
no_image['Cxx']['Cxx/ImageData'] = {'CellIdFromGridCoordinates', 'GetCellCenter', 'ImageDataToPointSet',
                                    'ImageIterator', 'ImageReslice', 'IterateImageData'}
no_image['Cxx']['Cxx/ImageProcessing'] = {'RescaleAnImage'}
no_image['Cxx']['Cxx/Images'] = {'ImageAccumulate', 'ImageExport', 'ImageText', 'ImageValueRange', 'NegativeIndices'}
no_image['Cxx']['Cxx/ImplicitFunctions'] = {'ImplicitDataSet'}
no_image['Cxx']['Cxx/InfoVis'] = {'ArrayToTable', 'DelimitedTextWriter', 'PKMeansClustering', 'PassThrough'}
no_image['Cxx']['Cxx/Interaction'] = {'vtkTestFilter'}
no_image['Cxx']['Cxx/Math'] = {'1DTupleInterpolation', 'EigenSymmetric', 'HomogeneousLeastSquares', 'LUFactorization',
                               'LeastSquares', 'MatrixInverse', 'MatrixTranspose', 'NormalizeVector',
                               'PerpendicularVector', 'VectorDot', 'VectorNorm'}
no_image['Cxx']['Cxx/Matlab'] = {'MatlabEngineFilter'}
no_image['Cxx']['Cxx/Medical'] = {'GenerateModelsFromLabels'}
no_image['Cxx']['Cxx/Meshes'] = {'AddCell', 'CellEdges'}
no_image['Cxx']['Cxx/Parallel'] = {'ExodusIIWriter'}
no_image['Cxx']['Cxx/Parallel'] = {'ExodusIIWriter'}
no_image['Cxx']['Cxx/PolyData'] = {'AlignFrames', 'AttachAttributes', 'Casting', 'CellLocator', 'CellTreeLocator',
                                   'CenterOfMass', 'CleanPolyData', 'ClosedSurface', 'CopyAllArrays', 'DataBounds',
                                   'DataSetSurfaceFilter', 'DeletePoint', 'DetermineArrayDataTypes', 'FieldData',
                                   'GeometryFilter', 'GetMiscCellData', 'GetMiscPointData', 'InterpolateTerrain',
                                   'IterateOverLines', 'MergePoints', 'MiscCellData', 'MiscPointData',
                                   'MultiBlockMergeFilter', 'NullPoint', 'PointCellIds', 'PointLocatorRadius',
                                   'PolyDataCellNormals', 'PolyDataContourToImageData', 'PolyDataExtractNormals',
                                   'PolyDataGetPoint', 'PolyDataPointNormals', 'PolyDataToImageData',
                                   'PolyDataToUnstructuredGrid', 'RemoveVertices', 'ReverseSense', 'RotationAroundLine',
                                   'Stripper', 'ThresholdCells', 'ThresholdPoints', 'TriangleArea'}
no_image['Cxx']['Cxx/Qt'] = {'BorderWidgetQt', 'BorderWidgetQtDriver', 'EventQtSlotConnect', 'EventQtSlotConnectDriver',
                             'ImageDataToQImage', 'QImageToImageSource', 'QtBarChart', 'RenderWindowNoUiFile',
                             'RenderWindowUIMultipleInheritance', 'RenderWindowUIMultipleInheritanceDriver',
                             'RenderWindowUISingleInheritance', 'RenderWindowUISingleInheritanceDriver',
                             'ShareCameraQt', 'ShareCameraQtDriver', 'ShowEvent', 'ShowEventDriver',
                             'SideBySideRenderWindowsQt', 'SideBySideRenderWindowsQtDriver'}
no_image['Cxx']['Cxx/RectilinearGrid'] = {'RectilinearGridToTetrahedra'}
no_image['Cxx']['Cxx/SimpleOperations'] = {'DistanceBetweenPoints', 'DistancePointToLine', 'FloatingPointExceptions',
                                           'GaussianRandomNumber', 'PerspectiveTransform', 'ProjectPointPlane',
                                           'RandomSequence', 'UniformRandomNumber'}
no_image['Cxx']['Cxx/StructuredGrid'] = {'GetLinearPointId'}
no_image['Cxx']['Cxx/StructuredPoints'] = {'StructuredPointsToUnstructuredGrid'}
no_image['Cxx']['Cxx/Utilities'] = {'2DArray', '3DArray', 'ArrayCalculator', 'ArrayLookup', 'ArrayRange', 'ArrayWriter',
                                    'BoundingBox', 'BoundingBoxIntersection', 'Box', 'CMakeVTKVersionCheck',
                                    'CardinalSpline', 'CheckVTKVersion', 'ColorLookupTable', 'ColorTransferFunction',
                                    'ConstructTable', 'Coordinate', 'CustomDenseArray', 'DeepCopy', 'DenseArrayRange',
                                    'DiscretizableColorTransferFunction', 'ExtractArrayComponent', 'ExtractFaces',
                                    'FileOutputWindow', 'FilenameFunctions', 'FunctionParser', 'GetClassName',
                                    'GetDataRoot', 'KnownLengthArray', 'LUTUtilities', 'MassProperties', 'ObserveError',
                                    'OffScreenRendering', 'PCAStatistics', 'PiecewiseFunction', 'PointInPolygon',
                                    'ReportRenderWindowCapabilities', 'ShallowCopy', 'SortDataArray', 'SparseArray',
                                    'TimeStamp', 'TimerLog', 'UnknownLengthArray', 'Variant', 'Vector',
                                    'VectorArrayKnownLength', 'VectorArrayUnknownLength', 'VersionMacros', 'ZBuffer'}
no_image['Cxx']['Cxx/VTKConcepts'] = {'Scalars'}
no_image['Cxx']['Cxx/Video'] = {'FFMPEG', 'MPEG2', 'OggTheora'}
no_image['Cxx']['Cxx/Views'] = {'RenderView'}
no_image['Cxx']['Cxx/Visualization'] = {'NamedColorPatches', 'ReverseAccess'}
# For Python, Java and CSharp assume that their layout is the same and images are named the same way.
for ex in ['CSharp', 'Java', 'Python']:
    for pk, lst in no_image['Cxx'].items():
        new_k = pk.replace('Cxx', ex)
        no_image[ex][new_k] = lst

no_image['Python']['Python/Filtering'].add('IterativeClosestPoints')
no_image['Python']['Python/Arrays'] = no_image['Python']['Python/Arrays'] | {'GetValues', 'RenameArray'}
no_image['Python']['Python/ImageData'].add('SumVTKImages')
no_image['Python']['Python/PolyData'] = no_image['Python']['Python/PolyData'] | {'ColoredTriangle',
                                                                                 'SolidColoredTriangle',
                                                                                 'TriangleColoredPoints',
                                                                                 'TriangleCornerVertices',
                                                                                 'TriangleCorners'}
no_image['Python']['Python/Utilities'].add('VTKVersion')
no_image['Python']['Python/Untested/HasBugs'].add('UnstructuredTransientVolumeRendering')

no_image['Java']['Java/IO'].add('WriteTriangleToFile')


def get_program_parameters():
    import argparse
    description = 'Produce a list of VTK examples that have no test images.'
    epilogue = '''
Typical usage:
   For each file in VTKExamples/src look in the corresponding folder in
      VTKExamples/src/Testing/Baseline for a corresponding image file.
      If there is none then flag that example as having a missing image file.
      
   To produce a list of VTK examples that have no test files:
      FindExamplesMissingTestImages.py some_path/VTKExamples/src
      
   Note: Some examples may legitimately have no test files.
'''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('vtk_example_src_path', help='The path to the VTK example source files.')

    args = parser.parse_args()
    return args.vtk_example_src_path


def path_splitter(path):
    """
    Split a path into its constituent parts.
    Might be better written as a recursive function.
    :param path: The path to split.
    :return: A list of the path's constituent parts.
    """
    res = []
    while True:
        p = os.path.split(path)
        if p[0] == path:
            # Were done, this is an absolute path.
            res.insert(0, p[0])
            break
        elif p[1] == path:
            # Were done, this is a relative path.
            res.insert(0, p[0])
            break
        else:
            path = p[0]
            res.insert(0, p[1])
    return res


class ExamplesMissingTestImages:
    """
    Find examples that have missing test images
    """

    def __init__(self, base_directory):
        self.example_types = ['CSharp', 'Cxx', 'Java', 'Python']
        self.excluded_dirs = ['Cxx/CMakeTechniques', 'Cxx/Developers', 'Cxx/Untested', 'Cxx/Untested/Video',
                              'Cxx/Untested/HasBugs', 'Java/Untested/Video']
        self.base_directory = base_directory
        self.test_images_base_directory = os.path.join(self.base_directory, 'Testing/Baseline')
        # A dictionary consisting of [example type][directory name][example name ...]
        self.all_examples = defaultdict(lambda: defaultdict(set))
        self.all_test_images = defaultdict(lambda: defaultdict(set))
        self.examples_no_test_images = defaultdict(lambda: defaultdict(set))

    def get_all_examples(self):
        """
        For each example, get the example file paths and the example file names.
        """
        for eg in self.example_types:
            # Get the paths to the examples in a particular sub directory e.g Cxx.
            directory = os.path.join(self.base_directory, eg)
            # Does the directory exist?
            if not os.path.isdir(directory):
                raise RuntimeError('Non-existent folder: {:s}'.format(directory))
            if eg == 'CSharp':
                fn_pattern = re.compile(r'^[0-9a-zA-Z_\-]+\.cs$')
            elif eg == 'Cxx':
                fn_pattern = re.compile(
                    r'^[0-9a-zA-Z_\-]+\.(hxx|HXX|hpp|HPP|[hH]\+\+|[hH]|cpp|CPP|cxx|CXX|[cC]\+\+|txx|TXX)$')

            elif eg == 'Java':
                fn_pattern = re.compile(r'^[0-9a-zA-Z_\-]+\.java$')
            elif eg == 'Python':
                fn_pattern = re.compile(r'^[0-9a-zA-Z_\-]+\.py$')
            else:
                raise RuntimeError('Unknown example type.')

            # Walk the tree.
            for root, directories, files in os.walk(directory):
                sp = path_splitter(root)
                idx = sp.index(eg)
                key = '/'.join(sp[idx:])
                examples = set()
                if key in self.excluded_dirs:
                    continue
                for filename in files:
                    m = fn_pattern.match(filename)
                    if m:
                        examples.add(os.path.splitext(filename)[0])
                self.all_examples[eg][key] = examples

    def get_all_test_images(self):
        """
        For each example, get the example file paths and the example file names.
        """
        for eg in self.example_types:
            # Get the paths to the examples in a particular sub directory e.g Cxx.
            directory = os.path.join(self.test_images_base_directory, eg)
            # Does the directory exist?
            if not os.path.isdir(directory):
                raise RuntimeError('Non-existent folder: {:s}'.format(directory))

            prefix = 'Test'
            # Walk the tree.
            for root, directories, files in os.walk(directory):
                sp = path_splitter(root)
                idx = sp.index(eg)
                key = '/'.join(sp[idx:])
                images = set()
                if key in self.excluded_dirs:
                    continue
                for filename in files:
                    s = os.path.splitext(filename)
                    if s[1] == '.png':
                        if s[0].startswith(prefix):
                            images.add(s[0][len(prefix):])
                self.all_test_images[eg][key] = images
        # Remove those examples that do not produce an image.
        for k, v in no_image.items():
            for kk, vv in v.items():
                if bool(self.all_examples[k][kk]):
                    self.all_examples[k][kk] = self.all_examples[k][kk] - no_image[k][kk]

    def get_examples_missing_test_images(self):
        if not self.all_examples:
            self.get_all_examples()
        if not self.all_test_images:
            self.get_all_test_images()
        for k in self.all_examples.keys():
            for k1 in self.all_examples[k].keys():
                if bool(self.all_examples[k][k1]):
                    if bool(self.all_test_images[k][k1]):
                        self.examples_no_test_images[k][k1] = self.all_examples[k][k1] - self.all_test_images[k][k1]
                    else:
                        self.examples_no_test_images[k][k1] = self.all_examples[k][k1]

    def display(self):
        if not self.examples_no_test_images:
            self.get_examples_missing_test_images()
        res = []
        for k, v in sorted(self.examples_no_test_images.items()):
            res.append('\n' + k)
            for kk, vv in sorted(v.items()):
                if bool(vv):
                    res.append('\t' + kk)
                    for vvv in sorted(vv):
                        res.append('\t\t' + vvv)
        return res


def main():
    base_directory = get_program_parameters()
    emti = ExamplesMissingTestImages(base_directory)
    res = emti.display()
    if res:
        print('Examples with missing test images')
        print('\n'.join(res))


if __name__ == '__main__':
    main()
