#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 ourCoords;

uniform float xxsOffset;
uniform float xOffset;
uniform float xxOffset;

void main()
{
    /*if(aPos.x==1.0f && aPos.y==-1.0f){
        gl_Position = vec4(aPos.x - xOffset, aPos.y+xOffset, aPos.z, 1.0);
    }else{
    gl_Position = vec4(aPos.x , aPos.y, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
    }*/
    gl_Position = vec4(aPos.x , aPos.y, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
    //ourColor= vec3(xOffset,xOffset,xOffset);
    ourColor = aColor;
    //ourColor = aPos;
    ourCoords = aPos;
}