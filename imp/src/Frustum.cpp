#include "Frustum.hpp"
#include <math.h>

using namespace imp;

// based on:
// http://www.racer.nl/reference/vfc_markmorley.htm
// http://www.cescg.org/CESCG-2002/DSykoraJJelinek/index.html


void Frustum::Update( const float* modelViewVect16, const float* projVect16 )
{
	float clip[16];

	clip[ 0] = modelViewVect16[  0 ]*projVect16[  0 ] +	modelViewVect16[  1 ]*projVect16[  4 ] +
			   modelViewVect16[  2 ]*projVect16[  8 ] +	modelViewVect16[  3 ]*projVect16[ 12 ];
	clip[ 1] = modelViewVect16[  0 ]*projVect16[  1 ] +	modelViewVect16[  1 ]*projVect16[  5 ] +
			   modelViewVect16[  2 ]*projVect16[  9 ] + modelViewVect16[  3 ]*projVect16[ 13 ];
	clip[ 2] = modelViewVect16[  0 ]*projVect16[  2 ] +	modelViewVect16[  1 ]*projVect16[  6 ] +
			   modelViewVect16[  2 ]*projVect16[ 10 ] + modelViewVect16[  3 ]*projVect16[ 14 ];
	clip[ 3] = modelViewVect16[  0 ]*projVect16[  3 ] +	modelViewVect16[  1 ]*projVect16[  7 ] +
			   modelViewVect16[  2 ]*projVect16[ 11 ] + modelViewVect16[  3 ]*projVect16[ 15 ]; 

	clip[ 4] = modelViewVect16[  4 ]*projVect16[  0 ] + modelViewVect16[  5 ]*projVect16[  4 ] +
			   modelViewVect16[  6 ]*projVect16[  8 ] + modelViewVect16[  7 ]*projVect16[ 12 ];
	clip[ 5] = modelViewVect16[  4 ]*projVect16[  1 ] + modelViewVect16[  5 ]*projVect16[  5 ] +
			   modelViewVect16[  6 ]*projVect16[  9 ] + modelViewVect16[  7 ]*projVect16[ 13 ];
	clip[ 6] = modelViewVect16[  4 ]*projVect16[  2 ] + modelViewVect16[  5 ]*projVect16[  6 ] +
			   modelViewVect16[  6 ]*projVect16[ 10 ] + modelViewVect16[  7 ]*projVect16[ 14 ];
	clip[ 7] = modelViewVect16[  4 ]*projVect16[  3 ] + modelViewVect16[  5 ]*projVect16[  7 ] +
			   modelViewVect16[  6 ]*projVect16[ 11 ] + modelViewVect16[  7 ]*projVect16[ 15 ];

	clip[ 8] = modelViewVect16[  8 ]*projVect16[  0 ] + modelViewVect16[  9 ]*projVect16[  4 ] +
			   modelViewVect16[ 10 ]*projVect16[  8 ] + modelViewVect16[ 11 ]*projVect16[ 12 ];
	clip[ 9] = modelViewVect16[  8 ]*projVect16[  1 ] + modelViewVect16[  9 ]*projVect16[  5 ] +
			   modelViewVect16[ 10 ]*projVect16[  9 ] + modelViewVect16[ 11 ]*projVect16[ 13 ];
	clip[10] = modelViewVect16[  8 ]*projVect16[  2 ] + modelViewVect16[  9 ]*projVect16[  6 ] +
			   modelViewVect16[ 10 ]*projVect16[ 10 ] + modelViewVect16[ 11 ]*projVect16[ 14 ];
	clip[11] = modelViewVect16[  8 ]*projVect16[  3 ] + modelViewVect16[  9 ]*projVect16[  7 ] +
			   modelViewVect16[ 10 ]*projVect16[ 11 ] + modelViewVect16[ 11 ]*projVect16[ 15 ];

	clip[12] = modelViewVect16[ 12 ]*projVect16[  0 ] + modelViewVect16[ 13 ]*projVect16[  4 ] +
			   modelViewVect16[ 14 ]*projVect16[  8 ] + modelViewVect16[ 15 ]*projVect16[ 12 ];
	clip[13] = modelViewVect16[ 12 ]*projVect16[  1 ] + modelViewVect16[ 13 ]*projVect16[  5 ] +
		       modelViewVect16[ 14 ]*projVect16[  9 ] + modelViewVect16[ 15 ]*projVect16[ 13 ];
	clip[14] = modelViewVect16[ 12 ]*projVect16[  2 ] + modelViewVect16[ 13 ]*projVect16[  6 ] +
			   modelViewVect16[ 14 ]*projVect16[ 10 ] + modelViewVect16[ 15 ]*projVect16[ 14 ];
	clip[15] = modelViewVect16[ 12 ]*projVect16[  3 ] + modelViewVect16[ 13 ]*projVect16[  7 ] +
			   modelViewVect16[ 14 ]*projVect16[ 11 ] + modelViewVect16[ 15 ]*projVect16[ 15 ];

	
	// right plane - equation is result of multiplication components of
	// plane -1x+0y+0z+1=0 by projVect16ection matrix and modelview matrix
	m_frustum[ 0 ][ 0 ] = clip[  3 ] - clip[  0 ];	// A
	m_frustum[ 0 ][ 1 ] = clip[  7 ] - clip[  4 ];	// B
	m_frustum[ 0 ][ 2 ] = clip[ 11 ] - clip[  8 ];	// C
	m_frustum[ 0 ][ 3 ] = clip[ 15 ] - clip[ 12 ];	// D

	// left plane
	m_frustum[ 1 ][ 0 ] = clip[  3 ] + clip[  0 ];
	m_frustum[ 1 ][ 1 ] = clip[  7 ] + clip[  4 ];
	m_frustum[ 1 ][ 2 ] = clip[ 11 ] + clip[  8 ];
	m_frustum[ 1 ][ 3 ] = clip[ 15 ] + clip[ 12 ];

	// bottom plane
	m_frustum[ 2 ][ 0 ] = clip[  3 ] + clip[  1 ];
	m_frustum[ 2 ][ 1 ] = clip[  7 ] + clip[  5 ];
	m_frustum[ 2 ][ 2 ] = clip[ 11 ] + clip[  9 ];
	m_frustum[ 2 ][ 3 ] = clip[ 15 ] + clip[ 13 ];

	// top plane
	m_frustum[ 3 ][ 0 ] = clip[  3 ] - clip[  1 ];
	m_frustum[ 3 ][ 1 ] = clip[  7 ] - clip[  5 ];
	m_frustum[ 3 ][ 2 ] = clip[ 11 ] - clip[  9 ];
	m_frustum[ 3 ][ 3 ] = clip[ 15 ] - clip[ 13 ];

	// back plane
	m_frustum[ 4 ][ 0 ] = clip[  3 ] - clip[  2 ];
	m_frustum[ 4 ][ 1 ] = clip[  7 ] - clip[  6 ];
	m_frustum[ 4 ][ 2 ] = clip[ 11 ] - clip[ 10 ];
	m_frustum[ 4 ][ 3 ] = clip[ 15 ] - clip[ 14 ];

	// front plane
	m_frustum[ 5 ][ 0 ] = clip[  3 ] + clip[  2 ];
	m_frustum[ 5 ][ 1 ] = clip[  7 ] + clip[  6 ];
	m_frustum[ 5 ][ 2 ] = clip[ 11 ] + clip[ 10 ];
	m_frustum[ 5 ][ 3 ] = clip[ 15 ] + clip[ 14 ];


	// normalize planes
	for( int loop = 0 ; loop < 6 ; loop++ )
	{
		float dist = sqrtf( m_frustum[loop][0]*m_frustum[loop][0] +
			    			m_frustum[loop][1]*m_frustum[loop][1] +
						    m_frustum[loop][2]*m_frustum[loop][2] );

		m_frustum[ loop ][ 0 ] /= dist;
		m_frustum[ loop ][ 1 ] /= dist;
		m_frustum[ loop ][ 2 ] /= dist;
		m_frustum[ loop ][ 3 ] /= dist;
	}
}


