#ifndef __TERRAIN_H 
#define __TERRAIN_H 
 
#define WIN32_LEAN_AND_MEAN 
#define WIN32_EXTRA_LEAN 
 
#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 
 
#include "camera.h" 
#include "object.h" 
#include "texture.h" 
#include "vector.h" 
 
class CTerrain : public CObject 
{ 
private: 
	int width;		// ���δ�СΪwidth X width�������2^n 
	float widthScale;	// ���ο�ȵı��� 
	float terrainMul; 
	float heightMul; 
	float scanDepth; 
	float textureMul; 
 
	float RangedRandom(float v1,float v2); 
	void NormalizeTerrain(float field[],int size); 
	void FilterHeightBand(float *band,int stride,int count,float filter); 
	void FilterHeightField(float field[],int size,float filter); 
	void MakeTerrainPlasma(float field[],int size,float rough); 
 
protected: 
	// ����û�ж���Ч�� 
	void OnAnimate(scalar_t deltaTime) {} 
 
	void OnDraw(CCamera *camera); 
	void OnCollision(CObject *collisionObject); 
 
public: 
	float *heightMap;		// ��̬�߳�ӳ�� 
	CTexture terrainTex[5];	// �����ϵĶ������� 
	float fogColor[4];		// �����ɫ 
 
	CTerrain(); 
	CTerrain(int width, float rFactor); 
	~CTerrain() { delete [] heightMap; } 
 
	void Load() {} 
	void Unload() {} 
 
	void BuildTerrain(int width, float rFactor); 
	
	float GetWidth() { return (float)width; }
	float GetMul() { return terrainMul; }
	float GetScanDepth() { return scanDepth; }

	float GetHeight(float x, float z) 
	{	 
		float projCameraX, projCameraZ; 
 
		projCameraX = x / terrainMul; 
		projCameraZ = z / terrainMul; 
		// ����߳�����(Col0, Row0)��(Col1, Row1) 
		int col0 = int(projCameraX); 
		int row0 = int(projCameraZ); 
		int col1 = col0 + 1; 
		int row1 = row0 + 1; 
		// ȷ����Ԫ���겻�����߳����� 
		if (col1 > width) 
			col1 = 0; 
		if (row1 > width) 
			row1 = 0; 
		// ��ȡ��Ԫ���ĸ��ǵĸ߶� 
		float h00 = heightMul * (float)heightMap[col0 + row0*width]; 
		float h01 = heightMul * (float)heightMap[col1 + row0*width]; 
		float h11 = heightMul * (float)heightMap[col1 + row1*width]; 
		float h10 = heightMul * (float)heightMap[col0 + row1*width]; 
		// ��������������ڵ�Ԫ���λ�� 
		float tx = projCameraX - float(col0); 
		float ty = projCameraZ - float(row0); 
		// ��һ���ǽ���˫���Բ�ֵ 
		float txty = tx * ty; 
 
		float final_height = h00 * (1.0f - ty - tx + txty) 
						+ h01 * (tx - txty) 
						+ h11 * txty 
						+ h10 * (ty - txty); 
		return final_height; 
	} 
}; 
 
#endif
