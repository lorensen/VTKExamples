# About the Examples

The VTK source distribution includes a sizeable number of [examples](https://gitlab.kitware.com/vtk/vtk/blob/master/Examples).
The goal of the VTK examples is to illustrate specific VTK concepts in a consistent and simple format. Some have been there since the inception of the toolkit. These examples have been subject to peer review and revision over the years. However, these examples only cover a small part of the capabilities of VTK.

Hundreds of tests are distributed with the toolkit source. The tests reside in ''Kit''/Testing directories (for example, Filters/Points/Testing) in the source distribution. However, these tests are meant to exercise the toolkit rather than illustrate how to use it. For the most part, the tests are not good educational resources.

We are now using a gitlab wiki to provide examples that will help both new and experienced VTK users. The wiki can be used to find examples that answer questions like, "How do I extract normals from a filter's output?", "How do I generate models from segmented data?", and "How do I compute the area of a triangle?", just to name a few.

Over time we hope that the examples will answer many of the users' questions. Some questions won't have a solution in the current example repertoire. For those questions, we encourage the user to create a simple example that illustrates either a dilemma or a new solution.

# Examples are available for the following programming languages:
* [C++](Cxx/)
* [Python](Python/)
* [Java](Java/)
* [Tcl](Tcl/)
* [C#](CSharp/)
* [C](C/)

The above examples demonstrate how to *use* VTK functionalities. There are also examples specifically to demonstrate how to write code as a VTK filter using VTK techniques. This is helpful so that your custom code can be called in a fashion that other people are already familiar with. It is also necessary if you plan to contribute your classes to VTK.

# Information about the Wiki Examples
* [Users](Instructions/ForUsers/): If you just want to use the Wiki Examples, this is the place for you. You will learn how to search for examples, build a few examples and build all of the examples.
* [Developers](Instructions/ForDevelopers/): If you want to contribute examples, this section explains everything you need to know. You will learn how to add a new example and the guidelines for writing an example.
* [Adminstratore](Instructions/ForAdministrators/): This section is for a Wiki Example Administrators or people want to learn more about the process. You will learn how the Wiki Examples repository is organized, how the repository is synced to the wiki and how to add new topics, tests and regression baselines.

# How can I help?
This project of creating examples has grown very large. We are always looking for people to help the cause. You can help by:

* Adding new examples (see procedure [here](Instructions/ForDevelopers/))
* Proof reading existing examples, for correctness, style, and clarity.
* Add comments to existing examples where they are unclear.
