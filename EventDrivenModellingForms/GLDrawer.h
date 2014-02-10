#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>

#include "Point2F.h"
#include "EDM_Rect.h"
#include "Actor.h"
#include "Events.h"
#include "ActorsContainer.h"

#include "TriangNode.h"
#include "TriangNodesContainer.h"
#include "TriangEdge.h"
#include "EdgesContainer.h"

#include "Properties.h"

using namespace std;
using namespace EDM;
using namespace EDM::EDM_Graphics;

/*static const float PI = 3.1415926535898f;*/

namespace EDM { namespace EDM_Graphics
{
	inline GLfloat GetGLSizeFromWorld(GLfloat worldSize, GLint pixelsPerMeter)
	{
		return worldSize * pixelsPerMeter;
	}

	class GLDrawer
	{
	public:
		

		static GLvoid DrawPoint(GLfloat x, GLfloat y, GLfloat size)
		{
			glPointSize(size);
			glBegin(GL_POINTS);
				glVertex2f(x, y);
			glEnd();
		}

	
		static GLvoid DrawTriangEdges(EdgesT &edges, TriangNodesT &nodes, GLfloat lineWidth)
		{
			glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
			for (size_t edgeIter = 0; edgeIter < edges.size(); edgeIter++)
			{
				Point2F startPoint = nodes[edges[edgeIter].m_begin].coord;
				Point2F endPoint = nodes[edges[edgeIter].m_end].coord;
				DrawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, lineWidth);
			}
		}

		static GLvoid DrawTriangNodes(TriangNodesT &nodes, double sysTime, GLint pixelsPerMeter, GLfloat size = -1.0f)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			GLfloat actSize;
			GLint actorCntr = 0;
			TriangNodesT::iterator pIter = nodes.begin();			
			glColor3f(1.0f, 0.0f, 0.0f);
			while (actorCntr < nodes.size())
			{
				if (size < 0)
					actSize = GetGLSizeFromWorld(pIter->radius * 2, pixelsPerMeter);
				else
					actSize = GetGLSizeFromWorld(size, pixelsPerMeter);
				//////////////////////////////////////////////////////////////////////////
				pIter->coord = pIter->localCoord + pIter->vel * (sysTime - pIter->evnt->args->localTime);
				DrawPoint(pIter->coord.x, pIter->coord.y, actSize);
				pIter++; 
				actorCntr++;
			}						
		}

		static GLvoid DrawActors(ActorsT &actors, double sysTime, GLint pixelsPerMeter, GLfloat size = -1.0f)
		{
			GLfloat actSize;
			GLint actorCntr = 0;
			ActorsT::iterator pIter = actors.begin();			
			glColor3f(1.0f, 0.0f, 0.0f);
			while (actorCntr < EDM_Prop->ActorsCount)
			{
				if (size < 0)
					actSize = GetGLSizeFromWorld(pIter->radius * 2, pixelsPerMeter);
				else
					actSize = GetGLSizeFromWorld(size, pixelsPerMeter);
				//////////////////////////////////////////////////////////////////////////
				pIter->coord = pIter->localCoord + pIter->vel * (sysTime - pIter->evnt->args->localTime);
				DrawPoint(pIter->coord.x, pIter->coord.y, actSize);
				pIter++; 
				actorCntr++;
			}
		}

		static GLvoid DrawPointsList(const list<Point2F> &points, GLfloat size)
		{
			list<Point2F>::const_iterator pIter = points.begin();
			glPointSize(size);
			glBegin(GL_POINTS);					
				while (pIter != points.end())
				{
					glVertex2f(pIter->x, pIter->y);
					pIter++;
				}
			glEnd();
		}

		static GLvoid DrawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat lineWidth)
		{
			glLineWidth(lineWidth);
			glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
			glEnd();
		}

		static GLvoid DrawCoordGrid(GLfloat left, GLfloat bottom, GLint xOrtCount, GLint yOrtCount, int width, int height)
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			yOrtCount++; xOrtCount++;
			for(GLfloat i = 1.0f; i < yOrtCount; i++)
			{
				DrawLine(left, i, width, i, 1.0f);		
			}
			for(GLfloat i = 1.0f; i < xOrtCount; i++)
			{
				DrawLine(i, bottom, i, height, 1.0f);
			}
		}

		static GLvoid DrawCellsGrid(GLfloat left, GLfloat bottom, GLint _xCellsCount, GLint _yCellsCount, 
			GLfloat _xCellSize, GLfloat _yCellSize)
		{
			glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
			GLint xlinesCount = _xCellsCount + 1;
			GLint ylinesCount = _yCellsCount + 1;			
			for(GLfloat i = 0; i < xlinesCount; i++)
			{
				DrawLine(i * _xCellSize, bottom, i * _xCellSize, _yCellsCount, 1.0f);
			}
			for(GLfloat i = 0; i < ylinesCount; i++)
			{
				DrawLine(left, i * _yCellSize, _xCellsCount, i * _yCellSize, 1.0f);		
			}
		}

		static GLvoid DrawFillBoundEDM_Rect(const EDM_Rect &rect, GLfloat lineWidth)
		{
			glColor4f(0.0f, 0.0f, 1.0f, 0.25f);
			DrawFillEDM_Rect(rect);

			glLineWidth(lineWidth);
			glColor4f(0.0f, 0.0f, 1.0f, 5.0f);			
			DrawBoundEDM_Rect(rect, lineWidth);			
		}

		static GLvoid DrawFillEDM_Rect(const EDM_Rect &rect)
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			glBegin(GL_QUADS);				
				glVertex2f(rect.leftBottom.x, rect.leftBottom.y);
				glVertex2f(rect.rightTop.x, rect.leftBottom.y);
				glVertex2f(rect.rightTop.x, rect.rightTop.y);
				glVertex2f(rect.leftBottom.x, rect.rightTop.y);
			glEnd();
		}

		static GLvoid DrawBoundEDM_Rect(const EDM_Rect &rect, GLfloat lineWidth)
		{
			glLineWidth(lineWidth);
			glColor4f(0.0f, 0.0f, 1.0f, 0.85f);
			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_QUADS);				
				glVertex2f(rect.leftBottom.x, rect.leftBottom.y);
				glVertex2f(rect.rightTop.x, rect.leftBottom.y);
				glVertex2f(rect.rightTop.x, rect.rightTop.y);
				glVertex2f(rect.leftBottom.x, rect.rightTop.y);
			glEnd();
		}

// 		static GLvoid DrawCircle(GLint vertexCount, GLfloat radius, GLfloat xCenter, GLfloat yCenter)
// 		{			
// 			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
// 			glBegin( GL_TRIANGLE_FAN );
// 				glVertex2f(xCenter + 0.0f, yCenter + 0.0f ); // vertex in the circle center
// 				for(GLint i = 0; i <= vertexCount; i++ ) {
// 					GLfloat a = (float)i / vertexCount * PI * 2.0f;
// 					glVertex2f(xCenter + cos( a ) * radius, yCenter + sin( a ) * radius );
// 				}
// 			glEnd();
// 		}

	private:

	};		
}}