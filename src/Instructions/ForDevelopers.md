The success of the VTK Wiki Examples depends on the contributions from
the VTK user community. If you wish to contribute to this valuable
resource, please follow these guidelines. If you are a Wiki Example
User, [go here](Instructions/ForUsers) or a Wiki Example
Administrator [go here](Instructions/ForAdministrators).

C++, C#, Tcl, Python and Java examples are welcome! Examples should
illustrate a single concept.

[TOC]

# Follow the Coding Guidelines

When you write an example, please follow the [coding guidelines](Instructions/Guidelines). Create the example on your local repository, compile and run it before you generate a merge request.

# Setup for developement

## Fork the repository

1. Sign into gitlab [at Kitware](https://gitlab.kitware.com/users/sign_in).

    If you do not have an account, you can register on the signin page.

2. Fork the [VTKExamples repository](https://gitlab.kitware.com/lorensen/VTKExamples)

    A fork is a copy of a project. Forking a repository allows you to make changes without affecting the original project.

3. Clone the repository on your local machine

    ```
    git clone https://YOURNAME@gitlab.kitware.com/YOURNAME/VTKExamples.git
    ```

    Or, if you are using SSH:

    ```
    git clone git@gitlab.kitware.com:YOURNAME/VTKExamples.git
    ```

    where **YOURNAME** is your gitlab username.

4. Add the VTKExamples repository as a *remote* called *upstream*

    ```
    git remote add upstream https://gitlab.kitware.com/lorensen/VTKExamples
    ```

5. Before adding your examples, sync your repository with the VTKExamples repository. Remember that in order to run the following commands you need to be in the **VTKExamples** directory.

    ```
    git fetch upstream
    git checkout master
    git merge upstream/master
    git push
    ```

6. Build the VTKExamples

    ```
    cd VTKExamples
    mkdir build
    cd build
    cmake -DVTK_DIR:PATH=YOUR_VTK_BIN_DIR -DBUILD_TESTING:BOOL=ON ..
    make
    ```

    where **YOUR_VTK_BIN_DIR** is the location of your VTK build.

# Add the example

## Choose a Topic

The examples are organized by topic. Current topics include Animation,
DataStructures, Filters, GeometricObjects, Images, Meshes, etc.

## Write the source

1. Create a branch in your repository

    ```
    git checkout -b MyNewExample
    ```

    where **MyNewExample** is the name of your new example.

2. Save your source code in VTKExamples/LANGUAGE/TOPIC/

    where **LANGUAGE** is Cxx, Python, CSharp, or Tcl.

    and **TOPIC** is the topic that you have chosen.

3. Build and test your example (**NOTE:** only for cxx examples)

    ```
    cd VTKExamples/build
    cmake ..
    make
    ctest -V -R MyNewExample
    ```

4. If your example does any rendering, the test will fail the first time and create an image in VTKExamples/build/Testing/Temporary. The image will be called Test**MyNewExample**.png.

5. Copy the image into: VTKExamples/Testing/Baseline/**TOPIC**/

6. Rerun ctest and the test should pass.

## Add the example to the language page.

Depending on the language of your example, edit the file *Cxx.md*, *Python.md*, *CSharp.md*, *Java.md*, or *Tcl.md*.

Find the section for your topic and add a line for your new example. The format of the line is:

\[**MyNewExample**\]\(**LANG**/**TOPIC**/**MyNewExample**\) | doxygen | short description

where **LANG** is one of Cxx, Python, CSharp, Java, Tcl.

## Commit your changes to your topic branch

```
git add MyNewExample.cxx
```

and if you have a baseline image,

```
git add Testing/Baseline/TOPIC/TestMyNewExample.png
```

```
git commit
```

## Push the changes to gitlab

```
git push origin MyNewExample
```

## Go to your gitlab project and [generate a merge request](https://docs.gitlab.com/ee/gitlab-basics/add-merge-request.html).

# Advanced usage

## Add a description

If your example could benefit from an extended description, you can create a file **MyNewExample**.md. Store the file along side your source code. Use [markdown](https://gitlab.kitware.com/help/user/markdown) to format the description.

## Add arguments to the test

If your example requires arguments, you will need to edit the CMakeLists.txt in the topic directory.

1. Add the name of your example to the *NEEDS_ARGS* variable
2. Add an *ADD_TEST* line. See other CMakeLists.txt files for examples.

## Review changes on your wiki

If you want to preview your changes on a wiki (**NOTE:** You must have python nstalled on your system)

  1. Install the markdown package for python. Go [here](https://pythonhosted.org/Markdown/install.html)
  1. On gitlab, click the wiki button.
  2. Create a home page. The contents will eventually be replaced
  3. Clone the wiki repo on your local system

    ```
    cd VTKExamples
    ```

    ```
    git clone https://YOURNAME@gitlab.kitware.com/YOURNAME/VTKExamples.wiki.git wiki
    ```

    Or, if you are using SSH:

    ```
    git clone git@gitlab.kitware.com:YOURNAME/VTKExamples.wiki.git wiki
    ```
    where **YOURNAME** is your gitlab username.
  4. Sync your wiki with your repository
    ```
    ./SyncWikiWithRepo.sh
    ```
