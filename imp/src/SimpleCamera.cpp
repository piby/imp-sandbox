#include "SimpleCamera.hpp"
#include <math.h>
#include <assert.h>

using namespace imp;

SimpleCamera::SimpleCamera()
{
	SetPosition( 0.0f, 0.0f, 0.0f );

	m_viewMatrix[ 0] = 1.0f;	m_viewMatrix[ 4] = 0.0f;	m_viewMatrix[ 8] = 0.0f;	m_viewMatrix[12] = 0.0f;
	m_viewMatrix[ 1] = 0.0f;	m_viewMatrix[ 5] = 1.0f;	m_viewMatrix[ 9] = 0.0f;	m_viewMatrix[13] = 0.0f;
	m_viewMatrix[ 2] = 0.0f;	m_viewMatrix[ 6] = 0.0f;	m_viewMatrix[10] = 1.0f;	m_viewMatrix[14] = 0.0f;

	// this values in view matrix never change
	m_viewMatrix[ 3] = 0.0f;	m_viewMatrix[ 7] = 0.0f;	m_viewMatrix[11] = 0.0f;	m_viewMatrix[15] = 1.0f;
}


SimpleCamera::~SimpleCamera()
{
}


void SimpleCamera::Move( float xAxisAdd, float yAxisAdd, float zAxisAdd )
{
	m_position[0] += xAxisAdd;
	m_position[1] += yAxisAdd;
	m_position[2] += zAxisAdd;

	UpdateViewPosition();
}


void SimpleCamera::MoveRelative( float rightAdd, float upAdd, float dirAdd )	
{
	// NOTE: direction components are substracted
	// because in view matrix direction is negated

	m_position[0] += ( rightAdd * m_rightX + upAdd * m_upX - dirAdd * m_negDirX );
	m_position[1] += ( rightAdd * m_rightY + upAdd * m_upY - dirAdd * m_negDirY );
	m_position[2] += ( rightAdd * m_rightZ + upAdd * m_upZ - dirAdd * m_negDirZ );

	UpdateViewPosition();
}


void SimpleCamera::Rotate( float xAngleRad, float yAngleRad, float zAngleRad )
{
	// create rotation quaternion
	// from three angles

	xAngleRad *= 0.5f;
	yAngleRad *= 0.5f;
	zAngleRad *= 0.5f;

	float sx = sinf( xAngleRad );
	float cx = cosf( xAngleRad );
	float sy = sinf( yAngleRad );
	float cy = cosf( yAngleRad );
	float sz = sinf( zAngleRad );
	float cz = cosf( zAngleRad );

	float q[4];
	q[0] = sx * cy * cz  -  cx * sy * sz;
	q[1] = cx * sy * cz  +  sx * cy * sz;
	q[2] = cx * cy * sz  -  sx * sy * cz;
	q[3] = cx * cy * cz  +  sx * sy * sz;	


	RotateAtAndUp( q );
	UpdateRightVector();
	UpdateViewPosition();
}


void SimpleCamera::RotateRelative( float rightAngleRad, float upAngleRad, float dirAngleRad )
{
	// create quaternions represeting rotation
	// around right, up and direction vectors;
	// if angle is almost zero then it is asumed
	// that it is zero (in most cases only one
	// angle will be diferent from zero)

	float qx[4];
	if( ( rightAngleRad > -0.000005f ) && ( rightAngleRad < 0.000005f ) )
	{
		qx[0] = 0.0f;	// sin(0) = 0
		qx[1] = 0.0f;
		qx[2] = 0.0f;
		qx[3] = 1.0f;	// cos(0) = 1
	}
	else
	{
		rightAngleRad *= 0.5f;
		qx[3] = cosf( rightAngleRad );
		rightAngleRad = sinf( rightAngleRad );
		qx[0] = m_rightX * rightAngleRad;
		qx[1] = m_rightY * rightAngleRad;
		qx[2] = m_rightZ * rightAngleRad;
	}

	float qy[4];
	if( ( upAngleRad > -0.000005f ) && ( upAngleRad < 0.000005f ) )
	{
		qy[0] = 0.0f;	// sin(0) = 0
		qy[1] = 0.0f;
		qy[2] = 0.0f;
		qy[3] = 1.0f;	// cos(0) = 1
	}
	else
	{
		upAngleRad *= 0.5f;
		qy[3] = cosf( upAngleRad );
		upAngleRad = sinf( upAngleRad );
		qy[0] = m_upX * upAngleRad;
		qy[1] = m_upY * upAngleRad;
		qy[2] = m_upZ * upAngleRad;
	}

	float qz[4];
	if( ( dirAngleRad > -0.000005f ) && ( dirAngleRad < 0.000005f ) )
	{
		qz[0] = 0.0f;	// sin(0) = 0
		qz[1] = 0.0f;
		qz[2] = 0.0f;
		qz[3] = 1.0f;	// cos(0) = 1
	}
	else
	{
		dirAngleRad *= 0.5f;
		qz[3] = cosf( dirAngleRad );
		dirAngleRad = sinf( dirAngleRad );
		qz[0] = -m_negDirX * dirAngleRad;
		qz[1] = -m_negDirY * dirAngleRad;
		qz[2] = -m_negDirZ * dirAngleRad;
	}


	// quaternion multiplication to
	// obtain the final rotation quaternion

	float tmp[4];
	tmp[0] = qx[3]*qy[0] + qx[0]*qy[3] + qx[1]*qy[2] - qx[2]*qy[1];	// x
	tmp[1] = qx[3]*qy[1] + qx[1]*qy[3] + qx[2]*qy[0] - qx[0]*qy[2];	// y
	tmp[2] = qx[3]*qy[2] + qx[2]*qy[3] + qx[0]*qy[1] - qx[1]*qy[0];	// z
	tmp[3] = qx[3]*qy[3] - qx[0]*qy[0] - qx[1]*qy[1] - qx[2]*qy[2];	// w

	float q[4];
	q[0] = tmp[3]*qz[0] + tmp[0]*qz[3] + tmp[1]*qz[2] - tmp[2]*qz[1];	// x
	q[1] = tmp[3]*qz[1] + tmp[1]*qz[3] + tmp[2]*qz[0] - tmp[0]*qz[2];	// y
	q[2] = tmp[3]*qz[2] + tmp[2]*qz[3] + tmp[0]*qz[1] - tmp[1]*qz[0];	// z
	q[3] = tmp[3]*qz[3] - tmp[0]*qz[0] - tmp[1]*qz[1] - tmp[2]*qz[2];	// w

	float len = sqrtf( q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3] );
	assert( len > 0.0f );

	q[0] /= len;
	q[1] /= len;
	q[2] /= len;
	q[3] /= len;


	RotateAtAndUp( q );
	UpdateRightVector();
	UpdateViewPosition();
}
