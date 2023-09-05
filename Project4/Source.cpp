
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include"shader.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<vector>
#include<string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"camera.h"
#include"mesh.h"
#include<map>
#include <ft2build.h>
#include FT_FREETYPE_H

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f,   1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f,   1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

using namespace glm;
glm::vec3 objectcolor(1.0f, 0.5f, 0.31f);

Camera ourcamera(glm::vec3(-40.5f, 0.3f, 0.0f));

glm::vec3 lightcolor(1.0, 1.0, 1.0);

glm::vec3 lightPos(-40.0f, 0.5f, 2.0f);

int crouch = 0;

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
unsigned int VAO, VBO;//for text

class text
{
public:

	Shader shader;
	text()
	{
		shader = Shader("text.vs", "text.fs");
	}
	void intialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1600), 0.0f, static_cast<float>(900));

		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		FT_Library ft;

		FT_Init_FreeType(&ft);

		FT_Face face;
		FT_New_Face(ft, "VINERITC.ttf", 0, &face);

		FT_Set_Pixel_Sizes(face, 0, 48);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


		for (unsigned char c = 0; c < 128; c++)
		{

			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);


		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};

void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state	
	shader.use();
	glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

enum shape
{
	CUBE,
	CUBOID
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	ourcamera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	ourcamera.ProcessMouseScroll(yoffset);
}

void key_input(GLFWwindow* window, float deltaTime, int touching)
{

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		ourcamera.ProcessKeyboard(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		ourcamera.ProcessKeyboard(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && touching == 0)
		ourcamera.ProcessKeyboard(LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && touching == 0)
		ourcamera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		ourcamera.Position.y += 0.1f;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		ourcamera.Position.y -= 0.1f;


	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		if (crouch == 0)
		{
			crouch = 1;
			ourcamera.Position.y -= 0.1f;
		}
	}
	else if (crouch == 1)
	{
		crouch = 0;
		ourcamera.Position.y += 0.1f;
	}

}

void processshaders(Shader cubeshader, vec3 lightPos, int dark, glm::mat4 change, float texcoordmult, int shineness = 32.0f, int processprojection = 1)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat3 normal1 = glm::mat3(glm::transpose(glm::inverse(model)));

	cubeshader.use();
	cubeshader.setInt("material.texture1", 0);
	cubeshader.setInt("material.texture2", 1);
	cubeshader.setInt("material.texture3", 2);

	model = model * change;

	if (processprojection == 1)
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	view = ourcamera.GetViewMatrix();

	cubeshader.setMat4("model", model);
	cubeshader.setVec3("objectColor", objectcolor);
	cubeshader.setVec3("lightColor", lightcolor);
	cubeshader.setMat4("projection", projection);

	cubeshader.setVec3("lightpos", lightPos);
	cubeshader.setMat3("normal1", normal1);

	cubeshader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	cubeshader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	cubeshader.setVec3("material.specular", 0.1f, 0.1f, 0.1f);
	cubeshader.setFloat("material.shininess", shineness);

	glm::vec3 lightdiffuse = lightcolor * (1.0f);
	glm::vec3 lightambient = lightdiffuse * (0.2f);

	cubeshader.setVec3("light.ambient", lightambient);
	cubeshader.setVec3("light.diffuse", lightdiffuse); // darken diffuse light a bit
	cubeshader.setVec3("light.specular", lightcolor);


	cubeshader.setMat4("view", view);
	cubeshader.setVec3("viewPos", ourcamera.Position);

	cubeshader.setFloat("light.constant", 1.0f);
	cubeshader.setFloat("light.linear", 0.09f);
	cubeshader.setFloat("light.quadratic", 0.032f);
	cubeshader.setFloat("texcoordmult", texcoordmult);
	cubeshader.setInt("dark", dark);
}

