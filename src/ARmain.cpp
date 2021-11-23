#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2/opencv.hpp>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "SOIL.h"

// some extra required imports
#include <string.h>
#include <vector>
#include <math.h>

//MINE
#include "Shader.h"
#include "Object.h"

//DLIB
#include<dlib/image_processing/frontal_face_detector.h>
#include<dlib/image_processing.h>
#include<dlib/opencv.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When the user presses the escape key, we set the window should close property to true, and close the application.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


GLFWwindow* initializeOpenglWindow(int width_window, int height_window)
{
	// =========================================================================================================
	// OpenGL initializations
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(width_window, height_window, "AR Camera", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}

	glEnable(GL_DEPTH_TEST);

	return window;
}


int width_window = 640, height_window = 480;

int main(int argc, char** argv)
{
	
	GLFWwindow* window = initializeOpenglWindow(width_window, height_window);

	if (window == NULL)
	{
		return -1;
	}

	// Viewport dimensions
	glfwGetFramebufferSize(window, &width_window, &height_window);
	glViewport(0, 0, width_window, height_window);

	Shader bg_shader("Shaders/bg_vertex_shader.vert", "Shaders/bg_fragment_shader.frag");
	Shader tri_shader("Shaders/triangle_shader.vert", "Shaders/triangle_shader.frag");

	//TRIANGLE//--------------------//

	GLfloat vertices_tri[68*3];

	GLfloat texture_coord[] = 
	{
		0.0f, 0.0f,
		0.5f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.6f, 0.0f,
		1.0f, 0.0f
	}; 

	unsigned int indices[] =
	{
		20, 21, 23,
		21, 22, 23,
		0, 1, 36,
		15, 16, 45,
		0, 36, 17,
		16, 26, 45,
		17, 18, 37,
		25, 26, 44,
		17, 36, 37,
		26, 44, 45,
		18, 19, 38,
		24, 25, 43,
		18, 37, 38,
		25, 43, 44,
		19, 20, 38,
		23, 24, 43,
		20, 21, 39,
		22, 23, 42,
		20, 38, 39,
		23, 42, 43,
		21, 22, 27,
		21, 27, 39,
		22, 27, 42,
		27, 28, 42,
		27, 28, 39,
		28, 42, 47,
		28, 39, 40,
		1,  36, 41,
		15, 45, 46,
		1,  2, 41,
		14, 15, 46,
		28, 29, 40,
		28, 29, 47,
		2,  40, 41,
		14, 46, 47,
		2,  29, 40,
		14, 29, 47,
		2,  3, 29,
		13, 14, 29,
		29, 30, 31,
		29, 30, 35,
		3,  29, 31,
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
		6, 48, 59,
		10, 54, 55,
		6, 7, 59,
		9, 10, 55,
		7, 58, 59,
		9, 55, 56,
		8, 57, 58,
		8, 56, 57,
		7, 8, 58,
		8, 9, 56,
		4, 31, 48,
		12, 35, 54,
		31, 48, 49,
		35, 53, 54,
		31, 49, 50,
		35, 52, 53,
		31, 32, 50,
		34, 35, 52,
		32, 33, 50,
		33, 34, 52,
		33, 50, 51,
		33, 51, 52,
		49, 48, 60,
		49, 60, 50,
		50, 60, 61,
		50, 51, 61,
		51, 52, 61,
		61, 62, 52,
		52, 53, 62,
		53, 54, 62,
		54, 55, 63,
		56, 55, 65,
		56, 63, 64,
		64, 65, 57,
		58, 57, 66,
		59, 58, 67,
		48, 59, 60,
		60, 59, 67,
		67, 58, 66,
		66, 57, 65,
	};

	GLuint EBO;

	GLuint VBO_tri_Pos, VBO_tri_texcoord, VAO_tri;
	glGenVertexArrays(1, &VAO_tri);
	glGenBuffers(1, &VBO_tri_Pos);

	glBindVertexArray(VAO_tri);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tri_Pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(68*3*(sizeof(float))), NULL, GL_DYNAMIC_DRAW);
	
	// Postion Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind vbo

	// Texture Attribute
	glGenBuffers(1, &VBO_tri_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tri_texcoord);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coord), texture_coord, GL_STATIC_DRAW);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL); 
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind vbo

	//Index buffer
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0); // Unbind VAO


	glm::mat4 model_tri;
	//model_tri = glm::translate(model_tri, glm::vec3(0.0f, 0.0f, -2.0f));	//Translate always comes first
	//model_tri *= glm::scale(model_tri, glm::vec3(1.0f, 1.0f, 1.0f)); 


	glm::mat4 view_tri = glm::mat4(1.0f);
	//view_tri = glm::translate(view_tri, glm::vec3(0, 0, -100));

	float nearTriangles = 0.1f;
	float farTriangles = 1000.0f;

	
	//glm::mat4 orthographic_projection_tri = glm::ortho();	
	
	/*glm:: mat4 orthographic_projection_tri =
		glm::ortho(-100.0f,
			100.0f,
			(-100.0f * ((GLfloat)height_window / (GLfloat)width_window)),
			(100.0f * ((GLfloat)height_window / (GLfloat)width_window)),
			-100.0f,
			100.0f);
	*/

	glm::mat4 orthographic_projection_tri = glm::ortho(0.0f, (GLfloat)width_window, 0.0f, (GLfloat)height_window, -100.0f, 100.0f);

	///BACKGROUND DEFINITIONS///
	cv::Mat frame;

	GLfloat vertices_bg[] =
	{
		0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	};

	//Object sphere = Object("Models/sphere.obj");

	//unsigned int indices_pyramid[] = {
	//	0, 3, 1,
	//	1, 3, 2,
	//	2, 3, 0,
	//	0, 1, 2
	//};
	

	GLuint VBO_bg, VAO_bg;
	glGenVertexArrays(1, &VAO_bg);
	glGenBuffers(1, &VBO_bg);

	glBindVertexArray(VAO_bg);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_bg);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_bg), vertices_bg, GL_STATIC_DRAW);

	// Postion Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO_bg

	// -----------------------------------------------------------------------------------------------
	// webcam texture

	float nearPlane = 0.1f;
	//float far = 500.0f;

	int width, height;
	cv::VideoCapture cap(1);

	if (!cap.isOpened()) {
		std::cerr << "ERROR: Could not open camera" << std::endl;
		return 1;
	}

	cap >> frame;
	width = frame.size().width;
	height = frame.size().height;

	std::cout << width << std::endl; //TESTING

	GLuint texture_bg;
	glGenTextures(1, &texture_bg);
	glBindTexture(GL_TEXTURE_2D, texture_bg);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	// =========================================================================================================
	// transformation presets for the background object (model, view and orthographic projection)
	glm::mat4 model_bg(1.0f);
	glm::mat4 view_bg(1.0f);
	GLfloat ortho_far = 10000.0f;

	model_bg = glm::scale(model_bg, glm::vec3(width_window, height_window, 1));
	view_bg = glm::translate(view_bg, glm::vec3(0, 0, -ortho_far));

	// use orthographic projection for the webcam background
	glm::mat4 orthographic_projection_bg = glm::ortho(0.0f, (GLfloat)width_window, 0.0f, (GLfloat)height_window, nearPlane, ortho_far);
	// =========================================================================================================

	//////////DLIB LANDMARKS STUFF////////////// 
	//define the face detector
	dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();

	//define landmark detector
	dlib::shape_predictor landmarkDetector;

	//load face landmark model
	dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> landmarkDetector;

	//define resize height
	float resizeHeight = 480;
	
	//calculate resize scale
	float resizeScale = frame.rows / resizeHeight;

	//define to hold detected faces
	std::vector<dlib::rectangle> faces;

	while (!glfwWindowShouldClose(window))
	{
		
		glfwPollEvents();
		//glClearColor(0.27f, 0.27f, 0.27f, 1.0f);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cap >> frame;

		//smaller image frame for more effecient face recognition 
		cv::Mat smallFrame; 
		cv::resize(frame, smallFrame, cv::Size(), 1.0 / resizeScale, 1.0 / resizeScale); 

		//change to dlib image format
		dlib::cv_image<dlib::bgr_pixel> dlibImageSmall(smallFrame);
		dlib::cv_image<dlib::bgr_pixel> dlibImage(frame);

		faces = faceDetector(dlibImageSmall);

		//loop over faces
		for (int i = 0; i < faces.size(); i++) {

			//scale the rectangle coordinates as we did face detection on resized smaller image
			dlib::rectangle rect(int(faces[i].left() * resizeScale),
				int(faces[i].top() * resizeScale),
				int(faces[i].right() * resizeScale),
				int(faces[i].bottom() * resizeScale));

			cv::Point topLeft = cv::Point(faces[i].left(), faces[i].top());
			cv::Point bottomRight = cv::Point(faces[i].right(), faces[i].bottom());

			cv::rectangle(frame, topLeft,bottomRight, cv::Scalar(255, 0, 0));

			//Face landmark detection
			dlib::full_object_detection faceLandmark = landmarkDetector(dlibImage, rect);

			int index = 0;
			for (int j = 0; j < 68; j++)
			{
				
				int x = faceLandmark.part(j).x();
				int y = faceLandmark.part(j).y();

				vertices_tri[index] = x * (width_window/float(width)); //get the pixel coordinate of the landmark and scale it to fit the window width and project matrix
				vertices_tri[index + 1] = (height - y) * (height_window/float(height)); //same as the x coordinate but first minus the y from height because opencv y coordinate is flipped

				//std::cout << y << std::endl;

				vertices_tri[index + 2] = 1.0f;
				index += 3;
				//std::cout << faceLandmark.part(i).x()/float(width) << std::endl; //TESTING
				cv::Point point = cv::Point(x, y);
				cv::circle(frame, point, 3, cv::Scalar(0, 0, 255));
			}
		}

		//wait
		//Draw background
		glUseProgram(bg_shader.program);
		glUniformMatrix4fv(glGetUniformLocation(bg_shader.program, "model_bg"), 1, GL_FALSE, glm::value_ptr(model_bg));
		glUniformMatrix4fv(glGetUniformLocation(bg_shader.program, "view_bg"), 1, GL_FALSE, glm::value_ptr(view_bg));
		glUniformMatrix4fv(glGetUniformLocation(bg_shader.program, "orthographic_projection_bg"), 1, GL_FALSE, glm::value_ptr(orthographic_projection_bg));

		glBindVertexArray(VAO_bg);

		glActiveTexture(GL_TEXTURE2);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
		glBindTexture(GL_TEXTURE_2D, texture_bg);
		glUniform1i(glGetUniformLocation(bg_shader.program, "webcam_texture"), 2);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glUseProgram(0);
		// -----------------------------------------------------------------------------------------------------

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Matrix should be here
		model_tri = glm::mat4(1.0f);
		view_tri = glm::mat4(1.0f);

		model_tri = glm::translate(model_tri, glm::vec3(0, 0, -100.0f));
		//model_tri = glm::scale(model_tri, glm::vec3(3.0f, 3.0f, 3.0f));
		//DRAW TRIANGLE

		
			glUseProgram(tri_shader.program);
			glUniformMatrix4fv(glGetUniformLocation(tri_shader.program, "model_tri"), 1, GL_FALSE, glm::value_ptr(model_tri));
			glUniformMatrix4fv(glGetUniformLocation(tri_shader.program, "view_tri"), 1, GL_FALSE, glm::value_ptr(view_tri));
			glUniformMatrix4fv(glGetUniformLocation(tri_shader.program, "orthographic_projection_tri"), 1, GL_FALSE, glm::value_ptr(orthographic_projection_bg));

			glBindVertexArray(VAO_tri);	

			glPointSize(5.0f);
			glBindBuffer(GL_ARRAY_BUFFER, VBO_tri_Pos);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_tri), vertices_tri, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			//glDrawArrays(GL_TRIANGLE_STRIP, 0, 68);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, 279, GL_UNSIGNED_INT, 0);
			
			glBindVertexArray(0);
		
		glUseProgram(0); 

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO_bg);
	glDeleteBuffers(1, &VBO_bg);

	glfwTerminate();
	return EXIT_SUCCESS;
}