#pragma once
#include <GL/glew.h>
#include <cstddef>

class Facemesh
{
public:
	Facemesh();
	~Facemesh();

	void CreateMesh();
	void Render();
	void ClearMesh();
	void updateVertex(int index, GLfloat x, GLfloat y, GLfloat z);

private:
	GLuint VAO, VBO_position, VBO_TexCoord, EBO;

	GLfloat vertices[68 * 3];

	const unsigned int indices[285] = {
	20, 21, 23,
	21, 22, 23,
	0, 1, 36,
	15, 16, 45,
	0, 36, 17,
	16, 26, 45,
	17, 18, 37, //cw
	25, 26, 44, //cw
	17, 36, 37,
	26, 44, 45,
	18, 19, 38, //cw
	24, 25, 43, //cw
	18, 37, 38,
	25, 43, 44,
	19, 20, 38, //cw
	23, 24, 43, //cw
	20, 21, 39, //cw
	22, 23, 42, //cw
	20, 38, 39,
	23, 42, 43,
	21, 22, 27, //cw
	21, 27, 39, //cw
	22, 27, 42,
	27, 28, 42,
	27, 28, 39, //cw
	28, 42, 47, //cw
	28, 39, 40,
	1,  36, 41, // cw
	15, 45, 46,
	1,  2, 41,
	14, 15, 46,
	28, 29, 40, //cw
	28, 29, 47,
	2,  40, 41,
	14, 46, 47,
	2,  29, 40,
	14, 29, 47, //cw
	2,  3, 29,
	13, 14, 29,
	29, 30, 31, //cw
	29, 30, 35,
	3,  29, 31, //cw
	13, 29, 35,
	30, 32, 33,
	30, 33, 34,
	30, 31, 32,
	30, 34, 35,
	3,  4, 31,
	12, 13, 35,
	4,  5, 48,
	11, 12, 54,
	5, 6, 48,
	10, 11, 54,
	6, 48, 59, //cw
	10, 54, 55,
	6, 7, 59,
	9, 10, 55,
	7, 58, 59,
	9, 55, 56,
	8, 57, 58,
	8, 56, 57,
	7, 8, 58,
	8, 9, 56,
	4, 31, 48, //cw
	12, 35, 54,
	31, 48, 49,
	35, 53, 54,
	31, 49, 50,
	35, 52, 53,
	31, 32, 50, //cw
	34, 35, 52, //cw
	32, 33, 50, //cw
	33, 34, 52, //cw
	33, 50, 51,
	33, 51, 52,
	49, 48, 60,
	64, 54, 53,
	55, 54, 64,
	56, 55, 65,
	53, 63, 64,
	63, 53, 52,
	55, 64, 65,
	58, 57, 66,
	59, 58, 67,
	48, 59, 60,
	60, 59, 67,
	67, 58, 66,
	57, 56, 66,
	56, 65, 66,
	60, 61, 49, //
	49, 61, 50, //
	50, 61, 51, //
	51, 61, 62, //
	62, 63, 51,
	51, 63, 52,
	};

