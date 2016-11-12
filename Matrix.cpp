#include"Matrix.h"
#include<string.h>

Matrix::Matrix()
{

}

Matrix::Matrix(const MATRIX& M) : MATRIX(M)
{
	*this = M;
}

Matrix& Matrix::operator=(const MATRIX& M)
{
	memcpy( m, &M.m, sizeof(float)*16 );
	return *this;
}

void Matrix::setZero()
{
	Fill( 0.0f );
}

void Matrix::setIdentity()
{
	//set most elements to zero
    m[0][1] = m[0][2] = m[0][3] =
    m[1][0] = m[1][2] = m[1][3] =
    m[2][0] = m[2][1] = m[2][3] =
    m[3][0] = m[3][1] = m[3][2] = 0.0f;
	
	//set diagonals 11,22,33,44 to one
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;

}
void Matrix::Fill( int value )
{
	Fill( (float) value );
}
void Matrix::Fill( float value )
{
	m[0][0] = m[0][1] = m[0][2] = m[0][3] =
    m[1][0] = m[1][1] = m[1][2] = m[1][3] =
    m[2][0] = m[2][1] = m[2][2] = m[2][3] =
    m[3][0] = m[3][1] = m[3][2] = m[3][3] = value;
}

void Matrix::Fill( double value )
{
	Fill ((float) value );
}

void Matrix::Translate(float x, float y, float z)
{
	m[0][0] +=m[3][0]*x; m[0][1] += m[3][1]*x; m[0][2] += m[3][2]*x; m[0][3] += m[3][3]*x;
	m[1][0] +=m[3][0]*y; m[1][1] += m[3][1]*y; m[1][2] += m[3][2]*y; m[1][3] += m[3][3]*y;
	m[2][0] +=m[3][0]*z; m[2][1] += m[3][1]*z; m[2][2] += m[3][2]*z; m[2][3] += m[3][3]*z;
}

void Matrix::Translate(CVector& V)
{
	Translate( (float)V.x, (float)V.y, (float)V.z );
}

void Matrix::rotateYawPitchRoll(float z, float x, float y)
{
	rotateZ(z);
	rotateX(x);
	rotateY(y);
}

void Matrix::rotateYawPitchRoll(CVector& V)
{
	rotateYawPitchRoll((float)V.z,(float)V.x,(float)V.y);
}

void Matrix::rotateX( float x )
{
	float c = cosf(DEG2RAD(x));
    float s = sinf(DEG2RAD(x));
    float m4 = m[1][0], m5 = m[1][1], m6 = m[1][2],  m7 = m[1][3],
          m8 = m[2][0], m9 = m[2][1], m10= m[2][2], m11= m[2][3];

    m[1][0] = m4 * c + m8 *-s;
    m[1][1] = m5 * c + m9 *-s;
    m[1][2] = m6 * c + m10*-s;
    m[1][3] = m7 * c + m11*-s;
    m[2][0] = m4 * s + m8 * c;
    m[2][1] = m5 * s + m9 * c;
    m[2][2]= m6 * s + m10* c;
    m[2][3]= m7 * s + m11* c;
}

void Matrix::rotateY( float y )
{
	float c = cosf(DEG2RAD(y));
    float s = sinf(DEG2RAD(y));
    float m0 = m[0][0], m1 = m[0][1], m2 = m[0][2],  m3 = m[0][3],
          m8 = m[2][0], m9 = m[2][1], m10= m[2][2], m11= m[2][3];

    m[0][0] = m0 * c + m8 * s;
    m[0][0] = m1 * c + m9 * s;
    m[0][2] = m2 * c + m10* s;
    m[0][3] = m3 * c + m11* s;
    m[2][0] = m0 *-s + m8 * c;
    m[2][1] = m1 *-s + m9 * c;
    m[2][2]= m2 *-s + m10* c;
    m[2][3]= m3 *-s + m11* c;
}

void Matrix::rotateZ( float z )
{
	float c = cosf(DEG2RAD(z));
    float s = sinf(DEG2RAD(z));
    float m0 = m[0][0], m1 = m[0][1], m2 = m[0][2],  m3 = m[0][3],
          m4 = m[1][0], m5 = m[1][1], m6 = m[1][2],  m7 = m[1][3];

    m[0][0] = m0 * c + m4 *-s;
    m[1][1] = m1 * c + m5 *-s;
    m[2][2] = m2 * c + m6 *-s;
    m[3][3] = m3 * c + m7 *-s;
    m[1][0] = m0 * s + m4 * c;
    m[1][1] = m1 * s + m5 * c;
    m[1][2] = m2 * s + m6 * c;
    m[1][3] = m3 * s + m7 * c;
}

void Matrix::Scale( float x, float y, float z )
{
	m[0][0] = m[0][0]*x;   m[0][1] = m[0][1]*x;   m[0][2] = m[0][2]*x;   m[0][3] = m[0][3]*x;
    m[1][0] = m[1][0]*y;   m[1][1] = m[1][1]*y;   m[1][2] = m[1][2]*y;   m[1][3] = m[1][3]*y;
    m[2][0] = m[2][0]*z;   m[2][1] = m[2][1]*z;   m[2][2]= m[2][2]*z;    m[2][3]= m[2][3]*z;
}

void Matrix::Scale( CVector& V )
{
	Scale( (float)V.x, (float)V.y, (float)V.z );
}
