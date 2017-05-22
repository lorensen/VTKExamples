#ifdef WIN32
#include <windows.h>
#include <vtkWin32OpenGLRenderWindow.h>
#elif __APPLE__
#include <vtkCocoaRenderWindow.h>
#else
#include <vtkXOpenGLRenderWindow.h>
#endif
#include <vtkgl.h>

#include "Options.h"
#include <cassert>

#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPointData.h>
#include <vtkSphereSource.h>
#include <vtkOutlineSource.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkProperty.h>

#include <vtkRenderer.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkVolume16Reader.h>

#include <vtkTransform.h>
#include <vtkVolume.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkCommand.h>

#include <vtkRenderState.h>
#include <vtkRenderPass.h>
#include <vtkCameraPass.h>
#include <vtkLightsPass.h>
#include <vtkOpaquePass.h>
#include <vtkDepthPeelingPass.h>
#include <vtkTranslucentPass.h>
#include <vtkOverlayPass.h>
#include <vtkVolumetricPass.h>
#include <vtkRenderPassCollection.h>
#include <vtkSequencePass.h>


#include "vtkSmartPointer.h"
#define vtkNew(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()


class CRenderCommand : public vtkCommand
{
public:
	static CRenderCommand *New() { return new CRenderCommand; }
	void SetRenderPass(vtkRenderPass* p, vtkRenderState * s, std::vector<vtkProp*> &props)
	{
		renderPass = p;
		renderState = s;
		renderProps = props;
	}

	// This gets executed when the Renderer completes the rendering
	// (but before exiting UpdateGeometry()
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkRenderer *renderer = vtkRenderer::SafeDownCast(caller);
		vtkRenderWindow* rw = renderer->GetRenderWindow();

		renderState->GetRenderer()->GetRenderWindow()->SetSize(rw->GetSize());

		vtkCamera* cam = renderer->GetActiveCamera();
		vtkCamera* cam2 = renderState->GetRenderer()->GetActiveCamera();		
		
		cam2->SetFocalPoint(cam->GetFocalPoint());
		cam2->SetPosition(cam->GetPosition());
		cam2->SetViewUp(cam->GetViewUp());
		cam2->SetParallelScale(cam->GetParallelScale());
		cam2->SetParallelProjection(cam->GetParallelProjection());
		cam2->SetClippingRange(cam->GetClippingRange());


		renderState->SetPropArrayAndCount(&renderProps[0], renderProps.size());

		renderPass->Render(renderState);
	}
	vtkRenderPass *renderPass;
	vtkRenderState *renderState;
	std::vector<vtkProp*> renderProps;
};

vtkVolume *CreateVolume(const char * prefix);
vtkActor  *CreateActor(double opacity = 1.0);
vtkActor  *CreateOutline(double *bb);
void MergeBounds(double *bounds, const double *b);


