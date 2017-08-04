#ifndef IMP_FRUSTUM_HPP
#define IMP_FRUSTUM_HPP

namespace imp
{

class Frustum
{

public:

    enum class Plane
	{
        RIGHT,
        LEFT,
        BOTTOM,
        TOP,
        BACK,
        FRONT
	};

    enum class Test
	{
        OUTSIDE,
        INSIDE,
        INTERSECT
	};


public:

    /// Constructor
    Frustum() = default;

    /// Destructor
    ~Frustum() = default;


    /// Recalculate frustum planes basing on model-view matrix and projection matrix
	void Update( const float* modelViewVect16, const float* projVect16 );


    /// Test if point is inside frustum
    Test ContainsPoint( const float* posVect3 ) const;

    /// Test if sphere is fully or partially inside frustum
    Test ContainsSphere( const float* posVect3, float r ) const;

    /// Test if aabb is fully or partially inside frustum
    Test ContainsAABB( const float* minVect3, const float* maxVect3 ) const;


    /// Return parameters of specified frustum plane
    void GetPlane( Plane plane, float& a, float& b, float& c, float& d ) const;


protected:

	// frustum planes
	float m_frustum[6][4];

};

}

#endif // IMP_FRUSTUM_HPP
