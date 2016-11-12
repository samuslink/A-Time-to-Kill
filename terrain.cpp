#include "terrain.h"    
   
CTerrain::CTerrain()   
{   
    width = 256;   
    scanDepth = 80.0;   
    terrainMul = 50.0;   
    textureMul = 0.25;   
    widthScale = 5.0;   
    heightMul = 175.0;   
    fogColor[0] = 0.75f;   
    fogColor[1] = 0.9f;   
    fogColor[2] = 1.0f;   
    fogColor[3] = 1.0f;   
    // CObject���������    
    position = CVector(0,0,0);   
    velocity = CVector(0,0,0);   
    acceleration = CVector(0,0,0);   
    size = width*terrainMul/2;   
    // ���ɵ���    
    BuildTerrain(width, 0.5f);   
}   
   
CTerrain::CTerrain(int w, float rFactor)   
{   
    width = w;   
    scanDepth = 80.0;   
    terrainMul = 50.0;   
    textureMul = 0.25;   
    widthScale = 5.0;   
    heightMul = 175.0;   
    fogColor[0] = 0.75f;   
    fogColor[1] = 0.9f;   
    fogColor[2] = 1.0f;   
    fogColor[3] = 1.0f;   
    // CObject��������    
    position = CVector(0,0,0);   
    velocity = CVector(0,0,0);   
    acceleration = CVector(0,0,0);   
    size = width*terrainMul/2;   
    // ���ɵ���    
    BuildTerrain(width, rFactor);   
}   
   
void CTerrain::BuildTerrain(int w, float rFactor)   
{   
    width = w;   
    heightMap = new float[width*width];   
    MakeTerrainPlasma(heightMap, width, rFactor);   
    // װ������    
	terrainTex[0].LoadTexture("ground.tga");  
    glGenTextures(1, &terrainTex[0].texID);   
    glBindTexture(GL_TEXTURE_2D, terrainTex[0].texID);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   //or GL_CLAMP    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   //or GL_CLAMP    
   
    switch (terrainTex[0].textureType)   
    {   
    case BMP:   
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, terrainTex[0].width, terrainTex[0].height,   
                    GL_RGB, GL_UNSIGNED_BYTE, terrainTex[0].data);   
        break;   
    case PCX:   
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, terrainTex[0].width, terrainTex[0].height,   
                    GL_RGBA, GL_UNSIGNED_BYTE, terrainTex[0].data);   
        break;   
    case TGA:   
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, terrainTex[0].width, terrainTex[0].height,   
                    GL_RGB, GL_UNSIGNED_BYTE, terrainTex[0].data);   
        break;   
    default:   
        break;   
    }   
}   
   
void CTerrain::OnCollision(CObject *collisionObject)   
{}   
   
void CTerrain::OnDraw(CCamera *camera)   
{   
    int z, x;   
   
    glEnable(GL_DEPTH_TEST);   
   
    glFogi(GL_FOG_MODE, GL_LINEAR);   
    glFogfv(GL_FOG_COLOR, fogColor);   
    glFogf(GL_FOG_START, scanDepth * 0.2f);   
    glFogf(GL_FOG_END, scanDepth * 2.5);   
    glHint(GL_FOG_HINT, GL_FASTEST);   
    glEnable(GL_FOG);   
   
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   
    glEnable(GL_BLEND);   
    glEnable(GL_ALPHA_TEST);   
    glAlphaFunc(GL_GREATER,0.0);   
    glDisable(GL_ALPHA_TEST);   
   
    glEnable(GL_TEXTURE_2D);   
    glBindTexture(GL_TEXTURE_2D, terrainTex[0].texID);   
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   
   
    glColor3f(1.0, 1.0, 1.0);   
    for (z = (int)(camera->position.z / terrainMul - scanDepth), z=z<0?0:z; (z < camera->position.z / terrainMul + scanDepth) && z < width-1; z++)   
    {   
        glBegin(GL_TRIANGLE_STRIP);   
        for (x = (int)(camera->position.x / terrainMul - scanDepth), x=x<0?0:x; (x < camera->position.x / terrainMul + scanDepth) && x < width-1; x++)   
        {   
            glTexCoord2f(textureMul * x, textureMul * z);   
            glVertex3f((float)x*terrainMul, (float)heightMap[x + z*width]*heightMul, (float)z*terrainMul);   
   
            glTexCoord2f(textureMul * (x+1), textureMul * z);   
            glVertex3f((float)(x+1)*terrainMul, (float)heightMap[x+1 + z*width]*heightMul, (float)z*terrainMul);   
   
            glTexCoord2f(textureMul * x, textureMul * (z+1));   
            glVertex3f((float)x*terrainMul, (float)heightMap[x + (z+1)*width]*heightMul, (float)(z+1)*terrainMul);   
   
            glTexCoord2f(textureMul * (x+1), textureMul * (z+1));   
            glVertex3f((float)(x+1)*terrainMul, (float)heightMap[x+1 + (z+1)*width]*heightMul, (float)(z+1)*terrainMul);   
        }   
        glEnd();   
    }   
}   
   
