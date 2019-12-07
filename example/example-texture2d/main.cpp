#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stb_image.h>
#include "SGL.h"

using namespace std;
using namespace SGL;
using namespace glm;

static const string vs = R"(
#version 130
in vec3 position;
in vec2 uv;
uniform mat4 projectionMatrix, modelviewMatrix;
out vec2 u_uv;
void main() {
    gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
    u_uv = vec2(uv.x, 1.0 - uv.y);
}
)";
static const string fs = R"(
#version 130
in vec2 u_uv;
uniform sampler2D tex;
void main(){
    gl_FragColor = texture(tex, u_uv);
}
)";

Ptr<Scene> scene;
Ptr<PerspectiveCamera> camera;

void initializeGL() {
    glClearColor(0.2f, 0.0f, 0.2f, 1.f);

    Ptr<TriMesh> rect;
    {
        vec3 vertex[]={
                vec3(0., 0, 0), vec3(0.5, 0, 0), vec3(0.5, 0.5, 0), vec3(0., 0.5, 0)
        };
        vec2 uv[]={
                vec2(0,0),vec2(1,0),vec2(1,1),vec2(0,1)
        };
        unsigned indices[]={0,1,2, 0, 2,3};
        Ptr<VertexBuffer> vbo = VertexBuffer::create(vertex, sizeof(vertex), sizeof(vec3));
        Ptr<VertexBuffer> uvVBO = VertexBuffer::create(uv, sizeof(uv), sizeof(vec2));
        Ptr<IndexBuffer> ibo = IndexBuffer::create(indices, 6);
        Ptr<Geometry> geometry = Geometry::create();
        geometry->add_attribute("position", vbo);
        geometry->add_attribute("uv", uvVBO);
        geometry->set_indices(ibo);

        Ptr<Shader> shader = Shader::create(vs, fs);
        Ptr<ShaderMaterial> material = ShaderMaterial::create(shader);
        // create texture 2d
        {
            int x, y, ch;
            unsigned char *image = stbi_load("../../resouces/skybox/b.jpg", &x, &y, &ch, 3);
            assert(image);
            Ptr<Texture2D> tex2d = Texture2D::create();
            tex2d->set_data(PixelFormat::RGBA,x, y, PixelFormat::RGB, TextureDataType::UBYTE, image);
            stbi_image_free(image);
            material->set_texture("tex", tex2d);
        }
        rect = TriMesh::create(geometry, material);
        rect->set_position(vec3(0,0,-100));
        rect->set_name("rect");
        // rect->set_cull_face(Face::Back);
    }
    scene = Scene::create();
    {
        scene->add(rect);
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

void idle() {
    static float t = 0;
    Ptr<Object3D> ptr = scene->find("rect");
    if (ptr) {
        ptr->set_rotation(glm::rotate(glm::mat4(1.f), t, vec3(0.f, 1.f, 0.f)));
        t += 0.01f;
        glutPostRedisplay();
    }
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
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}