int main (int argc, char **argv)
{
	std::string fileName = "PATH/TO/vtkdata-5.6.1/Data/headsq/quarter";
	double opacity = 1.0;
	int UseCamera = 1;
	int UseLights = 1;

	// Create main renderer and render window
	vtkNew(vtkRenderer, ren1);
	ren1->SetBackground(0.5,0.5,0.5);
	vtkNew(vtkLight,light);
	ren1->AddLight(light);
	vtkNew(vtkRenderWindow, renWin1);
	renWin1->SetAlphaBitPlanes(1);
	renWin1->SetMultiSamples(0);
	renWin1->SetSize(500,500);
	renWin1->Render();// force render window to create context
	renWin1->AddRenderer(ren1);
	vtkNew(vtkRenderWindowInteractor, iren);
	iren->SetRenderWindow(renWin1);


	// Create another renderer, and dummy render window with same context as first
	vtkNew(vtkRenderer, ren2);
	ren2->EraseOff();
	ren2->AddLight(light);
	vtkNew(vtkRenderWindow, renWin2);
	renWin2->EraseOff();
	renWin2->SetAlphaBitPlanes(1);
	renWin2->SetMultiSamples(0);
	renWin2->DoubleBufferOn();
	renWin2->SwapBuffersOff();
	renWin2->AddRenderer(ren2);
#ifdef WIN32
	vtkWin32OpenGLRenderWindow * rw1 = vtkWin32OpenGLRenderWindow::SafeDownCast(renWin1);
	vtkWin32OpenGLRenderWindow * rw2 = vtkWin32OpenGLRenderWindow::SafeDownCast(renWin2);
	rw2->SetWindowId(rw1->GetWindowId());
	rw2->SetParentId(rw1->GetGenericParentId());
	rw2->SetDeviceContext((HDC)renWin1->GetGenericContext());
	rw2->SetContextId((HGLRC)renWin1->GetGenericDisplayId());
#elif __APPLE__
	// Assumes vtkCocoaRenderWindow
	vtkCocoaRenderWindow * rw1 = vtkCocoaRenderWindow::SafeDownCast(renWin1);
	vtkCocoaRenderWindow * rw2 = vtkCocoaRenderWindow::SafeDownCast(renWin2);
	rw2->SetWindowId(rw1->GetWindowId());
	rw2->SetParentId(rw1->GetParentId());
	rw2->SetContextId(rw1->GetContextId());
	rw2->SetRootWindow(rw1->GetRootWindow());
#else
	// Untested !!
	vtkXOpenGLRenderWindow * rw1 = vtkXOpenGLRenderWindow::SafeDownCast(renWin1);
	vtkXOpenGLRenderWindow * rw2 = vtkXOpenGLRenderWindow::SafeDownCast(renWin2);
	rw2->SetDisplayId(rw1->GetDisplayId());
	rw2->SetWindowId(rw1->GetWindowId());
#endif


	// Create actors & volumes
	vtkVolume * volume = NULL;
	if(fileName.empty())
		volume = CreateVolume();
	else
		volume = CreateVolume(fileName.c_str());
	vtkActor  * actor = CreateActor(opacity);

	// Create bounding box actor
	double bounds[6];
	actor->GetBounds(bounds);
	MergeBounds(bounds, volume->GetBounds());
	vtkActor * outline = CreateOutline(bounds);
	ren1->AddActor(outline);
	ren1->AddActor(actor);


	// Create render passes and state
	vtkNew(vtkCameraPass,cameraPass);
	vtkNew(vtkLightsPass,lightsPass);
	vtkNew(vtkOpaquePass, opaquePass);
	vtkNew(vtkDepthPeelingPass, peelingPass);
	vtkNew(vtkVolumetricPass, volumetricPass);
	vtkNew(vtkOverlayPass, overlayPass);

	vtkNew(vtkTranslucentPass,translucent);
	peelingPass->SetTranslucentPass(translucent);

	vtkNew(vtkRenderPassCollection, passes);
	if(UseLights) passes->AddItem(lightsPass);
	passes->AddItem(opaquePass);
	passes->AddItem(peelingPass);
	passes->AddItem(volumetricPass);
	passes->AddItem(overlayPass);

	vtkNew(vtkSequencePass, renderPass);
	renderPass->SetPasses(passes);

	cameraPass->SetDelegatePass(renderPass);

	vtkRenderState *renderState = new vtkRenderState(ren2);

	// Add Actors and Volumes to a array of vtkProp pointers
	std::vector<vtkProp*> props;
	//props.push_back(actor);
	props.push_back(volume);


	// Add callback function, which is called when first renderer finishes
	CRenderCommand * pCallback = CRenderCommand::New();
	if(UseCamera) pCallback->SetRenderPass(cameraPass, renderState, props);
	else pCallback->SetRenderPass(renderPass, renderState, props);
	ren1->AddObserver(vtkCommand::EndEvent, pCallback);
	pCallback->Delete();


	// Render an image (lights and cameras are created automatically)
	renWin1->Render();

	// Begin mouse interaction
	iren->Start();

	// Cleanup actors
	volume->Delete();
	actor->Delete();
	outline->Delete();

	if(peelingPass->GetLastRenderingUsedDepthPeeling())
		cout << "Used depth peeling" << endl;
	else
		cout << "Used alpha blending" << endl;

	return 0;
}


void MergeBounds(double *bounds, const double *b)
{
	for(int i=0; i<3; i++)
	{
		if(b[2*i]   < bounds[2*i])   bounds[2*i]   = b[2*i];
		if(b[2*i+1] > bounds[2*i+1]) bounds[2*i+1] = b[2*i+1];
	}
}

vtkActor  *CreateOutline(double *bb)
{
	vtkNew(vtkOutlineSource,source);
	source->SetBounds(bb);
	source->SetBoxTypeToAxisAligned();

	vtkNew(vtkDataSetMapper,mapper);
	mapper->SetInput(source->GetOutput());

	vtkActor * actor = vtkActor::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetLineWidth(3.0);
	return actor;
}