// ��v1��v2֮���������һ����    
float CTerrain::RangedRandom(float v1,float v2)   
{   
    return v1 + (v2-v1)*((float)rand())/((float)RAND_MAX);   
}   
// �Ը����ĸ߳����ݣ�����淶����ʹ����СֵΪ0.0�����ֵΪ1.0    
void CTerrain::NormalizeTerrain(float field[],int size)   
{   
    float maxVal,minVal,dh;   
    int i;   
    // ���Ҹ߳����ݵ����ֵ����Сֵ    
    maxVal = field[0];   
    minVal = field[0];   
    for (i=1;i<size*size;i++)   
    {   
        if (field[i] > maxVal)    
        {   
            maxVal = field[i];   
        }   
        else if (field[i] < minVal)    
        {   
            minVal = field[i];   
        }   
    }   
    // �����ݶȷ�Χ    
    if (maxVal <= minVal) return;   
    dh = maxVal-minVal;   
    // ������ֵ���ţ�ʹ֮λ��0-1֮��    
    for (i=0;i<size*size;i++)   
    {   
        field[i] = (field[i]-minVal)/dh;   
    }   
}   
   
void CTerrain::FilterHeightBand(float *band,int stride,int count,float filter)   
{   
    int i,j=stride;   
    float v = band[0];   
    for (i=0;i<count-1;i++)   
    {   
        band[j] = filter*v + (1-filter)*band[j];   
        v = band[j];   
        j+=stride;   
    }   
}   
   
void CTerrain::FilterHeightField(float field[],int size,float filter)   
{   
    int i;   
   
    for (i=0;i<size;i++)   
    {   
        FilterHeightBand(&field[size*i],1,size,filter);   
    }   
    for (i=0;i<size;i++)   
    {   
        FilterHeightBand(&field[size*i+size-1],-1,size,filter);   
    }   
    for (i=0;i<size;i++)   
    {   
        FilterHeightBand(&field[i],size,size,filter);   
    }   
    for (i=0;i<size;i++)   
    {   
        FilterHeightBand(&field[size*(size-1)+i],-size,size,filter);   
    }   
}   
   
// ���ɵ����㷨    
void CTerrain::MakeTerrainPlasma(float field[],int size,float rough)   
{   
    int i,j,ni,nj,mi,mj,pmi,pmj,rectSize = size;   
    float dh = (float)rectSize/2,r = (float)pow(2,-1*rough);   
    field[0] = 0;   
    while(rectSize > 0)   
    {   
        for (i=0;i<size;i+=rectSize)   
        for (j=0;j<size;j+=rectSize)   
        {   
            ni = (i+rectSize)%size;   
            nj = (j+rectSize)%size;   
            mi = (i+rectSize/2);   
            mj = (j+rectSize/2);   
            field[mi+mj*size] = (field[i+j*size] + field[ni+j*size] + field[i+nj*size] + field[ni+nj*size])/4 + RangedRandom(-dh/2,dh/2);   
        }   
        for (i=0;i<size;i+=rectSize)   
        for (j=0;j<size;j+=rectSize)   
        {   
            ni = (i+rectSize)%size;   
            nj = (j+rectSize)%size;   
            mi = (i+rectSize/2);   
            mj = (j+rectSize/2);   
            pmi = (i-rectSize/2+size)%size;   
            pmj = (j-rectSize/2+size)%size;   
            // ������ε��ϱߵ�ֵ    
            field[mi+j*size] = (field[i+j*size] + field[ni+j*size] + field[mi+pmj*size] + field[mi+mj*size])/4 + RangedRandom(-dh/2,dh/2);   
            // ������ε���ߵ�ֵ    
            field[i+mj*size] = (field[i+j*size] + field[i+nj*size] + field[pmi+mj*size] + field[mi+mj*size])/4 + RangedRandom(-dh/2,dh/2);   
        }   
        // ���õڶ��ε�����ֵ    
        rectSize /= 2;   
        dh *= r;   
    }   
    // �淶���������ݣ�ʹ֮λ��0-1֮��    
    NormalizeTerrain(field,size);   
}