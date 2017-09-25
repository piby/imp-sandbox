

Sampler::Sampler()
	: m_id(0)
{
}

Sampler::~Sampler()
{
	if( m_id )
		glDeleteSamplers( 1, &m_id );
}


void Sampler::create( const Data& data )
{
	glGenSamplers( 1, &m_id );
	glSamplerParameteri( m_id, GL_TEXTURE_MIN_FILTER, static_cast<int>(data.minf) );
	glSamplerParameteri( m_id, GL_TEXTURE_MAG_FILTER, static_cast<int>(data.magf) );

	glSamplerParameteri( m_id, GL_TEXTURE_WRAP_S, static_cast<int>(data.sCoord) );
	glSamplerParameteri( m_id, GL_TEXTURE_WRAP_T, static_cast<int>(data.tCoord) );
	glSamplerParameteri( m_id, GL_TEXTURE_WRAP_R, static_cast<int>(data.rCoord) );
}


inline void Sampler::bind(GLuint unit) const
{
	glBindSampler( unit, m_id );
}


void Sampler::unbind() const
{
	glBindSampler( 0, 0 );
}


inline MinFilter Sampler::getMinFilter() const
{
	int minFilter = 0;
	glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &minFilter );
	return static_cast<MagFilter>( minFilter );
}


inline MagFilter Sampler::getMagFilter() const
{
	int magFilter = 0;
	glGetSamplerParameteriv( m_id, GL_TEXTURE_MAG_FILTER, &magFilter );
	return static_cast<MagFilter>( magFilter );
}


inline WrapMode Sampler::getSWrapMode() const
{
	int mode = 0;
	glGetSamplerParameteriv( m_id, GL_TEXTURE_WRAP_S, &mode );
	return static_cast<WrapMode>( mode );
}


inline WrapMode Sampler::getTWrapMode() const
{
	int mode = 0;
	glGetSamplerParameteriv( m_id, GL_TEXTURE_WRAP_T, &mode );
	return static_cast<WrapMode>( mode );
}


inline WrapMode Sampler::getRWrapMode() const
{
	int mode = 0;
	glGetSamplerParameteriv( m_id, GL_TEXTURE_WRAP_R, &mode );
	return static_cast<WrapMode>( mode );
}

inline GLuint Sampler::getId() const
{
	return m_id;
}
