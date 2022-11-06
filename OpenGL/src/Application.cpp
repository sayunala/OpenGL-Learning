#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<tuple>
#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "./tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestBatchRender.h"

static std::tuple<std::string, std::string>ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    enum class ShaderType {
        None = -1,
        Vertex = 0,
        Fragment = 1
    };
    ShaderType type = ShaderType::None;
    while (getline(stream,line))
    {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::Vertex;
            else
                type = ShaderType::Fragment;
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return std::tuple<std::string, std::string>(ss[0].str(), ss[1].str());
    
}
/*
* 编译着色器
*/
static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);//绑定着色器代码，生成着色器
    glCompileShader(id);//编译id表示的着色器

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);//获取当前编译状态
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);//获取需要打印的编译信息长度
        char* message = (char*)_malloca(sizeof(char) * length);
        glGetShaderInfoLog(id, length, &length, message);//获取编译失败日志
        
        std::cout << "Failed to compile " 
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
            << "shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);//编译失败删除id指向的着色器
        return 0;
    }
    return id;

}
static unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
    unsigned int program = glCreateProgram();//创建着色器程序
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vs);//将生成着色器附加到程序中
    glAttachShader(program, fs);
    glLinkProgram(program);//链接程序
    glValidateProgram(program);//验证程序的有效性

    glDeleteShader(vs);//删除已经没用的着色器
    glDeleteShader(fs);
    return program;
}
int main(void)
{
    /* Initialize the library */

    GLFWwindow* window;
    if (!glfwInit())
        return -1;
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
    //GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3));
    //GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3));
    //GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE)); 
  
    /* Create a windowed m ode window and its OpenGL context */
    window = glfwCreateWindow(960, 720, "Hello OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA));
        GLCall(glEnable(GL_BLEND));
     
        Renderer renderer;

        ImGui::CreateContext();
		ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
        
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        test::Test* currentTest = nullptr;
        test::TestMenu *testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;
        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture2D");
        testMenu->RegisterTest<test::TestBatchRender>("TestBatchRender");
      
        while (!glfwWindowShouldClose(window))
        {

            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
            renderer.Clear();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
				ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
          
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}