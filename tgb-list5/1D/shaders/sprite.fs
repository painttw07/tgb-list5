#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

// pixels da textura
uniform sampler2D screenTexture;

void main()
{
    FragColor = texture(screenTexture, TexCoords);
    FragColor.r = 1.0 - FragColor.r;
    FragColor.g = 1.0 - FragColor.g;
    FragColor.b = 1.0 - FragColor.b;
   
   
   //FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
}
