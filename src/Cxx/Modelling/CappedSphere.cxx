#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRotationalExtrusionFilter.h>
#include <vtkSmartPointer.h>

#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace {
/**
 * Get the points for a line.
 *
 * @param angle: Length of the arc in degrees.
 * @param step: Step size in degrees.
 * @param radius: Radius of the arc.
 * @param uncapped: True if uncapped.
 * @param start: Starting angle.
 * @return: A vector of points.
 */
std::vector<std::array<double, 3>>
GetLine(double const& angle, double const& step, double const& radius,
        bool const& noCap, double const& start);

/**
 * Show the command line parameters.
 *
 * @param fn: The program name.
 */
std::string ShowUsage(std::string fn);

} // namespace

int main(int argc, char* argv[])
{
  // Our degree/radian conversions
  constexpr auto pi = 3.141592653589793238462643383279502884L; /* pi */
  auto d_r = [pi](long double d) { return pi * d / 180.0; };
  // auto r_d = [pi](long double r) { return 180 * r / pi; };
  auto isNumber = [](std::string& token) {
    return std::regex_match(
        token, std::regex(("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?")));
  };

  auto angle = 90.0;
  auto step = 1.0;
  auto radius = 1.0;
  auto uncapped = false;
  auto showLine = false;

  // The command line arguments
  std::vector<std::string> cmdVec;
  for (auto i = 1; i < argc; ++i)
  {
    cmdVec.push_back(argv[i]);
  }
  if (!cmdVec.empty())
  {
    // Look for parmeters
    auto posCnt = 0;
    for (auto token : cmdVec)
    {
      if (token == "-h" || token == "--help")
      {
        std::cout << ShowUsage(argv[0]) << std::endl;
        return EXIT_SUCCESS;
      }
      if (token == "-u" || token == "--uncapped")
      {
        uncapped = true;
      }
      if (token == "-s" || token == "--show_line")
      {
        showLine = true;
      }
      if (isNumber(token) && posCnt < 3)
      {
        switch (posCnt)
        {
        case 0:
          angle = std::stod(token);
          break;
        case 1:
          step = std::stod(token);
          break;
        case 2:
          radius = std::stod(token);
          break;
        default:
          break;
        }
        posCnt++;
      }
    }
  }
  angle = d_r(std::abs(angle));
  step = d_r(std::abs(step));
  radius = std::abs(radius);
  // With default settings set this to 45 and you get a bowl with a flat bottom.
  auto start = d_r(90);

  auto pts = GetLine(angle, step, radius, uncapped, start);

  // Setup points and lines
  auto points = vtkSmartPointer<vtkPoints>::New();
  auto lines = vtkSmartPointer<vtkCellArray>::New();
  for (auto pt : pts)
  {
    unsigned long pt_id = points->InsertNextPoint(pt.data());
    if (pt_id < pts.size() - 1)
    {
      auto line = vtkSmartPointer<vtkLine>::New();
      line->GetPointIds()->SetId(0, pt_id);
      line->GetPointIds()->SetId(1, pt_id + 1);
      lines->InsertNextCell(line);
    }
  }

  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(lines);

  // Extrude the profile to make the capped sphere
  auto extrude = vtkSmartPointer<vtkRotationalExtrusionFilter>::New();
  extrude->SetInputData(polydata);
  extrude->SetResolution(60);

  //  Visualize
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  // To see the line
  auto lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputData(polydata);

  auto lineActor = vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  lineActor->GetProperty()->SetLineWidth(4);
  lineActor->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());

  // To see the surface
  auto surfaceMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  surfaceMapper->SetInputConnection(extrude->GetOutputPort());

  auto surfaceActor = vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(surfaceMapper);
  surfaceActor->GetProperty()->SetColor(colors->GetColor3d("Khaki").GetData());

  auto ren = vtkSmartPointer<vtkRenderer>::New();
  auto renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  ren->AddActor(surfaceActor);
  if (showLine)
  {
    ren->AddActor(lineActor);
  }
  ren->SetBackground(colors->GetColor3d("LightSlateGray").GetData());

  ren->ResetCamera();
  ren->GetActiveCamera()->Azimuth(0);
  ren->GetActiveCamera()->Elevation(60);
  ren->ResetCameraClippingRange();

  renWin->SetSize(600, 600);
  renWin->Render();
  renWin->SetWindowName("CappedSphere");
  iren->Start();

  return EXIT_SUCCESS;
}

namespace {

std::vector<std::array<double, 3>>
GetLine(double const& angle, double const& step, double const& radius,
        bool const& uncapped, double const& start)
{
  auto constexpr precision = 1.0e-06;
  std::vector<std::array<double, 3>> pts;
  // Do the curved line
  auto theta = 0.0;
  while (theta <= angle)
  {
    std::array<double, 3> p{{0.0, 0.0, 0.0}};
    p[0] = radius * std::cos(start - theta);
    p[2] = radius * std::sin(theta - start);
    if (p[0] < 0)
    {
      p[0] = 0;
      pts.push_back(p);
      break;
    }
    if (std::abs(p[0]) < precision)
    {
      p[0] = 0;
    }
    if (std::abs(p[2]) < precision)
    {
      p[2] = 0;
    }
    pts.push_back(p);
    theta += step;
  }
  if (!uncapped)
  {
    // Drop a perpendicular from the last point to the x-axis
    if (pts.size() > 1)
    {
      std::array<double, 3> lastPoint = pts.back();
      if (lastPoint[0] > 0)
      {
        auto numPts = 10;
        auto interval = double(numPts) / radius;
        auto i = 1;
        while (i < numPts)
        {
          std::array<double, 3> p{{0.0, 0.0, lastPoint[2]}};
          p[0] = lastPoint[0] - i / interval;
          if (p[0] < 0)
          {
            p[0] = 0;
            pts.push_back(p);
            break;
          }
          if (std::abs(p[0]) < precision)
          {
            p[0] = 0;
          }
          if (std::abs(p[2]) < precision)
          {
            p[2] = 0;
          }
          pts.push_back(p);
          ++i;
        }
      }
      lastPoint = pts.back();
      if (lastPoint[0] > precision)
      {
        std::array<double, 3> p{{0.0, 0.0, lastPoint[2]}};
        pts.push_back(p);
      }
    }
  }
  return pts;
}

std::string ShowUsage(std::string fn)
{
  // Remove the folder (if present) then emove the extension in this order
  // since the folder name may contain perionds.
  auto last_slash_idx = fn.find_last_of("\\/");
  if (std::string::npos != last_slash_idx)
  {
    fn.erase(0, last_slash_idx + 1);
  }
  // auto period_idx = fn.rfind('.');
  // if (std::string::npos != period_idx)
  //{
  //  fn.erase(period_idx);
  //}
  std::ostringstream os;
  os << "\nusage: " << fn << " [-h] [-u] [-s] [angle] [step] [radius]\n";
  os << "\n";
  os << "Display a capped sphere.\n";
  os << "\n";
  os << "positional arguments:\n";
  os << "  angle            The length of the arc in degrees from +z to -z in "
        "the +x\n";
  os << "                   direction in the x-z plane.\n";
  os << "  step             Step size in degrees.\n";
  os << "  radius           Radius of the arc.\n";
  os << "\n";
  os << "optional arguments:\n";
  os << "  -h, --help       show this help message and exit\n";
  os << "  -u, --uncapped   Uncap the sphere.\n";
  os << "  -s, --show_line  Show the line that is rotationally extruded to "
        "make the\n";
  os << "                   surface.";
  os << std::endl;
  return os.str();
}

} // namespace
