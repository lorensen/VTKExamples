<div class="toc"><span class="toctitle">Contents</span><ul>
<li><a href="#requirements">Requirements</a></li>
<li><a href="#guidelines">Guidelines</a></li>
</ul>
</div>
<h2 id="requirements">Requirements</h2>
<p>Although education of new users in the main motivation, the VTK wiki examples should also:</p>
<ol>
<li>Encourage good programming style</li>
<li>Promote the proper and modern way to use VTK and write VTK programs</li>
<li>Facilitate the nightly compilation and testing of examples that reside in the VTK wiki</li>
</ol>
<p>These requirements must be met without compromising the main goal of user education.</p>
<h2 id="guidelines">Guidelines</h2>
<p>All examples should follow the VTK programming style.</p>
<ul>
<li>
<p>The indentation style can be characterized as the <a href="https://en.wikipedia.org/wiki/Indent_style#Allman_style">Allmann
Style</a>. The curly brace (scope delimiter) is on a separate line and aligns with the control statement, The control block is indented by two spaces (<strong>no tabs</strong>).</p>
<p>Example:</p>
<p><code>if (this-&gt;Locator == locator)
{
  return;
}
for (i = 0; i &lt; this-&gt;Source-&gt;GetNumberOfPoints(); i++)
{
  p1 = this-&gt;Source-&gt;GetPoint(i);
  [...]
}</code></p>
</li>
<li>
<p>Where appropriate, explicitly use the std:: namespace:</p>
<p><code>std::cout &lt;&lt; "Print something" &lt;&lt; std::endl;</code>
rather than</p>
<p><code>cout &lt;&lt; "Print something" &lt;&lt; endl;</code></p>
</li>
<li>
<p>All includes from the toolkit should use &lt;&gt; notation. This follows C++ programming conventions.</p>
<p>For example: <code>#include &lt;vtkContourFilter.h&gt;</code> is preferred over <code>#include "vtkContourFilter.h"</code></p>
</li>
<li>
<p>The main program must have the following signature:</p>
<p><code>int main (int argc, char *argv{})</code></p>
<p>or, if argc and argv are not referenced in the code,</p>
<p><code>int main (int, char *[])</code></p>
</li>
<li>
<p>If arguments are required, a check similar to the following should be made at the start of the main program.</p>
<p><code>if (argc != 3)
{
  std::cerr &lt;&lt; "Usage: " &lt;&lt; argv[0] &lt;&lt; "Alpha InputFile OutputFile" &lt;&lt; std::endl;
  return EXIT_FAILURE;
}</code></p>
</li>
<li>
<p>An example should <strong>never call exit()</strong>. If the main program executes successfully, it should</p>
<p><code>return EXIT_SUCCESS;</code></p>
<p>otherwise</p>
<p><code>return EXIT_FAILURE;</code></p>
</li>
<li>
<p>The use of SmartPointers is preferred in VTK examples.</p>
<p><code>vtkSmartPointer&lt;vtkCutter&gt; cutter = vtkSmartPointer&lt;vtkCutter&gt;::New();</code>
or</p>
<p><code>vtkNew(vtkCutter&gt; cutter;</code></p>
<p>is preferred over</p>
<p><code>vtkCutter *cutter = vtkCutter::New();</code></p>
</li>
<li>
<p>When building pipelines, the new <code>SetInputConnection()</code>, <code>GetOutputPort()</code> methods should be used instead of <code>SetInput()</code>, <code>GetOutput()</code></p>
</li>
<li>
<p>Input/Output filenames</p>
<p>When possible, filenames should be passed on the command line. This gives the examples utility beyond the data that is used in the specific example.</p>
</li>
<li>
<p>If there are just a few parameters for the example, these should be passed in as arguments. This increases the utility of the example and facilitates testing.</p>
<p>For example, this program</p>
<p><code>Delaunay3DAlpha Alpha InputPolydataFileName(.vtp) OutputUnstructuredGridFilename(.vtu)</code></p>
<p>would use the arguments in this manner</p>
<p><code>reader-&gt;SetFileName (argv[2]);
delaunay3D-&gt;SetAlpha(atof(argv[1]));
writer-&gt;SetFileName ( argv[3] );</code></p>
</li>
</ul>