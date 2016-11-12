#include"vector.h"

typedef struct MATRIX
{
	union
	{
		struct
		{
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};
}MATRIX;

class Matrix : public MATRIX
{
public:
	Matrix();
	Matrix(const MATRIX&);
	Matrix& operator=( const MATRIX& M);
	void setZero();
	void setIdentity();
	void Fill(int);
	void Fill(float);
	void Fill(double);
	void Translate( float x, float y, float z );
    void Translate( CVector& );
	void rotateYawPitchRoll(float x, float y, float z);
	void rotateYawPitchRoll(CVector& V);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	void Scale(float x, float y, float z);
	void Scale(CVector&);

};