unsigned int gettexture(const char* imagename)
{
	unsigned int textureID;

	glGenTextures(1, &textureID);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrComponents;
	unsigned char* data = stbi_load(imagename, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << imagename << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}

float magnitude(vec3 vector)
{
	float mag;
	mag = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
	return mag;
}

class collisionwithbox
{
public:

	vec3 boxcenter;
	vec3 normals[6];
	int touching;
	vec3 final1;
	vec4 boxcenter1;
	float lengthx;
	float breadthz;
	float heighty;
	shape s;
	vec3 dimensionsvector;
	int mirrorlasercollision;

	collisionwithbox(float vertices[], mat4 change, float length = 1.0f, float breadth = 1.0f, float height = 1.0f, shape a = CUBOID)
	{
		mirrorlasercollision = 0;

		boxcenter = vec3(0.0f);
		for (int i = 0; i < 6; i++)
			normals[i] = vec3(0.0f);


		for (int i = 0; i < 8 * 36; i = i + 8)
		{
			boxcenter.x += vertices[i];
			boxcenter.y += vertices[i + 1];
			boxcenter.z += vertices[i + 2];
		};

		for (int i = 3; i <= 283; i = i + 48)
		{
			normals[(i - 3) / 48].x = vertices[i];                            //i=0 =>-ve z axis            i=1 => z axis
			normals[(i - 3) / 48].y = vertices[i + 1];                        //i=2 => -x axis              i=3=> x axis
			normals[(i - 3) / 48].z = vertices[i + 2];                        //i=4 => -y axis              i=5=> y axis
		};

		boxcenter.x = boxcenter.x / 6;
		boxcenter.y = boxcenter.y / 6;
		boxcenter.z = boxcenter.z / 6;

		boxcenter1 = change * vec4(boxcenter, 1.0f);
		lengthx = length;
		breadthz = breadth;
		heighty = height;
		s = a;
		dimensionsvector = vec3(lengthx / 2, heighty / 2, breadthz / 2);
		touching = 0;
	}

	collisionwithbox()
	{

	};

	int cameracollisondetection(float deltatime)
	{
		touching = 0;
		float dist = ourcamera.MovementSpeed * deltatime;
		float component = 1;

		vec3 newcamerapos = ourcamera.Position;

		if (distance(ourcamera.Position.x, boxcenter1.x) <= lengthx - 0.2 && distance(boxcenter1.z, ourcamera.Position.z) <= breadthz - 0.2)
		{

			for (int i = 0; i <= 5; i++)
			{
				if (s == CUBOID)
				{
					// component = dot(normalize(ourcamera.Position - vec3(boxcenter1)), normals[i]);
					if (dot(normals[i], vec3(1.0f)) >= 0.0)
					{

						if (dot(ourcamera.Position - vec3(boxcenter1), normals[i]) >= dot(dimensionsvector, normals[i]) - 0.1f && dot(ourcamera.Position - vec3(boxcenter1), normals[i]) <= dot(dimensionsvector, normals[i]) + 0.1f)
						{
							touching = touching + 1;
							ourcamera.Position = ourcamera.Position + (component * dist * normals[i]);
						}
					}
					else
					{
						if (dot(ourcamera.Position - vec3(boxcenter1), normals[i]) >= dot(-dimensionsvector, normals[i]) - 0.1f && dot(ourcamera.Position - vec3(boxcenter1), normals[i]) <= dot(-dimensionsvector, normals[i]) + 0.1f)
						{
							touching++;
							ourcamera.Position = ourcamera.Position + (component * dist * normals[i]);
						}
					}
				}
				else if (s == CUBE)
				{
					if ((dot(ourcamera.Position - vec3(boxcenter1), normals[i])) / (magnitude(ourcamera.Position - vec3(boxcenter1)) * magnitude(normals[i])) <= 1 && (dot(ourcamera.Position - vec3(boxcenter1), normals[i])) / (magnitude(ourcamera.Position - vec3(boxcenter1)) * magnitude(normals[i])) >= sqrt(1 / 2))
					{
						ourcamera.Position = ourcamera.Position + (dist * normals[i]);
					}
				}
			}
		}

		return touching;
	}

	vec3 laserboxdete(float laserpoints[], vec3 final, int divisor, float* lenght)
	{

		final1 = final;
		vec3 inital = vec3(laserpoints[0], laserpoints[1], laserpoints[2]);
		vec3 final2;

		for (int i = 0; i < divisor; i = i + 3)
		{


			if (distance(boxcenter1.x, laserpoints[i]) <= lengthx / 2 && distance(boxcenter1.y, laserpoints[i + 1]) <= heighty / 2 && distance(boxcenter1.z, laserpoints[i + 2]) <= breadthz / 2)
			{
				final2 = vec3(laserpoints[i], laserpoints[i + 1], laserpoints[i + 2]);
				if (*lenght >= length(final2 - inital))
				{
					final1.x = laserpoints[i];
					final1.y = laserpoints[i + 1];
					final1.z = laserpoints[i + 2];
					*lenght = length(final2 - inital);
					break;
				}
			}

		}

		return final1;
	}
	vec3 laserboxdetemirror(float laserpoints[], vec3 final, int divisor, vec3* normal, int* mirrorlasercoll, int* reflec)
	{
		final1 = final;

		for (int i = 0; i < divisor; i = i + 3)
		{

			if (distance(boxcenter1.x, laserpoints[i]) <= lengthx / 2 && distance(boxcenter1.y, laserpoints[i + 1]) <= heighty / 2 && distance(boxcenter1.z, laserpoints[i + 2]) <= breadthz / 2)
			{


				final1.x = laserpoints[i];
				final1.y = laserpoints[i + 1];
				final1.z = laserpoints[i + 2];
				break;
			}

		}

		if (distance(boxcenter1.x, final1.x) <= lengthx / 2 && distance(boxcenter1.y, final1.y) <= heighty / 2 && distance(boxcenter1.z, final1.z) <= breadthz / 2)
		{
			mirrorlasercollision += 1;
			*reflec = 1;

			if (mirrorlasercollision == 1)
				*mirrorlasercoll += 1;

			for (int j = 0; j < 6; j++)
			{
				if (dot(final1 - vec3(boxcenter1), normals[j]) >= dot(dimensionsvector, normals[j]) - 0.1f && dot(final1 - vec3(boxcenter1), normals[j]) <= dot(dimensionsvector, normals[j]) + 0.1f)
				{

					*normal = normals[j];
					break;
				}
			}

		}
		else
		{
			*reflec = 0;
		}


		return final1;
	}

};

class lightmechanism
{
public:
	vec3 prevlightpos;
	int canhold;
	int holding, holding1;

	lightmechanism()
	{
		prevlightpos = lightPos;
		canhold = 0;
		holding = 0;

	}

	void initialize(GLFWwindow* window)
	{
		holding1 = holding;

		prevlightpos = lightPos;

		if (distance(lightPos, ourcamera.Position) <= 0.5f)
		{
			canhold = 1;
		}
		else
		{
			canhold = 0;
		}

		if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && canhold == 1)
		{

			lightPos = ourcamera.Position + ourcamera.mouseFront * 0.1f;
			holding = 1;
		}
		else
		{
			holding = 0;
			lightPos = prevlightpos;
		}
		if (holding1 == 1 && holding == 0)
		{
			lightPos = ourcamera.Position + ourcamera.mouseFront * 0.5f;
		}

	}

	void processlightshader(GLFWwindow* window, Shader lightshader, mat4 change)
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);

		model = model * change;

		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = ourcamera.GetViewMatrix();
		if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && canhold == 1)
		{
			view = translate(view, lightPos);
			view = rotate(view, radians(-ourcamera.Yaw), ourcamera.WorldUp);
			view = rotate(view, radians(ourcamera.Pitch), vec3(0.0f, 0.0f, 1.0f));
			view = translate(view, -lightPos);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.01f));
		}
		else
		{
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.1f));
		}
		lightshader.use();
		lightshader.setMat4("view", view);
		lightshader.setMat4("model", model);
		lightshader.setMat4("projection", projection);
		lightshader.setVec3("lightcolor", lightcolor);
	}

};

