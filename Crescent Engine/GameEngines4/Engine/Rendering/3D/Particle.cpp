#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_) {
	VAO = 0;
	VBO = 0;
	modelLocation = 0;
	viewLocation = 0;
	projectionLocation = 0;

	colourLocation = 0; 
	textureLocation = 0; 

	shaderProgram = shaderProgram_; 
	textureID = textureID_; 

	lifeTime = 0.0f; 
	particleSize = 0.0f; 
	angle = 0.0f;

	velocity = glm::vec3(0.0f); 
	position = glm::vec3(0.0f);
	particleColour = glm::vec3(0.0f); 
	rotation = glm::vec3(0.0f);

	GenerateBuffers();
}

Particle::~Particle() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (vertexList.size() > 0) {
		vertexList.clear();
	}
}

void Particle::SetLifeTime(float lifeTime_){
	lifeTime = lifeTime_;
}

void Particle::SetParticleSize(float particleSize_){
	particleSize = particleSize_;
}

void Particle::SetPosition(glm::vec3 position_){
	position = position_;
}

void Particle::SetVelocity(glm::vec3 velocity_){
	velocity = velocity_;
}

float Particle::GetLifeTime(){
	return lifeTime;
}

float Particle::GetParticleSize(){
	return particleSize;
}

glm::vec3 Particle::GetPosition(){
	return position;
}

glm::vec3 Particle::GetVelocity(){
	return velocity;
}

glm::mat4 Particle::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const {
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);

	return model;
}

void Particle::Render(Camera* camera_) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GetTransform(position, angle, rotation, glm::vec3(particleSize))));

	glUniform3f(colourLocation, particleColour.x, particleColour.y, particleColour.z);
	glUniform1ui(textureLocation, textureID); 

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}

void Particle::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex3D), &vertexList[0], GL_STATIC_DRAW);

	// Particle Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (GLvoid*)offsetof(Vertex3D, position));

	// Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (GLvoid*)offsetof(Vertex3D, texCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "projection");
}