vtkVolume *CreateVolume(const char * prefix)
{
	// The following reader is used to read a series of 2D slices (images)
	// that compose the volume. The slice dimensions are set, and the
	// pixel spacing. The data Endianness must also be specified. The reader
	// uses the FilePrefix in combination with the slice number to construct
	// filenames using the format FilePrefix.%d. (In this case the FilePrefix
	// is the root name of the file: quarter.)
	vtkVolume16Reader * v16 = vtkVolume16Reader::New();
	v16->SetDataDimensions(64, 64);
	v16->SetImageRange(1, 93);
	v16->SetDataByteOrderToLittleEndian();
	v16->SetFilePrefix(prefix);
	v16->SetDataSpacing(3.2, 3.2, 1.5);
	//v16->SetDataSpacing(0.32, 0.32, 0.15);

	// The volume will be displayed by ray-cast alpha compositing.
	// A ray-cast mapper is needed to do the ray-casting, and a
	// compositing function is needed to do the compositing along the ray. 
	vtkVolumeRayCastCompositeFunction * rayCastFunction = vtkVolumeRayCastCompositeFunction::New();

	vtkVolumeRayCastMapper * volumeMapper = vtkVolumeRayCastMapper::New();
	volumeMapper->SetInput(v16->GetOutput());
	volumeMapper->SetVolumeRayCastFunction(rayCastFunction);

	// The color transfer function maps voxel intensities to colors.
	// It is modality-specific, and often anatomy-specific as well.
	// The goal is to one color for flesh (between 500 and 1000) 
	// and another color for bone (1150 and over).
	vtkColorTransferFunction * volumeColor = vtkColorTransferFunction::New();
	volumeColor->AddRGBPoint(0,    0.0, 0.0, 0.0);
	volumeColor->AddRGBPoint(500,  1.0, 0.5, 0.3);
	volumeColor->AddRGBPoint(1000, 1.0, 0.5, 0.3);
	volumeColor->AddRGBPoint(1150, 1.0, 1.0, 0.9);

	// The opacity transfer function is used to control the opacity
	// of different tissue types.
	vtkPiecewiseFunction * volumeScalarOpacity = vtkPiecewiseFunction::New();
	volumeScalarOpacity->AddPoint(0,    0.00);
	volumeScalarOpacity->AddPoint(500,  0.15);
	volumeScalarOpacity->AddPoint(1000, 0.15);
	volumeScalarOpacity->AddPoint(1150, 0.85);

	// The gradient opacity function is used to decrease the opacity
	// in the "flat" regions of the volume while maintaining the opacity
	// at the boundaries between tissue types.  The gradient is measured
	// as the amount by which the intensity changes over unit distance.
	// For most medical data, the unit distance is 1mm.
	vtkPiecewiseFunction * volumeGradientOpacity = vtkPiecewiseFunction::New();
	volumeGradientOpacity->AddPoint(0,   0.0);
	volumeGradientOpacity->AddPoint(90,  0.5);
	volumeGradientOpacity->AddPoint(100, 1.0);

	// The VolumeProperty attaches the color and opacity functions to the
	// volume, and sets other volume properties.  The interpolation should
	// be set to linear to do a high-quality rendering.  The ShadeOn option
	// turns on directional lighting, which will usually enhance the
	// appearance of the volume and make it look more "3D".  However,
	// the quality of the shading depends on how accurately the gradient
	// of the volume can be calculated, and for noisy data the gradient
	// estimation will be very poor.  The impact of the shading can be
	// decreased by increasing the Ambient coefficient while decreasing
	// the Diffuse and Specular coefficient.  To increase the impact
	// of shading, decrease the Ambient and increase the Diffuse and Specular.  
	vtkVolumeProperty * volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(volumeColor);
	volumeProperty->SetScalarOpacity(volumeScalarOpacity);
	volumeProperty->SetGradientOpacity(volumeGradientOpacity);
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(0.4);
	volumeProperty->SetDiffuse(0.6);
	volumeProperty->SetSpecular(0.2);

	// The vtkVolume is a vtkProp3D (like a vtkActor) and controls the position
	// and orientation of the volume in world coordinates.
	vtkVolume * vol = vtkVolume::New();
	vol->SetMapper(volumeMapper);
	vol->SetProperty(volumeProperty);

	v16->Delete();
	rayCastFunction->Delete();
	volumeMapper->Delete();
	volumeColor->Delete();
	volumeScalarOpacity->Delete();
	volumeGradientOpacity->Delete();
	volumeProperty->Delete();

	return vol;
}

vtkActor * CreateActor(double opacity)
{
	vtkSphereSource * source = vtkSphereSource::New();
	source->SetRadius(30.0);
	source->SetCenter(20,20,20);
	source->Update();
	vtkPolyData * pd = vtkPolyData::New();
	pd->DeepCopy(source->GetOutput());
	pd->GetPointData()->RemoveArray("Normals");

	vtkDataSetMapper *mapper = vtkDataSetMapper::New();
	mapper->SetInput(pd);

	vtkActor * actor = vtkActor::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(0,0,1);
	actor->GetProperty()->EdgeVisibilityOn();
	actor->GetProperty()->SetOpacity(opacity);

	source->Delete();
	pd->Delete();
	mapper->Delete();

	return actor;
}
