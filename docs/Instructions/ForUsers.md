<p>If you want to use <a href="https://gitlab.kitware.com/lorensen/VTKExamples/wikis/home">VTK Examples</a> you have several options. If you are a Wiki Example Developer, <a href="Instructions/ForDevelopers">go here</a> or a Wiki Example Administrator <a href="Instructions/ForAdministrators">go here</a>.</p>
<h2 id="build-an-example">Build an example</h2>
<p>At the bottom of each example page, there are instructions on how to build the example.</p>
<h2 id="build-all-of-the-examples">Build all of the examples</h2>
<p>If you are really getting excited about learning VTK and are tried of
downloading individual examples you can build them all.</p>
<ol>
<li>
<p>As a VTK Remote module
   When you configure your VTK build, set Module_WikiExamples:BOOL=ON and rebuild VTK.</p>
</li>
<li>
<p>Download a <a href="https://gitlab.kitware.com/lorensen/VTKExamples/repository/archive.zip?ref=master">zip</a>
or <a href="https://gitlab.kitware.com/lorensen/VTKExamples/repository/archive.tar.gz?ref=master">tar</a> file containing the source</p>
</li>
<li>
<p>Clone the VTK examples repository</p>
</li>
</ol>
<p><code>git clone https://lorensen@gitlab.kitware.com/lorensen/VTKExamples.git</code></p>
<h3 id="update-the-examples-repository">Update the examples repository</h3>
<p>If you cloned the examples repository, you can get the latest updates:</p>
<p><code>cd VTKWikiExamples
git pull https://github.com/lorensen/VTKWikiExamples.git
cd ../VTKWikiExamples-build
cmake ../VTKWikiExamples
make</code></p>
<h3 id="run-all-of-the-examples">Run all of the examples</h3>
<p><code>ctest</code></p>