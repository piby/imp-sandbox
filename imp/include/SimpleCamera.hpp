#ifndef IMP_SIMPLE_CAMERA_HPP
#define IMP_SIMPLE_CAMERA_HPP

namespace imp
{

class SimpleCamera
{

public:

	// constructor
	SimpleCamera();

	// destructor
	~SimpleCamera();


	// set camera position
	void SetPosition( float x, float y, float z );

	// set camera orientation by defining look direction
	// and up vector, both should be normalized
	void SetOrientation( float* atVect3, float* upVect3 );


	// move camera along world axes
	void Move( float xAxisAdd, float yAxisAdd, float zAxisAdd );		

	// move camera along it's own axes
	void MoveRelative( float rightAdd, float upAdd, float dirAdd );		

	// rotate camera along world axes, angles are in radians
	void Rotate( float xAngleRad, float yAngleRad, float zAngleRad );
	
	// rotate camera along it's own axes, angles are in radians
	void RotateRelative( float rightAngleRad, float upAngleRad, float dirAngleRad );



	// returns camera position
	const float* GetPosition() const;

	// returns pointer to 16 element
	// array containing view matrix
	const float* GetViewMatrix() const;


	// retrieve camera look direction
	void GetDirection( float* vect3 ) const;

	// retrieve camera up vector
	void GetUpVector( float* vect3 ) const;

	// retrieve camera right vector
	void GetRightVector( float* vect3 ) const;


protected:

	// rotates direction vector and
	// up vector by given quaternion
	void RotateAtAndUp( float* quat4 );

	// updates right vector
	void UpdateRightVector();

	// updates part of view matrix
	// that is responsible for position
	void UpdateViewPosition();


private:

	// camera position
	float m_position[3];

	union
	{
		// camera view matrix
		float m_viewMatrix[16];


		struct
		{
			// order of following values is 
			// equivalent to ogl view matrix
			// (see man pages for gluLookAt
			// and glMultMatrix)

			// first column
			float m_rightX;
			float m_upX;
			float m_negDirX;
			float m_dummyA;

			// second column
			float m_rightY;
			float m_upY;
			float m_negDirY;
			float m_dummyB;

			// third column
			float m_rightZ;
			float m_upZ;
			float m_negDirZ;
			float m_dummyC;

			// fourth column
			float m_rightPos;
			float m_upPos;
			float m_negDirPos;
			float m_dummyD;
		};
	};

};

#include "SimpleCamera.inl"

}

#endif // IMP_SIMPLE_CAMERA_HPP
