#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkDelaunay2D.h>
#include <vtkMath.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkCamera.h>


int main(int, char *[])
{
    // Create parabola over a grid of points
    vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();

    int GridSize = 20;
    double z;
    for (int x = -GridSize; x < GridSize; x++)
    {
        for (int y = -GridSize; y < GridSize; y++)
        {
            z = vtkMath::Random(-1, 1)+ 0.05*x*x + 0.05*y*y;
            points->InsertNextPoint(x, y, z);
        }
    }

    // Add the grid points to a polydata object
    vtkSmartPointer<vtkPolyData> inputPolyData =
        vtkSmartPointer<vtkPolyData>::New();
    inputPolyData->SetPoints(points);

    // Triangulate the grid points
    vtkSmartPointer<vtkDelaunay2D> delaunay =
        vtkSmartPointer<vtkDelaunay2D>::New();
    delaunay->SetInputData(inputPolyData);
    delaunay->Update();

    vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilter =
        vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    smoothFilter->SetInputConnection(delaunay->GetOutputPort());
    smoothFilter->SetNumberOfIterations(15);
    smoothFilter->SetRelaxationFactor(0.1);
    smoothFilter->FeatureEdgeSmoothingOff();
    smoothFilter->BoundarySmoothingOn();
    smoothFilter->Update();

    // Update normals on newly smoothed polydata
    vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputConnection(smoothFilter->GetOutputPort());
    normalGenerator->ComputePointNormalsOn();
    normalGenerator->ComputeCellNormalsOn();
    normalGenerator->Update();

    vtkSmartPointer<vtkPolyDataMapper> inputMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    inputMapper->SetInputConnection(delaunay->GetOutputPort());
    vtkSmartPointer<vtkActor> inputActor =
        vtkSmartPointer<vtkActor>::New();
    inputActor->SetMapper(inputMapper);

    vtkSmartPointer<vtkPolyDataMapper> smoothedMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    smoothedMapper->SetInputConnection(normalGenerator->GetOutputPort());
    vtkSmartPointer<vtkActor> smoothedActor =
        vtkSmartPointer<vtkActor>::New();
    smoothedActor->SetMapper(smoothedMapper);

    // There will be one render window
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(600, 300);

    // And one interactor
    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
    double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

    // Setup both renderers
    vtkSmartPointer<vtkRenderer> leftRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(leftRenderer);
    leftRenderer->SetViewport(leftViewport);
    leftRenderer->SetBackground(.6, .5, .4);

    vtkSmartPointer<vtkRenderer> rightRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(rightRenderer);
    rightRenderer->SetViewport(rightViewport);
    rightRenderer->SetBackground(.4, .5, .6);

    // Add the input parabola to the left and the smoothed parabola to the right
    leftRenderer->AddActor(inputActor);
    rightRenderer->AddActor(smoothedActor);

    leftRenderer->ResetCamera();
    leftRenderer->GetActiveCamera()->Azimuth(130);
    leftRenderer->GetActiveCamera()->Elevation(-80);

    rightRenderer->ResetCamera();
    rightRenderer->GetActiveCamera()->Azimuth(130);
    rightRenderer->GetActiveCamera()->Elevation(-80);

    renderWindow->Render();
    interactor->Start();

    return EXIT_SUCCESS;
}
