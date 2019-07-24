#ifndef __AnimateActors_h
#include <vector>
#include <vtkActor.h>
#include <vtkAnimationCue.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>

class ActorAnimator
{
public:
  ActorAnimator()
  {
    this->Actor = 0;
    this->Observer = AnimationCueObserver::New();
    this->Observer->Animator = this;
    this->StartPosition.resize(3);
    this->StartPosition.insert(this->StartPosition.begin(), 3, 0.0);
    this->EndPosition.resize(3);
    this->EndPosition.insert(this->EndPosition.begin(), 3, .5);
  }

  ~ActorAnimator()
  {
    if (this->Actor)
    {
      this->Actor->UnRegister(0);
      this->Actor = 0;
    }
    this->Observer->UnRegister(0);
  }
  void SetActor(vtkActor* actor)
  {
    if (this->Actor)
    {
      this->Actor->UnRegister(0);
    }
    this->Actor = actor;
    this->Actor->Register(0);
  }
  void SetStartPosition(std::vector<double> const& position)
  {
    this->StartPosition = position;
  }
  void SetEndPosition(std::vector<double> const& position)
  {
    this->EndPosition = position;
  }
  void AddObserversToCue(vtkAnimationCue* cue)
  {
    cue->AddObserver(vtkCommand::StartAnimationCueEvent, this->Observer);
    cue->AddObserver(vtkCommand::EndAnimationCueEvent, this->Observer);
    cue->AddObserver(vtkCommand::AnimationCueTickEvent, this->Observer);
  }

  void Start(vtkAnimationCue::AnimationCueInfo* vtkNotUsed(info))
  {
    this->Actor->SetPosition(this->StartPosition[0], this->StartPosition[1],
                             this->StartPosition[2]);
  }

  void Tick(vtkAnimationCue::AnimationCueInfo* info)
  {
    double t = (info->AnimationTime - info->StartTime) /
        (info->EndTime - info->StartTime);
    double position[3];
    for (int i = 0; i < 3; i++)
    {
      position[i] = this->StartPosition[i] +
          (this->EndPosition[i] - this->StartPosition[i]) * t;
    }
    this->Actor->SetPosition(position);
  }

  void End(vtkAnimationCue::AnimationCueInfo* vtkNotUsed(info))
  {
    this->Actor->SetPosition(this->EndPosition[0], this->EndPosition[1],
                             this->EndPosition[2]);
  }

protected:
  class AnimationCueObserver : public vtkCommand
  {
  public:
    static AnimationCueObserver* New()
    {
      return new AnimationCueObserver;
    }

    virtual void Execute(vtkObject* vtkNotUsed(caller), unsigned long event,
                         void* calldata)
    {
      if (this->Animator != 0)
      {
        vtkAnimationCue::AnimationCueInfo* info =
            static_cast<vtkAnimationCue::AnimationCueInfo*>(calldata);
        switch (event)
        {
        case vtkCommand::StartAnimationCueEvent:
          this->Animator->Start(info);
          break;
        case vtkCommand::EndAnimationCueEvent:
          this->Animator->End(info);
          break;
        case vtkCommand::AnimationCueTickEvent:
          this->Animator->Tick(info);
          break;
        }
      }
    }

    AnimationCueObserver()
    {
      this->Animator = 0;
    }
    ActorAnimator* Animator;
  };

  vtkActor* Actor;
  AnimationCueObserver* Observer;
  std::vector<double> StartPosition;
  std::vector<double> EndPosition;
};

class AnimationSceneObserver : public vtkCommand
{
public:
  static AnimationSceneObserver* New()
  {
    return new AnimationSceneObserver;
  }

  void SetRenderWindow(vtkRenderWindow* renWin)
  {
    if (this->RenderWindow)
    {
      this->RenderWindow->UnRegister(this);
    }
    this->RenderWindow = renWin;
    this->RenderWindow->Register(this);
  }
  virtual void Execute(vtkObject* vtkNotUsed(caller), unsigned long event,
                       void* vtkNotUsed(calldata))
  {
    if (this->RenderWindow != 0)
    {
      switch (event)
      {
      case vtkCommand::AnimationCueTickEvent:
        this->RenderWindow->Render();
        break;
      }
    }
  }

protected:
  AnimationSceneObserver()
  {
    this->RenderWindow = 0;
  }
  ~AnimationSceneObserver()
  {
    if (this->RenderWindow)
    {
      this->RenderWindow->UnRegister(this);
      this->RenderWindow = 0;
    }
  }
  vtkRenderWindow* RenderWindow;
};

#endif
