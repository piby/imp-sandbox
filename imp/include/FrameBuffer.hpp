#ifndef IMP_FRAME_BUFFER_OBJECT_HPP
#define IMP_FRAME_BUFFER_OBJECT_HPP


namespace imp
{

class FrameBufferObject
{

public:

	FrameBufferObject();
	~FrameBufferObject();

	// creates FBO, if all went ok it returns true
	bool Create( unsigned int width, unsigned int height );

	// removes FBO
	void Destroy();

	// start render to FBO
	void Bind();

	// stop rendering to FBO
	void Unbind();

	// returns width of currently bound buffer 
	int GetWidth();

	// returns height of currently bound buffer 
	int GetHeight();

	// returns id of texture that was used as colour buffer
	unsigned int GetTextureId();

	// returns FBO id
	unsigned int GetFBOId();


private:


	// handle to frame buffer object
	unsigned int m_fboId;

	// handle to depth buffer object
	unsigned int m_depthBufferId;

	// handle to texture that will be used like color buffer
	unsigned int m_textureId;

	//unsigned int m_stencilBufferID;
	//unsigned int m_colorBufferID;

};

}

#endif // IMP_FRAME_BUFFER_OBJECT_HPP