	const GLfloat texture_coord[136] = {
		0.017f, 0.315f, //1
		0.023f, 0.419f,
		0.038f, 0.522f,
		0.068f, 0.621f,
		0.122f, 0.709f, //5
		0.196f, 0.785f,
		0.283f, 0.851f,
		0.384f, 0.901f,
		0.499f, 0.923f,
		0.614f, 0.901f, //10
		0.713f, 0.851f,
		0.802f, 0.785f,
		0.876f, 0.708f,
		0.929f, 0.619f,
		0.960f, 0.521f, //15
		0.976f, 0.418f,
		0.980f, 0.314f,
		0.149f, 0.172f,
		0.204f, 0.139f,
		0.270f, 0.126f, //20
		0.338f, 0.129f,
		0.402f, 0.146f,
		0.595f, 0.146,
		0.660f, 0.120f,
		0.729f, 0.126f, //25
		0.794f, 0.139f,
		0.849f, 0.171f,
		0.498f, 0.248f,
		0.499f, 0.307f,
		0.500f, 0.366f, //30
		0.500f, 0.423f,
		0.427f, 0.483f,
		0.463f, 0.494f,
		0.500f, 0.500f,
		0.534f, 0.493f, //35
		0.570f, 0.484f,
		0.227f, 0.271f,
		0.267f, 0.248f,
		0.320f, 0.247f,
		0.366f, 0.271f, //40
		0.317f, 0.283f,
		0.268f, 0.283f,
		0.633f, 0.271f,
		0.678f, 0.247f,
		0.732f, 0.248f, //45
		0.777f, 0.271f,
		0.731f, 0.283f,
		0.681f, 0.283f,
		0.343f, 0.632f,
		0.385f, 0.594f, //50
		0.439f, 0.570f,
		0.500f, 0.573f,
		0.559f, 0.570f,
		0.612f, 0.596f,
		0.655f, 0.632f, //55
		0.616f, 0.676f,
		0.563f, 0.708f,
		0.500f, 0.718f,
		0.434f, 0.708f,
		0.381f, 0.676f, //60
		0.382f, 0.630f,
		0.438f, 0.609f,
		0.500f, 0.607f,
		0.559f, 0.609f,
		0.615f, 0.630f, //65
		0.562f, 0.652f,
		0.500f, 0.664f,
		0.437f, 0.652f
	};



	//const GLfloat texture_coord[136] = {
	//	0.102f, 0.232f, //0
	//	0.104f, 0.338f,
	//	0.117f, 0.443f,
	//	0.141f, 0.551f,
	//	0.180f, 0.646f,
	//	0.246f, 0.732f, //5
	//	0.322f, 0.809f,
	//	0.410f, 0.865f,
	//	0.519f, 0.881f,
	//	0.609f, 0.864f,
	//	0.695f, 0.803f, //10
	//	0.773f, 0.729f,
	//	0.836f, 0.639f,
	//	0.877f, 0.541f,
	//	0.896f, 0.434f,
	//	0.904f, 0.324f, //15
	//	0.906f, 0.217f,
	//	0.180f, 0.150f,
	//	0.227f, 0.109f,
	//	0.293f, 0.100f,
	//	0.359f, 0.107f, //20
	//	0.426f, 0.135f,
	//	0.559f, 0.131f,
	//	0.625f, 0.100f,
	//	0.695f, 0.090f,
	//	0.765f, 0.100f, //25
	//	0.816f, 0.139f,
	//	0.494f, 0.213f,
	//	0.495f, 0.283f,
	//	0.500f, 0.354f,
	//	0.500f, 0.424f, //30 
	//	0.421f, 0.471f,
	//	0.459f, 0.484f,
	//	0.500f, 0.500f,
	//	0.540f, 0.484f,
	//	0.578f, 0.469f, //35
	//	0.258f, 0.223f,
	//	0.297f, 0.199f,
	//	0.350f, 0.199f,
	//	0.391f, 0.230f,
	//	0.348f, 0.242f, //40
	//	0.297f, 0.240f,
	//	0.600f, 0.227f,
	//	0.643f, 0.193f,
	//	0.693f, 0.193f,
	//	0.734f, 0.216f, //45
	//	0.687f, 0.234f,
	//	0.648f, 0.234f,
	//	0.348f, 0.600f,
	//	0.404f, 0.576f,
	//	0.461f, 0.5625f, //50
	//	0.502f, 0.574f,
	//	0.543f, 0.561f,
	//	0.602f, 0.570f,
	//	0.660f, 0.592f,
	//	0.646f, 0.652f, //55
	//	0.551f, 0.678f,
	//	0.504f, 0.686f,
	//	0.461f, 0.682f,
	//	0.404f, 0.656f,
	//	0.373f, 0.604f, //60
	//	0.461f, 0.598f,
	//	0.500f, 0.602f,
	//	0.543f, 0.596f,
	//	0.635f, 0.598f,
	//	0.547f, 0.627f, //65
	//	0.502f, 0.631f,
	//	0.461f, 0.627f
	//};


};
