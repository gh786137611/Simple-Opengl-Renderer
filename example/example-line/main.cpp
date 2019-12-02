#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "SGL.h"

using namespace std;
using namespace SGL;
using namespace glm;

static const string vs = R"(
#version 130
in vec3 position;
in vec3 color;
uniform mat4 projectionMatrix, modelviewMatrix;
out vec3 u_color;
void main() {
    gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
    u_color = color;
}
)";
static const string fs = R"(
#version 130
in vec3 u_color;
void main(){
    gl_FragColor = vec4(u_color,1.0);
}
)";

Ptr<Scene> scene;
Ptr<PerspectiveCamera> camera;

void initializeGL() {
    glClearColor(0.2f, 0.0f, 0.2f, 1.f);

    Ptr<Line> twoLines;
    {
        vec3 vertex[]={
                vec3(0., 0, -100), vec3(0.5, 0, -100), vec3(0.5, 0.5, -100)
        };
        vec3 color[]={
                vec3(1,0,0), vec3(0,1,0), vec3(0,0,1)
        };
        Ptr<VertexBuffer> vbo = VertexBuffer::create(vertex, sizeof(vertex), sizeof(vec3));
        Ptr<VertexBuffer> cbo = VertexBuffer::create(color, sizeof(color), sizeof(vec3));
        Ptr<Geometry> geometry = Geometry::create();
        geometry->add_attribute("position", vbo);
        geometry->add_attribute("color", cbo);

        Ptr<Shader> shader = Shader::create(vs, fs);
        Ptr<ShaderMaterial> material = ShaderMaterial::create(shader);
        twoLines = Line::create(geometry, material);
        twoLines->set_line_width(2.0f);
    }

    scene = Scene::create();
    {
        scene->add(twoLines);
    }

    camera = PerspectiveCamera::create();
    {
        camera->lookat(vec3(0,0,0),vec3(0,0,-1),vec3(0,1,0));
        camera->perspective(atan(1.0/100.0)*2.0, 1.0, 1.0, 1000.0);
    }
}

void display() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    scene->draw(camera.get());
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("example");

    if (GLEW_OK != glewInit()) {
        cout <<"failed to init glew" << endl;
        return 1;
    }

    initializeGL();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}