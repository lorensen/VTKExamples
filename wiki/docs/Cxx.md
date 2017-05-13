<p>These are fully independent, compilable examples. There is significant overlap in the examples, but they are each intended to illustrate a different concept and be fully stand alone compilable.</p>
<p>Please add examples in your areas of expertise!</p>
<div class="toc"><span class="toctitle">Contents</span><ul>
<li><a href="#hello-world">Hello World</a></li>
<li><a href="#simple-operations">Simple Operations</a></li>
<li><a href="#input-and-output">Input and Output</a><ul>
<li><a href="#graph-formats">Graph Formats</a></li>
<li><a href="#3d-file-formats">3D File Formats</a><ul>
<li><a href="#standard-formats">Standard Formats</a><ul>
<li><a href="#input">Input</a></li>
<li><a href="#output">Output</a></li>
</ul>
</li>
<li><a href="#vtk-formats">VTK Formats</a><ul>
<li><a href="#input_1">Input</a></li>
<li><a href="#output_1">Output</a></li>
</ul>
</li>
<li><a href="#legacy-vtk-formats">Legacy VTK Formats</a></li>
</ul>
</li>
<li><a href="#image-format">Image Format</a><ul>
<li><a href="#input_2">Input</a></li>
<li><a href="#output_2">Output</a></li>
</ul>
</li>
</ul>
</li>
<li><a href="#geometric-objects">Geometric Objects</a><ul>
<li><a href="#parametric-objects">Parametric Objects</a></li>
</ul>
</li>
<li><a href="#implicit-functions-and-iso-surfaces">Implicit Functions and Iso-surfaces</a></li>
<li><a href="#working-with-3d-data">Working with 3D Data</a><ul>
<li><a href="#data-types">Data Types</a></li>
<li><a href="#data-type-conversions">Data Type Conversions</a></li>
<li><a href="#point-cloud-operations">Point cloud operations</a></li>
<li><a href="#working-with-meshes">Working with Meshes</a><ul>
<li><a href="#clipping">Clipping</a></li>
</ul>
</li>
<li><a href="#working-with-structured-3d-data">Working with Structured 3D Data</a><ul>
<li><a href="#vtkimagedata">vtkImageData</a></li>
<li><a href="#conversions">Conversions</a></li>
<li><a href="#vtkstructuredgrid">vtkStructuredGrid</a></li>
<li><a href="#vtkstructuredpoints">vtkStructuredPoints</a></li>
<li><a href="#vtkrectilineargrid">vtkRectilinearGrid</a></li>
</ul>
</li>
<li><a href="#registration">Registration</a></li>
<li><a href="#medical">Medical</a></li>
<li><a href="#surface-reconstruction">Surface reconstruction</a></li>
</ul>
</li>
<li><a href="#utilities">Utilities</a><ul>
<li><a href="#arrays">Arrays</a></li>
<li><a href="#events">Events</a></li>
</ul>
</li>
<li><a href="#cmake-techniques">CMake Techniques</a></li>
<li><a href="#math-operations">Math Operations</a></li>
<li><a href="#graphs">Graphs</a><ul>
<li><a href="#graph-conversions">Graph Conversions</a></li>
</ul>
</li>
<li><a href="#data-structures">Data Structures</a><ul>
<li><a href="#timing-demonstrations">Timing Demonstrations</a></li>
<li><a href="#kd-tree">KD-Tree</a></li>
<li><a href="#oriented-bounding-box-obb-tree">Oriented Bounding Box (OBB) Tree</a></li>
<li><a href="#octree">Octree</a></li>
<li><a href="#modified-bsp-tree">Modified BSP Tree</a></li>
</ul>
</li>
<li><a href="#vtk-concepts">VTK Concepts</a></li>
<li><a href="#rendering">Rendering</a></li>
<li><a href="#lighting">Lighting</a></li>
<li><a href="#visualization">Visualization</a></li>
<li><a href="#volume-rendering">Volume Rendering</a></li>
<li><a href="#user-interaction">User Interaction</a></li>
<li><a href="#working-with-images">Working with Images</a></li>
<li><a href="#image-processing">Image Processing</a></li>
<li><a href="#widgets">Widgets</a></li>
<li><a href="#plotting">Plotting</a></li>
<li><a href="#animation">Animation</a></li>
<li><a href="#geographic-visualization-geovis">Geographic Visualization (Geovis)</a></li>
<li><a href="#information-visualization-infovis">Information Visualization (Infovis)</a></li>
<li><a href="#qt">Qt</a></li>
<li><a href="#matlab">Matlab</a></li>
<li><a href="#databases">Databases</a><ul>
<li><a href="#sql">SQL</a></li>
</ul>
</li>
<li><a href="#renderman">RenderMan</a></li>
<li><a href="#remote-modules">Remote Modules</a></li>
</ul>
</div>
<h1 id="hello-world">Hello World</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxRendering/CylinderRenderingProperties">A hello world example</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html">vtkPolyDataMapper</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a></td>
<td>Cylinder example from the VTK Textbook and source code.</td>
</tr>
</tbody>
</table>
<h1 id="simple-operations">Simple Operations</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxSimpleOperations/DistanceBetweenPoints">DistanceBetweenPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a></td>
<td>Distance between two points.</td>
</tr>
<tr>
<td><a href="CxxSimpleOperations/DistancePointToLine">DistancePointToLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLine.html">vtkLine</a></td>
<td>Distance between a point and a line.</td>
</tr>
<tr>
<td><a href="CxxSimpleOperations/FloatingPointExceptions">FloatingPointExceptions</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFloatingPointExceptions.html">vtkFloatingPointExceptions</a></td>
<td>Floating Point Exceptions</td>
</tr>
<tr>
<td><a href="CxxSimpleOperations/GaussianRandomNumber">GaussianRandomNumber</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a></td>
<td>Generates Gaussian random numbers.</td>
</tr>
<tr>
<td><a href="CxxSimpleOperations/UniformRandomNumber">UniformRandomNumber</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a></td>
<td>Generates uniform random numbers.</td>
</tr>
<tr>
<td><a href="CxxSimpleOperations/RandomSequence">RandomSequence</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMinimalStandardRandomSequence.html">vtkMinimalStandardRandomSequence</a></td>
<td>This is the preferred way to generate random numbers.</td>
</tr>
<tr>
<td><a href="CxxSimpleOperations/ProjectPointPlane">ProjectPointPlane</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlane.html">vtkPlane</a></td>
<td>Project a point onto a plane.</td>
</tr>
<tr>
<td><a href="CxxSimpleOperations/PerspectiveTransform">PerspectiveTransform</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPerspectiveTransform.html">vtkPerspectiveTransform</a></td>
<td>Apply a perspective transformation to a point.</td>
</tr>
</tbody>
</table>
<h1 id="input-and-output">Input and Output</h1>
<h2 id="graph-formats">Graph Formats</h2>
<h2 id="3d-file-formats">3D File Formats</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxIO/ConvertFile">ConvertFile</a></td>
<td></td>
<td>Convert a file from one type to another</td>
</tr>
<tr>
<td><a href="CxxInfoVis/XGMLReader">XGMLReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXGMLReader.html">vtkXGMLReader</a></td>
<td>Read a .gml file</td>
</tr>
</tbody>
</table>
<h3 id="standard-formats">Standard Formats</h3>
<h4 id="input">Input</h4>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxIO/DEMReader">DEMReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDEMReader.html">vtkDEMReader</a></td>
<td>Read DEM (elevation map) files</td>
</tr>
<tr>
<td><a href="CxxIO/DumpXMLFile">DumpXMLFile</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDataSetReader.html">vtkDataSetReader</a></td>
<td>Report the contents of a VTK XML or legacy file</td>
</tr>
<tr>
<td><a href="CxxIO/IndividualVRML">IndividualVRML</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVRMLImporter.html">vtkVRMLImporter</a></td>
<td>This example is used to get each actor and object from a scene and verify axes correspondence</td>
</tr>
<tr>
<td><a href="CxxIO/ParticleReader">ParticleReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkParticleReader.html">vtkParticleReader</a></td>
<td>This example reads ascii files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file format.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadDICOMSeries">ReadDICOMSeries</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDICOMImageReader.html">vtkDICOMImageReader</a></td>
<td>This example demonstrates how to read a series of DICOM images and scroll through slices</td>
</tr>
<tr>
<td><a href="CxxIO/ReadDICOM">ReadDICOM</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDICOMImageReader.html">vtkDICOMImageReader</a></td>
<td>Read DICOM file</td>
</tr>
<tr>
<td><a href="CxxInfoVis/ReadDelimitedFile">ReadDelimitedFile</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDelimitedTextReader.html">vtkDelimitedTextReader</a></td>
<td>Read a delimited file into a polydata.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadOBJ">ReadOBJ</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOBJReader.html">vtkOBJReader</a></td>
<td>Read an OBJ (.obj) file.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadPDB">ReadPDB</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPDBReader.html">vtkPDBReader</a></td>
<td>Read Protein Data Bank Files.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadPLOT3D">ReadPLOT3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPLOT3DReader.html">vtkPLOT3DReader</a></td>
<td>Read CFD (computational fluid dynamics) data produced by PLOT3D.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadPLY">ReadPLY</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPLYReader.html">vtkPLYReader</a></td>
<td>Read PLY (.ply) files</td>
</tr>
<tr>
<td><a href="CxxIO/ReadPlainTextTriangles">ReadPlainTextTriangles</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkSmartPointer.html">vtkSmartPointer</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkPoints.html">vtkPoints</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkCellArray.html">vtkCellArray</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html">vtkXMLPolyDataWriter</a></td>
<td>Read a plain text file into a polydata.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadPlainText">ReadPlainText</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td>Read a plain text file into a polydata.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadSTL">ReadSTL</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSTLReader.html">vtkSTLReader</a></td>
<td>Read stereo lithography STL (.stl) files</td>
</tr>
<tr>
<td><a href="CxxIO/SimplePointsReader">SimplePointsReader </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSimplePointsReader.html">vtkSimplePointsReader</a></td>
<td>Read a simple "xyz" file of points.</td>
</tr>
<tr>
<td><a href="CxxIO/VRML">VRML</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVRMLImporter.html">vtkVRMLImporter</a></td>
<td>Read a VRML (WRL) file.</td>
</tr>
</tbody>
</table>
<h4 id="output">Output</h4>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxInfoVis/DelimitedTextWriter">DelimitedTextWriter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDelimitedTextWriter.html">vtkDelimitedTextWriter</a></td>
<td>Write data to a delimited file</td>
</tr>
<tr>
<td><a href="CxxIO/SimplePointsWriter">SimplePointsWriter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSimplePointsWriter.html">vtkSimplePointsWriter</a></td>
<td>Write a simple ".xyz" file</td>
</tr>
<tr>
<td><a href="CxxIO/WritePLY">WritePLY</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPLYWriter.html">vtkPLYWriter</a></td>
<td>Write PLY (.ply) files</td>
</tr>
<tr>
<td><a href="CxxIO/WriteSTL">WriteSTL</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSTLWriter.html">vtkSTLWriter</a></td>
<td>Write stereo lithography STL (.stl) files</td>
</tr>
</tbody>
</table>
<h3 id="vtk-formats">VTK Formats</h3>
<h4 id="input_1">Input</h4>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxIO/ReadImageData">ReadImageData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataReader.html">vtkXMLImageDataReader</a></td>
<td>Read a image data (.vti) file</td>
</tr>
<tr>
<td><a href="CxxIO/ReadPolyData">ReadPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html">vtkXMLPolyDataReader</a></td>
<td>Read a polygonal data (.vtp) file</td>
</tr>
<tr>
<td><a href="CxxIO/ReadRectilinearGrid">ReadRectilinearGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLRectilinearGridReader.html">vtkXMLRectilinearGridReader</a></td>
<td>Read a rectilinear grid (.vtr) file</td>
</tr>
<tr>
<td><a href="CxxIO/ReadStructuredGrid">ReadStructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLStructuredGridReader.html">vtkXMLStructuredGridReader</a></td>
<td>Read a structured grid (.vts) file</td>
</tr>
<tr>
<td><a href="CxxIO/ReadUnknownTypeXMLFile">ReadUnknownTypeXMLFile</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLGenericDataObjectReader.html">vtkXMLGenericDataObjectReader</a></td>
<td>Read an XML file and later decide what kind it is</td>
</tr>
<tr>
<td><a href="CxxIO/ReadUnstructuredGrid">ReadUnstructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridReader.html">vtkXMLUnstructuredGridReader</a></td>
<td>Read an unstructured grid (.vtu) file</td>
</tr>
</tbody>
</table>
<h4 id="output_1">Output</h4>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxIO/ExportDICOMtoVTI">ExportDICOMtoVTI</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataWriter.html">vtkXMLImageDataWriter</a></td>
<td>Write a .vti file from a DICOM image.</td>
</tr>
<tr>
<td><a href="CxxIO/ExodusIIWriter">Write an ExodusII file</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExodusIIWriter.html">vtkExodusIIWriter</a></td>
<td>Write a time varying ExodusII file.</td>
</tr>
<tr>
<td><a href="CxxIO/XMLPImageDataWriter">Write an image file to parallel files</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPImageDataWriter.html">vtkXMLPImageDataWriter</a></td>
<td>Write a .pvti file with 4 .vti pieces.</td>
</tr>
<tr>
<td><a href="CxxIO/XMLPUnstructuredGridWriter">Write an unstructured grid to parallel files</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPUnstructuredGridWriter.html">vtkXMLPUnstructuredGridWriter</a></td>
<td>Write a .pvtu with 4 .vtu pieces.</td>
</tr>
<tr>
<td><a href="CxxIO/WriteVTI">WriteVTI</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataWriter.html">vtkXMLImageDataWriter</a></td>
<td>Write a .vti file. VTI is an "ImageData".</td>
</tr>
<tr>
<td><a href="CxxIO/WriteVTP">WriteVTP</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html">vtkXMLPolyDataWriter</a></td>
<td>Write a .vtp file. VTP is a "PolyData". This format allows for the most complex geometric objects to be stored.</td>
</tr>
<tr>
<td><a href="CxxIO/WriteVTU">WriteVTU</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html">vtkXMLUnstructuredGridWriter</a></td>
<td>Write a .vtu file. VTU is an "Unstructured Grid". This format allows for 3D data to be stored.</td>
</tr>
<tr>
<td><a href="CxxIO/XMLStructuredGridWriter">XMLStructuredGridWriter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLStructuredGridWriter.html">vtkXMLStructuredGridWriter</a></td>
<td>Write a .vts file from a <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html">vtkStructuredGrid</a>.</td>
</tr>
</tbody>
</table>
<h3 id="legacy-vtk-formats">Legacy VTK Formats</h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxIO/GenericDataObjectReader">GenericDataObjectReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGenericDataObjectReader.html">vtkGenericDataObjectReader</a></td>
<td>Read any type of legacy .vtk file.</td>
</tr>
<tr>
<td><a href="CxxIO/StructuredGridReader">StructuredGridReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGridReader.html">vtkStructuredGridReader</a></td>
<td>Read a structured grid (.vtk) file.</td>
</tr>
<tr>
<td><a href="CxxIO/StructuredPointsReader">StructuredPointsReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredPointsReader.html">vtkStructuredPointsReader</a></td>
<td>Read a structured points (.vtk) file.</td>
</tr>
</tbody>
</table>
<h2 id="image-format">Image Format</h2>
<h3 id="input_2">Input</h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxIO/ImageReader2Factory">ImageReader2Factory</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageReader2Factory.html">vtkImageReader2Factory</a></td>
<td>This class tries to find an appropriate reader. It is very convenient to use this when you don't know what kind of file to expect.</td>
</tr>
<tr>
<td><a href="CxxIO/JPEGReader">JPEGReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkJPEGReader.html">vtkJPEGReader</a></td>
<td>Read a JPG image.</td>
</tr>
<tr>
<td><a href="CxxIO/MetaImageReader">MetaImageReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMetaImageReader.html">vtkMetaImageReader</a></td>
<td>Read .mha files.</td>
</tr>
<tr>
<td><a href="CxxIO/PNGReader">PNGReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPNGReader.html">vtkPNGReader</a></td>
<td>Read a PNG image.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadBMP">ReadBMP</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBMPReader.html">vtkBMPReader</a></td>
<td>Read BMP (.bmp) files.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadPNM">ReadPNM</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPNMReader.html">vtkPNMReader</a></td>
<td>Read PNM (.pnm) files.</td>
</tr>
<tr>
<td><a href="CxxIO/ReadTIFF">ReadTIFF</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTIFFReader.html">vtkTIFFReader</a></td>
<td>Read TIFF (.tif) files.</td>
</tr>
</tbody>
</table>
<h3 id="output_2">Output</h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxIO/JPEGWriter">JPEGWriter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkJPEGWriter.html">vtkJPEGWriter</a></td>
<td>Write a JPEG (.jpg) file.</td>
</tr>
<tr>
<td><a href="CxxIO/MetaImageWriter">MetaImageWriter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMetaImageWriter.html">vtkMetaImageWriter</a></td>
<td>Write a .mha/.mhd + .raw file.</td>
</tr>
<tr>
<td><a href="CxxIO/WriteBMP">WriteBMP</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBMPWriter.html">vtkBMPWriter</a></td>
<td>Write a BMP (.bmp) file.</td>
</tr>
<tr>
<td><a href="CxxIO/WritePNG">WritePNG</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPNGWriter.html">vtkPNGWriter</a></td>
<td>Write a PNG (.png) file.</td>
</tr>
<tr>
<td><a href="CxxIO/WritePNM">WritePNM</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPNMWriter.html">vtkPNMWriter</a></td>
<td>Write a PNM (.pnm) file.</td>
</tr>
<tr>
<td><a href="CxxIO/WriteTIFF">WriteTIFF</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTIFFWriter.html">vtkTIFFWriter</a></td>
<td>Write a TIFF (.tif) file.</td>
</tr>
</tbody>
</table>
<h1 id="geometric-objects">Geometric Objects</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxGeometricObjects/Arrow">Arrow</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html">vtkArrowSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Axes">Axes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html">vtkAxesActor</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Cell3DDemonstration">Cell3DDemonstration</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHexagonalPrism.html">vtkHexagonalPrism</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html">vtkHexahedron</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkPentagonalPrism.html">vtkPentagonalPrism</a>  <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html">vtkPolyhedron</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkPyramid.html">vtkPyramid</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkTetra.html">vtkTetra</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkVoxel.html">vtkVoxel</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkWedge.html">vtkWedge</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a></td>
<td>Demonstrate the use of <a href="http://www.vtk.org/doc/nightly/html/classvtkCell3D.html">vtkCell3D</a> to construct geometric objects. Sample objects are generated from the classes derived from <a href="http://www.vtk.org/doc/nightly/html/classvtkCell3D.html">vtkCell3D</a> and displayed.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/ColoredLines">Colored Lines</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellData.html">vtkCellData</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkLine.html">vtkLine</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Cone">Cone</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkConeSource.html">vtkConeSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Cube">Cube</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCubeSource.html">vtkCubeSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Cylinder">Cylinder</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html">vtkCylinderSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Disk">Disk</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDiskSource.html">vtkDiskSource</a></td>
<td>A circle with a hole in it.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Dodecahedron">Dodecahedron</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html">vtkPolyhedron</a></td>
<td>Create a dodecahedron using <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html">vtkPolyhedron</a></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Frustum">Frustum</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFrustumSource.html">vtkFrustumSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/GeometricObjectsDemo">GeometricObjectsDemo</a></td>
<td></td>
<td>A demonstration of all geometric objects that work the same way.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Hexahedron">Hexahedron</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html">vtkHexahedron</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Line">Line</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLineSource.html">vtkLineSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/LongLine">LongLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLine.html">vtkLine</a></td>
<td>Manually create a polyline</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/OrientedArrow">Oriented Arrow</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html">vtkArrowSource</a></td>
<td>Orient an arrow along an arbitrary vector</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/OrientedCylinder">Oriented Cylinder</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html">vtkCylinderSource</a></td>
<td>Orient a cylinder along an arbitrary vector</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Plane">Plane</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html">vtkPlaneSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/PlanesIntersection">PlanesIntersection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlanesIntersection.html">vtkPlanesIntersection</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Planes">Planes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlanes.html">vtkPlanes</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/PlatonicSolid">PlatonicSolid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlatonicSolidSource.html">vtkPlatonicSolidSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Point">Point</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPoints.html">vtkPoints</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/PolyLine">PolyLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html">vtkPolyLine</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/PolygonIntersection">PolygonIntersection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolygon.html">vtkPolygon</a></td>
<td>Compute the intersection of a line segment with a polygon.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Polygon">Polygon</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolygon.html">vtkPolygon</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Polyhedron">Polyhedron</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html">vtkPolyhedron</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Pyramid">Pyramid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPyramid.html">vtkPyramid</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Quad">Quad</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuad.html">vtkQuad</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/RegularPolygonSource">Regular Polygon</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRegularPolygonSource.html">vtkRegularPolygonSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Sphere">Sphere</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html">vtkSphereSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Tetrahedron">Tetrahedron</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTetra.html">vtkTetra</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/TriangleStrip">Triangle strip</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangleStrip.html">vtkTriangleStrip</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Triangle">Triangle</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangle.html">vtkTriangle</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Vertex">Vertex</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVertex.html">vtkVertex</a></td>
<td></td>
</tr>
</tbody>
</table>
<h2 id="parametric-objects">Parametric Objects</h2>
<p>These examples demonstrate how to create an display one of the many <a href="http://www.vtk.org/doc/nightly/html/classvtkParametric.html">vtkParametric</a> objects. All of the classes listed can be used in an identical fashion.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxGeometricObjects/ParametricObjects">ParametricObjects</a></td>
<td></td>
<td>Create and display a parametric object. Uncomment the object that you wish to be displayed.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/ParametricObjectsDemo">ParametricObjectsDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkParametricBoy.html">vtkParametricBoy</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricConicSpiral.html">vtkParametricConicSpiral</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricCrossCap.html">vtkParametricCrossCap</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricDini.html">vtkParametricDini</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricEllipsoid.html">vtkParametricEllipsoid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricEnneper.html">vtkParametricEnneper</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricFigure8Klein.html">vtkParametricFigure8Klein</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricKlein.html">vtkParametricKlein</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricMobius.html">vtkParametricMobius</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html">vtkParametricRandomHills</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricRoman.html">vtkParametricRoman</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html">vtkParametricSpline</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html">vtkParametricSuperEllipsoid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html">vtkParametricSuperToroid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricTorus.html">vtkParametricTorus</a></td>
<td>Demonstration of of the <a href="http://www.vtk.org/doc/nightly/html/classvtkParametric.html">vtkParametric</a>* classes added by Andrew Maclean. All the objects are displayed in a 4X4 array.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/ParametricObjectsDemo2">ParametricObjectsDemo2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkParametricBohemianDome.html">vtkParametricBohemianDome</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricBour.html">vtkParametricBour</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricCatalanMinimal.html">vtkParametricCatalanMinimal</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricHenneberg.html">vtkParametricHenneberg</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricKuen.html">vtkParametricKuen</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricPluckerConoid.html">vtkParametricPluckerConoid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricPseudosphere.html">vtkParametricPseudosphere</a></td>
<td>Demonstration of additional vtkParametric* classes added by  Tim Meehan. All the objects are displayed in a 4X2 array.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/ParametricKuenDemo">ParametricKuenDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkParametricKuen.html">vtkParametricKuen</a></td>
<td>Interactively change the parameters for a Kuen Surface.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/ParametricSuperEllipsoidDemo">ParametricSuperEllipsoidDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html">vtkParametricSuperEllipsoid</a></td>
<td>Interactively change the parameters for a SuperEllipsoid Surface.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/ParametricSuperToroidDemo">ParametricSuperToroidDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html">vtkParametricSuperToroid</a></td>
<td>Interactively change the parameters for a SuperToroid Surface.</td>
</tr>
</tbody>
</table>
<h1 id="implicit-functions-and-iso-surfaces">Implicit Functions and Iso-surfaces</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxVisualizationAlgorithms/BandedPolyDataContourFilter">BandedPolyDataContourFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html">vtkBandedPolyDataContourFilter</a></td>
<td>Create filled contours.</td>
</tr>
<tr>
<td><a href="CxxModelling/ContourTriangulator">ContourTriangulator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMarchingSquares.html">vtkMarchingSquares</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkContourTriangulator.html">vtkContourTriangulator</a></td>
<td>Create a contour from a structured point set (image) and triangulate it.</td>
</tr>
<tr>
<td><a href="CxxVisualizationAlgorithms/CutWithCutFunction">CutWithCutFunction</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCutter.html">vtkCutter</a></td>
<td>Cut a surface with an implicit plane using <a href="http://www.vtk.org/doc/nightly/html/classvtkCutter.html">vtkCutter</a>.</td>
</tr>
<tr>
<td><a href="CxxVisualizationAlgorithms/CutWithScalars">CutWithScalars</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html">vtkContourFilter</a></td>
<td>Cut a surface with scalars.</td>
</tr>
<tr>
<td><a href="CxxModelling/ExtractLargestIsosurface">ExtractLargestIsosurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html">vtkPolyDataConnectivityFilter</a></td>
<td>Extract largest isosurface.</td>
</tr>
<tr>
<td><a href="CxxVisualizationAlgorithms/FilledContours">FilledContours</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html">vtkContourFilter</a></td>
<td>Create filled contours (using <a href="http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html">vtkClipPolyData</a>).</td>
</tr>
<tr>
<td><a href="/ImplicitFunctions/ImplicitDataSet">ImplicitDataSet</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html">vtkImplicitDataSet</a></td>
<td>Convert an imagedata to an implicit function.</td>
</tr>
<tr>
<td><a href="CxxImplicitFunctions/ImplicitSphere">ImplicitSphere</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphere.html">vtkSphere</a></td>
<td>An implicit representation of a sphere.</td>
</tr>
<tr>
<td><a href="CxxImplicitFunctions/IsoContours">IsoContours</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkContourFunction.html">vtkContourFunction</a></td>
<td>Visualize different isocontours using a slider.</td>
</tr>
<tr>
<td><a href="CxxModelling/MarchingCubes">MarchingCubes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html">vtkMarchingCubes</a></td>
<td>Create a voxelized sphere.</td>
</tr>
<tr>
<td><a href="CxxModelling/MarchingSquares">MarchingSquares</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMarchingSquares.html">vtkMarchingSquares</a></td>
<td>Create a contour from a structured point set (image).</td>
</tr>
<tr>
<td><a href="CxxImplicitFunctions/SampleFunction">SampleFunction</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSampleFunction.html">vtkSampleFunction</a></td>
<td>Sample and visualize an implicit function.</td>
</tr>
</tbody>
</table>
<h1 id="working-with-3d-data">Working with 3D Data</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxPolyData/AlignFrames">AlignFrames</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLandmarkTransform.html">vtkLandmarkTransform</a></td>
<td>Align coordinate frames.</td>
</tr>
<tr>
<td><a href="CxxFilters/AppendFilter">AppendFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAppendFilter.html">vtkAppendFilter</a></td>
<td>Append different types of data,</td>
</tr>
<tr>
<td><a href="CxxPolyData/BooleanOperationPolyDataFilter">BooleanOperationPolyDataFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBooleanOperationPolyDataFilter.html">vtkBooleanOperationPolyDataFilter</a></td>
<td>Perform boolean operations on two <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> objects.</td>
</tr>
<tr>
<td><a href="CxxPolyData/CellCenters">CellCenters</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellCenters.html">vtkCellCenters</a></td>
<td>Compute points at the center of every cell.</td>
</tr>
<tr>
<td><a href="CxxPolyData/CellEdgeNeighbors">CellEdgeNeighbors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>::GetCellNeighbors</td>
<td>Determine which cells share an edge with a specific cell.</td>
</tr>
<tr>
<td><a href="CxxPolyData/CellPointNeighbors">CellPointNeighbors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>::GetCellNeighbors</td>
<td>Determine which cells share a single point with a specific cell.</td>
</tr>
<tr>
<td><a href="CxxPolyData/CenterOfMass">CenterOfMass</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCenterOfMass.html">vtkCenterOfMass</a></td>
<td>Compute the center of mass of the points.</td>
</tr>
<tr>
<td><a href="CxxGeometricObjects/Circle">Circle</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCutter.html">vtkCutter</a></td>
<td>Create a circle by cutting through a sphere.</td>
</tr>
<tr>
<td><a href="CxxPolyData/CleanPolyData">CleanPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCleanPolyData.html">vtkCleanPolyData</a></td>
<td>Remove coincident points.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ColorCellsWithRGB">ColorCellsWithRGB</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellData.html">vtkCellData</a></td>
<td>Color individual cells of a polydata with rgb colors.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ColorCells">ColorCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a></td>
<td>Color individual cells of a polydata with scalar index.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ColoredPoints">Colored Points</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html">vtkUnsignedCharArray</a></td>
<td>Add three points to a polydata and associate a color with each of them.</td>
</tr>
<tr>
<td><a href="CxxFilters/CombinePolydata">CombinePolydata</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAppendPolyData.html">vtkAppendPolyData</a></td>
<td>Combine/Append PolyData.</td>
</tr>
<tr>
<td><a href="CxxFilters/ConnectivityFilter">ConnectivityFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkConnectivityFilter.html">vtkConnectivityFilter</a></td>
<td>Color any dataset type based on connectivity.</td>
</tr>
<tr>
<td><a href="CxxFiltering/ContoursFromPolyData">ContoursFromPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCutter.html">vtkCutter</a></td>
<td>Create contours from PolyData.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ContoursToSurface">ContoursToSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVoxelContoursToSurfaceFilter.html">vtkVoxelContoursToSurfaceFilter</a></td>
<td>Convert contours to a surface.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ConvexHull_ShrinkWrap">ConvexHull_ShrinkWrap</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSmoothPolyDataFilter.html">vtkSmoothPolyDataFilter</a></td>
<td>Convex hull using shrink wrapping.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ConvexHull_vtkHull">ConvexHull_vtkHull</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHull.html">vtkHull</a></td>
<td>Convex hull using <a href="http://www.vtk.org/doc/nightly/html/classvtkHull.html">vtkHull</a>.</td>
</tr>
<tr>
<td><a href="CxxPolyData/CopyAllArrays">CopyAllArrays</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td>Copy all arrays from one <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> to another.</td>
</tr>
<tr>
<td><a href="CxxPolyData/DataBounds">Data Bounds</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>::GetBounds</td>
<td>Get the minimum and maximum value in each dimension. (Axis aligned bounding box)</td>
</tr>
<tr>
<td><a href="CxxPolyData/DataSetSurfaceFilter">DataSetSurfaceFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDataSetSurfaceFilter.html">vtkDataSetSurfaceFilter</a></td>
<td>Convert <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a> to <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>.</td>
</tr>
<tr>
<td><a href="CxxPolyData/DecimatePolyline">DecimatePolyline</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDecimatePolylineFilter.html">vtkDecimatePolylineFilter</a></td>
<td>Decimate polyline.</td>
</tr>
<tr>
<td><a href="CxxBroken/PolyData/DeleteCells">Delete cells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td>Delete a cell from a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
</tr>
<tr>
<td><a href="CxxPolyData/DeletePoint">DeletePoint</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPoints.html">vtkPoints</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxPolyData/DetermineArrayDataTypes">DetermineArrayDataTypes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td>Determine data types of arrays.</td>
</tr>
<tr>
<td><a href="CxxPolyData/DistancePolyDataFilter">DistancePolyDataFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDistancePolyDataFilter.html">vtkDistancePolyDataFilter</a></td>
<td>Compute the distance function from one <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> to another.</td>
</tr>
<tr>
<td><a href="CxxPolyData/EmbedPointsIntoVolume">EmbedPointsIntoVolume</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGaussianSplatter.html">vtkGaussianSplatter</a></td>
<td>Embed points into a volume.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ExternalContour">ExternalContour</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html">vtkWindowToImageFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html">vtkContourFilter</a></td>
<td>Get the External Contour from Polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ExtractCellsUsingPoints">ExtractCellsUsingPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html">vtkExtractSelection</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSelection.html">vtkSelection</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSelectionNode.html">vtkSelectionNode</a></td>
<td>Extract points but bring cells that are still complete with them.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ExtractOutsideSurface">ExtractOutsideSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html">vtkPolyDataConnectivityFilter</a></td>
<td>Extract the outer surface of a multiple surface polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ExtractPolyLinesFromPolyData">ExtractPolyLinesFromPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td>Extract polylines from polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ExtractSelectedIds">ExtractSelectedIds</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelectedIds.html">vtkExtractSelectedIds</a></td>
<td>Extract selected points.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ExtractSelectionCells">ExtractSelectionCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html">vtkExtractSelection</a></td>
<td>Extract selection cells.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ExtractSelectionOriginalId">ExtractSelectionOriginalId</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html">vtkExtractSelection</a></td>
<td>Extract selection and find correspondence between new and original Id.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ExtractSelection">ExtractSelection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html">vtkExtractSelection</a></td>
<td>Extract selection points.</td>
</tr>
<tr>
<td><a href="CxxFiltering/ExtractVisibleCells">ExtractVisibleCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHardwareSelector.html">vtkHardwareSelector</a></td>
<td>Extract and highlight visible cells.</td>
</tr>
<tr>
<td><a href="CxxPolyData/FieldData">FieldData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFieldData.html">vtkFieldData</a></td>
<td>Add Global Miscellaneous Data (FieldData) to a Polydata.</td>
</tr>
<tr>
<td><a href="CxxIO/FindAllArrayNames">FindAllArrayNames</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td>Get the names of all of the data arrays.</td>
</tr>
<tr>
<td><a href="CxxPolyData/FitSplineToCutterOutput">FitSplineToCutterOutput</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html">vtkKochanekSpline</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSplineFilter.html">vtkSplineFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSpline.html">vtkSpline</a></td>
<td>Fit a spline to cutter output.</td>
</tr>
<tr>
<td><a href="CxxPolyData/GeometryFilter">GeometryFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGeometryFilter.html">vtkGeometryFilter</a></td>
<td>Convert <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a> to <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> (another way).</td>
</tr>
<tr>
<td><a href="CxxPolyData/GetMiscCellData">GetMiscCellData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellData.html">vtkCellData</a></td>
<td>Get Miscellaneous Data from Cells in a Polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/GetMiscPointData">GetMiscPointData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDoubleArray.html">vtkDoubleArray</a></td>
<td>Get Miscellaneous Data from Points in a Polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/GradientFilter">GradientFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGradientFilter.html">vtkGradientFilter</a></td>
<td>Compute the gradient of a scalar field on a data set.</td>
</tr>
<tr>
<td><a href="CxxFilters/ImplicitBoolean">ImplicitBoolean</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitBoolean.html">vtkImplicitBoolean</a></td>
<td>Operations include intersection and union.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ImplicitModeller">ImplicitModeller</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitModeller.html">vtkImplicitModeller</a></td>
<td>Compute the distance from an object to every point on a uniform grid.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ImplicitPolyDataDistance">ImplicitPolyDataDistance</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html">vtkImplicitPolyDataDistance</a></td>
<td>Compute the distance function in a space around a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>.</td>
</tr>
<tr>
<td><a href="CxxPolyData/InterpolateMeshOnGrid">InterpolateMeshOnGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html">vtkProbeFilter</a></td>
<td>Interpolate a mesh over a grid.</td>
</tr>
<tr>
<td><a href="CxxPolyData/InterpolateTerrain">InterpolateTerrain</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html">vtkProbeFilter</a></td>
<td>[http://<a href="http://www.vtk.org/doc/nightly/html/classvtk.html">vtk</a>.org/Wiki/Demystifying_the_<a href="http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html">vtkProbeFilter</a> Here] is a good explanation of what is going on.Interpolate terrain.</td>
</tr>
<tr>
<td><a href="CxxPolyData/IntersectionPolyDataFilter">IntersectionPolyDataFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkIntersectionPolyDataFilter.html">vtkIntersectionPolyDataFilter</a></td>
<td>Compute the intersection of two <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> objects.</td>
</tr>
<tr>
<td><a href="CxxPolyData/IterateOverLines">IterateOverLines</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellArray.html">vtkCellArray</a></td>
<td>Iterate through the lines of a PolyData.</td>
</tr>
<tr>
<td><a href="CxxInfoVis/KMeansClustering">KMeansClustering</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKMeansStatistics.html">vtkKMeansStatistics</a></td>
<td>KMeans Clustering</td>
</tr>
<tr>
<td><a href="CxxPolyData/KochanekSpline">KochanekSpline</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html">vtkKochanekSpline</a></td>
<td>Create an Kochanek spline on a set of points.</td>
</tr>
<tr>
<td><a href="CxxPolyData/LinearExtrusion">LinearExtrusion</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html">vtkLinearExtrusionFilter</a></td>
<td>Extrude a shape.</td>
</tr>
<tr>
<td><a href="CxxPolyData/MaskPoints">MaskPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMaskPoints.html">vtkMaskPoints</a></td>
<td>Select a subset (mask) of a point set.</td>
</tr>
<tr>
<td><a href="CxxPolyData/MergePoints">MergePoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMergePoints.html">vtkMergePoints</a></td>
<td>Remove duplicate (merge) points.</td>
</tr>
<tr>
<td><a href="CxxPolyData/MiscCellData">MiscCellData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellData.html">vtkCellData</a></td>
<td>Add Miscellaneous Data to Cells in a Polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/MiscPointData">MiscPointData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointData.html">vtkPointData</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html">vtkFloatArray</a></td>
<td>Add Miscellaneous Data to Points in a Polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/MultiBlockMergeFilter">MultiBlockMergeFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMultiBlockMergeFilter.html">vtkMultiBlockMergeFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkMultiBlockDataSet.html">vtkMultiBlockDataSet</a></td>
<td>Combine MultiBlockDataSets.</td>
</tr>
<tr>
<td><a href="CxxPolyData/NullPoint">NullPoint</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointData.html">vtkPointData</a></td>
<td>Set everything in PointData at a specified index to NULL</td>
</tr>
<tr>
<td><a href="CxxPolyData/Outline">Outline</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOutlineFilter.html">vtkOutlineFilter</a></td>
<td>Draw the bounding box of the data</td>
</tr>
<tr>
<td><a href="CxxInfoVis/PKMeansClustering">PKMeansClustering</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPKMeansStatistics.html">vtkPKMeansStatistics</a></td>
<td>Parallel KMeans Clustering.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ParametricSpline">ParametricSpline</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html">vtkCardinalSpline</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html">vtkParametricSpline</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricFunctionSource.html">vtkParametricFunctionSource</a></td>
<td>Create a Cardinal spline on a set of points.</td>
</tr>
<tr>
<td><a href="CxxFilters/PerlinNoise">Perlin Noise</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPerlinNoise.html">vtkPerlinNoise</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxPolyData/PointCellIds">PointCellIds</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkIdFilter.html">vtkIdFilter</a></td>
<td>Generate point and cell id arrays.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PointInsideObject2">PointInsideObject2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDelaunay3D.html">vtkDelaunay3D</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>::FindCell</td>
<td>This uses a Delaunay triangulation to compute a volume. This gives more of an "is inside convex hull" effect than an "is inside object".</td>
</tr>
<tr>
<td><a href="CxxPolyData/PointInsideObject">PointInsideObject</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSelectEnclosedPoints.html">vtkSelectEnclosedPoints</a></td>
<td>Check if a point is inside an object.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PointsProjectedHull">PointsProjectedHull</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointsProjectedHull.html">vtkPointsProjectedHull</a></td>
<td>Convex hull of points projected onto the coordinate planes.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataCellNormals">PolyDataCellNormals</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellData.html">vtkCellData</a></td>
<td>Add/Get Normals to/from cells in a Polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataContourToImageData">PolyDataContourToImageData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html">vtkLinearExtrusionFilter</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html">vtkPolyDataToImageStencil</a></td>
<td>Generate a binarized image from a closed contour.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataExtractNormals">PolyDataExtractNormals</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataNormals.html">vtkPolyDataNormals</a></td>
<td>Extract Normals from a Polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataGetPoint">PolyDataGetPoint</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td>Get point locations/coordinates from a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataIsoLines">PolyDataIsoLines</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html">vtkBandedPolyDataContourFilter</a></td>
<td>Iso lines on the surface of a polydata</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataPointNormals">PolyDataPointNormals</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointData.html">vtkPointData</a></td>
<td>Add/Get Normals to/from points in a Polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataPointSampler">PolyDataPointSampler</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataPointSampler.html">vtkPolyDataPointSampler</a></td>
<td>Sample the edges or surfaces of a polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataToImageData">PolyDataToImageData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html">vtkPolyDataToImageStencil</a></td>
<td>Generate a binarized volume from a closed surface.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ProcrustesAlignmentFilter">ProcrustesAlignmentFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProcrustesAlignmentFilter.html">vtkProcrustesAlignmentFilter</a></td>
<td>Align point sets.</td>
</tr>
<tr>
<td><a href="CxxFilters/ProgrammableFilter">ProgrammableFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html">vtkProgrammableFilter</a></td>
<td>Create a custom filter without subclassing.</td>
</tr>
<tr>
<td><a href="CxxFiltering/ProgrammableSource">ProgrammableSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProgrammableSource.html">vtkProgrammableSource</a></td>
<td>Create points using a programmable source. Generates points for a strange attractor.</td>
</tr>
<tr>
<td><a href="CxxVisualization/ProjectSphere">ProjectSphere</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProjectSphereFilter.html">vtkProjectSphereFilter</a></td>
<td>Unroll a sphere or spherical-like model.</td>
</tr>
<tr>
<td><a href="CxxPolyData/QuantizePolyDataPoints">QuantizePolyDataPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuantizePolyDataPoints.html">vtkQuantizePolyDataPoints</a></td>
<td>Snap (quantize) points to a grid.</td>
</tr>
<tr>
<td><a href="CxxPolyData/Reflection">Reflection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkReflectionFilter.html">vtkReflectionFilter</a></td>
<td>Mirror a DataSet.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ReverseSense">ReverseSense</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkReverseSense.html">vtkReverseSense</a></td>
<td>Flip normals.</td>
</tr>
<tr>
<td><a href="CxxPolyData/RibbonFilter">RibbonFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRibbonFilter.html">vtkRibbonFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxPolyData/RotationAroundLine">RotationAroundLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTransform.html">vtkTransform</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html">vtkTransformPolyDataFilter</a></td>
<td>Rotation around a line.</td>
</tr>
<tr>
<td><a href="CxxPolyData/RuledSurfaceFilter">RuledSurfaceFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRuledSurfaceFilter.html">vtkRuledSurfaceFilter</a></td>
<td>Create a surface between lines.</td>
</tr>
<tr>
<td><a href="CxxInfoVis/SCurveSpline">SCurveSpline</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSCurveSpline.html">vtkSCurveSpline</a></td>
<td>Create an SCurve spline on a set of points.</td>
</tr>
<tr>
<td><a href="CxxPolyData/SelectVisiblePoints">SelectVisiblePoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSelectVisiblePoints.html">vtkSelectVisiblePoints</a></td>
<td>Select visible points.</td>
</tr>
<tr>
<td><a href="CxxFiltering/SelectionSource">SelectionSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSelectionSource.html">vtkSelectionSource</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html">vtkExtractSelection</a></td>
<td>Specify a selection.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ShrinkPolyData">ShrinkPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkShrinkPolyData.html">vtkShrinkPolyData</a></td>
<td>Move all items in a PolyData towards their centroid.</td>
</tr>
<tr>
<td><a href="CxxPolyData/Silhouette">Silhouette</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataSilhouette.html">vtkPolyDataSilhouette</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxPolyData/Stripper">Stripper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStripper.html">vtkStripper</a></td>
<td>Convert triangles to triangle strips.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ThinPlateSplineTransform">ThinPlateSplineTransform</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkThinPlateSplineTransform.html">vtkThinPlateSplineTransform</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxPolyData/ThresholdingCells">ThresholdingCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkThreshold.html">vtkThreshold</a></td>
<td>Thresholding Cells.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ThresholdingPoints">ThresholdingPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkThresholdPoints.html">vtkThresholdPoints</a></td>
<td>Thresholding Points.</td>
</tr>
<tr>
<td><a href="CxxPolyData/TransformFilter">TransformFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTransformFilter.html">vtkTransformFilter</a></td>
<td>Transform a data set.</td>
</tr>
<tr>
<td><a href="CxxPolyData/TransformOrder">TransformOrder</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html">vtkTransformPolyDataFilter</a></td>
<td>Demonstrate how the order of applying transforms affects the result.</td>
</tr>
<tr>
<td><a href="CxxPolyData/TransformPipeline">TransformPipeline</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTransform.html">vtkTransform</a></td>
<td>Combining the transformation, in order to manipulate a group of <a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>. Shown in the example robot arm motion.</td>
</tr>
<tr>
<td><a href="CxxFiltering/TransformPolyData">TransformPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html">vtkTransformPolyDataFilter</a></td>
<td>Apply a Transformation to a PolyData.</td>
</tr>
<tr>
<td><a href="CxxPolyData/TriangleArea">TriangleArea</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangle.html">vtkTriangle</a>::TriangleArea</td>
<td>Compute the area of all triangles in a polydata.</td>
</tr>
<tr>
<td><a href="CxxPolyData/TriangleColoredPoints">TriangleColoredPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html">vtkUnsignedCharArray</a></td>
<td>Set the color of each point of a triangle. You will be able to interpolate the colors across the triangle.</td>
</tr>
<tr>
<td><a href="CxxPolyData/TriangleSolidColor">TriangleSolidColor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html">vtkUnsignedCharArray</a></td>
<td>Create a solid colored triangle.</td>
</tr>
<tr>
<td><a href="CxxPolyData/TubeFilter">TubeFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html">vtkTubeFilter</a></td>
<td>Give lines a thickness (produce a cylinder around lines.</td>
</tr>
<tr>
<td><a href="CxxFiltering/VectorFieldNonZeroExtraction">VectorFieldNonZeroExtraction</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelectedThresholds.html">vtkExtractSelectedThresholds</a></td>
<td>Extract non-zero vectors from a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a>.</td>
</tr>
<tr>
<td><a href="CxxPolyData/VertexConnectivity">VertexConnectivity</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>::GetCellPoints</td>
<td>Get a list of vertices attached (through an edge) to a vertex.</td>
</tr>
<tr>
<td><a href="CxxPolyData/WarpScalar">WarpScalar</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWarpScalar.html">vtkWarpScalar</a></td>
<td>Move vertices along normals.</td>
</tr>
<tr>
<td><a href="CxxPolyData/WarpSurface">WarpSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html">vtkWarpVector</a></td>
<td>Warp a surface along its normal.</td>
</tr>
<tr>
<td><a href="CxxFiltering/WarpTo">WarpTo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWarpTo.html">vtkWarpTo</a></td>
<td>Bend an object.</td>
</tr>
<tr>
<td><a href="CxxPolyData/WarpVector">WarpVector</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html">vtkWarpVector</a></td>
<td></td>
</tr>
</tbody>
</table>
<h2 id="data-types">Data Types</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxCompositeData/CompositePolyDataMapper">CompositePolyDataMapper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCompositePolyDataMapper.html">vtkCompositePolyDataMapper</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxCompositeData/MultiBlockDataSet">MultiBlockDataSet</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMultiBlockDataSet.html">vtkMultiBlockDataSet</a></td>
<td>Demonstrates how to make and use VTK's MultiBlock type data</td>
</tr>
<tr>
<td><a href="CxxCompositeData/OverlappingAMR">OverlappingAMR</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOverlappingAMR.html">vtkOverlappingAMR</a></td>
<td>Demonstrates how to create and populate a VTK's Overlapping AMR Grid type Data</td>
</tr>
</tbody>
</table>
<h2 id="data-type-conversions">Data Type Conversions</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxPolyData/PolyDataToUnstructuredGrid">PolyDataToUnstructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAppendFilter.html">vtkAppendFilter</a></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> to a <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a>.</td>
</tr>
</tbody>
</table>
<h2 id="point-cloud-operations">Point cloud operations</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxPoints/DensifyPoints">DensifyPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDensifyPointCloudFilter.html">vtkDensifyPointCloudFilter</a></td>
<td>Add points to a point cloud.</td>
</tr>
<tr>
<td><a href="CxxPolyData/DownsamplePointCloud">DownsamplePointCloud</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCleanPolyData.html">vtkCleanPolyData</a></td>
<td>Downsample a point cloud. Remove points so that there are no points within a tolerance of any point.</td>
</tr>
<tr>
<td><a href="CxxPoints/ExtractCluster">ExtractCluster</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkEuclideanClusterExtraction.html">vtkEuclideanClusterExtraction</a></td>
<td>From a set of randomly distributed spheres, extract connected clusters.</td>
</tr>
<tr>
<td><a href="CxxPoints/ExtractPointsDemo">ExtractPointsDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractPoints.html">vtkExtractPoints</a></td>
<td>Extract points inside an implicit function.</td>
</tr>
<tr>
<td><a href="CxxPoints/ExtractSurfaceDemo">ExtractSurfaceDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html">vtkExtractSurface</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html">vtkPCANormalEstimation</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html">vtkSignedDistance</a></td>
<td>Create a surface from Unorganized Points using Point filters (DEMO).</td>
</tr>
<tr>
<td><a href="CxxPoints/ExtractSurface">ExtractSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html">vtkExtractSurface</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html">vtkPCANormalEstimation</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html">vtkSignedDistance</a></td>
<td>Create a surface from Unorganized Points using Point filters.</td>
</tr>
<tr>
<td><a href="CxxPoints/FitImplicitFunction">FitImplicitFunction</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFitImplicitFunction.html">vtkFitImplicitFunction</a></td>
<td>Extract points within a distance to an implicit function.</td>
</tr>
<tr>
<td><a href="CxxPoints/MaskPointsFilter">MaskPointsFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMaskPointsFilter.html">vtkMaskPointsFilter</a></td>
<td>Extract points within an image mask.</td>
</tr>
<tr>
<td><a href="CxxPoints/NormalEstimation">NormalEstimation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html">vtkPCANormalEstimation</a></td>
<td>Estimate the normals of a random points that lie on a sphere.</td>
</tr>
<tr>
<td><a href="CxxPoints/PointOccupancy">PointOccupancy</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointOccupancy.html">vtkPointOccupancy</a></td>
<td>Show which voxels contain points.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PointSource">PointSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointSource.html">vtkPointSource</a></td>
<td>Generate a random point cloud.</td>
</tr>
<tr>
<td><a href="CxxPoints/RadiusOutlierRemoval">RadiusOutlierRemoval</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRadiusOutlierRemoval.html">vtkRadiusOutlierRemoval</a></td>
<td>Remove outliers.</td>
</tr>
<tr>
<td><a href="CxxPoints/SignedDistance">SignedDistance</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html">vtkSignedDistance</a></td>
<td>Compute signed distance to a point cloud.</td>
</tr>
<tr>
<td><a href="CxxPoints/UnsignedDistance">UnsignedDistance</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnsignedDistance.html">vtkUnsignedDistance</a></td>
<td>Compute unsigned distance to a point cloud.</td>
</tr>
</tbody>
</table>
<h2 id="working-with-meshes">Working with Meshes</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxMeshes/AddCell">AddCell</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td>Add a cell to an existing mesh.</td>
</tr>
<tr>
<td><a href="CxxMeshes/BoundaryEdges">BoundaryEdges</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFeatureEdges.html">vtkFeatureEdges</a></td>
<td>Find the edges that are used by only one face.</td>
</tr>
<tr>
<td><a href="CxxMeshes/CellEdges">CellEdges</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCell.html">vtkCell</a></td>
<td>Get edges of cells.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ClosedSurface">ClosedSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFeatureEdges.html">vtkFeatureEdges</a></td>
<td>Check if a surface is closed.</td>
</tr>
<tr>
<td><a href="CxxPolyData/ColorDisconnectedRegions">ColorDisconnectedRegions</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html">vtkPolyDataConnectivityFilter</a></td>
<td>Color each disconnected region of a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> a different color.</td>
</tr>
<tr>
<td><a href="CxxMeshes/ColoredElevationMap">ColoredElevationMap</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a></td>
<td>Color a mesh by height.</td>
</tr>
<tr>
<td><a href="CxxPolyData/Curvatures">Curvatures</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html">vtkCurvatures</a></td>
<td>Compute Gaussian, Mean, Min, and Max Curvatures.</td>
</tr>
<tr>
<td><a href="CxxMeshes/Decimation">Decimation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDecimatePro.html">vtkDecimatePro</a></td>
<td>Reduce the number of triangles in a mesh.</td>
</tr>
<tr>
<td><a href="CxxMeshes/DeformPointSet">DeformPointSet</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDeformPointSet.html">vtkDeformPointSet</a></td>
<td>Deform a point set with a control polyhedra.</td>
</tr>
<tr>
<td><a href="CxxPolyData/DijkstraGraphGeodesicPath">DijkstraGraphGeodesicPath</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDijkstraGraphGeodesicPath.html">vtkDijkstraGraphGeodesicPath</a></td>
<td>Find the shortest path between two points on a mesh.</td>
</tr>
<tr>
<td><a href="CxxMeshes/ElevationFilter">ElevationFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkElevationFilter.html">vtkElevationFilter</a></td>
<td>Color a mesh by height.</td>
</tr>
<tr>
<td><a href="CxxMeshes/ExtractEdges">ExtractEdges</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractEdges.html">vtkExtractEdges</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxMeshes/FillHoles">FillHoles</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFillHolesFilter.html">vtkFillHolesFilter</a></td>
<td>Close holes in a mesh.</td>
</tr>
<tr>
<td><a href="CxxPolyData/GreedyTerrainDecimation">GreedyTerrainDecimation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGreedyTerrainDecimation.html">vtkGreedyTerrainDecimation</a></td>
<td>Create a mesh from an ImageData</td>
</tr>
<tr>
<td><a href="CxxPolyData/HighlightBadCells">HighlightBadCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMeshQuality.html">vtkMeshQuality</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataConnectivityFilter_LargestRegion">LargestRegion</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html">vtkPolyDataConnectivityFilter</a></td>
<td>Extract the largest connected region in a polydata.</td>
</tr>
<tr>
<td><a href="CxxMeshes/MatrixMathFilter">MatrixMathFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMatrixMathFilter.html">vtkMatrixMathFilter</a></td>
<td>Compute various quantities on cell and points in a mesh.</td>
</tr>
<tr>
<td><a href="CxxPolyData/MeshQuality">MeshQuality</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMeshQuality.html">vtkMeshQuality</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxMeshes/OBBDicer">OBBDicer</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOBBDicer.html">vtkOBBDicer</a></td>
<td>Breakup a mesh into pieces.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolygonalSurfaceContourLineInterpolator">PolygonalSurfaceContourLineInterpolator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolygonalSurfaceContourLineInterpolator.html">vtkPolygonalSurfaceContourLineInterpolator</a></td>
<td>Interactively find the shortest path between two points on a mesh.</td>
</tr>
<tr>
<td><a href="CxxMeshes/QuadricClustering">QuadricClustering</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuadricClustering.html">vtkQuadricClustering</a></td>
<td>Reduce the number of triangles in a mesh.</td>
</tr>
<tr>
<td><a href="CxxMeshes/QuadricDecimation">QuadricDecimation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuadricDecimation.html">vtkQuadricDecimation</a></td>
<td>Reduce the number of triangles in a mesh.</td>
</tr>
<tr>
<td><a href="CxxPolyData/SelectPolyData">SelectPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSelectPolyData.html">vtkSelectPolyData</a></td>
<td>Select a region of a mesh.</td>
</tr>
<tr>
<td><a href="CxxMeshes/SimpleElevationFilter">SimpleElevationFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSimpleElevationFilter.html">vtkSimpleElevationFilter</a></td>
<td>Color a mesh by dotting a vector from the origin to each point with a specified vector.</td>
</tr>
<tr>
<td><a href="CxxPolyData/SmoothPolyDataFilter">SmoothPolyDataFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSmoothPolyDataFilter.html">vtkSmoothPolyDataFilter</a></td>
<td>Laplacian smoothing.</td>
</tr>
<tr>
<td><a href="CxxPolyData/PolyDataConnectivityFilter_SpecifiedRegion">SpecifiedRegion</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html">vtkPolyDataConnectivityFilter</a></td>
<td>Extract a specific (specified) connected region in a polydata.</td>
</tr>
<tr>
<td><a href="CxxMeshes/SplitPolyData">SplitPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOBBDicer.html">vtkOBBDicer</a></td>
<td>Breakup a mesh into pieces and save the pieces into files</td>
</tr>
<tr>
<td><a href="CxxMeshes/Subdivision">Subdivision</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html">vtkButterflySubdivisionFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLoopSubdivisionFilter.html">vtkLoopSubdivisionFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLinearSubdivisionFilter.html">vtkLinearSubdivisionFilter</a></td>
<td>Increase the number of triangles in a mesh.</td>
</tr>
<tr>
<td><a href="CxxMeshes/Triangulate">Triangluate</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangleFilter.html">vtkTriangleFilter</a></td>
<td>Convert all polygons in a mesh to triangles.</td>
</tr>
<tr>
<td><a href="CxxPolyData/WeightedTransformFilter">WeightedTransformFilter </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWeightedTransformFilter.html">vtkWeightedTransformFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxMeshes/WindowedSincPolyDataFilter">WindowedSincPolyDataFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWindowedSincPolyDataFilter.html">vtkWindowedSincPolyDataFilter</a></td>
<td>Smooth a mesh (windowed sinc filter).</td>
</tr>
</tbody>
</table>
<h3 id="clipping">Clipping</h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxVisualization/BoxClipStructuredPoints">BoxClipStructuredPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoxClipDataSet.html">vtkBoxClipDataSet</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html">vtkStructuredPoints</a></td>
<td>Clip <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html">vtkStructuredPoints</a> with a box. The results are unstructured grids with tetrahedra.</td>
</tr>
<tr>
<td><a href="CxxVisualization/BoxClipUnstructuredGrid">BoxClipUnstructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoxClipDataSet.html">vtkBoxClipDataSet</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a></td>
<td>Clip a <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a> with a box. The results are unstructured grids with tetrahedra.</td>
</tr>
<tr>
<td><a href="CxxMeshes/CapClip">CapClip</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html">vtkClipPolyData</a></td>
<td>Cap a clipped polydata with a polygon.</td>
</tr>
<tr>
<td><a href="CxxMeshes/ClipClosedSurface">ClipClosedSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkClipClosedSurface.html">vtkClipClosedSurface</a></td>
<td>Clip a surface with multiple planes.</td>
</tr>
<tr>
<td><a href="CxxMeshes/ClipDataSetWithPolyData">ClipDataSetWithPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html">vtkClipDataSet</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html">vtkImplicitPolyDataDistance</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a></td>
<td>Clip a <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a> with arbitrary polydata. In this example, use a <a href="http://www.vtk.org/doc/nightly/html/classvtkConeSource.html">vtkConeSource</a> to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the next example.</td>
</tr>
<tr>
<td><a href="CxxFiltering/GenericClip">GenericClip</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGenericClip.html">vtkGenericClip</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkBridgeDataSet.html">vtkBridgeDataSet</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGenericDataSet.html">vtkGenericDataSet</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxPolyData/ImplicitDataSetClipping">ImplicitDataSetClipping</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html">vtkImplicitDataSet</a></td>
<td>Clip using an implicit data set.</td>
</tr>
<tr>
<td><a href="CxxMeshes/SolidClip">SolidClip</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html">vtkClipPolyData</a></td>
<td>Create a "solid" clip.</td>
</tr>
<tr>
<td><a href="CxxMeshes/TableBasedClipDataSetWithPolyData">TableBasedClipDataSetWithPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTableBasedClipDataSet.html">vtkTableBasedClipDataSet</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html">vtkImplicitPolyDataDistance</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a></td>
<td>Clip a <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a> with arbitrary polydata. In this example, use a <a href="http://www.vtk.org/doc/nightly/html/classvtkConeSource.html">vtkConeSource</a> to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the previous example.</td>
</tr>
</tbody>
</table>
<h2 id="working-with-structured-3d-data">Working with Structured 3D Data</h2>
<p>This section includes <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html">vtkStructuredGrid</a>, and <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a>.</p>
<p>"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. <a href="http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes">Here is an overview of these data structures</a>. Image data can represent at typical 2D image, but also, a 3D volume.</p>
<ul>
<li>[[CxxVisualization/StructuredDataTypes|Demonstration of structured data types]]</li>
<li>[[CxxStructuredData/GetLinearPointId|Get the linear point id of a point in a grid]]</li>
</ul>
<h3 id="vtkimagedata"><a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a></h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxImageData/GetCellCenter">GetCellCenter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a></td>
<td>Get the coordinates of the center of a cell.</td>
</tr>
<tr>
<td><a href="CxxImageData/CellIdFromGridCoordinates">CellIdFromGridCoordinates</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredData.html">vtkStructuredData</a></td>
<td>Get the id of a cell from its grid coordinates.</td>
</tr>
<tr>
<td><a href="CxxImageData/IterateImageData">IterateImageData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a></td>
<td>Iterating over a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a>.</td>
</tr>
<tr>
<td><a href="CxxImageData/ImageNormalize">ImageNormalize</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageNormalize.html">vtkImageNormalize</a></td>
<td>Normalize an image.</td>
</tr>
<tr>
<td><a href="eCxxImageData/ExtractVOI">ExtractVOI</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractVOI.html">vtkExtractVOI</a></td>
<td>Extract a volume of interest (subvolume).</td>
</tr>
<tr>
<td><a href="CxxImageData/ImageWeightedSum">ImageWeightedSum</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html">vtkImageWeightedSum</a></td>
<td>Add two or more images.</td>
</tr>
<tr>
<td><a href="CxxImageData/ImageReslice">ImageReslice</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageReslice.html">vtkImageReslice</a></td>
<td>Resize a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a>.</td>
</tr>
<tr>
<td><a href="CxxImageData/ImageTranslateExtent">ImageTranslateExtent</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageTranslateExtent.html">vtkImageTranslateExtent</a></td>
<td>Change the extent of a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a>.</td>
</tr>
<tr>
<td><a href="CxxImageData/IntersectLine">IntersectLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a></td>
<td>Intersect a line with all cells of a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a>.</td>
</tr>
<tr>
<td><a href="CxxImageData/ImageIterator">ImageIterator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageIterator.html">vtkImageIterator</a></td>
<td></td>
</tr>
</tbody>
</table>
<h3 id="conversions">Conversions</h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxImageData/ImageDataGeometryFilter">ImageDataGeometryFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageDataGeometryFilter.html">vtkImageDataGeometryFilter</a></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a> to a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
</tr>
<tr>
<td><a href="CxxImageData/ImageDataToPointSet">ImageDataToPointSet</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageDataToPointSet.html">vtkImageDataToPointSet</a></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a> to a <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html">vtkStructuredGrid</a>.</td>
</tr>
</tbody>
</table>
<h3 id="vtkstructuredgrid"><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html">vtkStructuredGrid</a></h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxStructuredGrid/BlankPoint">BlankPoint</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html">vtkStructuredGrid</a></td>
<td>Blank a point of a <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html">vtkStructuredGrid</a>.</td>
</tr>
<tr>
<td><a href="CxxStructuredGrid/OutlineStructuredGrid">OutlineStructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGridOutlineFilter.html">vtkStructuredGridOutlineFilter</a></td>
<td>Visualize the outline of a structured grid.</td>
</tr>
<tr>
<td><a href="CxxStructuredGrid/StructuredGrid">StructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html">vtkStructuredGrid</a></td>
<td>Structured Grid.</td>
</tr>
<tr>
<td><a href="CxxStructuredGrid/VisualizeStructuredGridCells">VisualizeStructuredGridCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkShrinkFilter.html">vtkShrinkFilter</a></td>
<td>Visualize the cells of a structured grid.</td>
</tr>
<tr>
<td><a href="CxxStructuredGrid/VisualizeStructuredGrid">VisualizeStructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGridGeometryFilter.html">vtkStructuredGridGeometryFilter</a></td>
<td>Visualize the points of a structured grid.</td>
</tr>
</tbody>
</table>
<h3 id="vtkstructuredpoints"><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html">vtkStructuredPoints</a></h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxStructuredPoints/StructuredPointsToUnstructuredGrid">StructuredPointsToUnstructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html">vtkStructuredPoints</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html">vtkStructuredPoints</a> to a <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a>.</td>
</tr>
</tbody>
</table>
<h3 id="vtkrectilineargrid"><a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a></h3>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxRectilinearGrid/RectilinearGridToTetrahedra">RectilinearGridToTetrahedra</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGridToTetrahedra.html">vtkRectilinearGridToTetrahedra</a></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a> to a <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a> mesh</td>
</tr>
<tr>
<td><a href="CxxRectilinearGrid/RectilinearGrid">RectilinearGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a></td>
<td>Rectilinear grid</td>
</tr>
<tr>
<td><a href="CxxRectilinearGrid/VisualizeRectilinearGridCells">VisualizeRectilinearGridCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkShrinkFilter.html">vtkShrinkFilter</a></td>
<td>Visualize the cells of a rectilinear grid</td>
</tr>
</tbody>
</table>
<h2 id="registration">Registration</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxFilters/IterativeClosestPointsTransform">IterativeClosestPointsTransform</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkIterativeClosestPointTransform.html">vtkIterativeClosestPointTransform</a></td>
<td>Iterative Closest Points (ICP) Transform.</td>
</tr>
<tr>
<td><a href="CxxFilters/LandmarkTransform">LandmarkTransform</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLandmarkTransform.html">vtkLandmarkTransform</a></td>
<td>Landmark Transform.</td>
</tr>
</tbody>
</table>
<h2 id="medical">Medical</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxMedical/MedicalDemo1">MedicalDemo1</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html">vtkMarchingCubes</a></td>
<td>Create a skin surface from volume data</td>
</tr>
<tr>
<td><a href="CxxMedical/MedicalDemo2">MedicalDemo2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html">vtkMarchingCubes</a></td>
<td>Create a skin and bone surface from volume data</td>
</tr>
<tr>
<td><a href="CxxMedical/MedicalDemo3">MedicalDemo3</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html">vtkMarchingCubes</a></td>
<td>Create skin, bone and slices from volume data</td>
</tr>
<tr>
<td><a href="CxxMedical/MedicalDemo4">MedicalDemo4</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFixedPointVolumeRayCastMapper.html">vtkFixedPointVolumeRayCastMapper</a></td>
<td>Create a volume rendering</td>
</tr>
<tr>
<td><a href="CxxMedical/TissueLens">TissueLens</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html">vtkMarchingCubes</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html">vtkClipDataSet</a>  <a href="http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html">vtkProbeFilter</a></td>
<td>Cut a volume with a sphere</td>
</tr>
</tbody>
</table>
<h2 id="surface-reconstruction">Surface reconstruction</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxModelling/Delaunay3D">Delaunay3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDelaunay3D.html">vtkDelaunay3D</a></td>
<td>Create a solid mesh from Unorganized Points (Delaunay3D).</td>
</tr>
<tr>
<td><a href="CxxPoints/ExtractSurfaceDemo">ExtractSurfaceDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html">vtkExtractSurface</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html">vtkPCANormalEstimation</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html">vtkSignedDistance</a></td>
<td>Create a surface from Unorganized Points using Point filters (DEMO).</td>
</tr>
<tr>
<td><a href="CxxPoints/ExtractSurface">ExtractSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html">vtkExtractSurface</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html">vtkPCANormalEstimation</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html">vtkSignedDistance</a></td>
<td>Create a surface from Unorganized Points using Point filters.</td>
</tr>
<tr>
<td><a href="CxxFiltering/GaussianSplat">GaussianSplat</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGaussianSplatter.html">vtkGaussianSplatter</a></td>
<td>Create a surface from Unorganized Points (Gaussian Splat).</td>
</tr>
<tr>
<td><a href="CxxMedical/GenerateCubesFromLabels">GenerateCubesFromLabels</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMetaImageReader.html">vtkMetaImageReader</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkMaskFields.html">vtkMaskFields</a></td>
<td>Create cubes from labeled volume data.</td>
</tr>
<tr>
<td><a href="CxxMedical/GenerateModelsFromLabels">GenerateModelsFromLabels</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html">vtkDiscreteMarchingCubes</a></td>
<td>Create models from labeled volume data (Discrete MarchingCubes).</td>
</tr>
<tr>
<td><a href="CxxFiltering/SurfaceFromUnorganizedPointsWithPostProc">SurfaceFromUnorganizedPointsWithPostProc</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSurfaceReconstructionFilter.html">vtkSurfaceReconstructionFilter</a></td>
<td>Create a surface from Unorganized Points (with post processing).</td>
</tr>
<tr>
<td><a href="CxxFiltering/SurfaceFromUnorganizedPoints">SurfaceFromUnorganizedPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSurfaceReconstructionFilter.html">vtkSurfaceReconstructionFilter</a></td>
<td>Create a surface from Unorganized Points.</td>
</tr>
<tr>
<td><a href="CxxFiltering/TriangulateTerrainMap">TriangulateTerrainMap</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html">vtkDelaunay2D</a></td>
<td>Generate heights (z values) on a 10x10 grid (a terrain map) and then triangulate the points to form a surface.</td>
</tr>
</tbody>
</table>
<h1 id="utilities">Utilities</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxUtilities/BoundingBoxIntersection">BoundingBoxIntersection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoundingBox.html">vtkBoundingBox</a></td>
<td>Box intersection and Inside tests.</td>
</tr>
<tr>
<td><a href="CxxUtilities/BoundingBox">BoundingBox</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoundingBox.html">vtkBoundingBox</a></td>
<td>Bounding Box construction.</td>
</tr>
<tr>
<td><a href="CxxUtilities/BrownianPoints">BrownianPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBrownianPoints.html">vtkBrownianPoints</a></td>
<td>Produce a random vector at each point in a dataset.</td>
</tr>
<tr>
<td><a href="CxxUtilities/CardinalSpline">CardinalSpline</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html">vtkCardinalSpline</a></td>
<td>Cardinal spline Interpolation.</td>
</tr>
<tr>
<td><a href="CxxPolyData/Casting">Casting</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkObject.html">vtkObject</a>::SafeDownCast</td>
<td>Casting VTK objects.</td>
</tr>
<tr>
<td><a href="CxxUtilities/Check[VTKVersion](http://www.vtk.org/doc/nightly/html/classVTKVersion.html)">CheckVTKVersion</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVersion.html">vtkVersion</a></td>
<td>Check VTK Version.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ColorLookupTable">ColorLookupTable</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a></td>
<td>Color Lookup Table.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ColorTransferFunction">ColorTransferFunction</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html">vtkColorTransferFunction</a></td>
<td>Color Transfer Function.</td>
</tr>
<tr>
<td><a href="CxxUtilities/CommandSubclass">CommandSubclass</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCommand.html">vtkCommand</a></td>
<td>Instead of using a callback function, it is more powerful to subclass <a href="http://www.vtk.org/doc/nightly/html/classvtkCommand.html">vtkCommand</a>.</td>
</tr>
<tr>
<td><a href="CxxFiltering/ConstrainedDelaunay2D">ConstrainedDelaunay2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html">vtkDelaunay2D</a></td>
<td>Perform a 2D Delaunay triangulation on a point set respecting a specified boundary.</td>
</tr>
<tr>
<td><a href="CxxUtilities/Coordinate">Coordinate</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCoordinate.html">vtkCoordinate</a></td>
<td>Coordinate system conversions.</td>
</tr>
<tr>
<td><a href="CxxUtilities/DeepCopy">DeepCopy</a></td>
<td></td>
<td>Deep copy a VTK object.</td>
</tr>
<tr>
<td><a href="CxxFiltering/Delaunay2D">Delaunay2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html">vtkDelaunay2D</a></td>
<td>Perform a 2D Delaunay triangulation on a point set.</td>
</tr>
<tr>
<td><a href="CxxUtilities/DetermineActorType">DetermineActorType</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkActorCollection.html">vtkActorCollection</a></td>
<td>Determine the type of an actor.</td>
</tr>
<tr>
<td><a href="CxxUtilities/DetermineVariableType">DetermineVariableType</a></td>
<td>GetClassName()</td>
<td>Determine the type of a VTK variable.</td>
</tr>
<tr>
<td><a href="CxxUtilities/DiscretizableColorTransferFunction">DiscretizableColorTransferFunction</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDiscretizableColorTransferFunction.html">vtkDiscretizableColorTransferFunction</a></td>
<td>Discretizable Color Transfer Function.</td>
</tr>
<tr>
<td><a href="CxxUtilities/FileOutputWindow">FileOutputWindow</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFileOutputWindow.html">vtkFileOutputWindow</a></td>
<td>Write errors to a log file instead of the screen.</td>
</tr>
<tr>
<td><a href="CxxUtilities/FilenameFunctions">FilenameFunctions</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDirectory.html">vtkDirectory</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtksys.html">vtksys</a>/SystemTools</td>
<td>Do things like get the file extension, strip the file extension, etc.</td>
</tr>
<tr>
<td><a href="CxxUtilities/FilterProgress">FilterProgress</a></td>
<td></td>
<td>Monitor a filters progress.</td>
</tr>
<tr>
<td><a href="CxxUtilities/FrameRate">FrameRate</a></td>
<td></td>
<td>Get the frame rate of the rendering.</td>
</tr>
<tr>
<td><a href="CxxUtilities/FullScreen">FullScreen</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a></td>
<td>Maximize/full screen a <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a>.</td>
</tr>
<tr>
<td><a href="CxxUtilities/FunctionParser">FunctionParser</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFunctionParser.html">vtkFunctionParser</a></td>
<td>String function parser.</td>
</tr>
<tr>
<td><a href="CxxUtilities/GetDataRoot">GetDataRoot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTesting.html">vtkTesting</a></td>
<td>Find the path of VTK_DATA_ROOT.</td>
</tr>
<tr>
<td><a href="CxxUtilities/LUTUtilities">LUTUtilities</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html">vtkColorSeries</a></td>
<td>A utility class for <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a> allowing you to output the table contents or to compare tables.</td>
</tr>
<tr>
<td><a href="CxxVisualization/MultipleRenderWindows">MultipleRenderWindows</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a></td>
<td>Multiple Render Windows</td>
</tr>
<tr>
<td><a href="CxxVisualization/MultipleViewports">MultipleViewports</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>::SetViewPort</td>
<td>Multiple Viewports.</td>
</tr>
<tr>
<td><a href="CxxUtilities/OffScreenRendering">OffScreenRendering</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImagingFactory.html">vtkImagingFactory</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGraphicsFactory.html">vtkGraphicsFactory</a></td>
<td>Off Screen Rendering.</td>
</tr>
<tr>
<td><a href="CxxUtilities/PCADemo">PCADemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPCAStatistics.html">vtkPCAStatistics</a></td>
<td>Project 2D points onto the best 1D subspace (PCA Demo).</td>
</tr>
<tr>
<td><a href="CxxUtilities/PCAStatistics">PCAStatistics</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPCAStatistics.html">vtkPCAStatistics</a></td>
<td>Compute Principal Component Analysis (PCA) values.</td>
</tr>
<tr>
<td><a href="CxxInfoVis/PassThrough">PassThrought</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPassThrough.html">vtkPassThrough</a></td>
<td>Pass input along to outpu.</td>
</tr>
<tr>
<td><a href="CxxUtilities/PiecewiseFunction">PiecewiseFunction</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPiecewiseFunction.html">vtkPiecewiseFunction</a></td>
<td>Interpolation using a piecewise function.</td>
</tr>
<tr>
<td><a href="CxxUtilities/PointInPolygon">PointInPolygon</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolygon.html">vtkPolygon</a></td>
<td>Point inside polygon test.</td>
</tr>
<tr>
<td><a href="CxxUtilities/Screenshot">Screenshot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html">vtkWindowToImageFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxUtilities/ShallowCopy">ShallowCopy</a></td>
<td></td>
<td>Shallow copy a VTK object.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ShareCamera">ShareCamera</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkCamera.html">vtkCamera</a></td>
<td>Share a camera between multiple renderers.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ShepardMethod">ShepardMethod</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkShepardMethod.html">vtkShepardMethod</a></td>
<td>Shepard method interpolation.</td>
</tr>
<tr>
<td><a href="CxxVisualization/SideBySideViewports">SideBySideViewports</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>::SetViewPort</td>
<td>Side by side viewports.</td>
</tr>
<tr>
<td><a href="CxxUtilities/TimeStamp">TimeStamp</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTimeStamp.html">vtkTimeStamp</a></td>
<td>Time stamp.</td>
</tr>
<tr>
<td><a href="CxxUtilities/TimerLog">TimerLog</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTimerLog.html">vtkTimerLog</a></td>
<td>Timer log.</td>
</tr>
<tr>
<td><a href="CxxUtilities/Timer">Timer</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a>::CreateRepeatingTimer</td>
<td></td>
</tr>
<tr>
<td><a href="CxxUtilities/Variant">Variant</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVariant.html">vtkVariant</a></td>
<td>Convert between data types.</td>
</tr>
<tr>
<td><a href="CxxUtilities/Vector">Vector</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVector.html">vtkVector</a></td>
<td>Mathematical vector class.</td>
</tr>
<tr>
<td><a href="CxxUtilities/VersionMacros">VersionMacros</a></td>
<td>Macro/#define's</td>
<td>Check VTK Version.</td>
</tr>
<tr>
<td><a href="CxxUtilities/VisualDebugging">VisualDebugging</a></td>
<td></td>
<td>Update the screen from inside an algorithm.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ZBuffer">ZBuffer</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a></td>
<td>zbuffer.</td>
</tr>
</tbody>
</table>
<h2 id="arrays">Arrays</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxUtilities/2DArray">2DArray</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html">vtkDenseArray</a></td>
<td>2D Array.</td>
</tr>
<tr>
<td><a href="CxxUtilities/3DArray">3DArray</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html">vtkDenseArray</a></td>
<td>3D Array.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ArrayCalculator">ArrayCalculator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkArrayCalculator.html">vtkArrayCalculator</a></td>
<td>Perform in-place operations on arrays.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ArrayLookup">ArrayLookup</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDataArray.html">vtkDataArray</a></td>
<td>Find the location of a value in a <a href="http://www.vtk.org/doc/nightly/html/classvtkDataArray.html">vtkDataArray</a>.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ArrayRange">ArrayRange</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html">vtkFloatArray</a>::GetRange</td>
<td>Get the bounds (min,max) of a <a href="http://www.vtk.org/doc/nightly/html/classvtk.html">vtk</a> array.</td>
</tr>
<tr>
<td><a href="CxxInfoVis/ArrayToTable">ArrayToTable</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkArrayToTable.html">vtkArrayToTable</a></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html">vtkDenseArray</a> to a <a href="http://www.vtk.org/doc/nightly/html/classvtkTable.html">vtkTable</a>.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ArrayWriter">ArrayWriter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkArrayWriter.html">vtkArrayWriter</a></td>
<td>Write a DenseArray or SparseArray to a file.</td>
</tr>
<tr>
<td><a href="CxxTextAnalysis/ConcatenateArray">ConcatenateArray</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkConcatenateArray.html">vtkConcatenateArray</a></td>
<td>Concatenate two arrays.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ConstructTable">ConstructTable</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTable.html">vtkTable</a></td>
<td>A table is a 2D array of any type of elements. They do not all have to be the same type. This is achieved using <a href="http://www.vtk.org/doc/nightly/html/classvtkVariant.html">vtkVariant</a>.</td>
</tr>
<tr>
<td><a href="CxxUtilities/CustomDenseArray">CustomDenseArray</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html">vtkDenseArray</a></td>
<td>Custom type Dense (2D) Array.</td>
</tr>
<tr>
<td><a href="CxxUtilities/DenseArrayRange">DenseArrayRange</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html">vtkDenseArray</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkArrayRange.html">vtkArrayRange</a></td>
<td>Get the bounds of a <a href="http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html">vtkDenseArray</a>.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ExtractArrayComponent">ExtractArrayComponent</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkArrayCalculator.html">vtkArrayCalculator</a></td>
<td>Extract a component of an array.</td>
</tr>
<tr>
<td><a href="CxxUtilities/KnownLengthArrayOfVectors">KnownLengthArrayOfVectors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html">vtkFloatArray</a></td>
<td>Array of Vectors (Known Length).</td>
</tr>
<tr>
<td><a href="CxxUtilities/KnownLengthArray">KnownLengthArray</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html">vtkFloatArray</a></td>
<td>Known Length Array.</td>
</tr>
<tr>
<td><a href="CxxUtilities/SortDataArray">SortDataArray</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSortDataArray.html">vtkSortDataArray</a></td>
<td>Reorder array values based on an ordering (key) array.</td>
</tr>
<tr>
<td><a href="CxxUtilities/SparseArray">SparseArray</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSparseArray.html">vtkSparseArray</a></td>
<td>Sparse Array.</td>
</tr>
<tr>
<td><a href="CxxUtilities/UnknownLengthArrayOfVectors">UnknownLengthArrayOfVectors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html">vtkFloatArray</a></td>
<td>Array of Vectors (Unknown Length).</td>
</tr>
<tr>
<td><a href="CxxUtilities/UnknownLengthArray">UnknownLengthArray</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html">vtkFloatArray</a></td>
<td>Unknown Length Array.</td>
</tr>
</tbody>
</table>
<h2 id="events">Events</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxUtilities/CameraModifiedEvent">CameraModifiedEvent</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCameraWindow.html">vtkCameraWindow</a></td>
<td>Catch the camera modified event.</td>
</tr>
<tr>
<td><a href="CxxUtilities/ObserveError">ObserveError</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCommand.html">vtkCommand</a></td>
<td>Catch errors and warnings.</td>
</tr>
<tr>
<td><a href="CxxUtilities/WindowModifiedEvent">WindowModifiedEvent</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a></td>
<td>Catch the window modified event.</td>
</tr>
</tbody>
</table>
<h1 id="cmake-techniques">CMake Techniques</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxCMakeTechniques/CheckForModule">Check if a specific module is present</a></td>
<td></td>
<td></td>
</tr>
<tr>
<td><a href="CxxUtilities/CMake[VTKVersionCheck](http://www.vtk.org/doc/nightly/html/classVTKVersionCheck.html)">Check VTK Version in CMake</a></td>
<td></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="math-operations">Math Operations</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Math/EigenSymmetric">EigenSymmetric</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a>::Jacobi</td>
<td>Compute eigenvalues and eigenvectors of a symmetric matrix.</td>
</tr>
<tr>
<td><a href="Cxx/Math/HomogeneousLeastSquares">HomogeneousLeastSquares</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a>::SolveHomogeneousLeastSquares</td>
<td>Homogeneous Least Squares.</td>
</tr>
<tr>
<td><a href="Cxx/Math/1DTupleInterpolation">1DTupleInterpolation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTupleInterpolator.html">vtkTupleInterpolator</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html">vtkCardinalSpline</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html">vtkKochanekSpline</a></td>
<td>A simple example demonstrating how functions defined by sparsely distributed supporting points can be interpolated at arbitrary positions.</td>
</tr>
<tr>
<td><a href="Cxx/Math/LUFactorization">LUFactorization</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a></td>
<td>LU Factorization.</td>
</tr>
<tr>
<td><a href="Cxx/Math/LeastSquares">LeastSquares</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a>::SolveLeastSquares</td>
<td>Least Squares.</td>
</tr>
<tr>
<td><a href="Cxx/Math/MatrixInverse">MatrixInverse</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMatrix3x3.html">vtkMatrix3x3</a></td>
<td>Matrix inverse.</td>
</tr>
<tr>
<td><a href="Cxx/Math/MatrixTranspose">MatrixTranspose</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMatrix3x3.html">vtkMatrix3x3</a></td>
<td>Matrix transpose.</td>
</tr>
<tr>
<td><a href="Cxx/Math/NormalizeVector">NormalizeVector</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a></td>
<td>Normalize a vector.</td>
</tr>
<tr>
<td><a href="Cxx/Math/PerpendicularVector">PerpendicularVector</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMath.html">vtkMath</a>::Perpendiculars</td>
<td>Get a vector perpendicular to another vector.</td>
</tr>
<tr>
<td><a href="Cxx/TextAnalysis/PowerWeighting">PowerWeighting</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPowerWeighting.html">vtkPowerWeighting</a></td>
<td>Raise all elements in an array to a power.</td>
</tr>
<tr>
<td><a href="Cxx/Math/VectorDot">VectorDot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVectorDot.html">vtkVectorDot</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Math/VectorNorm">VectorNorm</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVectorNorm.html">vtkVectorNorm</a></td>
<td>Get the lengths of an array of vectors.</td>
</tr>
</tbody>
</table>
<h1 id="graphs">Graphs</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Graphs/AdjacencyMatrixToEdgeTable">AdjacencyMatrixToEdgeTable</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAdjacencyMatrixToEdgeTable.html">vtkAdjacencyMatrixToEdgeTable</a></td>
<td>Convert an adjacency matrix to an edge table.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/AdjacentVertexIterator">AdjacentVertexIterator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAdjacentVertexIterator.html">vtkAdjacentVertexIterator</a></td>
<td>Get all vertices connected to a specified vertex.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/BFSTree">BFSTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoostBreadthFirstSearchTree.html">vtkBoostBreadthFirstSearchTree</a></td>
<td>Breadth first search tree. Can also be used to convert a graph to a tree.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/BreadthFirstDistance">BreadthFirstDistance</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoostBreadthFirstSearch.html">vtkBoostBreadthFirstSearch</a></td>
<td>Distance from origin.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/BreadthFirstSearchIterator">BreadthFirstSearchIterator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTreeBFSIterator.html">vtkTreeBFSIterator</a></td>
<td>Breadth First Search iterator.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/ColorEdges">ColorEdges</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a></td>
<td>Color edges.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/ColorVertexLabels">ColorVertexLabels</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html">vtkRenderedGraphRepresentation</a></td>
<td>Set the color of vertex labels.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/ColorVerticesLookupTable">ColorVerticesLookupTable</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a></td>
<td>Color vertices.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/ConnectedComponents">ConnectedComponents</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoostConnectedComponents.html">vtkBoostConnectedComponents</a></td>
<td>Find connected components of a graph.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/ConstructGraph">ConstructGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMutableUndirectedGraph.html">vtkMutableUndirectedGraph</a></td>
<td>Construct a graph.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/ConstructTree">ConstructTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTree.html">vtkTree</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a></td>
<td>Construct a tree.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/DFSAnimation">DFSAnimation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTreeDFSIterator.html">vtkTreeDFSIterator</a></td>
<td>Depth First Search Animation.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/DepthFirstSearchIterator">DepthFirstSearchIterator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTreeDFSIterator.html">vtkTreeDFSIterator</a></td>
<td>Depth First Search iterator.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/EdgeWeights">EdgeWeights</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraph.html">vtkGraph</a>::GetEdgeData::AddArray</td>
<td>Edge weights.</td>
</tr>
<tr>
<td><a href="Cxx/InfoVis/GraphPoints">GraphPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraph.html">vtkGraph</a>::SetPoints, <a href="http://www.vtk.org/doc/nightly/html/classvtkPassThroughLayoutStrategy.html">vtkPassThroughLayoutStrategy</a></td>
<td>Manually set coordinates of vertices in a graph.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/GraphToPolyData">GraphToPolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphToPolyData.html">vtkGraphToPolyData</a></td>
<td>Convert a graph to a PolyData.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/InEdgeIterator">InEdgeIterator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInEdgeIterator.html">vtkInEdgeIterator</a></td>
<td>Iterate over edges incoming to a vertex.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/IterateEdges">IterateEdges</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkEdgeListIterator.html">vtkEdgeListIterator</a></td>
<td>Iterate over edges of a graph.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/LabelVerticesAndEdges">LabelVerticesAndEdges</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a>::SetEdgeLabelArrayName, <a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a>::SetVertexLabelArrayName</td>
<td>Label vertices and edges.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/MinimumSpanningTree">MinimumSpanningTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoostPrimMinimumSpanningTree.html">vtkBoostPrimMinimumSpanningTree</a></td>
<td>Minimum spanning tree of a graph.</td>
</tr>
<tr>
<td><a href="Cxx/InfoVis/MutableGraphHelper">MutableGraphHelper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMutableGraphHelper.html">vtkMutableGraphHelper</a></td>
<td>Create either a <a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a> or <a href="http://www.vtk.org/doc/nightly/html/classvtkMutableUndirectedGraph.html">vtkMutableUndirectedGraph</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/NOVCAGraph">NOVCAGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html">vtkXMLUnstructuredGridWriter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html">vtkPolyLine</a></td>
<td>Create a graph &amp; visualize it in ParaView/VisIt.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/OutEdgeIterator">OutEdgeIterator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOutEdgeIterator.html">vtkOutEdgeIterator</a></td>
<td>Iterate over edges outgoing from a vertex.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/RandomGraphSource">RandomGraphSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRandomGraphSource.html">vtkRandomGraphSource</a></td>
<td>Create a random graph.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/RemoveIsolatedVertices">RemoveIsolatedVertices</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRemoveIsolatedVertices.html">vtkRemoveIsolatedVertices</a></td>
<td>Remove vertices of degree 0 from a <a href="http://www.vtk.org/doc/nightly/html/classvtkGraph.html">vtkGraph</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/ScaleVertices">ScaleVertices</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html">vtkRenderedGraphRepresentation</a></td>
<td>Size/scale vertices based on a data array.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/SelectedVerticesAndEdges">SelectedVerticesAndEdges </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html">vtkAnnotationLink</a></td>
<td>Get a list of selected vertices and edges.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/SelectedVerticesAndEdgesObserver">SelectedVerticesAndEdgesObserver</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html">vtkAnnotationLink</a></td>
<td>Get a list of selected vertices and edges using an observer of AnnotationChangedEvent.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/ShortestPath">ShortestPath</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDijkstraGraphGeodesicPath.html">vtkDijkstraGraphGeodesicPath</a></td>
<td>Find the shortest path on a graph.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/SideBySideGraphs">SideBySideGraphs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a></td>
<td>Display two graphs side by side.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/VertexSize">VertexSize</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html">vtkRenderedGraphRepresentation</a></td>
<td>Set the size of vertices.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/VisualizeDirectedGraph">VisualizeDirectedGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyphSource2D.html">vtkGlyphSource2D</a></td>
<td>Visualize a directed graph.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/VisualizeGraph">VisualizeGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutStrategy.html">vtkGraphLayoutStrategy</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSimple2DLayoutStrategy.html">vtkSimple2DLayoutStrategy</a></td>
<td>Visualize a graph.</td>
</tr>
</tbody>
</table>
<h2 id="graph-conversions">Graph Conversions</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Graphs/Conversions/DirectedGraphToMutableDirectedGraph">DirectedGraphToMutableDirectedGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html">vtkDirectedGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html">vtkDirectedGraph</a> to <a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/Conversions/MutableDirectedGraphToDirectedGraph">MutableDirectedGraphToDirectedGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html">vtkDirectedGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a> to <a href="http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html">vtkDirectedGraph</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Graphs/Conversions/TreeToMutableDirectedGraph">TreeToMutableDirectedGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkTree.html">vtkTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTree.html">vtkTree</a> to <a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a></td>
</tr>
</tbody>
</table>
<h1 id="data-structures">Data Structures</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/PolyData/AttachAttributes">AttachAttributes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInformation.html">vtkInformation</a></td>
<td>Attach attributes to a VTK array</td>
</tr>
<tr>
<td><a href="Cxx/PolyData/CellLocatorVisualization">CellLocatorVisualization</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html">vtkCellLocator</a></td>
<td>Visualization of the tree of a <a href="http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html">vtkCellLocator</a>.</td>
</tr>
<tr>
<td><a href="Cxx/PolyData/CellLocator">CellLocator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html">vtkCellLocator</a></td>
<td>Project a point onto a mesh. Closest point on a mesh.Efficient 3D cell query.</td>
</tr>
<tr>
<td><a href="Cxx/PolyData/CellTreeLocator">CellTreeLocator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellTreeLocator.html">vtkCellTreeLocator</a></td>
<td>Points inside an object using <a href="http://www.vtk.org/doc/nightly/html/classvtkCellTreeLocator.html">vtkCellTreeLocator</a>.</td>
</tr>
<tr>
<td><a href="Cxx/PolyData/PointLocatorVisualization">PointLocatorVisualization</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html">vtkPointLocator</a></td>
<td>Visualization of the tree of a <a href="http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html">vtkPointLocator</a>.</td>
</tr>
<tr>
<td><a href="Cxx/PolyData/PointLocator">PointLocator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html">vtkPointLocator</a></td>
<td>Efficient 3D point query.</td>
</tr>
<tr>
<td><a href="Cxx/PolyData/PointLocator_Radius">Radius</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html">vtkPointLocator</a></td>
<td>Find all points within a radius of a specified point.</td>
</tr>
</tbody>
</table>
<h2 id="timing-demonstrations">Timing Demonstrations</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/DataStructures/KDTreeTimingDemo">KDTreeTimingDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html">vtkKdTreePointLocator</a></td>
<td>Plot the runtime vs MaxLevel (doesn't seem correct)</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/ModifiedBSPTreeTimingDemo">ModifiedBSPTreeTimingDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html">vtkModifiedBSPTree</a></td>
<td>Plot the runtime vs MaxLevel</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/OBBTreeTimingDemo">OBBTreeTimingDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html">vtkOBBTree</a></td>
<td>Plot the runtime vs MaxLevel</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/OctreeTimingDemo">OctreeTimingDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html">vtkOctreePointLocator</a></td>
<td>Plot the runtime vs MaxPointsPerRegionOctree timing demo.</td>
</tr>
</tbody>
</table>
<h2 id="kd-tree">KD-Tree</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/DataStructures/BuildLocatorFromKClosestPoints">BuildLocatorFromKClosestPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTree.html">vtkKdTree</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/KdTreePointLocator/ClosestNPoints">ClosestNPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html">vtkKdTreePointLocator</a></td>
<td>Find the closest N points to a query point.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/DataStructureComparison">DataStructureComparison</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTree.html">vtkKdTree</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html">vtkOBBTree</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html">vtkOctreePointLocator</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html">vtkModifiedBSPTree</a></td>
<td>Illustrates, side by side, the differences between several spatial data structures</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/KDTreeAccessPoints">KDTreeAccessPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTree.html">vtkKdTree</a></td>
<td>Access the points of a KDTree.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/KDTreeFindPointsWithinRadius">KDTreeFindPointsWithinRadius</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html">vtkKdTreePointLocator</a></td>
<td>Find points within a specified radius of  a query point.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/KdTreePointLocatorClosestPoint">KdTreePointLocatorClosestPoint</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html">vtkKdTreePointLocator</a></td>
<td>Find the closest point to a query point.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/KdTree">KdTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTree.html">vtkKdTree</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/VisualizeKDTree">VisualizeKDTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html">vtkKdTreePointLocator</a></td>
<td>Visualize levels of the tree.</td>
</tr>
</tbody>
</table>
<h2 id="oriented-bounding-box-obb-tree">Oriented Bounding Box (OBB) Tree</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/DataStructures/OBBTree_IntersectWithLine">IntersectWithLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html">vtkOBBTree</a></td>
<td>Intersect a line with a <a href="http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html">vtkOBBTree</a>.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/OBBTreeExtractCells">OBBTreeExtractCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html">vtkOBBTree</a></td>
<td>Intersect a line with an OBB Tree and display all intersected cells.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/VisualizeOBBTree">VisualizeOBBTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html">vtkOBBTree</a></td>
<td>Visualize levels of the tree.</td>
</tr>
</tbody>
</table>
<h2 id="octree">Octree</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/DataStructures/Octree/BuildTree">BuildTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html">vtkOctreePointLocator</a></td>
<td>Create an octree.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/Octree/ClosestPoint">ClosestPoint</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html">vtkOctreePointLocator</a></td>
<td>Find the closest point to a query point.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/Octree/FindPointsWithinRadius">FindPointsWithinRadius</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html">vtkOctreePointLocator</a></td>
<td>Find the points within a sphere of specified radius to a query point.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/IncrementalOctreePointLocator">IncrementalOctreePointLocator</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkIncrementalOctreePointLocator.html">vtkIncrementalOctreePointLocator</a></td>
<td>Insert points into an octree without rebuilding it.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/Octree/KClosestPoints">KClosestPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html">vtkOctreePointLocator</a></td>
<td>Find the K closest points to a query point.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/OctreeVisualize">OctreeVisualize</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html">vtkOctreePointLocator</a></td>
<td>Visualize levels of the tree.</td>
</tr>
</tbody>
</table>
<h2 id="modified-bsp-tree">Modified BSP Tree</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/DataStructures/ModifiedBSPTreeIntersectWithLine">ModifiedBSPTreeIntersectWithLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html">vtkModifiedBSPTree</a></td>
<td>Intersect a line with a modified BSP Tree.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/ModifiedBSPTreeExtractCells">ModifiedBSPTreeExtractCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html">vtkModifiedBSPTree</a></td>
<td>Intersect a line with a modified BSP Tree and display all intersected cells.</td>
</tr>
<tr>
<td><a href="Cxx/DataStructures/ModifiedBSPTree/VisualizeModifiedBSPTree">VisualizeModifiedBSPTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html">vtkModifiedBSPTree</a></td>
<td>Visualize levels of the tree.</td>
</tr>
</tbody>
</table>
<h1 id="vtk-concepts">VTK Concepts</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/[VTKConcepts](http://www.vtk.org/doc/nightly/html/classVTKConcepts.html)/Scalars">Scalars</a></td>
<td></td>
<td>Attach a scalar value to each point (PointData) or cell (CellData) in a data set.</td>
</tr>
</tbody>
</table>
<h1 id="rendering">Rendering</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Rendering/AmbientSpheres">AmbientSpheres</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProperty.html">vtkProperty</a></td>
<td>Demonstrates the effect of ambient lighting on spheres.</td>
</tr>
<tr>
<td><a href="Cxx/Rendering/DiffuseSpheres">DiffuseSpheres</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProperty.html">vtkProperty</a></td>
<td>Demonstrates the effect of diffuse lighting on spheres.</td>
</tr>
<tr>
<td><a href="Cxx/Rendering/SpecularSpheres">SpecularSpheres</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProperty.html">vtkProperty</a></td>
<td>Demonstrates the effect of specular lighting on spheres.</td>
</tr>
<tr>
<td><a href="Cxx/Rendering/CylinderRenderingProperties">CylinderRenderingProperties</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProperty.html">vtkProperty</a></td>
<td>Change the properties of a cylinder.</td>
</tr>
</tbody>
</table>
<h1 id="lighting">Lighting</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Visualization/Shadows">Shadows</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkShadowMapPass.html">vtkShadowMapPass</a></td>
<td>Create shadows.</td>
</tr>
<tr>
<td><a href="Cxx/Lighting/Light">Light</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLight.html">vtkLight</a></td>
<td>Add a directional light to a scene.</td>
</tr>
<tr>
<td><a href="Cxx/Lighting/LightActor">LightActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLightActor.html">vtkLightActor</a></td>
<td>Display the location and direction of a light.</td>
</tr>
</tbody>
</table>
<h1 id="visualization">Visualization</h1>
<p>See <a href="http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes">this tutorial</a> for a brief explanation of the VTK terminology of mappers, actors, etc.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Visualization/BillboardTextActor3D"> BillboardTextActor3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBillboardTextActor3D.html">vtkBillboardTextActor3D</a></td>
<td>Label points with billboards.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CameraActor"> CameraActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCameraActor.html">vtkCameraActor</a></td>
<td>Visualize a camera (frustum) in a scene.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/DistanceToCamera"> DistanceToCamera</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDistanceToCamera.html">vtkDistanceToCamera</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/VisualizationAlgorithms/FindCellIntersections"> FindCellIntersections</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html">vtkCellLocator</a></td>
<td>Find the intersection of a line and the cells in an unstructured dataset</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/FlatShading"> FlatShading</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetInterpolationToFlat</td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Visualization/KochSnowflake"> KochSnowflake</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html">vtkPolyLine</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkTriangle.html">vtkTriangle</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a>,</td>
<td>Use recursion to represent a Koch snowflake fractal.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Legend"> Legend</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLegendBoxActor.html">vtkLegendBoxActor</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Visualization/NoShading"> NoShading</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetAmbient, <a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetDiffuse, <a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetSpecular</td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Visualization/PointSize"> PointSize</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetPointSize</td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Arbitrary3DCursor">Arbitrary3DCursor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointWidget.html">vtkPointWidget</a></td>
<td>Track a 3D cursor.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/AssignColorsFromLUT">AssignColorsFromLUT</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html">vtkNamedColors</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html">vtkPlaneSource</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html">vtkColorTransferFunction</a></td>
<td>Demonstrates how to assign colors to cells in a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a> structure using lookup tables.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/BackfaceCulling">BackfaceCulling</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::BackfaceCullingOn</td>
<td>Backface culling.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/BackgroundColor">BackgroundColor </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>::SetBackground</td>
<td>Background color.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/BackgroundGradient">BackgroundGradient </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>::GradientBackgroundOn, <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>::Setbackground2</td>
<td>Background gradient.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/BackgroundTexture">BackgroundTexture</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkTexture.html">vtkTexture</a></td>
<td>Use a texture for the background of a <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Camera">Camera</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCamera.html">vtkCamera</a></td>
<td>Positioning and aiming the camera.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CaptionActor2D">CaptionActor2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCaptionActor2D.html">vtkCaptionActor2D</a></td>
<td>Draw a caption/bubble pointing to a particular point.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ClipArt">ClipArt </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTextureMapToPlane.html">vtkTextureMapToPlane</a></td>
<td>Generate 3D clip art from an image.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CloseWindow">CloseWindow</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a>::TerminateApp, <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a>::Finalize</td>
<td>Close a render window.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ColorActorEdges">ColorActorEdges </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetEdgeColor</td>
<td>Color the edges of an Actor.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ColorAnActor">ColorAnActor </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetColor</td>
<td>Color an Actor.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ColorGlyphs">ColorGlyphs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a>::SetColorModeToColorByScalar</td>
<td>Color glyphs.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CornerAnnotation">CornerAnnotation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCornerAnnotation.html">vtkCornerAnnotation</a></td>
<td>Write text in the corners of a window.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CorrectlyRenderingTranslucentGeometry">CorrectlyRenderingTranslucentGeometry</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDepthSortPolyData.html">vtkDepthSortPolyData</a></td>
<td>Correctly Rendering Translucent Geometry.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CubeAxesActor2D">CubeAxesActor2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor2D.html">vtkCubeAxesActor2D</a></td>
<td>This example uses the <a href="http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor2D.html">vtkCubeAxesActor2D</a> to show your scene with axes to indicate the spatial extent of your data.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CubeAxesActor">CubeAxesActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor.html">vtkCubeAxesActor</a></td>
<td>Display three orthogonal axes with labels.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Cursor3D">Cursor3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCursor3D.html">vtkCursor3D</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CursorShape">CursorShape</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a></td>
<td>Change the shape of the cursor.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CurvatureBandsWithGlyphs">CurvatureBandsWithGlyphs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html">vtkCurvatures</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html">vtkBandedPolyDataContourFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html">vtkColorSeries</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/CurvedReformation">CurvedReformation </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html">vtkProbeFilter</a></td>
<td>Sample a volume with a curved surface. In medical imaging, this is often called curved multi planar reformation.</td>
</tr>
<tr>
<td><a href="Cxx/VisualizationAlgorithms/Cutter">Cutter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCutter.html">vtkCutter</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Visualization/DisplayCoordinateAxes">DisplayCoordinateAxes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOrientationMarkerWidget.html">vtkOrientationMarkerWidget</a></td>
<td>Display coordinate axes.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/DisplayQuadraticSurfaces">DisplayQuadraticSurfaces</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuadric.html">vtkQuadric</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSampleFunction.html">vtkSampleFunction</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html">vtkContourFilter</a></td>
<td>Display Quadratic Surfaces.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/DisplayText">DisplayText</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTextActor.html">vtkTextActor</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkTextProperty.html">vtkTextProperty</a></td>
<td>Display Text.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ElevationBandsWithGlyphs">ElevationBandsWithGlyphs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html">vtkBandedPolyDataContourFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html">vtkColorSeries</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/FastSplatter">FastSplatter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFastSplatter.html">vtkFastSplatter</a></td>
<td>Convolve a splat image with every point in an input image.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Follower">Follower </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFollower.html">vtkFollower</a></td>
<td>Draw text that stays right side up.</td>
</tr>
<tr>
<td><a href="Cxx/Filtering/Glyph2D">Glyph2D </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph2D.html">vtkGlyph2D</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Filtering/Glyph3D">Glyph3D </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Glyph3DMapper">Glyph3DMapper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3DMapper.html">vtkGlyph3DMapper</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Visualization/HedgeHog">HedgeHog</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHedgeHog.html">vtkHedgeHog</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html">vtkStructuredGrid</a></td>
<td>Create oriented lines (hedgehogs) from vector data.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/HideActor">Hide an actor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPropCollection.html">vtkPropCollection</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkProp.html">vtkProp</a>::VisibilityOff</td>
<td>visible</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/HideAllActors">HideAllActors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a>::RemoveAllViewProps</td>
<td>Hide all actors.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ImageMapper">ImageMapper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMapper.html">vtkImageMapper</a></td>
<td>Display an image in 2D.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ImageOrder">ImageOrder</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a></td>
<td>Determine the display order of a stack of images.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ImageOrientation">ImageOrientation </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleImage.html">vtkInteractorStyleImage</a></td>
<td>Orientation of the view of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ImageTransparency">ImageTransparency</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a></td>
<td>Set transparency of image pixels.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/IsosurfaceSampling">IsosurfaceSampling </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html">vtkProbeFilter</a></td>
<td>Demonstrates how to create point data on an isosurface.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/LODProp3D">LODProp3D </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLODProp3D.html">vtkLODProp3D</a></td>
<td>Level of detail rendering.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/LabelContours">LabelContours</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html">vtkLabeledDataMapper</a></td>
<td>Label Contours.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/LabelMesh">LabelMesh </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html">vtkLabeledDataMapper</a></td>
<td>Label Mesh.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/LabelPlacementMapper">LabelPlacementMapper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointSetToLabelHierarchy.html">vtkPointSetToLabelHierarchy</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLabelPlacementMapper.html">vtkLabelPlacementMapper</a></td>
<td>Display a non-overlapping text label at each point.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/LabeledDataMapper">LabeledDataMapper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html">vtkLabeledDataMapper</a></td>
<td>Display the point ID at each point.</td>
</tr>
<tr>
<td><a href="Cxx/WishList/Visualization/LayeredRenderers">LayeredRenderers</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a></td>
<td>Layered renderers.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/LegendScaleActor">LegendScaleActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLegendScaleActor.html">vtkLegendScaleActor</a></td>
<td>Display the scale of a scene.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/LineWidth">LineWidth</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkProperty.html">vtkProperty</a></td>
<td>Change the width/thickness of lines in an actor.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/MovableAxes">MovableAxes </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFollower.html">vtkFollower</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html">vtkAxesActor</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkAssembly.html">vtkAssembly</a></td>
<td>Movable axes.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/MoveActor">MoveActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html">vtkInteractorStyleTrackballActor</a></td>
<td>Moving an Actor.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/MoveCamera">MoveCamera</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html">vtkInteractorStyleTrackballCamera</a></td>
<td>Moving the Camera.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/MultipleActors">MultipleActors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a></td>
<td>Multiple Actors.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/NamedColorPatches">NamedColorPatches </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html">vtkNamedColors</a></td>
<td>Creates a HTML file called <a href="Python/Visualization/VTKNamedColorPatches.html">VTKNamedColorPatches.html</a> showing the available colors in the vtkNamedColors class.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/NamedColors">NamedColors </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html">vtkNamedColors</a></td>
<td>Demonstrates how to use the <a href="http://www.vtk.org/doc/nightly/html/classvtkNamedColor.html">vtkNamedColor</a> class.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Opacity">Opacity</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetOpacity</td>
<td>Transparency, transparent.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/OrientedGlyphs">OrientedGlyphs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Create oriented glyphs from vector data.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/PolyDataDepthSorting">PolyDataDepthSorting</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDepthSortPolyData.html">vtkDepthSortPolyData</a></td>
<td>Poly Data Depth Sorting.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ProgrammableGlyphFilter">ProgrammableGlyphFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProgrammableGlyphFilter.html">vtkProgrammableGlyphFilter</a></td>
<td>Generate a custom glyph at each point.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/QuadraticSurface">QuadraticSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuadric.html">vtkQuadric</a></td>
<td>Display a quadratic surface.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/QuadricLODActor">QuadricLODActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuadricLODActor.html">vtkQuadricLODActor</a></td>
<td>Level of detail adjustment.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/RandomProbe">RandomProbe</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html">vtkProbeFilter</a></td>
<td>Demonstrates how to probe a dataset with random points and select points inside the data set.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/RenderLargeImage">RenderLargeImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderLargeImage.html">vtkRenderLargeImage</a></td>
<td>Render a large image, larger than a window.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/RenderPassExistingContext">RenderPassExistingContext</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderPass.html">vtkRenderPass</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkVolumetricPass.html">vtkVolumetricPass</a></td>
<td>Render into an existing OpenGL Context.</td>
</tr>
<tr>
<td><a href="Cxx/Views/RenderView">RenderView</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderView.html">vtkRenderView</a></td>
<td>A little bit easier rendering.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ReverseAccess">ReverseAccess </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a></td>
<td>Demonstrates how to access the source (e.g. <a href="http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html">vtkSphereSource</a>) of an actor reversely.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/RotateActor">RotateActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetMatrix</td>
<td>Rotate an Actor.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ScalarBarActor">ScalarBarActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkScalarBarActor.html">vtkScalarBarActor</a></td>
<td>Display a color bar.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ScalarVisibility">ScalarVisibility</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDataSetMapper.html">vtkDataSetMapper</a></td>
<td>Switch between coloring the actor and coloring the data.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/ScaleGlyphs">ScaleGlyphs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a>::SetScaleModeToScaleByScalar</td>
<td>Scale glyphs.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/SceneBounds">SceneBounds</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a></td>
<td>Get the bounds of the whole scene.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/SelectWindowRegion">SelectWindowRegion</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html">vtkInteractorStyleRubberBand2D</a></td>
<td>Select a region of a window.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/StreamLines">StreamLines</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStreamLine.html">vtkStreamLine</a></td>
<td>Stream Lines.</td>
</tr>
<tr>
<td><a href="Visualization/TensorGlyph">TensorGlyph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTensorGlyph.html">vtkTensorGlyph</a></td>
<td>Draw a rotated/scaled glyph at each point.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/TextSource">TextSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTextSource.html">vtkTextSource</a></td>
<td>Display text.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/TextureMapImageData">TextureMapImageData </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html">vtkImageCanvasSource2D</a></td>
<td>Texture map an ImageData.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/TextureMapPlane">TextureMapPlane</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTextureMapToPlane.html">vtkTextureMapToPlane</a></td>
<td>Texture map a plane.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/TextureMapQuad">TextureMapQuad</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolygon.html">vtkPolygon</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>::GetPointData::SetTCoords</td>
<td>Texture map a quad.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/TransformActorCollection">TransformActorCollection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActorCollection.html">vtkActorCollection</a></td>
<td>Transform an actor collection.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/TransformActor">TransformActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::SetUserTransform</td>
<td>Transform an Actor.</td>
</tr>
<tr>
<td><a href="Cxx/VisualizationAlgorithms/TubesFromSplines">TubesFromSplines</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html">vtkTubeFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricFunctionSource.html">vtkParametricFunctionSource</a>  <a href="http://www.vtk.org/doc/nightly/html/classvtkTupleInterpolator.html">vtkTupleInterpolator</a></td>
<td>Create tubes from interpolated points and scalars.</td>
</tr>
<tr>
<td><a href="Cxx/VisualizationAlgorithms/TubesWithVaryingRadiusAndColors">TubesWithVaryingRadiusAndColors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html">vtkTubeFilter</a></td>
<td>Create tubes with varying radius and colors.</td>
</tr>
<tr>
<td><a href="Cxx/WishList/Visualization/VectorField">VectorField </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Visualize a vector field.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/VectorOfActors">VectorOfActors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a></td>
<td>Multiple Actors in a Vector.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/VectorText">VectorText</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVectorText.html">vtkVectorText</a></td>
<td>Display high resolution text.</td>
</tr>
<tr>
<td><a href="Cxx/Filtering/VertexGlyphFilter">VertexGlyphFilter </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVertexGlyphFilter.html">vtkVertexGlyphFilter</a></td>
<td>Add a vertex to each point.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Visualize2DPoints">Visualize2DPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper2D.html">vtkPolyDataMapper2D</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkProperty2D.html">vtkProperty2D</a></td>
<td>Visualize a 2D Set of Points.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/VisualizeImageData">VisualizeImageData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDataSetMapper.html">vtkDataSetMapper</a></td>
<td>Visualize the points of an ImageData.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/VisualizeVTP">VisualizeVTP</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html">vtkXMLPolyDataReader</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html">vtkPolyDataMapper</a></td>
<td>Visualize a VTP File.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/WindowSize">WindowSize</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a>:SetSize</td>
<td>Change the size of a window.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/WindowTitle">WindowTitle</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a>::SetWindowName</td>
<td>Change the title of a window.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Wireframe">Wireframe</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::GetProperty::SetRepresentationToWireframe</td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="volume-rendering">Volume Rendering</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/VolumeRendering/HAVSVolumeMapper">HAVS</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHAVSVolumeMapper.html">vtkHAVSVolumeMapper</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/VolumeRendering/MinIntensityRendering">MinIntensityRendering</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFixedPointVolumeRayCastMapper.html">vtkFixedPointVolumeRayCastMapper</a></td>
<td>Min intensity rendering.</td>
</tr>
<tr>
<td><a href="Cxx/VolumeRendering/SmartVolumeMapper">SmartVolumeMapper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSmartVolumeMapper.html">vtkSmartVolumeMapper</a></td>
<td>Smart volume mapper.</td>
</tr>
<tr>
<td><a href="Cxx/VolumeRendering/itk[VtkImageConvert](http://www.vtk.org/doc/nightly/html/classVtkImageConvert.html)">itk[VtkImageConvert](http://www.vtk.org/doc/nightly/html/classVtkImageConvert.html)</a></td>
<td></td>
<td>Conversion maintaining DICOM orientation and positionITK-&gt;VTK conversion.</td>
</tr>
</tbody>
</table>
<h1 id="user-interaction">User Interaction</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Picking/AreaPicking">AreaPicking</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAreaPicker.html">vtkAreaPicker</a></td>
<td>Area Picking.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/Assembly">Assembly</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAssembly.html">vtkAssembly</a></td>
<td>Combine/group actors into an assembly.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/CallData">CallData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCommand.html">vtkCommand</a></td>
<td>Pass an observer a value (via CallData).</td>
</tr>
<tr>
<td><a href="Cxx/Picking/CellPicking">CellPicking</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellPicker.html">vtkCellPicker</a></td>
<td>Cell Picking.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/ClientData">ClientData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCommand.html">vtkCommand</a></td>
<td>Give an observer access to an object (via ClientData).</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/DoubleClick">DoubleClick</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html">vtkInteractorStyleTrackballCamera</a></td>
<td>Catch a double click.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/Game">Game</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html">vtkInteractorStyleTrackballActor</a></td>
<td>Move a cube into a sphere.</td>
</tr>
<tr>
<td><a href="Cxx/Picking/HighlightPickedActor">HighlightPickedActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html">vtkPropPicker</a></td>
<td>Highlight a picked actor.</td>
</tr>
<tr>
<td><a href="Cxx/Picking/HighlightSelectedPoints">HighlightSelectedPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractGeometry.html">vtkExtractGeometry</a></td>
<td>Highlight Selected Points.</td>
</tr>
<tr>
<td><a href="Cxx/Picking/HighlightSelection">HighlightSelection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractPolyDataGeometry.html">vtkExtractPolyDataGeometry</a></td>
<td>Highlight selection.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/ImageClip">ImageClip</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageClip.html">vtkImageClip</a></td>
<td>Demonstrates how to interactively select and display a region of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/ImageRegion">ImageRegion</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCommand.html">vtkCommand</a></td>
<td>Select a region of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/InteractorStyleTerrain">InteractorStyleTerrain</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTerrain.html">vtkInteractorStyleTerrain</a></td>
<td>Terrain mode.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/InteractorStyleUser">InteractorStyleUser</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleUser.html">vtkInteractorStyleUser</a></td>
<td>Create a completely custom interactor style (no default functionality is provided)</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/KeypressEvents">KeypressEvents</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html">vtkInteractorStyleTrackballCamera</a></td>
<td>Handle keypress events.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/KeypressObserver">KeypressObserver </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html">vtkCallbackCommand</a></td>
<td>This uses a callback function rather than a derived interactor class. Handle keypress events (lightweight).</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/MouseEvents">MouseEvents </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html">vtkInteractorStyleTrackballCamera</a></td>
<td>Subclass the interactor style. Handle mouse events.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/MouseEventsObserver">MouseEventsObserver </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html">vtkCallbackCommand</a></td>
<td>Use an observer. Handle mouse events (light weight).</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/MoveAGlyph">MoveAGlyph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Drag a glyph around.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/MoveAVertexUnstructuredGrid">MoveAVertexUnstructuredGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html">vtkPointPicker</a></td>
<td>Click and drag a vertex of a <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/MoveAVertex">MoveAVertex</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html">vtkPointPicker</a></td>
<td>Click and drag a vertex of a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/ObserverMemberFunction">ObserverMemberFunction</a></td>
<td></td>
<td>Set observers to be class member functions.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/PickableOff">PickableOff</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a>::PickableOff</td>
<td>Disallow interaction with a specific actor.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/Picking">Picking</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html">vtkPropPicker</a></td>
<td>Get the world coordinate of the mouse click (if you clicked an actor)</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/PointPicker">PointPicker</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html">vtkPointPicker</a></td>
<td>Get the coordinates of the closest point in the data set to the mouse click.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/RubberBand2DObserver">RubberBand2DObserver</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html">vtkInteractorStyleRubberBand2D</a></td>
<td>RubberBand2D Observer.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/RubberBand2D">RubberBand2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html">vtkInteractorStyleRubberBand2D</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Interaction/RubberBand3D">RubberBand3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand3D.html">vtkInteractorStyleRubberBand3D</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Interaction/RubberBandPick">RubberBandPick</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBandPick.html">vtkInteractorStyleRubberBandPick</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Interaction/RubberBandZoom">RubberBandZoom</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBandZoom.html">vtkInteractorStyleRubberBandZoom</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Interaction/SelectAnActor">SelectAnActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html">vtkPropPicker</a></td>
<td>Select an actor.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/ShiftAndControl">ShiftAndControl</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a>::GetControlKey()</td>
<td>Hold/holding down a key. Check if shift or control is being held.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/StyleSwitch">StyleSwitch</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleSwitch.html">vtkInteractorStyleSwitch</a></td>
<td>Choose between multiple interaction modes.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/TrackballActor">TrackballActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html">vtkInteractorStyleTrackballActor</a></td>
<td>Trackball actor mode.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/TrackballCamera">TrackballCamera</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html">vtkInteractorStyleTrackballCamera</a></td>
<td>Trackball camera mode.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/UserEvent">UserEvent</a></td>
<td></td>
<td>Simple observer. Create, invoke, and handle a custom event.</td>
</tr>
<tr>
<td><a href="Cxx/Interaction/WorldPointPicker">WorldPointPicker</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWorldPointPicker.html">vtkWorldPointPicker</a></td>
<td>Get world coordinates of mouse click.</td>
</tr>
</tbody>
</table>
<h1 id="working-with-images">Working with Images</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Images/Actor2D">Actor2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor2D.html">vtkActor2D</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkMapper2D.html">vtkMapper2D</a></td>
<td>2D actor and mapper.</td>
</tr>
<tr>
<td><a href="Cxx/Images/BackgroundImage">BackgroundImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html">vtkImageCanvasSource2D</a></td>
<td>Display an image as the background of a scene.</td>
</tr>
<tr>
<td><a href="Cxx/Images/BorderPixelSize">BorderPixelSize</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html">vtkImageSliceMapper</a></td>
<td>Set the size of border pixels.</td>
</tr>
<tr>
<td><a href="Cxx/Images/CannyEdgeDetector">CannyEdgeDetector</a></td>
<td></td>
<td>Perform Canny edge detection on an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/Cast">Cast</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageCast.html">vtkImageCast</a></td>
<td>Cast an image to a different type.</td>
</tr>
<tr>
<td><a href="Cxx/Images/DotProduct">DotProduct</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageDotProduct.html">vtkImageDotProduct</a></td>
<td>Compute the pixel-wise dot product of two vector images.</td>
</tr>
<tr>
<td><a href="Cxx/Images/DrawOnAnImage">DrawOnAnImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html">vtkImageCanvasSource2D</a></td>
<td>Drawing on an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/DrawShapes">DrawShapes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html">vtkImageCanvasSource2D</a></td>
<td>Drawing shapes in an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ExtractComponents">ExtractComponents</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageExtractComponents.html">vtkImageExtractComponents</a></td>
<td>Extract components of an image. This can be used to get, for example, the red channel of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/FillWindow">FillWindow</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCamera.html">vtkCamera</a></td>
<td>Fit imageSetup the camera to fill the window with an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageAccumulateGreyscale">ImageAccumulateGreyscale</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageAccumulate.html">vtkImageAccumulate</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkBarChartActor.html">vtkBarChartActor</a></td>
<td>Display a greyscale histogram.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageCheckerboard">ImageCheckerboard</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageCheckerboard.html">vtkImageCheckerboard</a></td>
<td>Visually Compare Two Images.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageCityBlockDistance">ImageCityBlockDistance</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageCityBlockDistance.html">vtkImageCityBlockDistance</a></td>
<td>Compute the Manhattan distance from every point to every black point in a binary image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageDilateErode3D">ImageDilateErode3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageDilateErode3D.html">vtkImageDilateErode3D</a></td>
<td>Dilate or erode an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageExport">ImageExport </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageExport.html">vtkImageExport</a></td>
<td>Export an image to a C array.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageGridSource">ImageGridSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageGridSource.html">vtkImageGridSource</a></td>
<td>Create a image of a grid.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageHybridMedian2D">ImageHybridMedian2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageHybridMedian2D.html">vtkImageHybridMedian2D</a></td>
<td>Median filter an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageIdealHighPass">ImageIdealHighPass</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageIdealHighPass.html">vtkImageIdealHighPass</a></td>
<td>High pass filter an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageImport">ImageImport </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageImport.html">vtkImageImport</a></td>
<td>Import an image from a C array.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageIslandRemoval2D">ImageIslandRemoval2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageIslandRemoval2D.html">vtkImageIslandRemoval2D</a></td>
<td>Remove small patches from an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageMagnify">ImageMagnify</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMagnify.html">vtkImageMagnify</a></td>
<td>Supersample and stretch an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageMandelbrotSource">ImageMandelbrotSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMandelbrotSource.html">vtkImageMandelbrotSource</a></td>
<td>Create a Mandelbrot image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageMask">ImageMask</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMask.html">vtkImageMask</a></td>
<td>Mask a region of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageMathematics">ImageMathematics</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMathematics.html">vtkImageMathematics</a></td>
<td>Perform mathematical operations on an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageMedian3D">ImageMedian3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMedian3D.html">vtkImageMedian3D</a></td>
<td>Median filter a 3d or 2d image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageMirrorPad">ImageMirrorPad</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMirrorPad.html">vtkImageMirrorPad</a></td>
<td>Pad the edges of an extended image by mirror existing pixels.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageNonMaximumSuppression">ImageNonMaximumSuppression</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageNonMaximumSuppression.html">vtkImageNonMaximumSuppression</a></td>
<td>Find peaks in an image using non maximum suppression.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageOpenClose3D">ImageOpenClose3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageOpenClose3D.html">vtkImageOpenClose3D</a></td>
<td>Open or close (morphologically) an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageRFFT">ImageRFFT</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageRFFT.html">vtkImageRFFT</a></td>
<td>Inverse FFT.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageRange3D">ImageRange3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageRange3D.html">vtkImageRange3D</a></td>
<td>Replace every pixel with the range of its neighbors according to a kernel.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageRotate">ImageRotate</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html">vtkImageSlice</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageResliceMapper.html">vtkImageResliceMapper</a></td>
<td>Rotate a 2D image. This is even more powerful than <a href="http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html">vtkImageSliceMapper</a>. It can also do oblique slices.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageSeparableConvolution">ImageSeparableConvolution</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageSeparableConvolution.html">vtkImageSeparableConvolution</a></td>
<td>Convolve a separable kernel with an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageShiftScale">ImageShiftScale</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageShiftScale.html">vtkImageShiftScale</a></td>
<td>Shift and scale an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageSinusoidSource">ImageSinusoidSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageSinusoidSource.html">vtkImageSinusoidSource</a></td>
<td>Create a sinusoidal image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageSliceMapper">ImageSliceMapper</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html">vtkImageSlice</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html">vtkImageSliceMapper</a></td>
<td>Visualize and interact with an image. This is the new way to do this. It is much more powerful.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageSlice">ImageSlice</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html">vtkImageSlice</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageResliceMapper.html">vtkImageResliceMapper</a></td>
<td>Visualize and interact with an image. This is even more powerful than <a href="http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html">vtkImageSliceMapper</a>. It can also do oblique slices.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageStack">ImageStack</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageStack.html">vtkImageStack</a></td>
<td>Display layers of images.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageStencil">ImageStencil</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageStencil.html">vtkImageStencil</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageToImageStencil.html">vtkImageToImageStencil</a></td>
<td>Copy one image into another image.</td>
</tr>
<tr>
<td><a href="Cxx/Broken/Images/ImageText">ImageText</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFreeTypeUtilities.html">vtkFreeTypeUtilities</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageBlend.html">vtkImageBlend</a></td>
<td>Draw text in an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageThreshold">ImageThreshold</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageThreshold.html">vtkImageThreshold</a></td>
<td>Threshold an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageToPolyDataFilter">ImageToPolyDataFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageToPolyDataFilter.html">vtkImageToPolyDataFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageQuantizeRGBToIndex.html">vtkImageQuantizeRGBToIndex</a></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a> to a <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageToStructuredPoints">ImageToStructuredPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageToStructuredPoints.html">vtkImageToStructuredPoints</a></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a> to a <a href="http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html">vtkStructuredPoints</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Images/InteractWithImage">InteractWithImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageActor.html">vtkImageActor</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleImage.html">vtkInteractorStyleImage</a></td>
<td>Visualize and interact with an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/Interpolation">Interpolation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html">vtkImageSlice</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageProperty.html">vtkImageProperty</a></td>
<td>Set the interpolation type for the display of an image. If pixels look blurry instead of sharp when zoomed in, change this.</td>
</tr>
<tr>
<td><a href="Cxx/Images/MarkKeypoints">MarkKeypoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVectorText.html">vtkVectorText</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkFollower.html">vtkFollower</a></td>
<td>Mark keypoints in an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/NegativeIndices">NegativeIndices</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a></td>
<td>A very powerful feature of <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a> is that you can use negative indices.</td>
</tr>
<tr>
<td><a href="Cxx/Images/PickingAPixel2">PickingAPixel2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html">vtkPropPicker</a></td>
<td>Picking a pixel 2 - modified version for exact pixel values.</td>
</tr>
<tr>
<td><a href="Cxx/Images/PickingAPixel">PickingAPixel</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html">vtkPropPicker</a></td>
<td>Picking a pixel.</td>
</tr>
<tr>
<td><a href="Cxx/Images/RTAnalyticSource">RTAnalyticSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRTAnalyticSource.html">vtkRTAnalyticSource</a></td>
<td>An image source that can be used for regression testing</td>
</tr>
<tr>
<td><a href="Cxx/Images/StaticImage">StaticImage</a></td>
<td>v<a href="http://www.vtk.org/doc/nightly/html/classvtkImageViewer2.html">vtkImageViewer2</a></td>
<td>This will display the image, but not allow you to interact with it.</td>
</tr>
<tr>
<td><a href="Cxx/Images/Transparency">Transparency</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html">vtkImageMapToColors</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a></td>
<td>Make part of an image transparent.</td>
</tr>
</tbody>
</table>
<h1 id="image-processing">Image Processing</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Images/Blending2DImagesWithDifferentColorMaps">Blending2DImagesWithDifferentColorMaps</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html">vtkImageMapToColors</a></td>
<td>Blending 2D images with different color maps.</td>
</tr>
<tr>
<td><a href="Cxx/Images/CenterAnImage">CenterAnImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageChangeInformation.html">vtkImageChangeInformation</a></td>
<td>Center an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/CombineImages">CombineImages</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageBlend.html">vtkImageBlend</a></td>
<td>Combine two images.</td>
</tr>
<tr>
<td><a href="Cxx/Images/CombiningRGBChannels">CombiningRGBChannels</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageAppendComponents.html">vtkImageAppendComponents</a></td>
<td>Combine layers into an RGB image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ConvertToGreyScale">ConvertToGreyScale</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMagnitude.html">vtkImageMagnitude</a></td>
<td>grayscaleConvert RGB image to greyscale.</td>
</tr>
<tr>
<td><a href="Cxx/Images/Flip">Flip</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageFlip.html">vtkImageFlip</a></td>
<td>Flip an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/Gradient">Gradient</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageGradient.html">vtkImageGradient</a></td>
<td>Compute the gradient vector at every pixel.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageAccumulate">ImageAccumulate</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageAccumulate.html">vtkImageAccumulate</a></td>
<td>Histogram</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageAnisotropicDiffusion2D">ImageAnisotropicDiffusion2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageAnisotropicDiffusion2D.html">vtkImageAnisotropicDiffusion2D</a></td>
<td>Anisotropic diffusion (2D).</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageContinuousDilate3D">ImageContinuousDilate3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageContinuousDilate3D.html">vtkImageContinuousDilate3D</a></td>
<td>Dilate an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageContinuousErode3D">ImageContinuousErode3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageContinuousErode3D.html">vtkImageContinuousErode3D</a></td>
<td>Erode an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageConvolve">ImageConvolve</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageConvolve.html">vtkImageConvolve</a></td>
<td>Convolve an image with a kernel.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageCorrelation">ImageCorrelation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageCorrelation.html">vtkImageCorrelation</a></td>
<td>Correlate two images.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageDifference">ImageDifference</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageDifference.html">vtkImageDifference</a></td>
<td>Compute the difference image of two images.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageDivergence">ImageDivergence</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageDivergence.html">vtkImageDivergence</a></td>
<td>Divergence of a vector field.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageEllipsoidSource">ImageEllipsoidSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageEllipsoidSource.html">vtkImageEllipsoidSource</a></td>
<td>Create an image of an ellipsoid.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageFFT">ImageFFT</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageFFT.html">vtkImageFFT</a></td>
<td>Compute the FFT of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageGaussianSmooth">ImageGaussianSmooth</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageGaussianSmooth.html">vtkImageGaussianSmooth</a></td>
<td>Smooth an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageGradientMagnitude">ImageGradientMagnitude</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageGradientMagnitude.html">vtkImageGradientMagnitude</a></td>
<td>Compute the magnitude of the gradient at each pixel of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageLaplacian">ImageLaplacian</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageLaplacian.html">vtkImageLaplacian</a></td>
<td>Compute the Laplacian of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageLuminance">ImageLuminance</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageLuminance.html">vtkImageLuminance</a></td>
<td>Convert RGB image to greyscale (luminance).</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageMapToColors">ImageMapToColors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html">vtkImageMapToColors</a></td>
<td>Use a lookup table to map scalar (grayscale) values to colorsConvert greyscale image to RGB.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageNoiseSource">ImageNoiseSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageNoiseSource.html">vtkImageNoiseSource</a></td>
<td>Create an image of noise.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImagePermute">ImagePermute</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImagePermute.html">vtkImagePermute</a></td>
<td>Switch axes of an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageShrink3D">ImageShrink3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageShrink3D.html">vtkImageShrink3D</a></td>
<td>Resample an image.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageSobel2D">ImageSobel2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageSobel2D.html">vtkImageSobel2D</a></td>
<td>Sobel edge detection 2D.</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageValueRange">ImageValueRange</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a></td>
<td>Get the range of image pixel values (min/max).</td>
</tr>
<tr>
<td><a href="Cxx/Images/ImageVariance3D">ImageVariance3D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageVariance3D.html">vtkImageVariance3D</a></td>
<td>Construct a new image consisting of the variance of the input image at each pixel.</td>
</tr>
<tr>
<td><a href="Cxx/Images/RGBToHSV">RGBToHSV</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageRGBToHSV.html">vtkImageRGBToHSV</a></td>
<td>Convert RGB to HSV.</td>
</tr>
<tr>
<td><a href="Cxx/ImageProcessing/RescaleAnImage">RescaleAnImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageShiftScale.html">vtkImageShiftScale</a></td>
<td>Rescale an image</td>
</tr>
<tr>
<td><a href="Cxx/Images/ResizeImage">ResizeImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageResize.html">vtkImageResize</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkImageSincInterpolator.html">vtkImageSincInterpolator</a></td>
<td>Resize an image using a sinc interpolator.</td>
</tr>
</tbody>
</table>
<h1 id="widgets">Widgets</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/PolyData/PolygonalSurfacePointPlacer"> PolygonalSurfacePointPlacer</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolygonalSurfacePointPlacer.html">vtkPolygonalSurfacePointPlacer</a></td>
<td>Used in conjuntion with <a href="http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html">vtkContourWidget</a> to draw curves on a surface.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/AffineWidget">AffineWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAffineWidget.html">vtkAffineWidget</a></td>
<td>Apply an affine transformation interactively.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/AngleWidget2D">AngleWidget2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html">vtkAngleWidget</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkAngleRepresentation2D.html">vtkAngleRepresentation2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html">vtkAngleWidget</a> + <a href="http://www.vtk.org/doc/nightly/html/classvtkAngleRepresentation2D.html">vtkAngleRepresentation2D</a>.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/AngleWidget">AngleWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html">vtkAngleWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/BalloonWidget">BalloonWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBalloonWidget.html">vtkBalloonWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/BiDimensionalWidget">BiDimensionalWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBiDimensionalWidget.html">vtkBiDimensionalWidget</a></td>
<td>When would you use this?</td>
</tr>
<tr>
<td><a href="BrokenCxxWidgets/BorderWorldCoords">BorderWorldCoords</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBorderWidget.html">vtkBorderWidget</a></td>
<td>2D selection box in world coordinates.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/Border">Border</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBorderWidget.html">vtkBorderWidget</a></td>
<td>2D selection, 2D box.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/BoxWidget2">BoxWidget2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoxWidget2.html">vtkBoxWidget2</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/BoxWidget">BoxWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoxWidget.html">vtkBoxWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/Caption">Caption</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCaptionWidget.html">vtkCaptionWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/CheckerboardWidget">CheckerboardWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCheckerboardWidget.html">vtkCheckerboardWidget</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkCheckerboardRepresentation.html">vtkCheckerboardRepresentation</a></td>
<td>Compare two images using a checkerboard.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/ContourWidget">ContourWidget </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html">vtkContourWidget</a></td>
<td>Create a contour from a set of points and dynamically change the contour using the points as control points.</td>
</tr>
<tr>
<td><a href="Cxx/Visualization/Cursor2D">Cursor2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCursor2D.html">vtkCursor2D</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/DistanceWidget">DistanceWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDistanceWidget.html">vtkDistanceWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/HoverWidget">HoverWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHoverWidget.html">vtkHoverWidget</a></td>
<td>How to detect a hover?</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/ImagePlaneWidget">ImagePlaneWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImagePlaneWidget.html">vtkImagePlaneWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/ImageTracerWidgetInsideContour">ImageTracerWidgetInsideContour</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html">vtkImageTracerWidget</a></td>
<td>Highlight pixels inside a non-regular region scribbled on an image.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/ImageTracerWidgetNonPlanar">ImageTracerWidgetNonPlanar</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html">vtkImageTracerWidget</a></td>
<td>Draw on a non-planar surface.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/ImageTracerWidget">ImageTracerWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html">vtkImageTracerWidget</a></td>
<td>Scribble on an image.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/ImplicitPlaneWidget2">ImplicitPlaneWidget2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitPlaneWidget2.html">vtkImplicitPlaneWidget2</a></td>
<td>Clip polydata with an implicit plane.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/LineWidget2">LineWidget2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLineWidget2.html">vtkLineWidget2</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/LogoWidget">LogoWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLogoWidget.html">vtkLogoWidget</a></td>
<td>Logo widget.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/OrientationMarkerWidget">OrientationMarkerWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOrientationMarkerWidget.html">vtkOrientationMarkerWidget</a></td>
<td>Display a polydata as an orientation icon.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/PlaneWidget">PlaneWidget </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlaneWidget.html">vtkPlaneWidget</a></td>
<td>Interact with a plane.</td>
</tr>
<tr>
<td><a href="Broken/Widgets/PointWidget">PointWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointWidget.html">vtkPointWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/RectilinearWipeWidget">RectilinearWipeWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageRectilinearWipe.html">vtkImageRectilinearWipe</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearWipeWidget.html">vtkRectilinearWipeWidget</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearWipeRepresentation.html">vtkRectilinearWipeRepresentation</a></td>
<td>Compare two images.</td>
</tr>
<tr>
<td><a href="Widgets/SeedWidgetImage">SeedWidgetImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageViewer2.html">vtkImageViewer2</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html">vtkSeedWidget</a></td>
<td>How to start the interaction?</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/SeedWidget">SeedWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html">vtkSeedWidget</a></td>
<td>Seed widget.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/Slider2D">Slider2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSliderWidget.html">vtkSliderWidget</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSliderRepresentation2D.html">vtkSliderRepresentation2D</a></td>
<td>2D Slider.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/Slider">Slider</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSliderWidget.html">vtkSliderWidget</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSliderRepresentation3D.html">vtkSliderRepresentation3D</a></td>
<td>3D Slider.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/SphereWidget2">SphereWidget2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphereWidget2.html">vtkSphereWidget2</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/SphereWidgetEvents">SphereWidgetEvents </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html">vtkSphereWidget</a></td>
<td>Sphere widget events.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/SphereWidget">SphereWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html">vtkSphereWidget</a></td>
<td>Sphere widget.</td>
</tr>
<tr>
<td><a href="Cxx/Widgets/Spline">SplineWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSplineWidget.html">vtkSplineWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Widgets/TextWidget">TextWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html">vtkSeedWidget</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxWidgets/TexturedButtonWidget">TexturedButtonWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkButtonWidget.html">vtkButtonWidget</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkTexturedButtonRepresentation2D.html">vtkTexturedButtonRepresentation2D</a></td>
<td>Create a textured 2D buttonx.</td>
</tr>
</tbody>
</table>
<h1 id="plotting">Plotting</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="Cxx/Plotting/BarChart">BarChart</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkChartXY.html">vtkChartXY</a></td>
<td>Bar chart.</td>
</tr>
<tr>
<td><a href="Cxx/Plotting/BoxChart">BoxChart</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkChartBox.html">vtkChartBox</a></td>
<td>Box plot.</td>
</tr>
<tr>
<td><a href="Cxx/Plotting/Diagram">Diagram</a></td>
<td></td>
<td></td>
</tr>
<tr>
<td><a href="Cxx/Plotting/LinePlot">LinePlot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkChartXY.html">vtkChartXY</a></td>
<td>Line plot.</td>
</tr>
<tr>
<td><a href="Cxx/Plotting/ParallelCoordinates">ParallelCoordinates</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkChartParallelCoordinates.html">vtkChartParallelCoordinates</a></td>
<td>Parallel coordinates.</td>
</tr>
<tr>
<td><a href="Cxx/Plotting/PieChart">PieChart</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkChartPie.html">vtkChartPie</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPlotPie.html">vtkPlotPie</a></td>
<td>Pie chart.</td>
</tr>
<tr>
<td><a href="Cxx/Plotting/ScatterPlot">ScatterPlot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlotPoints.html">vtkPlotPoints</a></td>
<td>Scatter plot.</td>
</tr>
<tr>
<td><a href="Cxx/Plotting/StackedBar">StackedBar</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlotBar.html">vtkPlotBar</a></td>
<td>Stacked bar.</td>
</tr>
<tr>
<td><a href="Cxx/Plotting/StackedPlot">StackedPlot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlotStacked.html">vtkPlotStacked</a></td>
<td>Stacked plot.</td>
</tr>
</tbody>
</table>
<h1 id="animation">Animation</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxAnimation/AnimateActors">AnimateActors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAnimationScene.html">vtkAnimationScene</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkAnimationCue.html">vtkAnimationCue</a></td>
<td>Animate actors.</td>
</tr>
<tr>
<td><a href="CxxUtilities/Animation">Animation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a>::CreateRepeatingTimer</td>
<td>Move a sphere across a scene.</td>
</tr>
<tr>
<td><a href="CxxUtilities/AnimationScene">AnimationScene</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAnimationScene.html">vtkAnimationScene</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkAnimationCue.html">vtkAnimationCue</a></td>
<td>Animation (the right way). Zoom in on a sphere.</td>
</tr>
<tr>
<td><a href="CxxUtilities/DataAnimation">DataAnimation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html">vtkCallbackCommand</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html">vtkProgrammableFilter</a></td>
<td>Data Animation. Update points in a dataset every specified interval.</td>
</tr>
<tr>
<td><a href="CxxUtilities/DataAnimationSubclass">DataAnimationSubclass</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCommand.html">vtkCommand</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html">vtkProgrammableFilter</a></td>
<td>Update points in a dataset every specified interval (using a <a href="http://www.vtk.org/doc/nightly/html/classvtkCommand.html">vtkCommand</a> subclass instead of a callback function.</td>
</tr>
</tbody>
</table>
<h1 id="geographic-visualization-geovis">Geographic Visualization (Geovis)</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxGeovis/CompassWidget">CompassWidget </a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCompassWidget.html">vtkCompassWidget</a></td>
<td>Compass Widget.</td>
</tr>
<tr>
<td><a href="CxxGeovis/EarthSource">EarthSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkEarthSource.html">vtkEarthSource</a></td>
<td>Create the Earth.</td>
</tr>
<tr>
<td><a href="CxxGeovis/GeoAssignCoordinates">GeoAssignCoordinates</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGeoAssignCoordinates.html">vtkGeoAssignCoordinates</a></td>
<td>Convert lat/long coordinates to world coordinates.</td>
</tr>
</tbody>
</table>
<h1 id="information-visualization-infovis">Information Visualization (Infovis)</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxInfoVis/ParallelCoordinatesView">ParallelCoordinatesView</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesView.html">vtkParallelCoordinatesView</a></td>
<td>Parallel coordinates.</td>
</tr>
<tr>
<td><a href="CxxInfoVis/TreeMapView">TreeMapView</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTreeMapView.html">vtkTreeMapView</a></td>
<td>Tree map.</td>
</tr>
</tbody>
</table>
<h1 id="qt">Qt</h1>
<p>Click <a href="http://www.vtk.org/Wiki/VTK/Tutorials/QtSetup">here</a> for a tutorial on how to setup Qt.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxQt/BorderWidget"> Border Widget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBorderWidget.html">vtkBorderWidget</a>, QApplication</td>
<td></td>
</tr>
<tr>
<td><a href="CxxQt/QtBarChart"> QtBarChart</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQtBarChart.html">vtkQtBarChart</a></td>
<td></td>
</tr>
<tr>
<td><a href="CxxQt/ShowEvent"> ShowEvent </a></td>
<td></td>
<td>Use QMainWindow::showEvent event to do things that you might want to do in the constructor</td>
</tr>
<tr>
<td><a href="CxxQt/EventQtSlotConnect">EventQtSlotConnect</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkEventQtSlotConnect.html">vtkEventQtSlotConnect</a></td>
<td>Connect a VTK event to a Qt slot.</td>
</tr>
<tr>
<td><a href="CxxQt/ImageDataToQImage">ImageDataToQImage</a></td>
<td></td>
<td>Convert a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a> to a QImage.</td>
</tr>
<tr>
<td><a href="CxxQt/QImageToImageSource">QImageToImageSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQImageToImageSource.html">vtkQImageToImageSource</a></td>
<td>Convert a QImage to a <a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a>.</td>
</tr>
<tr>
<td><a href="CxxQt/RenderWindowNoUiFile">RenderWindowNoUiFile</a></td>
<td>Q<a href="http://www.vtk.org/doc/nightly/html/classVTKWidget.html">VTKWidget</a></td>
<td>This is a very basic example that shows how to create a Qt window. Typically, one would want to design a form in the QtDesigner (this is shown in [[/Qt/RenderWindowUi</td>
</tr>
<tr>
<td><a href="CxxQt/RenderWindowUIMultipleInheritance">RenderWindowUIMultipleInheritance</a></td>
<td>QMainWindow</td>
<td>Using a Q<a href="http://www.vtk.org/doc/nightly/html/classVTKWidget.html">VTKWidget</a> with the Qt Multiple Inheritance model.</td>
</tr>
<tr>
<td><a href="CxxQt/RenderWindowUISingleInheritance">RenderWindowUISingleInheritance</a></td>
<td>QMainWindow</td>
<td>Using a Q<a href="http://www.vtk.org/doc/nightly/html/classVTKWidget.html">VTKWidget</a> with the Qt Single Inheritance model.</td>
</tr>
<tr>
<td><a href="CxxQt/ShareCameraBetweenQ[VTKWidgets](http://www.vtk.org/doc/nightly/html/classVTKWidgets.html)">ShareCameraBetweenQ[VTKWidgets](http://www.vtk.org/doc/nightly/html/classVTKWidgets.html)</a></td>
<td></td>
<td>Share the camera between Q<a href="http://www.vtk.org/doc/nightly/html/classVTKWidgets.html">VTKWidgets</a>.</td>
</tr>
<tr>
<td><a href="CxxQt/SideBySideRenderWindows">SideBySideRenderWindows</a></td>
<td>QApplication</td>
<td>Side by side render windows.</td>
</tr>
</tbody>
</table>
<h1 id="matlab">Matlab</h1>
<p>You must turn on VTK_USE_MATLAB_MEX to use these.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxMatlab/MatlabEngineFilter">MatlabEngineFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMatlabEngineFilter.html">vtkMatlabEngineFilter</a></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="databases">Databases</h1>
<h2 id="sql">SQL</h2>
<p>If you have any trouble or errors with the following examples, please troubleshoot using <a href="http://www.vtk.org/Wiki/Tutorials/SQLSetup">these instructions</a>.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxDatabases/SQL/MySQL/ConnectAndRead">ConnectAndRead</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html">vtkMySQLDatabase</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSQLQuery.html">vtkSQLQuery</a></td>
<td>Connect to and read a MySQL database.</td>
</tr>
<tr>
<td><a href="CxxDatabases/SQL/MySQL/CreateDatabase">CreateDatabase</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html">vtkMySQLDatabase</a></td>
<td>Create a MySQL database.</td>
</tr>
<tr>
<td><a href="CxxDatabases/SQL/MySQL/WriteToDatabase">WriteToDatabase</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSQLQuery.html">vtkSQLQuery</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html">vtkMySQLDatabase</a></td>
<td>Write to a MySQL database.</td>
</tr>
</tbody>
</table>
<h1 id="renderman">RenderMan</h1>
<p>RenderMan is a high quality rendering system created by <a href="https://renderman.pixar.com/view/renderman">Pixar</a>. VTK can export RenderMan RIB files for rendering by <a href="http://renderman.pixar.com/view/renderman-prman-the-rispec-and-renderman-studio">prman</a>. In the spring of 2015, Pixar released a <a href="http://renderman.pixar.com/view/PR-NCR">non-commercial version</a> of its RenderMan products.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxRenderMan/PolyDataRIB">PolyDataRIB</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRIBExporter.html">vtkRIBExporter</a></td>
<td>Apply a RenderMan Shader to a PolyData.</td>
</tr>
</tbody>
</table>
<h1 id="remote-modules">Remote Modules</h1>
<p>Remote modules are user contributed code that is not distributed with VTK. A description of a remote module and the location of its repository is listed in the VTK/Remote directory with the extension .remote.cmake. Once enabled, a remote module is treated like any other VTK module. Each of the remote module examples describes how to enable the example. More information about remote modules is <a href="http://www.vtk.org/Wiki/VTK/Remote_Modules">here</a>.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="CxxRemote/FrenetSerretFrame">FrenetSerretFrame</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFrenetSerretFrame.html">vtkFrenetSerretFrame</a></td>
<td>Compute tangent and normal vectors to a polyline.</td>
</tr>
<tr>
<td><a href="CxxRemote/FrenetSerretFrameDemo">FrenetSerretFrameDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFrenetSerretFrame.html">vtkFrenetSerretFrame</a></td>
<td>Uses <a href="http://www.vtk.org/doc/nightly/html/classvtkSplineWidget.html">vtkSplineWidget</a> to interact with a spline. Shows how to control a pipeline inside a callback.</td>
</tr>
</tbody>
</table>