Frustum::Test Frustum::ContainsPoint( const float* posVect3 ) const
{
	for( int loop = 0 ; loop < 6 ; loop++ )
	{
		// inserting point coordinates to the equation of each the plane, if 
		// the outcome is less than 0 then the point is not inside frustum
		if( ( m_frustum[loop][0]*posVect3[0] +
			  m_frustum[loop][1]*posVect3[1] +
			  m_frustum[loop][2]*posVect3[2] + 
			  m_frustum[loop][3] ) <= 0.0f )
            return Test::OUTSIDE;
	}

    return Test::INSIDE;
}


Frustum::Test Frustum::ContainsSphere( const float* posVect3, float r ) const
{
	float dist;
	int fullyInsideCount = 0;

	for( int loop = 0 ; loop < 6 ; loop++ )
	{
		// inserting sphere coordinates to the plane equation, if the result
		// is smaller than the radius of the sphere - is not inside frustum

		dist = m_frustum[loop][0]*posVect3[0] +
			   m_frustum[loop][1]*posVect3[1] +
			   m_frustum[loop][2]*posVect3[2] +
			   m_frustum[loop][3];

		if( dist <= -r )
            return Test::OUTSIDE;
		if( dist > r )
			++fullyInsideCount;
	}

    return ( fullyInsideCount == 6 ) ? Test::INSIDE : Test::INTERSECT;
}


Frustum::Test Frustum::ContainsAABB( const float* minVect3, const float* maxVect3 ) const
{
    auto result = Test::INSIDE;

	float pv[3];
	float nv[3];
	float n;
	float m;

	for( int loop = 0 ; loop < 6 ; loop++ )
	{
		if( m_frustum[loop][0] > 0.0f )
		{
			pv[0] = maxVect3[0];
			nv[0] = minVect3[0];
		}
		else
		{
			pv[0] = minVect3[0];
			nv[0] = maxVect3[0];
		}

		if( m_frustum[loop][1] > 0.0f )
		{
			pv[1] = maxVect3[1];
			nv[1] = minVect3[1];
		}
		else
		{
			pv[1] = minVect3[1];
			nv[1] = maxVect3[1];
		}

		if( m_frustum[loop][2] > 0.0f )
		{
			pv[2] = maxVect3[2];
			nv[2] = minVect3[2];
		}
		else
		{
			pv[2] = minVect3[2];
			nv[2] = maxVect3[2];
		}
		

		m = nv[0]*m_frustum[loop][0] +
		    nv[1]*m_frustum[loop][1] +
			nv[2]*m_frustum[loop][2] + 
			m_frustum[loop][3];
		if( m > 0.0f )
            return Test::OUTSIDE;

		n = pv[0]*m_frustum[loop][0] +
		    pv[1]*m_frustum[loop][1] +
			pv[2]*m_frustum[loop][2] + 
			m_frustum[loop][3];
		if( n > 0.0f )
            result = Test::INTERSECT;
	}

	return result;
}


void Frustum::GetPlane( Plane plane, float& a, float& b, float& c, float& d ) const
{
    auto index = static_cast<unsigned int>(plane);
    a = m_frustum[ index ][0];
    b = m_frustum[ index ][1];
    c = m_frustum[ index ][2];
    d = m_frustum[ index ][3];
}
