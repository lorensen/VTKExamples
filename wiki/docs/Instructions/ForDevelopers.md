<p>The success of the VTK Wiki Examples depends on the contributions from
the VTK user community. If you wish to contribute to this valuable
resource, please follow these guidelines. If you are a Wiki Example
User, <a href="Instructions/ForUsers">go here</a> or a Wiki Example
Administrator <a href="Instructions/ForAdministrators">go here</a>.</p>
<p>C++, C#, Tcl, Python and Java examples are welcome! Examples should
illustrate a single concept.</p>
<div class="toc"><span class="toctitle">Contents</span><ul>
<li><a href="#follow-the-coding-guidelines">Follow the Coding Guidelines</a></li>
<li><a href="#setup-for-developement">Setup for developement</a><ul>
<li><a href="#fork-the-repository">Fork the repository</a></li>
</ul>
</li>
<li><a href="#add-the-example">Add the example</a><ul>
<li><a href="#choose-a-topic">Choose a Topic</a></li>
<li><a href="#write-the-source">Write the source</a></li>
<li><a href="#add-the-example-to-the-language-page">Add the example to the language page.</a></li>
<li><a href="#commit-your-changes-to-your-topic-branch">Commit your changes to your topic branch</a></li>
<li><a href="#push-the-changes-to-gitlab">Push the changes to gitlab</a></li>
<li><a href="#go-to-your-gitlab-project-and-generate-a-merge-request">Go to your gitlab project and generate a merge request.</a></li>
</ul>
</li>
<li><a href="#advanced-usage">Advanced usage</a><ul>
<li><a href="#add-a-description">Add a description</a></li>
<li><a href="#add-arguments-to-the-test">Add arguments to the test</a></li>
<li><a href="#review-changes-on-your-wiki">Review changes on your wiki</a></li>
</ul>
</li>
</ul>
</div>
<h1 id="follow-the-coding-guidelines">Follow the Coding Guidelines</h1>
<p>When you write an example, please follow the <a href="Instructions/Guidelines">coding guidelines</a>. Create the example on your local repository, compile and run it before you generate a merge request.</p>
<h1 id="setup-for-developement">Setup for developement</h1>
<h2 id="fork-the-repository">Fork the repository</h2>
<ol>
<li>
<p>Sign into gitlab <a href="https://gitlab.kitware.com/users/sign_in">at Kitware</a>.</p>
<p>If you do not have an account, you can register on the signin page.</p>
</li>
<li>
<p>Fork the <a href="https://gitlab.kitware.com/lorensen/VTKExamples">VTKExamples repository</a></p>
<p>A fork is a copy of a project. Forking a repository allows you to make changes without affecting the original project.</p>
</li>
<li>
<p>Clone the repository on your local machine</p>
<p><code>git clone https://YOURNAME@gitlab.kitware.com/YOURNAME/VTKExamples.git</code></p>
<p>Or, if you are using SSH:</p>
<p><code>git clone git@gitlab.kitware.com:YOURNAME/VTKExamples.git</code></p>
<p>where <strong>YOURNAME</strong> is your gitlab username.</p>
</li>
<li>
<p>Add the VTKExamples repository as a <em>remote</em> called <em>upstream</em></p>
<p><code>git remote add upstream https://gitlab.kitware.com/lorensen/VTKExamples</code></p>
</li>
<li>
<p>Before adding your examples, sync your repository with the VTKExamples repository. Remember that in order to run the following commands you need to be in the <strong>VTKExamples</strong> directory.</p>
<p><code>git fetch upstream
git checkout master
git merge upstream/master
git push</code></p>
</li>
<li>
<p>Build the VTKExamples</p>
<p><code>cd VTKExamples
mkdir build
cd build
cmake -DVTK_DIR:PATH=YOUR_VTK_BIN_DIR -DBUILD_TESTING:BOOL=ON ..
make</code></p>
<p>where <strong>YOUR_VTK_BIN_DIR</strong> is the location of your VTK build.</p>
</li>
</ol>
<h1 id="add-the-example">Add the example</h1>
<h2 id="choose-a-topic">Choose a Topic</h2>
<p>The examples are organized by topic. Current topics include Animation,
DataStructures, Filters, GeometricObjects, Images, Meshes, etc.</p>
<h2 id="write-the-source">Write the source</h2>
<ol>
<li>
<p>Create a branch in your repository</p>
<p><code>git checkout -b MyNewExample</code></p>
<p>where <strong>MyNewExample</strong> is the name of your new example.</p>
</li>
<li>
<p>Save your source code in VTKExamples/LANGUAGE/TOPIC/</p>
<p>where <strong>LANGUAGE</strong> is Cxx, Python, CSharp, or Tcl.</p>
<p>and <strong>TOPIC</strong> is the topic that you have chosen.</p>
</li>
<li>
<p>Build and test your example (<strong>NOTE:</strong> only for cxx examples)</p>
<p><code>cd VTKExamples/build
cmake ..
make
ctest -V -R MyNewExample</code></p>
</li>
<li>
<p>If your example does any rendering, the test will fail the first time and create an image in VTKExamples/build/Testing/Temporary. The image will be called Test<strong>MyNewExample</strong>.png.</p>
</li>
<li>
<p>Copy the image into: VTKExamples/Testing/Baseline/<strong>TOPIC</strong>/</p>
</li>
<li>
<p>Rerun ctest and the test should pass.</p>
</li>
</ol>
<h2 id="add-the-example-to-the-language-page">Add the example to the language page.</h2>
<p>Depending on the language of your example, edit the file <em>Cxx.md</em>, <em>Python.md</em>, <em>CSharp.md</em>, <em>Java.md</em>, or <em>Tcl.md</em>.</p>
<p>Find the section for your topic and add a line for your new example. The format of the line is:</p>
<p>[<strong>MyNewExample</strong>](<strong>LANG</strong>/<strong>TOPIC</strong>/<strong>MyNewExample</strong>) | doxygen | short description</p>
<p>where <strong>LANG</strong> is one of Cxx, Python, CSharp, Java, Tcl.</p>
<h2 id="commit-your-changes-to-your-topic-branch">Commit your changes to your topic branch</h2>
<p><code>git add MyNewExample.cxx</code></p>
<p>and if you have a baseline image,</p>
<p><code>git add Testing/Baseline/TOPIC/TestMyNewExample.png</code></p>
<p><code>git commit</code></p>
<h2 id="push-the-changes-to-gitlab">Push the changes to gitlab</h2>
<p><code>git push origin MyNewExample</code></p>
<h2 id="go-to-your-gitlab-project-and-generate-a-merge-request">Go to your gitlab project and <a href="https://docs.gitlab.com/ee/gitlab-basics/add-merge-request.html">generate a merge request</a>.</h2>
<h1 id="advanced-usage">Advanced usage</h1>
<h2 id="add-a-description">Add a description</h2>
<p>If your example could benefit from an extended description, you can create a file <strong>MyNewExample</strong>.md. Store the file along side your source code. Use <a href="https://gitlab.kitware.com/help/user/markdown">markdown</a> to format the description.</p>
<h2 id="add-arguments-to-the-test">Add arguments to the test</h2>
<p>If your example requires arguments, you will need to edit the CMakeLists.txt in the topic directory.</p>
<ol>
<li>Add the name of your example to the <em>NEEDS_ARGS</em> variable</li>
<li>Add an <em>ADD_TEST</em> line. See other CMakeLists.txt files for examples.</li>
</ol>
<h2 id="review-changes-on-your-wiki">Review changes on your wiki</h2>
<p>If you want to preview your changes on a wiki (<strong>NOTE:</strong> You must have python nstalled on your system)</p>
<ol>
<li>Install the markdown package for python. Go <a href="https://pythonhosted.org/Markdown/install.html">here</a></li>
<li>On gitlab, click the wiki button.</li>
<li>Create a home page. The contents will eventually be replaced</li>
<li>
<p>Clone the wiki repo on your local system</p>
<p><code>cd VTKExamples</code></p>
<p><code>git clone https://YOURNAME@gitlab.kitware.com/YOURNAME/VTKExamples.wiki.git wiki</code></p>
<p>Or, if you are using SSH:</p>
<p><code>git clone git@gitlab.kitware.com:YOURNAME/VTKExamples.wiki.git wiki</code>
where <strong>YOURNAME</strong> is your gitlab username.
  4. Sync your wiki with your repository
<code>./SyncWikiWithRepo.sh</code></p>
</li>
</ol>