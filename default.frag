#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Gets the Texture Unit from the main function
uniform sampler2D tex0;

//uniform uvec4 img[1024];

void main() {
	FragColor = texture(tex0, texCoord);
	//FragColor = vec4(color, 0); //texture(tex0, texCoord);
	//FragColor = vec4(texCoord.x, 0, 0, 0); //texture(tex0, texCoord);
	//FragColor = img[uint(((texCoord.y) * 1024 * 1024)+((texCoord.x) * 1024))]; //texture(tex0, texCoord);
	//FragColor = vec4(img[200].xyz, 0); //texture(tex0, texCoord);
	//FragColor = img[1]; //texture(tex0, texCoord);
}