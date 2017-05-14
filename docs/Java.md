<p>Click <a href="http://www.vtk.org/Wiki/VTK/Tutorials/JavaEnvironmentSetup">hear</a> for a tutorial on setting up your Java environment.</p>
<p>It would be appreciated if there are any Python VTK experts who could convert any of the <a href="Cxx">c++ examples</a> to Java!</p>
<div class="toc"><span class="toctitle">Contents</span><ul>
<li><a href="#input-and-output">Input and Output</a></li>
<li><a href="#implicit-functions-and-iso-surfaces">Implicit Functions and Iso-surfaces</a></li>
<li><a href="#data-structures">Data Structures</a></li>
<li><a href="#image-processing">Image Processing</a></li>
<li><a href="#miscellaneous">Miscellaneous</a></li>
<li><a href="#visualization">Visualization</a></li>
<li><a href="#interaction">Interaction</a></li>
<li><a href="#graphs">Graphs</a></li>
<li><a href="#swing-integration">Swing Integration</a></li>
</ul>
</div>
<h1 id="input-and-output">Input and Output</h1>
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
<td><a href="/Java/IO/ReadPolyData">Read a polydata(.vtp) file</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html">vtkXMLPolyDataReader</a></td>
<td>IO</td>
</tr>
<tr>
<td><a href="/Java/IO/WritePolyData">Write a polygonal data (.vtp) file</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html">vtkXMLPolyDataWriter</a></td>
<td>IO</td>
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
<td><a href="/Java/ImplicitFunctions/ImplicitSphere">ImplicitSphere</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphere.html">vtkSphere</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkAppendPolyData.html">vtkAppendPolyData</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html">vtkTubeFilter</a></td>
<td>ImplicitFunctions, Append poly data, tube filter, sphere</td>
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
<td><a href="/Java/DataStructures/VisualizeKDTree">VisualizeKDTree</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html">vtkKdTreePointLocator</a></td>
<td></td>
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
<td><a href="/Java/Imaging/ImageTest">ImageTest</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageReader2Factory.html">vtkImageReader2Factory</a></td>
<td>use Java File Dialog to select Image File to Display</td>
</tr>
</tbody>
</table>
<h1 id="miscellaneous">Miscellaneous</h1>
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
<td><a href="/Java/Miscellaneous/Cutter">Cutter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCutter.html">vtkCutter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Java/Miscellaneous/Screenshot">Screenshot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html">vtkWindowToImageFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Java/Miscellaneous/Cone6">Cone6</a></td>
<td></td>
<td>The missing Step 6 Java example from Examples/Tutorial</td>
</tr>
</tbody>
</table>
<h1 id="visualization">Visualization</h1>
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
<td><a href="/Java/Visualization/Animation">Animation</a></td>
<td></td>
<td>Move a sphere across a scene</td>
</tr>
<tr>
<td><a href="/Java/Visualization/Follower">Follower</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFollower.html">vtkFollower</a></td>
<td>Draw text that stays right side up</td>
</tr>
<tr>
<td><a href="/Java/Visualization/AnimDataCone">AnimDataCone</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a></td>
<td>Animate a cone by modifying the polydata points - uses Interaction M key (Motion) to toggle animation.</td>
</tr>
<tr>
<td><a href="/Java/Visualization/ColorAnActor">ColorAnActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html::GetProperty">vtkActor</a>::SetColor</td>
<td>Animate a cone by modifying the polydata points - uses Interaction M key (Motion) to toggle animation.</td>
</tr>
<tr>
<td><a href="/Java/Visualization/VectorField">VectorField</a></td>
<td></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="interaction">Interaction</h1>
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
<td><a href="/Java/Interaction/SphereInteractionPanel">SphereInteractionPanel</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleSwitch.html">vtkInteractorStyleSwitch</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkCanvas.html">vtkCanvas</a></td>
<td>Switch style interaction adds C and A key actions for selecting Camera or Actor interaction, and T and J key actions for Trackball or Joystick interaction mode. Adds charEvent observer callback to restore the missing E and Q events to quit.</td>
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
<td><a href="/Java/Graphs/SelectGraphVertices">SelectGraphVertices</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html">vtkAnnotationLink</a></td>
<td>Select Edges and vertices in a graph</td>
</tr>
</tbody>
</table>
<h1 id="swing-integration">Swing Integration</h1>
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
<td><a href="/Java/SwingIntegration/JFrameRenderer">JFrameRender</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowPanel.html">vtkRenderWindowPanel</a></td>
<td>Render a scene in a JFrame using a vtkRenderWindowPanel</td>
</tr>
<tr>
<td><a href="/Java/SwingIntegration/SwingHandleMouseEvent">SwingHandleMouseEvent</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowPanel.html">vtkRenderWindowPanel</a></td>
<td>Display in a JLabel the point the mouse is hovering over using a mouse listener</td>
</tr>
</tbody>
</table>