#include"gun.h"

void CGun::OnDraw(CCamera *camera)
{
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glTranslatef(camera->position.x,camera->position.y-0.1f,camera->position.z + 0.05f);
		glRotatef(RAD2DEG(95.8),0.0,1.0,0.0);
		glRotatef(-camera->pitch,1.0,0.0,0.0);
		glRotatef(-camera->yaw,0.0,1.0,0.0);
		//glRotatef(camera->look.z,0.0,0.0,1.0);
		//gluLookAt(camera->position.x,camera->position.y - 0.2f,camera->position.z,camera->lookAt.x,camera->lookAt.y,camera->lookAt.z,0.0,1.0,0.0);
		gluCylinder(quadratic,0.02f,0.02f,1.0f,40,40); //The Cylinder for my gun.
		//glRotatef(camera->lookAt.z - camera->position.z,0.0,0.0,1.0);
		//glRotatef(0.0, 0.0, 0.0, 1.0);
		glScalef(0.025f, 0.025f, 0.025f);
		RenderFrame(0);
		glDisable(GL_TEXTURE_2D);
}

CGun::CGun(CVector *look)
{
	position = CVector(0.0, 0.0, 0.0);
	lookAt = look->UnitVector();
	forward = lookAt;
	up = CVector(0.0, 1.0, 0.0);
	right = forward.CrossProduct(up); //CVector(1.0, 0.0, 0.0);
	velocity = CVector(0.0, 0.0, 0.0);
	acceleration = CVector(0.0, 0.0, 0.0);	
	yaw = 0.0;
	pitch = 0.0;
}

CGun::CGun(CVector *pos, CVector *look)
{
	position = *pos;
	lookAt = look->UnitVector();
	forward = lookAt;
	up = CVector(0.0, 1.0, 0.0);
	right = CVector(1.0, 0.0, 0.0);
	velocity = CVector(0.0, 0.0, 0.0);
	acceleration = CVector(0.0, 0.0, 0.0);
	yaw = 0.0;
	pitch = 0.0;
}

void CGun::UpdateLookAt()
{
	CVector look = CVector(finalLookAt.x - lookAt.x,
					   finalLookAt.y - lookAt.y,
					   finalLookAt.z - lookAt.z);
	lookAtVel = look * 0.5;
}

void CGun::LookAtNow(CObject *object)
{
	lookAt = object->position;
}

void CGun::LookAt(CObject *object)
{
	CVector v = CVector(object->position - lookAt);
	initLookAt = lookAt;
	finalLookAt = object->position;
	lookAtAccel = -lookAt * 0.25f;
	UpdateLookAt();
}

void CGun::RotatePitch(scalar_t radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);
	up.y = cosine * up.Length();
	up.z = sine * up.Length();
	forward.y = -sine * forward.Length();
	forward.z = cosine * forward.Length();
}

void CGun::RotateRoll(scalar_t radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);
	right.x = cosine * right.Length();
	right.y = sine * right.Length();
	up.x = -sine * forward.Length();
	up.y = cosine * forward.Length();
}

void CGun::RotateYaw(scalar_t radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);
	right.x = cosine * right.Length();
	right.z = sine * right.Length();
	forward.x = -sine * forward.Length();
	forward.z = cosine * forward.Length();
}

void CGun::Load()
{

	//gluCylinder(quadratic,0.02f,0.02f,1.0f,40,40); //The Cylinder for my gun.
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals ( NEW ) 
	gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords ( NEW ) 

	//glTranslatef(objec, camera->position.y, camera->position.z);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0].texID); 
	glBegin(GL_QUADS); // top face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
	glBegin(GL_QUADS); // front face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS); // right face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
	glBegin(GL_QUADS); // left face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();
	glBegin(GL_QUADS); // bottom face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
	glBegin(GL_QUADS); // back face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

}

void CGun::UpdateMoveTo()
{
	CVector pos = CVector(finalPosition.x - position.x,
					  finalPosition.y - position.y,
					  finalPosition.z - position.z);
	velocity = pos * 0.5;
}

void CGun::MoveToNow(CObject *object)
{
	position = object->position;
}

void CGun::MoveToNow(scalar_t x, scalar_t y, scalar_t z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
void CGun::MoveTo(CObject *object)
{
	CVector v = CVector(object->position - position);
	initPosition = position;
	finalPosition = object->position;
	acceleration = -position * 0.25f;
	UpdateMoveTo();
}

void CGun::Animate(float yaw, float pitch)
{
	
}

void CGun::OnAnimate(scalar_t deltaTime)
{
	if ((yaw >= 360.0f) || (yaw <= -360.0f))
          yaw = 0.0f;
     if (pitch > 60.0f)
          pitch = 60.0f;
     if (pitch < -60.0f)
          pitch = -60.0f;
     float cosYaw = (scalar_t)cos(DEG2RAD(yaw));
     float sinYaw = (scalar_t)sin(DEG2RAD(yaw));
     float sinPitch = (scalar_t)sin(DEG2RAD(pitch));
	 float speed = velocity.z * deltaTime;
     float strafeSpeed = velocity.x * deltaTime;
     if (speed > 15.0)
          speed = 15.0;
     if (strafeSpeed > 15.0)
          strafeSpeed = 15.0;
     if (speed < -15.0)
          speed = -15.0;
     if (strafeSpeed < -15.0)
          strafeSpeed = -15.0;

     if (velocity.Length() > 0.0)
          acceleration = -velocity * 1.5f;

     velocity += acceleration*deltaTime;

     position.x += float(cos(DEG2RAD(yaw + 90.0)))*strafeSpeed;
     position.z += float(sin(DEG2RAD(yaw + 90.0)))*strafeSpeed;
     position.x += float(cosYaw)*speed;
     position.z += float(sinYaw)*speed;

     lookAt.x = float(position.x + cosYaw);
     lookAt.y = float(position.y + sinPitch);
     lookAt.z = float(position.z + sinYaw);
	 //glRotatef(lookAt.x,0.0,1.0,0.0);
}