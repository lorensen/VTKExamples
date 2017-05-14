using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Kitware.VTK;

namespace ActiViz.Examples {
   public class Form1 : Form {
      private System.ComponentModel.IContainer components = null;
      private vtkContourFilter _ContourFilter;
      private vtkRenderWindow _RenderWindow;
         

      public Form1() {
         InitializeComponent();
         this.Size = new Size(620, 400);
      }


      private void Form1_Load(object sender, EventArgs e) {
         try {
            IsoContours();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void sliderContourValue_Scroll(object sender, EventArgs e) {
         TrackBar slider = sender as TrackBar;
         if(slider != null) {
            _ContourFilter.GenerateValues(1, slider.Value, slider.Value);
            _RenderWindow.Render();
         }
      }


      private void IsoContours() {
         vtkImageData data = vtkImageData.New();
         CreateData(ref data);

         // Create an isosurface
         _ContourFilter = vtkContourFilter.New();
#if VTK_MAJOR_VERSION_5
         _ContourFilter.SetInput(data);
#else
         contourFilter.SetInputData(data);
#endif
         _ContourFilter.GenerateValues(1, 10, 10); // (numContours, rangeStart, rangeEnd)

         // Map the contours to graphical primitives
         vtkPolyDataMapper contourMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         contourMapper.SetInputConnection(_ContourFilter.GetOutputPort());
#else
         contourMapper.SetInputData(contourFilter);
#endif
         // Create an actor for the contours
         vtkActor contourActor = vtkActor.New();
         contourActor.SetMapper(contourMapper);

         // Create the outline
         vtkOutlineFilter outlineFilter = vtkOutlineFilter.New();
         vtkPolyDataMapper outlineMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         outlineFilter.SetInput(data);
         outlineMapper.SetInputConnection(outlineFilter.GetOutputPort());
#else
         outlineFilter.SetInputData(data);
         outlineMapper.SetInputData(outlineFilter);
#endif
         vtkActor outlineActor = vtkActor.New();
         outlineActor.SetMapper(outlineMapper);

         // get a reference to the renderwindow of our renderWindowControl1
         _RenderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = _RenderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .3, .4);
         // add our actor to the renderer
         renderer.AddActor(contourActor);
         renderer.AddActor(outlineActor);
      }


      void CreateData(ref vtkImageData data) {
         data.SetExtent(-25, 25, -25, 25, 0, 0);
#if VTK_MAJOR_VERSION_5
         data.SetNumberOfScalarComponents(1);
         data.SetScalarTypeToDouble();
#else
         data.AllocateScalars(VTK_DOUBLE,1);
#endif
         int[] extent = data.GetExtent();

         for(int y = extent[2]; y <= extent[3]; y++) {
            for(int x = extent[0]; x <= extent[1]; x++) {
               IntPtr ptr = data.GetScalarPointer(x, y, 0);
               double[] pixel = new double[] { Math.Sqrt(Math.Pow(x, 2.0) + Math.Pow(y, 2.0)) };
               Marshal.Copy(pixel, 0, ptr, 1);
            }
         }

         vtkXMLImageDataWriter writer = vtkXMLImageDataWriter.New();
         writer.SetFileName(@"c:\vtk\vtkdata-5.8.0\Data\testIsoContours.vti");
#if VTK_MAJOR_VERSION_5
         writer.SetInputConnection(data.GetProducerPort());
#else
         writer.SetInputData(data);
#endif
         writer.Write();
      }



      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
      protected override void Dispose(bool disposing) {
         if(disposing && ( components != null )) {
            components.Dispose();
         }
         base.Dispose(disposing);
      }

      #region Windows Form Designer generated code

      /// <summary>
      /// Required method for Designer support - do not modify
      /// the contents of this method with the code editor.
      /// </summary>
      private void InitializeComponent() {
         this.splitContainer1 = new System.Windows.Forms.SplitContainer();
         this.lblSliderMaxValue = new System.Windows.Forms.Label();
         this.lblSliderMinValue = new System.Windows.Forms.Label();
         this.lblSliderTitle = new System.Windows.Forms.Label();
         this.sliderContourValue = new System.Windows.Forms.TrackBar();
         this.renderWindowControl1 = new Kitware.VTK.RenderWindowControl();
         this.splitContainer1.Panel1.SuspendLayout();
         this.splitContainer1.Panel2.SuspendLayout();
         this.splitContainer1.SuspendLayout();
         ((System.ComponentModel.ISupportInitialize)(this.sliderContourValue)).BeginInit();
         this.SuspendLayout();
         // 
         // splitContainer1
         // 
         this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
         this.splitContainer1.IsSplitterFixed = true;
         this.splitContainer1.Location = new System.Drawing.Point(0, 0);
         this.splitContainer1.Name = "splitContainer1";
         // 
         // splitContainer1.Panel1
         // 
         this.splitContainer1.Panel1.Controls.Add(this.lblSliderMaxValue);
         this.splitContainer1.Panel1.Controls.Add(this.lblSliderMinValue);
         this.splitContainer1.Panel1.Controls.Add(this.lblSliderTitle);
         this.splitContainer1.Panel1.Controls.Add(this.sliderContourValue);
         // 
         // splitContainer1.Panel2
         // 
         this.splitContainer1.Panel2.Controls.Add(this.renderWindowControl1);
         this.splitContainer1.Size = new System.Drawing.Size(604, 362);
         this.splitContainer1.SplitterDistance = 213;
         this.splitContainer1.SplitterWidth = 1;
         this.splitContainer1.TabIndex = 0;
         // 
         // lblSliderMaxValue
         // 
         this.lblSliderMaxValue.AutoSize = true;
         this.lblSliderMaxValue.Location = new System.Drawing.Point(176, 69);
         this.lblSliderMaxValue.Name = "lblSliderMaxValue";
         this.lblSliderMaxValue.Size = new System.Drawing.Size(19, 13);
         this.lblSliderMaxValue.TabIndex = 1;
         this.lblSliderMaxValue.Text = "30";
         // 
         // lblSliderMinValue
         // 
         this.lblSliderMinValue.AutoSize = true;
         this.lblSliderMinValue.Location = new System.Drawing.Point(21, 69);
         this.lblSliderMinValue.Name = "lblSliderMinValue";
         this.lblSliderMinValue.Size = new System.Drawing.Size(13, 13);
         this.lblSliderMinValue.TabIndex = 1;
         this.lblSliderMinValue.Text = "1";
         // 
         // lblSliderTitle
         // 
         this.lblSliderTitle.AutoSize = true;
         this.lblSliderTitle.Location = new System.Drawing.Point(18, 11);
         this.lblSliderTitle.Name = "lblSliderTitle";
         this.lblSliderTitle.Size = new System.Drawing.Size(74, 13);
         this.lblSliderTitle.TabIndex = 1;
         this.lblSliderTitle.Text = "Contour Value";
         // 
         // sliderContourValue
         // 
         this.sliderContourValue.Location = new System.Drawing.Point(12, 37);
         this.sliderContourValue.Maximum = 30;
         this.sliderContourValue.Minimum = 1;
         this.sliderContourValue.Name = "sliderContourValue";
         this.sliderContourValue.Size = new System.Drawing.Size(186, 45);
         this.sliderContourValue.TabIndex = 0;
         this.sliderContourValue.TickFrequency = 5;
         this.sliderContourValue.Value = 10;
         this.sliderContourValue.Scroll += new System.EventHandler(this.sliderContourValue_Scroll);
         // 
         // renderWindowControl1
         // 
         this.renderWindowControl1.AddTestActors = false;
         this.renderWindowControl1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.renderWindowControl1.Location = new System.Drawing.Point(0, 0);
         this.renderWindowControl1.Name = "renderWindowControl1";
         this.renderWindowControl1.Size = new System.Drawing.Size(390, 362);
         this.renderWindowControl1.TabIndex = 0;
         this.renderWindowControl1.TestText = null;
         // 
         // Form1
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.ClientSize = new System.Drawing.Size(604, 362);
         this.Controls.Add(this.splitContainer1);
         this.Name = "Form1";
         this.Text = "IsoContours";
         this.Load += new System.EventHandler(this.Form1_Load);
         this.splitContainer1.Panel1.ResumeLayout(false);
         this.splitContainer1.Panel1.PerformLayout();
         this.splitContainer1.Panel2.ResumeLayout(false);
         this.splitContainer1.ResumeLayout(false);
         ((System.ComponentModel.ISupportInitialize)(this.sliderContourValue)).EndInit();
         this.ResumeLayout(false);

      }

      #endregion

      private System.Windows.Forms.SplitContainer splitContainer1;
      private System.Windows.Forms.Label lblSliderTitle;
      private System.Windows.Forms.TrackBar sliderContourValue;
      private Kitware.VTK.RenderWindowControl renderWindowControl1;
      private System.Windows.Forms.Label lblSliderMaxValue;
      private System.Windows.Forms.Label lblSliderMinValue;
   }
}