class laserclass
{
public:
	int mirrorsno;

	vec3 laservectors[20];

	int divisor;
	vec3 dirvector[10];

	float mindist;

	float laserlengthmax;

	vec3 normal;

	int canholdlaser = 0;
	int holdinglaser = 0;

	float laserpoints[2000]; //no. inside indicates to which accuracy the laser will detect the cube

	int laserpointnumber = 2000;

	float laservertices[100];
	float laserlengthcurrent;
	float commdiff;

	int lasermirrortouch;
	int mousebuttonpress;
	int mousebuttonpress1;

	laserclass(int mirrno)
	{

		mirrorsno = mirrno;
		divisor = laserpointnumber - 1 - ((laserpointnumber - 1) % 3);

		laserlengthmax = 40;

		laservectors[0] = vec3(-9.0f, 0.0f, 1.0f);
		laservectors[1] = vec3(10.0f, 0.0f, 3.0f);

		mindist = magnitude(laservectors[1] - laservectors[0]) / divisor;

		for (int i = 0; i < mirrorsno + 1; i++)
			dirvector[i] = normalize(laservectors[1] - laservectors[0]);

		for (int i = 2; i < mirrorsno + 2; i++)
			laservectors[i] = laservectors[0] + (laserlengthcurrent * dirvector[i - 1]);

		lasermirrortouch = 0;

	}
	void loop1(vec3 normal1, int index)
	{
		float cosangle = dot(normalize(normal1), -normalize(dirvector[index]));

		dirvector[1 + index] = (2 * cosangle * normalize(normal1)) + dirvector[index];

		// for (int i = 2+index; i < mirrorsno+2; i++)
		laservectors[index + 2] = laservectors[index + 1] + (laserlengthmax * dirvector[index + 1]);
	}
	void calculatevertices()
	{


		for (int i = 0; i < 3 * (mirrorsno + 2); i = i + 3)
		{
			laservertices[i] = laservectors[i / 3].x;

			laservertices[i + 1] = laservectors[i / 3].y;

			laservertices[i + 2] = laservectors[i / 3].z;

		}

	}

	void mouseinput(GLFWwindow* window, int lightholding, vec3 normal1, int counter)
	{


		if (distance(laservectors[0], ourcamera.Position) <= 0.5f)
		{
			canholdlaser = 1;
		}
		else
		{
			canholdlaser = 0;
		}


		if (((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && canholdlaser == 1 && lightholding != 1))
		{
			dirvector[0] = normalize(ourcamera.mouseFront); //0 because it it connected to the source

			for (int i = 0; i < mirrorsno + 1; i++)
				dirvector[i] = dirvector[0];

			laservectors[1] = laservectors[0] + dirvector[0] * laserlengthmax;
			holdinglaser = 1;

			laserlengthcurrent = laserlengthmax;
		}
		else
		{
			holdinglaser = 0;
			laserlengthcurrent = laserlengthmax;
		}


	}

	void calculatelaserpoints(int index)
	{


		for (int i = 0; i < divisor; i += 3)
		{
			laserpoints[i] = laservectors[index].x + (mindist * dirvector[index].x * i);
			laserpoints[i + 1] = laservectors[index].y + (mindist * dirvector[index].y * i);
			laserpoints[i + 2] = laservectors[index].z + (mindist * dirvector[index].z * i);
		}


	}

	inline void configureshaders(objectspace laser)
	{

		laser.shader.use();

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);

		view = ourcamera.GetViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));

		laser.shader.setMat4("view", view);
		laser.shader.setMat4("model", model);
		laser.shader.setMat4("projection", projection);


	}

};

