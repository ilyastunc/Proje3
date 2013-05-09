//
//  Model.h
//  Ders 5
//
//  Created by Gurel Erceis on 3/11/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//
// Assimp kutuphanesini kullaniyoruz.

#ifndef Fresnel_h
#define Fresnel_h
#include <windows.h>
#include "Camera.h"
#include "ShadedGeometry.h"
#include "Geometry.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <vector>
#include "SceneNode.h"

class Fresnel: public ShadedGeometry{
public:
    Fresnel(char *filename):
    ShadedGeometry(filename,
                   "fresnel.vert",
                   "fresnel.frag")
    {
        generateBuffers();    
    }
	std::vector<Fresnel*> children;
    Fresnel *parent;

   
    ~Fresnel(){
        
    }

	glm::mat4 getModelMatrix(){
        glm::mat4 result =  modelMatrix1;
        SceneNode* temp = parent;
        while( temp != NULL ){
            result =  temp->getModelMatrix() * result;
            temp = temp->parent;
        }
        return result;
    }

    void draw(SceneNode *camera){
        
        glUseProgram(programId);
        
        glm::mat4 MVPmatrix = ((Camera*)camera)->projectionMatrix * camera->getInverseModelMatrix() * getModelMatrix();
        
        glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVPmatrix[0][0]);
       
        
        // vertex bufferi bagla
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // indiceleri bagla
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);
        
        // Attributelari enable et
        glEnableVertexAttribArray(AttributePosition);
        
        // ciz
        glDrawElements(GL_TRIANGLES, int(faceArray.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
        

        // baglantilari kopar
        glDisableVertexAttribArray(AttributePosition);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        
        glUseProgram(0);
    }
private:
    GLuint UniformMVP;
    GLuint AttributePosition;

    
    void generateBuffers(){
        
        UniformMVP = glGetUniformLocation(programId, "MVP");
        printf("UniformMVP: %d\n",UniformMVP);
        
        AttributePosition = glGetAttribLocation(programId, "Position");
        printf("Position Attribute: %d\n", AttributePosition);
        
    }
	glm::mat4 modelMatrix1;
};

#endif
