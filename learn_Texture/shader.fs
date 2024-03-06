#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;


void main()
{
    //(80% container, 20% awesomeface)
    FragColor = mix(texture(ourTexture,TexCoord) , texture(ourFace,TexCoord), 0.2); 
}