void processshdaers2d(mat4 change, Shader shader)
{
	shader.use();
	glm::mat4 view = glm::mat4(1.0f);
	mat4 projection(1.0f);


	shader.setMat4("model", change);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	shader.setInt("texture1", 0);
}

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);


	GLFWmonitor* a = glfwGetPrimaryMonitor();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", a, NULL);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	text text1;
	text1.intialize();

	vec3 normal = vec3(1.0f);

	objectspace cube[8];

	cube[0] = objectspace("shader.vs", "shaderbox.fs", 1);
	cube[0].intitialize(vertices);

	cube[1] = objectspace("shader.vs", "shaderbox.fs", 1);
	cube[1].intitialize(vertices);
	cube[1].change = glm::translate(cube[1].change, glm::vec3(4.0f, 0.0f, 0.0f));

	cube[2] = objectspace("shader.vs", "shaderbox.fs", 100);
	cube[2].intitialize(vertices);
	cube[2].change = glm::translate(cube[2].change, vec3(0.0f, -0.5f, 0.0f));
	cube[2].change = glm::scale(cube[2].change, vec3(100.0, 0.001, 100.0));

	cube[3] = objectspace("shader.vs", "shaderbox.fs", 10);
	cube[3].intitialize(vertices);
	cube[3].change = glm::translate(cube[3].change, vec3(50.0, 4.5, 0.0f));
	cube[3].change = glm::scale(cube[3].change, vec3(1, 100, 100));

	cube[4] = objectspace("shader.vs", "shaderbox.fs", 10);
	cube[4].intitialize(vertices);
	cube[4].change = glm::translate(cube[4].change, vec3(-50.0, 4.5, 0.0f));
	cube[4].change = glm::scale(cube[4].change, vec3(1, 100, 100));

	cube[5] = objectspace("shader.vs", "shaderbox.fs", 10);
	cube[5].intitialize(vertices);
	cube[5].change = glm::translate(cube[5].change, vec3(0.0f, 4.5, 50.0));
	cube[5].change = glm::scale(cube[5].change, vec3(100, 100, 1));

	cube[6] = objectspace("shader.vs", "shaderbox.fs", 10);
	cube[6].intitialize(vertices);
	cube[6].change = glm::translate(cube[6].change, vec3(0.0f, 4.5, -50.0));
	cube[6].change = glm::scale(cube[6].change, vec3(100, 100, 1));

	cube[7] = objectspace("shader.vs", "shaderbox.fs", 1);
	cube[7].intitialize(vertices);
	cube[7].change = glm::translate(cube[7].change, vec3(0.0f, 49.5, 0.0f));
	cube[7].change = glm::scale(cube[7].change, vec3(100.0, 0.0001, 100.0));

	collisionwithbox cubecollision[8];

	cubecollision[0] = collisionwithbox(vertices, cube[0].change);
	cubecollision[1] = collisionwithbox(vertices, cube[1].change);
	cubecollision[2] = collisionwithbox(vertices, cube[2].change);
	cubecollision[3] = collisionwithbox(vertices, cube[3].change, 1, 100);
	cubecollision[4] = collisionwithbox(vertices, cube[4].change, 1, 100);
	cubecollision[5] = collisionwithbox(vertices, cube[5].change, 100, 1);
	cubecollision[6] = collisionwithbox(vertices, cube[6].change, 100, 1);
	cubecollision[7] = collisionwithbox(vertices, cube[7].change);

	objectspace light("shader.vs", "shaderlight.fs", 1);
	light.intitialize(vertices);

	objectspace instructions("shader.vs", "shaderlasercube.fs", 1);
	instructions.intitialize(vertices);
	instructions.change = translate(instructions.change, ourcamera.Position + vec3(0.0f, 0.0f, -0.2f));
	instructions.change = scale(instructions.change, vec3(1.0f, 2.0f, 0.0f));


	objectspace laser("shaderlaser.vs", "shaderlaser.fs", 1);

	laserclass lasermech(4);//fill the mirror number here

	objectspace lasercube;

	lasercube = objectspace("shader.vs", "shaderlasercube.fs", 1);
	lasercube.intitialize(vertices);
	lasercube.change = glm::translate(lasercube.change, lasermech.laservectors[0]);
	lasercube.change = glm::scale(lasercube.change, vec3(0.05f));

	objectspace mirror[4];


	mirror[0] = objectspace("shader.vs", "shaderbox.fs", 1);
	mirror[0].intitialize(vertices);
	mirror[0].change = translate(mirror[0].change, vec3(0.0f, 0.0f, 2.0f));
	mirror[0].change = scale(mirror[0].change, vec3(0.1f, 1.0f, 1.0f));

	mirror[1] = objectspace("shader.vs", "shaderbox.fs", 1);
	mirror[1].intitialize(vertices);
	mirror[1].change = translate(mirror[1].change, vec3(-12.0f, 0.0f, 3.0f));
	mirror[1].change = scale(mirror[1].change, vec3(0.1f, 1.0f, 1.0f));

	mirror[2] = objectspace("shader.vs", "shaderbox.fs", 1);
	mirror[2].intitialize(vertices);
	mirror[2].change = translate(mirror[2].change, vec3(4.0f, 0.0f, 4.0f));
	mirror[2].change = scale(mirror[2].change, vec3(0.1f, 1.0f, 1.0f));

	mirror[3] = objectspace("shader.vs", "shaderbox.fs", 1);
	mirror[3].intitialize(vertices);
	mirror[3].change = translate(mirror[3].change, vec3(-12.0f, 0.0f, 5.50f));
	mirror[3].change = scale(mirror[3].change, vec3(0.1f, 1.0f, 1.0f));

	collisionwithbox mirrorcollison[4];

	for (int i = 0; i < lasermech.mirrorsno; i++)
		mirrorcollison[i] = collisionwithbox(vertices, mirror[i].change, 0.1f, 1.0f, 1.0f);

	objectspace timer("shader.vs", "shader2d.fs", 1);
	timer.intitialize(vertices);
	timer.change = translate(timer.change, vec3(0.85f, 0.83f, -0.75f));
	timer.change = scale(timer.change, vec3(0.25f));

	objectspace pointer("shader.vs", "shader2d.fs", 1);
	pointer.intitialize(vertices);
	pointer.change = translate(pointer.change, vec3(-0.2f, -0.53f, -0.4f));
	pointer.change = scale(pointer.change, vec3(0.1f));

	objectspace pointer1("shader.vs", "shader2d.fs", 1);
	pointer1.intitialize(vertices);
	pointer1.change = translate(pointer1.change, vec3(-0.2f, -0.53f,0.4f));
	pointer1.change = scale(pointer1.change, vec3(0.1f));

	objectspace background("background.vs", "background.fs", 1);
	background.intitialize(vertices);
	background.change = translate(background.change, vec3(0.0f, 0.0f, 0.0f));
	background.change = scale(background.change, vec3(2));
	background.change = scale(background.change, vec3(1.3f, 1.0f, 0.1f));

	objectspace background2("shader.vs", "shader2d.fs", 1);
	background2.intitialize(vertices);
	background2.change = translate(background2.change, vec3(0.0f, 0.0f, 0.2f));
	background2.change = scale(background2.change, vec3(2));
	background2.change = scale(background2.change, vec3(1.3f, 1.0f, 0.1f));

	objectspace arrowsymbol("shader.vs", "shader2d.fs", 1);
	arrowsymbol.intitialize(vertices);
	arrowsymbol.change = scale(arrowsymbol.change, vec3(0.1f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

		unsigned int diffusemap, specularmap;
		diffusemap = gettexture("container.png");
		specularmap = gettexture("containerspec.png");

		unsigned int emissionmapsky;
		emissionmapsky = gettexture("sky.jpg");

		unsigned int eye;
		eye = gettexture("eye.jpg");

		unsigned int instructiostex;
		instructiostex = gettexture("instructions.png");

		unsigned int mirrortex;
		mirrortex = gettexture("mirror.jpg");

		unsigned int clocktexture;
		clocktexture = gettexture("wood.jpg");

		unsigned int pointertex = gettexture("pointer.png");

		unsigned int backgroundtex = gettexture("bg3.jpg");
		unsigned int bgtex2 = gettexture("bg4.jpg");

		unsigned int arrowtex = gettexture("arrow.png");

		unsigned int arrowtexdown = gettexture("arrowdown.png");

		unsigned int wall = gettexture("Wall.jpg");

		unsigned int door = gettexture("door.png");
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame   

	stbi_set_flip_vertically_on_load(true);

	lightmechanism lightmech1;

	int touching = 0;

	int instrstart = 0;

	int counter = 0;

	int reflec = 0;

	int k = 0;

	int l = 0;;

	int minutes;
	int seconds;

	float lenghtbwvectors = lasermech.laserlengthmax;

	int screen = 0;

	int choice = 1;
	int choice1 = 1;
	int choice11 = 0;


	int movementspeed = (int)(10 * ourcamera.MovementSpeed);
	int sensitivity = (int)(ourcamera.MouseSensitivity * 100);

	int movementspeed1 = movementspeed;
	int sensitivity1 = sensitivity;

	int time = 0;

	while (!glfwWindowShouldClose(window))
	{
		if (screen == 0 ||screen ==3) //Starting Screen
		{
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && counter > 1)
			{
				choice = choice + 1;
				pointer.change = translate(pointer.change, vec3(0.0f, 2.3f, 0.0f));
				if (choice > 3)
				{
					choice = 1;
					pointer.change = translate(pointer.change, vec3(0.0f, -6.9f, 0.0f));
				}
				counter = -10;


			}

			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && counter > 1)
			{
				choice = choice - 1;
				pointer.change = translate(pointer.change, vec3(0.0f, -2.3f, 0.0f));

				if (choice < 1)
				{
					choice = 3;
					pointer.change = translate(pointer.change, vec3(0.0f, 6.9f, 0.0f));
				}
				counter = -10;


			}
			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && counter > 0 && choice == 3)
			{
				screen = 1;
				if (screen == 0)
					glfwSetTime(0);

				else
					glfwSetTime(time);
				counter = -10;
			}


			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && counter > 0 && choice == 2)
			{
				movementspeed1 = movementspeed;
				sensitivity1 = sensitivity;

				screen = 2;
				counter = -10;
			}

			processshdaers2d(background2.change, background2.shader);

			background.shader.use();

			background.shader.setFloat("time", glfwGetTime());

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, backgroundtex);

			glBindVertexArray(background.vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			background2.shader.use();

			background2.shader.setFloat("time", glfwGetTime());

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, bgtex2);

			glBindVertexArray(background.vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			if(screen ==0)
			RenderText(text1.shader, "START", 700, 400, 1.0f, glm::vec3(1.0, 0.6f, 0.2f));

			else
				RenderText(text1.shader, "RESUME", 700, 400, 1.0f, glm::vec3(1.0, 0.6f, 0.2f));
			
			RenderText(text1.shader, "OPTIONS", 700, 300, 1.0f, glm::vec3(1.0, 0.6f, 0.2f));

			RenderText(text1.shader, "EXIT", 700, 200, 1.0f, glm::vec3(1.0, 0.6f, 0.2f));

			processshdaers2d(pointer.change, pointer.shader);
			processshdaers2d(background.change, background.shader);

			pointer.shader.use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, pointertex);

			glBindVertexArray(pointer.vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && choice == 1)
			{
				glfwSetWindowShouldClose(window, true);
			};


		}

		if (screen == 2)//Options Screen
		{
			arrowsymbol.change = mat4(1.0f);
			arrowsymbol.change = scale(arrowsymbol.change, vec3(0.08f));

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && counter > 1 && choice1 == 3)
			{
				choice11 = 3;
				counter = -10;
			}
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && choice11 == 3 && counter > 0)
			{
				counter = -3;

				ourcamera.MouseSensitivity = ourcamera.MouseSensitivity +0.01;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && choice11 == 3 && counter > 0)
			{
				counter = -3;
				ourcamera.MouseSensitivity = ourcamera.MouseSensitivity - 0.01;
			}
			if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && counter > 1 && choice1 == 3))
			{
				choice11 = 0;
				counter = -6;
			}

			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && counter > 1 && choice1 == 2)
			{
				choice11 = 2;
				counter = -10;
			}
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && choice11 == 2 && counter > 0)
			{
				counter = -3;
				ourcamera.MovementSpeed = ourcamera.MovementSpeed + 0.1;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && choice11 == 2 && counter > 0)
			{
				counter = -3;
				ourcamera.MovementSpeed = ourcamera.MovementSpeed - 0.1;
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && counter > 1 && choice1 == 2)
			{
				choice11 = 0;
				counter = -6;
			}

			movementspeed = (int)(10 * ourcamera.MovementSpeed);
			sensitivity = (int)(ourcamera.MouseSensitivity * 100);

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && counter > 1 && choice11 == 0)
			{
				choice1 = choice1 + 1;
				pointer1.change = translate(pointer1.change, vec3(0.0f, 2.3f, 0.0f));
				if (choice1 > 3)
				{
					choice1 = 1;
					pointer1.change = translate(pointer1.change, vec3(0.0f, -6.9f, 0.0f));
				}
				counter = -10;
			}

			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && counter > 1 && choice11 == 0)
			{
				choice1 = choice1 - 1;
				pointer1.change = translate(pointer1.change, vec3(0.0f, -2.3f, 0.0f));

				if (choice1 < 1)
				{
					choice1 = 3;
					pointer1.change = translate(pointer1.change, vec3(0.0f, 6.9f, 0.0f));
				}
				counter = -10;
			}
			if (choice11 == 3 && sensitivity != sensitivity1)
				arrowsymbol.change = translate(arrowsymbol.change, vec3(7.2f, -1.0f, 0.0f));
				
			if (choice11 == 2 && movementspeed!=movementspeed1)
				arrowsymbol.change = translate(arrowsymbol.change, vec3(7.2f, -3.8f, 0.0f));

			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && counter > 1 && choice1 == 1)
			{
				ourcamera.MouseSensitivity = SENSITIVITY;
				ourcamera.MovementSpeed = SPEED;
				counter = -10;
			}

			processshdaers2d(pointer1.change, pointer1.shader);
			processshdaers2d(arrowsymbol.change, arrowsymbol.shader);


			if (choice11 == 3)
				RenderText(text1.shader, "MouseSensitivity", 700, 400, 1.0f, glm::vec3(0.3, 0.0f, 0.9f));

			else
				RenderText(text1.shader, "MouseSensitivity", 700, 400, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));

			RenderText(text1.shader, ":", 1100, 400, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));

			string output1 = to_string(sensitivity);

			RenderText(text1.shader, output1, 1160, 400, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));

			if(choice11 ==2)
				RenderText(text1.shader, "Movementspeed", 700, 300, 1.0f, glm::vec3(0.3, 0.0, 0.9));
			
			else
			RenderText(text1.shader, "Movementspeed", 700, 300, 1.0f, glm::vec3(0.3, 0.7, 0.9));

			RenderText(text1.shader, ":", 1100, 300, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));

			output1 = to_string(movementspeed);

			RenderText(text1.shader, output1, 1160, 300, 1.0f, glm::vec3(0.3, 0.7, 0.9));

			RenderText(text1.shader, "Restore Default", 700, 200, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));

			if(choice11!=0)
			RenderText(text1.shader, "Use The Arrow Keys To Change The Values", 630.0f, 40.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

			else
				RenderText(text1.shader, "Press Enter To Select", 630.0f, 40.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

			pointer1.shader.use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, pointertex);

			glBindVertexArray(pointer1.vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);


			if (choice11 !=0)
			{
				
				arrowsymbol.shader.use();

				glActiveTexture(GL_TEXTURE0);
				
				if ((sensitivity > sensitivity1 && choice1 ==3) || (movementspeed > movementspeed1 &&choice1 ==2))
					glBindTexture(GL_TEXTURE_2D, arrowtex);

				else if ((sensitivity < sensitivity1 && choice1 == 3) || (movementspeed < movementspeed1 && choice1 == 2))
					glBindTexture(GL_TEXTURE_2D, arrowtexdown);

				else
					glBindTexture(GL_TEXTURE_2D, 0);

				glBindVertexArray(arrowsymbol.vao);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && counter > 0 && choice11 == 0)
			{
				screen = 0;
				counter = -10;
			}

		}

		if (screen == 1)//game screen
		{
			minutes = (900 - glfwGetTime()) / 60;
			seconds = (int)(900 - glfwGetTime()) % 60;

			k = 0;
			l = 0;

			for (int i = 0; i < lasermech.mirrorsno; i++)
				mirrorcollison[i].mirrorlasercollision = 0;

			if (instrstart == 1)
			{
				key_input(window, deltaTime, touching);
				glfwSetCursorPosCallback(window, mouse_callback);

			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			touching = 0;
			lasermech.lasermirrortouch = 0;

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;


			lightmech1.initialize(window);

			for (int i = 0; i < 8; i++)
				touching += cubecollision[i].cameracollisondetection(deltaTime);



			for (int i = 2; i < lasermech.mirrorsno + 2; i++)
				lasermech.laservectors[i] = lasermech.laservectors[1];
			lasermech.dirvector[0] = normalize(lasermech.laservectors[1] - lasermech.laservectors[0]);
			lasermech.mouseinput(window, lightmech1.holding, normal, counter);
			for (int i = 0; i < lasermech.mirrorsno; i++)
			{

				reflec = 0;
				lasermech.calculatelaserpoints(i);
				for (int j = 0; j < 8; j++)
				{
					lasermech.laservectors[i + 1] = cubecollision[j].laserboxdete(lasermech.laserpoints, lasermech.laservectors[i + 1], lasermech.divisor, &lenghtbwvectors);
				}
				for (int j = 0; j < lasermech.mirrorsno; j++)
				{
					if (!(j == k && i == l + 1))
					{
						lasermech.laservectors[i + 1] = mirrorcollison[j].laserboxdetemirror(lasermech.laserpoints, lasermech.laservectors[i + 1], lasermech.divisor, &normal, &lasermech.lasermirrortouch, &reflec);

						if (reflec == 1)
						{
							lasermech.loop1(normal, i);
							l = i;
							k = j;
							break;
						}
						else
						{
							// mirror[j].shader.use();
						   //  mirror[j].shader.setVec3("laserpos", vec3(0.0f));

						}
					}
				}
				lenghtbwvectors = lasermech.laserlengthmax;
			}
			lasermech.calculatelaserpoints(lasermech.mirrorsno);
			for (int i = 0; i < 8; i++)
				lasermech.laservectors[lasermech.mirrorsno + 1] = cubecollision[i].laserboxdete(lasermech.laserpoints, lasermech.laservectors[lasermech.mirrorsno + 1], lasermech.divisor, &lenghtbwvectors);

			lasermech.laserlengthcurrent = magnitude(lasermech.laservectors[1] - lasermech.laservectors[0]);




			for (int i = 0; i < 8; i++)
				processshaders(cube[i].shader, lightPos, 1, cube[i].change, cube[i].texcoordmultiplier);

			lightmech1.processlightshader(window, light.shader, light.change);

			processshaders(lasercube.shader, lightPos, 1, lasercube.change, lasercube.texcoordmultiplier);
			processshaders(instructions.shader, lightPos, 1, instructions.change, instructions.texcoordmultiplier, 32.0f, 0);


			for (int i = 0; i < lasermech.mirrorsno; i++)
				processshaders(mirror[i].shader, lightPos, 1, mirror[i].change, mirror[i].texcoordmultiplier, 1024.0f);


			processshdaers2d(timer.change, timer.shader);


			lasermech.calculatevertices();
			laser.intitialize(lasermech.laservertices, 3);
			lasermech.configureshaders(laser);

			for (int i = 0; i < 3; i++)
			{
				cube[i].shader.use();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, diffusemap);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, specularmap);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);

				glBindVertexArray(cube[i].vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			for (int i = 3; i < 6; i++)
			{
				cube[i].shader.use();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D,wall);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);

				glBindVertexArray(cube[i].vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			cube[6].shader.use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, wall);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, 0);

			glBindVertexArray(cube[6].vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			for (int i = 7; i < 8; i++)
			{
				cube[7].shader.use();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, emissionmapsky);

				glBindVertexArray(cube[7].vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			for (int i = 0; i < lasermech.mirrorsno; i++)
			{
				mirror[i].shader.use();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mirrortex);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, mirrortex);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);

				glBindVertexArray(mirror[i].vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			timer.shader.use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, clocktexture);

			glBindVertexArray(timer.vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			string output = to_string(minutes);
			if (minutes >= 10)
				RenderText(text1.shader, output, 1380.0f, 790.0f, 1.6, glm::vec3(0.0, 0.0f, 0.0f));

			else
			{
				RenderText(text1.shader, "0", 1380.0f, 790.0f, 1.6, glm::vec3(0.0, 0.0f, 0.0f));
				RenderText(text1.shader, output, 1420.0f, 790.0f, 1.6, glm::vec3(0.0, 0.0f, 0.0f));
			}

			RenderText(text1.shader, ":", 1465.0f, 800.0f, 1.6, glm::vec3(0.0, 0.0f, 0.0f));


			output = to_string(seconds);
			if (seconds > 9)
				RenderText(text1.shader, output, 1490.0f, 790.0f, 1.6, glm::vec3(0.0, 0.0f, 0.0f));

			else
			{
				RenderText(text1.shader, "0", 1490.0f, 790.0f, 1.6, glm::vec3(0.0, 0.0f, 0.0f));
				RenderText(text1.shader, output, 1530.0f, 790.0f, 1.6, glm::vec3(0.0, 0.0f, 0.0f));
			}

			light.shader.use();

			glBindVertexArray(light.vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			lasercube.shader.use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, eye);

			glBindVertexArray(lasercube.vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			laser.shader.use();
			glBindVertexArray(laser.vao);
			for (int i = 0; i < lasermech.lasermirrortouch + 1; i++)
			{
				glEnable(GL_POINT_SIZE);
				glLineWidth(4 - 0.5 * i);

				glDrawArrays(GL_LINES, i, 2);
			}
			if (instrstart == 0)
			{
				instructions.shader.use();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, instructiostex);

				glBindVertexArray(instructions.vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);

				if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && counter > 1)
				{
					instrstart = 1;
					counter = -10;
				}
			}

			if (lightmech1.canhold == 1 && lightmech1.holding == 0)
				RenderText(text1.shader, "Press 'Left Mouse' Button To Hold", 630.0f, 40.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

			else if (lightmech1.canhold == 1 && lightmech1.holding == 1)
				RenderText(text1.shader, "Release 'Left Mouse' Button To Release", 600.0f, 40.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

			if (lasermech.canholdlaser == 1 && lasermech.holdinglaser != 1)
				RenderText(text1.shader, "Press 'Left Mouse' Button To Hold", 630.0f, 40.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
			else if (lasermech.canholdlaser == 1 && lasermech.holdinglaser == 1)
				RenderText(text1.shader, "Rotate The Mouse To Rotate The Laser Accordingly", 580.0f, 40.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && counter > 0 && choice11 == 0)
			{
				screen = 3;
				time = glfwGetTime();
				counter = -10;
			}


		}

		glfwSwapBuffers(window);
		glfwPollEvents();
		counter = counter + 1;
	}

	for (int i = 0; i < 8; i++)
		cube[i].deinitialize();

	for (int i = 0; i < lasermech.mirrorsno; i++)
		mirror[i].deinitialize();

	light.deinitialize();
	laser.deinitialize();

	glfwTerminate();
	return 0;
}
