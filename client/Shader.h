
#ifndef Shader_H_GUARD
#define Shader_H_GUARD

#include <string>
#include <glm/glm.hpp>

#include "globals.h"

class Shader {
public:
	// state
	unsigned int id;

	// constructors
	Shader() : id(0) {};
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	// sets current shader as active
	Shader& use();

	// compiles shader from source code
	void compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

	// utility functions
	void setBool(const char* name, bool value, bool useShader = false);
	void setFloat(const char* name, float value, bool useShader = false);
	void setInteger(const char* name, int value, bool useShader = false);
	void setVector2f(const char* name, float x, float y, bool useShader = false);
	void setVector2f(const char* name, const glm::vec2& value, bool useShader = false);
	void setVector3f(const char* name, float x, float y, float z, bool useShader = false);
	void setVector3f(const char* name, const glm::vec3& value, bool useShader = false);
	void setVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
	void setVector4f(const char* name, const glm::vec4& value, bool useShader = false);
	void setMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

private:
	// check if compilation/linking failed
	void checkCompileErrors(unsigned int object, std::string type);

	// reads shader files, returns malloc'd string
	std::string readShader(const char* filepath) const;
};


#endif
