#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include <algorithm>
#include <list>

#include "Global.h"
#include "GLDrawer.h"
#include "Point2F.h"
#include "EDM_Rect.h"
#include "Properties.h"

using namespace std;
using namespace System::Windows::Forms;
using namespace EDM;
using namespace EDM::EDM_Graphics;

//static const float PI = 3.1415926535898f;

namespace OpenGLPanelExtention
{
	ref class OpenGLPanel: public System::Windows::Forms::Panel
	{

	private:
		HDC m_hDC;
		HGLRC m_hglrc;

		GLdouble		xOrtCount;
		GLdouble		yOrtCount;

		#pragma region GL System members
		GLint MySetPixelFormat(HDC hdc)
		{
			static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
			{
				sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
				1,											// Version Number
				PFD_DRAW_TO_WINDOW |						// Format Must Support Window
				PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
				PFD_DOUBLEBUFFER,							// Must Support Double Buffering
				PFD_TYPE_RGBA,								// Request An RGBA Format
				16,										// Select Our Color Depth
				0, 0, 0, 0, 0, 0,							// Color Bits Ignored
				0,											// No Alpha Buffer
				0,											// Shift Bit Ignored
				0,											// No Accumulation Buffer
				0, 0, 0, 0,									// Accumulation Bits Ignored
				16,											// 16Bit Z-Buffer (Depth Buffer)  
				0,											// No Stencil Buffer
				0,											// No Auxiliary Buffer
				PFD_MAIN_PLANE,								// Main Drawing Layer
				0,											// Reserved
				0, 0, 0										// Layer Masks Ignored
			};

			GLint  iPixelFormat; 

			// get the device context's best, available pixel format match 
			if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
			{
				MessageBox::Show("ChoosePixelFormat Failed");
				return 0;
			}

			// make that match the device context's current pixel format 
			if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
			{
				MessageBox::Show("SetPixelFormat Failed");
				return 0;
			}

			if((m_hglrc = wglCreateContext(m_hDC)) == NULL)
			{
				MessageBox::Show("wglCreateContext Failed");
				return 0;
			}

			if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
			{
				MessageBox::Show("wglMakeCurrent Failed");
				return 0;
			}

			return 1;
		}

		int InitGL(GLvoid) // All setup for opengl goes here										
		{
#pragma region Antialiasing

			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POINT_SMOOTH);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			// Really nice perspective calculations
			glHint(GL_LINE_SMOOTH_HINT | GL_LINE_SMOOTH_HINT, GL_NICEST);	

#pragma endregion Antialiasing

			//glShadeModel(GL_SMOOTH);							// Enable smooth shading
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);				// White background
			glClearDepth(1.0f);									// Depth buffer setup
			glEnable(GL_DEPTH_TEST);							// Enables depth testing
			glDepthFunc(GL_LEQUAL);								// The type of depth testing to do

			return 1;											// Initialization went ok
		}		

		GLvoid SwapOpenGLBuffers(System::Void)
		{
			SwapBuffers(m_hDC) ;
		}

		/*EDM_Rect GetOrtho2DEDM_Rect()
		{
			return EDM_Rect(Point2F(0.0f, 0.0f), Point2F((float)xOrtCount, (float)yOrtCount));
		}*/
#pragma endregion GL System members

	protected:
		~OpenGLPanel(System::Void)
		{
			this->DestroyHandle();
		}

	public:
		GLint		pixelsPerMeter;

		OpenGLPanel(GLsizei width, GLsizei height)
		{
			m_hDC = GetDC((HWND)this->Handle.ToPointer());

			if(m_hDC)
			{
				MySetPixelFormat(m_hDC);
				ReSizeGLScene(width, height);
				InitGL();				
			}	
		}

		GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize and initialize the gl window
		{
			if (height == 0)									// Prevent A Divide By Zero By
				height = 1;										// Making Height Equal One
			if (width == 0)										// Prevent A Divide By Zero By
				width = 1;										// Making Width Equal One

			glViewport(0, 0, width, height);					// Reset The Current Viewport

			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glLoadIdentity();									// Reset The Projection Matrix

			pixelsPerMeter = (GLint)min(width / Properties::Instance->ActualXCellsCount, height / Properties::Instance->ActualYCellsCount);
			if(pixelsPerMeter == 0)
			{
				pixelsPerMeter = 1;
			}

			xOrtCount = (double)width / pixelsPerMeter;
			yOrtCount = (double)height / pixelsPerMeter;

			gluOrtho2D(0, xOrtCount, 0, yOrtCount);

			glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
			glLoadIdentity();									// Reset The Modelview Matrix
		}	

		System::Void Render(double timeElapsed)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear screen and depth buffer

			if (EDM_Prop->ShowCellsGrid)
			{
				GLDrawer::DrawCellsGrid(0, 0, EDM_Prop->ActualXCellsCount, EDM_Prop->ActualYCellsCount, 1.0f, 1.0f);
			}			
			GLDrawer::DrawBoundEDM_Rect(EDM_Rect(1.0f,1.0f, (float)EDM_Prop->ActualXCellsCount - 1, (float)EDM_Prop->ActualYCellsCount - 1), 2.0f);
			ActorsContainer *acInst = ActorsContainer::Instance();
			GLDrawer::DrawActors(acInst->actors, timeElapsed, pixelsPerMeter, EDM_Prop->ActorsRadius * 2);
			acInst->FreeInst();

			glFlush();
			SwapOpenGLBuffers();			
		}

		//////////////////////////////////////////////////////////////////////////
		//ØÀÉÒÀÍ Ñ ÏÐÅÎÁÐÀÇÎÂÀÍÈßÌÈ, ÍÅÒÎ×ÍÎÑÒÜ ÎÊÐÓÃËÅÍÈß
		Point2F *GetPointInWorldCoordinates(int x, int y)
		{
			float newX = (float)x / pixelsPerMeter;
			int csHeight = this->ClientSize.Height;
			csHeight--;
			float newY = (float)(csHeight - y) / pixelsPerMeter;
			Point2F *worldCoord = new Point2F(newX, newY);
			return worldCoord;
		}
	};
}