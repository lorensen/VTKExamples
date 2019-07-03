## Introduction

The success of the VTK Examples depends on the contributions from the VTK user community. If you wish to contribute to this valuable resource, please follow these guidelines. If you are a VTK Example User, [go here](../Instructions/ForUsers) or an Example Administrator [go here](../Instructions/ForAdministrators).

C++, C#,  Python, and Java examples are welcome! Examples should illustrate a single concept.

## Follow the Coding Guidelines

When you write an example, please follow the [coding guidelines](../Instructions/Guidelines). Create the example on your local repository, compile and run it before you generate a pull request.

Some additional steps need to be done for Python C# and Java, see the sections below.

## Setup for Development

### Fork the repository

1. Sign into [github](https://github.com/login).

    If you do not have an account, you can register on the sign-in page.

2. Fork the [VTKExamples repository](https://github.com/lorensen/VTKExamples)

    A fork is a copy of a project. Forking a repository allows you to make changes without affecting the original project.

3. Enable a static web site for the examples.

    Under **Settings**, **GitHub Pages**, set the *Source* to **master branch** and click *Save*.

4. Clone the repository on your local machine

    ```
    git clone https://YOURNAME@github.com/YOURNAME/VTKExamples.git
    ```

    Or, if you are using SSH:

    ```
    git clone git@github.com:YOURNAME/VTKExamples.git
    ```

    where **YOURNAME** is your GitHub username.

5. Add the VTKExamples repository as a *remote* called *upstream*

    ```
    git remote add upstream https://github.com/lorensen/VTKExamples
    ```

6. Before adding your examples, sync your repository with the VTKExamples repository. Remember that to run the following commands, you need to be in the **VTKExamples** directory.

    ```
    git fetch upstream
    ```

    ```
    git checkout master
    ```

    ```
    git merge upstream/master
    ```

    ```
    git push
    ```

7. Build the VTKExamples

    ```
    cd VTKExamples
    ```

    ```
    cd build
    ```

    ```
    cmake -DVTK_DIR:PATH=YOUR_VTK_BIN_DIR -DBUILD_TESTING:BOOL=ON ..
    ```

    ```
    make
    ```

    where **YOUR_VTK_BIN_DIR** is the location of your VTK build.

### Add the example

#### Choose a Topic

The examples are organized by topic. Current topics include Animation,
DataStructures, Filters, GeometricObjects, Images, Meshes, etc.

#### Write the source

**Note**: Steps 4, 5 and 7 apply to C++. For Python, Java, and C# see the steps in the section **Steps for Python, Java and C#**.

1. Create a branch in your repository

    ```
    git checkout -b MyNewExample
    ```

    where **MyNewExample** is the name of your new example.

2. Check the:

    - [Cxx available snippets](/Cxx/Snippets).
    - [Python available snippets](/Cxx/Snippets).
    - [Java available snippets](/Cxx/Snippets).

3. Save your source code in VTKExamples/src/**LANGUAGE**/**TOPIC**/

    where **LANGUAGE** is Cxx, Python, CSharp or Java.

    and **TOPIC** is the topic that you have chosen.

4. Build and test your example (**NOTE:** only for cxx examples)

   - for Cxx

        ```
        cd VTKExamples/build
        ```

        ```
        cmake ..
        ```

        ```
        make
        ```

        ```
        ctest -V -R MyNewExample
        ```

        Note: If **MyNewExample** is not built, then in the directory where you put the file do:

        ```
        touch CMakeLists.txt
        ```

5. If your C++ example does any rendering, the test will fail the first time and create an image in VTKExamples/build/Testing/Temporary. The image will be called Test**MyNewExample**.png.

6. Copy the image into: VTKExamples/src/Testing/Baseline/**LANG**/**TOPIC**/. For Python and other languages, create an image with the proper name using a screen capture and copy that image into the proper location.

7. Rerun ctest and the test should pass.

#### Steps for Python, Java and C#

If you are basing your code on a Cxx example use the same name as the Cxx example. This ensures that cross-referencing works.

Keep the same directory structure as that in Cxx.

- Follow steps 1-3 above.
- Manually create a test image if your example does any rendering. The image should be called Test**MyNewExample**.png.

  The following snippets can be used to write the image out:

  - [WriteImage](https://lorensen.github.io/VTKExamples/site/Python/Snippets/WriteImage/) for Python
  - [WriteImage](https://lorensen.github.io/VTKExamples/site/Java/Snippets/WriteImage/) for Java

- Then follow step 6 above

#### Add the example to the language page.

Depending on the language of your example, edit the file *Cxx.md*, *Python.md*, *CSharp.md*, or *Java.md*.

Find the section for your topic and add a line for your new example. The format of the line is:

\[**MyNewExample**\]\(/**LANG**/**TOPIC**/**MyNewExample**\) | doxygen | short description

where **LANG** is one of Cxx, Python, CSharp, Java.

#### Commit your changes to your topic branch

```
git add MyNewExample.cxx
```

and if you have a baseline image,

```
git add Testing/Baseline/LANG/TOPIC/TestMyNewExample.png
```

```
git commit
```

#### Push the changes to GitHub

```
git push origin MyNewExample
```

#### Go to your GitHub project and [generate a pull request](https://help.github.com/articles/creating-a-pull-request/).

### Advanced usage

#### Add a description

If your example could benefit from an extended description, you can create a file **MyNewExample**.md. Store the file alongside your source code. Use [markdown](https://guides.github.com/features/mastering-markdown/) to format the description.

#### Add arguments to the test

If your example requires arguments, you will need to edit the *CMakeLists.txt* in the topic directory.

1. Add the name of your example to the *NEEDS_ARGS* variable

2. Add an *ADD_TEST* line. See other *CMakeLists.txt* files for examples.

#### Add extra files to a C++ example

Most C++ examples consist of one file. If other files are required,
place them in the same directory as the example. Then add a file with
the same prefix as the example name and a *.extras* suffix. List each
extra filename in the *.extras* file, one filename per line.

!!! warning
    If you add extra files to the example, but do not add their filenames to the *.extras* file, they will appear in the left-hand file menus **and** will not be included in the tar file for the example.

#### Review changes in a browser

If you want to preview your changes in a browser (**NOTE:** You must have Python installed on your system)

  1. Install the markdown package for Python. Go [here](https://pythonhosted.org/Markdown/install.html)

  2. Install the material theme for markdown. Go [here](http://squidfunk.github.io/mkdocs-material/#quick-start).

  3. Sync your site with your repository

    ```
    ./src/SyncSiteWithRepo.sh https::/github.com/**YOUR_NAME**/VTKExamples
    ```

  4. After a few minutes go to https://**YOUR_NAME**.github.io/VTKExamples/ to see your changes before issuing your pull request.
