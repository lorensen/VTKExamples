### Description
<!-- __NOTOC__ -->
The success of the VTK Wiki Examples depends on the contributions from the VTK user community. If you wish to contribute to this valuable resource, please follow these guidelines. If you are a Wiki Example User, [here]] or a Wiki Example Administrator [[VTK/Examples/Instructions/ForAdministrators|go here]]([VTK/Examples/Instructions/ForUsers|go).

==Create an Example==
C++, C#, Tcl, Python and Java examples are welcome! Examples should illustrate a single concept.

==Follow the Coding Guidelines==
When you write an example, please follow the [guidelines]]([VTK/Examples/GuideLines|coding). Create the example on your local system, compile and run it before you store it on the wiki.
==Choose a Topic==
The examples are organized by topic. Current topics include Animation, DataStructures, Filters, GeometricObjects, Images, Meshes, etc.
==Create a Wiki Page==
* If you don't already have a account, [create an account] or [http://vtk.org/Wiki/index.php?title=Special:UserLogin&returnto=Special:UserLogout login to an existing account](http://vtk.org/Wiki/index.php?title=Special:UserLogin&type=signup).
* Go to the page for the language of the example
* Click "Edit" in the topic section where you want to add an example.
* Create a new page and a link to the new page by adding:

 [| '''''What you want to display as the link''''']]([VTK/Examples/''Language''/''Topic''/'''''MyExample''''')
   where ''Language'' is one of Cxx, Tcl, Java, Python
The page name should be the same name as the example.

* When you save these changes, there be a red link. When you click this link, it immediately brings you to the "Edit" page of the new page.
* Add the content and save it.
* The link automatically turns blue (so it now goes to the "page" page instead of the "edit" page).
* Precede the code with a heading that defines the filename of the example. Ensure there are no spaces between the == and the filename. The name is important!. When the example is stored in the Wiki Examples source code repository, it will have this filename and reside in the '''''Topic''''' directory.

<pre>
