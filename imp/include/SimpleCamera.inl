#include <assert.h>
#include <math.h>


inline void SimpleCamera::SetPosition( float x, float y, float z )
{
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;

	UpdateViewPosition();
}


inline void SimpleCamera::SetOrientation( float* atVect3, float* upVect3 )
{
	m_negDirX = -atVect3[0];
	m_negDirY = -atVect3[1];
	m_negDirZ = -atVect3[2];

	m_upX = upVect3[0];
	m_upY = upVect3[1];
	m_upZ = upVect3[2];

	UpdateRightVector();
	UpdateViewPosition();
}


inline const float* SimpleCamera::GetPosition() const
{
	return m_position;
}


inline const float* SimpleCamera::GetViewMatrix() const
{
	return m_viewMatrix;
}


inline void SimpleCamera::GetDirection( float* vect3 ) const
{
	vect3[0] = -m_negDirX;
	vect3[1] = -m_negDirY;
	vect3[2] = -m_negDirZ;
}


inline void SimpleCamera::GetUpVector( float* vect3 ) const
{
	vect3[0] = m_upX;
	vect3[1] = m_upY;
	vect3[2] = m_upZ;
}


inline void SimpleCamera::GetRightVector( float* vect3 ) const
{
	vect3[0] = m_rightX;
	vect3[1] = m_rightY;
	vect3[2] = m_rightZ;
}


inline void SimpleCamera::UpdateViewPosition()
{
	// values in three rovs in view matrix
	// can be considered as planes which
	// define the coordinate system, their
	// normals are versors and their D
	// components are calculated basing
	// on camera position

	m_rightPos	= -m_rightX * m_position[0] 
				  -m_rightY * m_position[1]
				  -m_rightZ * m_position[2];
	m_upPos		= -m_upX * m_position[0]
				  -m_upY * m_position[1]
				  -m_upZ * m_position[2];
	m_negDirPos = -m_negDirX * m_position[0]
				  -m_negDirY * m_position[1]
				  -m_negDirZ * m_position[2];
}


inline void SimpleCamera::RotateAtAndUp( float* quat4 )
{
	// calculate inversed quaternion
	// (needed for vector rotation)
	float iq[3];
	iq[0] = -quat4[0];
	iq[1] = -quat4[1];
	iq[2] = -quat4[2];


	// rotate direction vector by multiplying: guat4 * dir * iquat;
	// NOTE: all signs in below (tmp) calculations were switched
	//       so here we are operating on actual direction

	float tmp[4];
	tmp[0] = -quat4[3]*m_negDirX                      - quat4[1]*m_negDirZ + quat4[2]*m_negDirY;	// x
	tmp[1] = -quat4[3]*m_negDirY                      - quat4[2]*m_negDirX + quat4[0]*m_negDirZ;	// y
	tmp[2] = -quat4[3]*m_negDirZ                      - quat4[0]*m_negDirY + quat4[1]*m_negDirX;	// z
	tmp[3] =                     + quat4[0]*m_negDirX + quat4[1]*m_negDirY + quat4[2]*m_negDirZ;	// w

	m_negDirX = tmp[3]*iq[0] + tmp[0]*quat4[3] + tmp[1]*iq[2] - tmp[2]*iq[1];	// x
	m_negDirY = tmp[3]*iq[1] + tmp[1]*quat4[3] + tmp[2]*iq[0] - tmp[0]*iq[2];	// y
	m_negDirZ = tmp[3]*iq[2] + tmp[2]*quat4[3] + tmp[0]*iq[1] - tmp[1]*iq[0];	// z


	// rotate up vector

	tmp[0] = quat4[3]*m_upX 				 + quat4[1]*m_upZ - quat4[2]*m_upY;	// x
	tmp[1] = quat4[3]*m_upY 				 + quat4[2]*m_upX - quat4[0]*m_upZ;	// y
	tmp[2] = quat4[3]*m_upZ 				 + quat4[0]*m_upY - quat4[1]*m_upX;	// z
	tmp[3] =			    - quat4[0]*m_upX - quat4[1]*m_upY - quat4[2]*m_upZ;	// w

	m_upX = tmp[3]*iq[0] + tmp[0]*quat4[3] + tmp[1]*iq[2] - tmp[2]*iq[1];	// x
	m_upY = tmp[3]*iq[1] + tmp[1]*quat4[3] + tmp[2]*iq[0] - tmp[0]*iq[2];	// y
	m_upZ = tmp[3]*iq[2] + tmp[2]*quat4[3] + tmp[0]*iq[1] - tmp[1]*iq[0];	// z


	// normalize direrction

	float len = sqrtf( m_negDirX*m_negDirX +
					   m_negDirY*m_negDirY +
					   m_negDirZ*m_negDirZ );
	assert( len > 0.0f );

	// NOTE: divide by -len so we have 
	//       negated direction in matrix
	m_negDirX /= -len;
	m_negDirY /= -len;
	m_negDirZ /= -len;


	// normalize up vector

	len = sqrtf( m_upX*m_upX +
				 m_upY*m_upY +
				 m_upZ*m_upZ );
	assert( len > 0.0f );

	m_upX /= len;
	m_upY /= len;
	m_upZ /= len;
}


inline void SimpleCamera::UpdateRightVector()
{
	// NOTE: in view matrix direction is negated so
	//		 here - was replaced with + and vice versa

	m_rightX = m_negDirZ * m_upY - m_negDirY * m_upZ;
	m_rightY = m_negDirX * m_upZ - m_negDirZ * m_upX;
	m_rightZ = m_negDirY * m_upX - m_negDirX * m_upY;

	float len = sqrtf( m_rightX * m_rightX +
					   m_rightY * m_rightY +
					   m_rightZ * m_rightZ );
	assert( len > 0.0f );

	m_rightX /= len;
	m_rightY /= len;
	m_rightZ /= len;
}
