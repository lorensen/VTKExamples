<p>Wiki Example Administrators have write access to the [https://github.com/lorensen/VTKWikiExamples.git git repository]. Wiki Example Developers do not need write access to the repository since the definitive copy of the source code resides on the Wiki. If you are a Wiki Example User [[VTK/Examples/Instructions/ForUsers| go here]] or a Wiki Example Developer[[VTK/Examples/Instructions/ForDevelopers| go here]].</p>
<p>Wiki Example Administrators maintain the CMakeLists.txt files, example input files, example regression baseline files and synchronization scripts.</p>
<div class="toc"><span class="toctitle">Contents</span><ul>
<li><a href="#organization-of-the-example-repository">Organization of the Example Repository</a></li>
<li><a href="#administrator-tasks">Administrator Tasks</a><ul>
<li><a href="#clone-repository-with-write-access">Clone repository with write access</a></li>
<li><a href="#add-a-new-topic">Add a new topic</a></li>
<li><a href="#create-a-cmakeliststxt-file">* Create a CMakeLists.txt file</a></li>
</ul>
</li>
<li><a href="#_1"></a></li>
<li><a href="#build-all-cxx-files-in-the-directory">Build all .cxx files in the directory</a></li>
<li><a href="#testing">Testing</a><ul>
<li><a href="#add-a-test-that-requires-arguments">Add a test that requires arguments</a></li>
<li><a href="#add-a-regression-baseline-image">Add a regression baseline image</a></li>
<li><a href="#add-example-input-data">Add example input data</a></li>
<li><a href="#add-a-testing-machine-to-the-dashboard">Add a testing machine to the dashboard</a></li>
<li><a href="#check-the-dashboard-frequently">Check the dashboard frequently!</a></li>
<li><a href="#fixing-build-problems">Fixing build problems</a></li>
</ul>
</li>
</ul>
</div>
<h1 id="organization-of-the-example-repository">Organization of the Example Repository</h1>
<p>The wiki examples are stored in a [https://github.com/lorensen/VTKWikiExamples.git git repository] hosted at [http://www.github.com/ github.com]. The repository contains several types of files:</p>
<ul>
<li>
<p>Top Level [https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CMakeLists.txt ''CMakeLists.txt''] file
:This cmake file locates and includes the VTK_USE_FILE and adds directories for each of the topics</p>
</li>
<li>
<p>[https://github.com/lorensen/VTKWikiExamples/tree/master/mwclient ''mwclient''] files
:[http://sourceforge.net/projects/mwclient/ mwclient] is a python framework to access MediaWiki's API. The ScrapeWiki script uses it to pull pages from the wiki and create example source files.</p>
</li>
<li>
<p>[https://github.com/lorensen/VTKWikiExamples/blob/master/Admin/ScrapeWiki ''Admin/ScrapeWiki'']
: This is a python script that uses [http://sourceforge.net/projects/mwclient/ mwclient] to access the pages of the wiki. It looks for pages in [[VTK/Examples|VTK/Examples]]. For each page, it looks for second level headings and stores the code that lies between <pre><source> and </source></pre> into a file in the proper topic subdirectory. Anyone, including users, can run this script. It updates the current directory with changes or new examples. If you run this script, be sure to re-run cmake.</p>
</li>
<li>
<p>[https://github.com/lorensen/VTKWikiExamples/blob/master/Admin/UploadBaselines ''Admin/UploadBaselines'']
: This is a python script that uses [http://sourceforge.net/projects/mwclient/ mwclient] to upload example baselines to the Wiki. The baselines are located in the Wiki git repository in [https://github.com/lorensen/VTKWikiExamples/tree/master/Testing/Baseline Testing/Baseline]. The script walks through the git baselines and checks to see if the baselines exist on the Wiki. If the baseline does not exist on the Wiki, the script uploads it. If the baseline does exist on the Wiki the [http://en.wikipedia.org/wiki/MD5 md5 hash] is checked to see if the image has changed.</p>
</li>
<li>
<p>[https://github.com/lorensen/VTKWikiExamples/blob/master/Admin/CheckPagesForImages ''Admin/CheckPagesForImages'']
: This is a python script that uses [http://sourceforge.net/projects/mwclient/ mwclient] to check each example to see if it should have a reference to a baseline image. If a baseline image exists for an example, the script looks for a <nowiki>''<div></div>''</nowiki> tag. This tag contains a reference for the baseline image for the example. If the tag is not found, the script generates a cut/paste line to edit the page as well as a cut/paste line that has the proper <nowiki>''<div></div>''</nowiki> for the baseline image.</p>
</li>
<li>
<p>[https://github.com/lorensen/VTKWikiExamples/blob/master/SyncRepoWithWiki.sh ''SyncRepoWithWiki.sh'']
: This shell script runs ''ScrapeWiki'' to create source files for all wiki examples. Then it uses git to add, remove or modify the source code. The resulting repository is pushed to [https://github.com/lorensen/VTKWikiExamples the github repository]. The script is run nightly by a cronjob on a designated host (currently BillsBasement). '''NOTE: this script should only be run by one individual (currently Lorensen)'''.</p>
</li>
<li>
<p>[https://github.com/lorensen/VTKWikiExamples/tree/master/Testing/Data ''Testing/Data'']
: Some examples require input data. A small number of datasets are distributed with the examples and are used by the regression tests. All administrators can add input data.</p>
</li>
<li>
<p>[https://github.com/lorensen/VTKWikiExamples/tree/master/Testing/Baseline ''Testing/Baseline'']
: Examples that produce images are regression tested. [http://www.cmake.org/Wiki/CMake_Testing_With_CTest ctest] runs the examples and when appropriate, compares the output  of the example to a baseline image. Each topic has a directory in Testing/Baseline. All administrators can add and modify baseline images. </p>
</li>
<li>
<p>Topic Directories
:Examples for each topic reside in a directory with the topic name. If the examples in a topic directory should be compiled and run, the topic directory has a CMakeLists.txt file. All administrators can create topic directories and CMakeLists.txt files.</p>
</li>
</ul>
<h1 id="administrator-tasks">Administrator Tasks</h1>
<h2 id="clone-repository-with-write-access">Clone repository with write access</h2>
<p>Exactly the same as cloning anonymously:</p>
<p>git clone https://github.com/lorensen/VTKWikiExamples.git</p>
<h2 id="add-a-new-topic">Add a new topic</h2>
<ul>
<li>Create a topic subdirectoy
 mkdir '''''MyTopic'''''
 cd '''''MyTopic'''''</li>
</ul>
<h2 id="create-a-cmakeliststxt-file">* Create a CMakeLists.txt file</h2>
<p><source lang='cmake'>
PROJECT (MyTopic)</p>
<p>SET(KIT MyTopic)
SET(KIT_LIBS vtkHybrid)</p>
<p>IF(NOT WikiExamples_BINARY_DIR)
  FIND_PACKAGE(VTK REQUIRED)
  INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)</p>
<h1 id="_1"></h1>
<h1 id="build-all-cxx-files-in-the-directory">Build all .cxx files in the directory</h1>
<p>FILE(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${EXAMPLE} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)</p>
<h1 id="testing">Testing</h1>
<p>INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
</source></p>
<hr />
<ul>
<li>Add the directory to the main CMakeLists.txt file
 ADD_SUBDIRECTORY(MyTopic)</li>
<li>Add and commit the new topic directory and CMakeLists.txt file's to the local repository
 cd ..
 git add MyTopic
 git add MyTopic/CMakeLists.txt
 git commit -m "ENH: Added topic MyTopic and CMakeLists.txt file." CMakeLists.txt MyTopic/CMakeLists.txt</li>
<li>Push to the master repository
 git push</li>
</ul>
<p>If you get an error, you should make sure your rsa key is uploaded to github and that you have done:
 git config remote.origin.pushurl https://github.com/lorensen/VTKWikiExamples.git</p>
<h2 id="add-a-test-that-requires-arguments">Add a test that requires arguments</h2>
<p>By default, the ''CMakeLists.txt'' in a topic directory creates a small test driver for each .cxx file it finds. Then it creates an '''ADD_TEST''' command. The default '''ADD_TEST''' command assumes that the test has no arguments.</p>
<p>Some tests require arguments. To prevent the '''ADD_TEST''' from being generated, add any examples that require arguments to the list '''NEEDS_ARGS''':</p>
<p><source lang="cmake">
  SET(NEEDS_ARGS 
    Example1
    Example2
  )
  INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
</source></p>
<p>Then, provide an '''ADD_TEST''' for each:</p>
<p><source lang="cmake">
  ADD_TEST(${KIT}-Example1 ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
    TestExample1  arg1 arg2)
  ADD_TEST(${KIT}-Example2 ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
    TestExample2  arg1 arg2 arg3)
</source></p>
<h2 id="add-a-regression-baseline-image">Add a regression baseline image</h2>
<p>Any example that uses a render window interactor will expect to find a baseline image for regression testing. The first time the test for the example is run, using ctest, the test will fail and report that a baseline image could not be found.</p>
<ul>
<li>
<p>The test for the example will produce a test output image in VTKWikiExamples-'''''build'''''/Testing/Temporary. The name of the image will be Test'''''ExampleName'''''.png</p>
</li>
<li>
<p>With an image viewer, verify that the image is correct.</p>
</li>
<li>
<p>Copy the image from Testing/Temporary into VTKWikiExamples/Testing/Baseline/'''''Topic'''''/Test'''ExampleName'''.png</p>
</li>
<li>
<p>If there is more than one possible output image, name the image VTKWikiExamples/Testing/Baseline/'''''Topic'''''/Test'''ExampleName'''_1.png instead</p>
</li>
<li>
<p>Rerun ctest -V -R Test'''''ExampleName'''''
: The test should now pass</p>
</li>
<li>
<p>Add the baseline to the repository
 git add Testing/Baseline/Topic/TestExampleName.png
 git commit -m "ENH: Added baseline for TestExampleName regression test
 git push</p>
</li>
<li>
<p>Overnight, a script automatically produces and uploads a file with the name 
 VTK_Examples_Baseline_'Folder'_Test'TestName'.png
You must add this tag to the top of the example page:</p>
</li>
</ul>
<p><nowiki>
 <div class="floatright">[[File:VTK_Examples_Baseline_'Folder'_Test'TestName'.png]]</div>
</nowiki></p>
<p>An example is:
<nowiki>
 <div class="floatright">[[File:VTK_Examples_Baseline_Filtering_TestLandmarkTransform.png]]</div>
</nowiki></p>
<h2 id="add-example-input-data">Add example input data</h2>
<p>We like to keep the example data to a small number of small files. If you must add input data for the tests:</p>
<p>git add Testing/Data/MyData.whatever
 git commit -m "ENH: Added new example input data." Testing/Data/Mydata.whatever
 git push</p>
<h2 id="add-a-testing-machine-to-the-dashboard">Add a testing machine to the dashboard</h2>
<ul>
<li>The simplest way is to add an Experimental build
 make Experimental</li>
<li>Or a Nightly build
 make Nightly</li>
<li>Or create a ctest script. A starting ctest script (SampleBuildTest.cmake) is created when you run cmake. You should edit this line so we know where the submissions is coming from:</li>
</ul>
<p><source lang="cmake">
set(CTEST_SITE "BillsBasement")
</source></p>
<p>Then you should comment one of these, depending on which type of build you would like to submit.</p>
<p><source lang="cmake">
set(DASHBOARD Nightly)
set(DASHBOARD Experimental)
</source></p>
<hr />
<p>:Copy the edited SampleBuildTest.cmake to '''''/home/foo/'''''WikiExamples.ctest. This can be run nightly from a cronjob (crontab -e)</p>
<p>0 23 * * * ctest -S '''''/home/foo/'''''WikiExamples.ctest -V  &amp;&gt; '''''/home/foo/'''''WikiExamplesNightly.log</p>
<h2 id="check-the-dashboard-frequently">Check the dashboard frequently!</h2>
<p>http://www.cdash.org/CDash/index.php?project=VTKWikiExamples</p>
<h2 id="fixing-build-problems">Fixing build problems</h2>
<p>If you notice that 'make' fails with a compiler error, you should attempt to fix the error in the source tree to ensure it works before copying the fix to the wiki. Once you change the source file, you will need to 'make rebuild_cache' so to re-create the Cxx/[directory]/CMakeFiles/IOCxxTests.dir/Test[ExampleName].cxx file that is actually built.</p>