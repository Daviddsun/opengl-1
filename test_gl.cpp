#include <iostream>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //如果按下ESC，把windowShouldClose设置为True，外面的循环会关闭应用
    if(key==GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    std::cout<<"ESC"<<mode;
}


const GLuint WIDTH = 800, HEIGHT = 600;
// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec3 ourColor;\n"
    // "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "ourColor = color;\n"
    // "vertexColor = vec4(0.5, 0.0f, 0.0f, 1.0f);\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "in vec3 ourColor;"
    "out vec4 color;\n"
    // "uniform vec4 ourColor;"
    "void main()\n"
    "{\n"
    "color = vec4(ourColor, 1.0f);\n"
    "}\n\0";

int main()
{
    if(!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #ifdef __APPLE__
    std::cout << "I'm apple machine" << endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    //创建窗口以及上下文
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    if(!window)
    {
        //创建失败会返回NULL
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback); //注册回调函数

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    //vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // log
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512, NULL, infoLog);
        std::cout << "ERROE::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //log
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader,512, NULL, infoLog);
        std::cout << "ERROE::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    //log
    glGetShaderiv(shaderProgram,GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderProgram,512, NULL, infoLog);
        std::cout << "ERROE::SHADER::shaderProgram::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // GLfloat vertices[] = {
    //     0.5f, 0.5f, 0.0f,   // 右上角
    //     0.5f, -0.5f, 0.0f,  // 右下角
    //     -0.5f, -0.5f, 0.0f, // 左下角
    //     -0.5f, 0.5f, 0.0f   // 左上角
    // };

    GLfloat vertices[] = 
    {
        // 位置              // 颜色
        0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 1.0f,      // 右上角
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // 右下角
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // 左下角
         -0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f  // 右下角
    };

    GLuint indices[] = { // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    GLuint EBO, VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // ..:: 初始化代码 :: ..
    // 1. 绑定顶点数组对象
    glBindVertexArray(VAO);
    // 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 3. 设定顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //4. 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // 5. 解绑VAO（不是EBO！）
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        // 激活着色器
        glUseProgram(shaderProgram);

        /*/
        / 更新uniform颜色
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue*4) / 2) + 0.5;
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        */
        // 绘制三角形
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        /*
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); //Red
        glVertex3f(0, 1, 1);

        glColor3f(0, 1, 0); //Green
        glVertex3f(-1, -1, 0);

        glColor3f(0, 0, 1); //Blue
        glVertex3f(1, -1, 0);
        //结束一个画图步骤
        glEnd();

        glBegin(GL_POLYGON);
        //再画个梯形，需要注意笔顺
        glColor3f(0.5, 0.5, 0.9); //Grey
        glVertex2d(0.5, 0.5);
        glVertex2d(1, 1);
        glVertex2d(1, 0);
        glVertex2d(0.5, 0);
        glEnd();
        */
        /******交换缓冲区，更新window上的内容******/
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}