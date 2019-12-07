#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stb_image.h>
#include "SGL.h"

using namespace std;
using namespace SGL;
using namespace glm;

static const string box_vs = R"(
#version 130
in vec3 position;
uniform mat4 projectionMatrix, modelviewMatrix;
out vec3 u_direction;
void main() {
    gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
    u_direction = position;
}
)";
static const string box_fs = R"(
#version 130
in vec3 u_direction;
uniform samplerCube cube;
void main(){
    gl_FragColor = texture(cube, normalize(u_direction));
}
)";


static const string sphere_vs = R"(
#version 130
in vec3 position;
in vec3 normal;
uniform mat4 projectionMatrix, modelviewMatrix;
uniform mat4 modelMatrix;
out vec3 u_position;
out vec3 u_normal;
void main() {
    vec4 tmp = modelMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
    u_position = tmp.xyz / tmp.w;
    u_normal = normal;
}
)";
static const string sphere_fs = R"(
#version 130
in vec3 u_position;
in vec3 u_normal;
uniform samplerCube cube;
uniform vec3 eye;
void main(){
    vec3 dir = refract(normalize(u_position - eye), normalize(u_normal), 1.0 / 1.2);
    gl_FragColor = texture(cube, normalize(dir));
}
)";
Ptr<Scene> scene;
Ptr<PerspectiveCamera> camera;

Ptr<TriMesh> create_sphere() {
    int n = 50;
    float thetaDelta = 2.f * M_PI / n;
    float phiDelta = M_PI / n;
    int width = 0, height = 0;

    vector<vec3> vertices;
    vertices.reserve(n * n);
    for (int h = 0; h<n+1; h++){
        float phi = h * phiDelta;
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        float z = cosPhi;

        for (int w = 0; w < n + 1; w++){
            float theta = w * thetaDelta;
            float x = cos(theta) * sinPhi;
            float y = sin(theta) * sinPhi;
            vertices.push_back(vec3(x,y,z));
        }
    }

    vector<unsigned> indices;
    indices.reserve(6 * (n-1) * (n-1));
    for (int h = 0; h<n; h++){
        for (int w = 0; w <n ; w++){
            int id = h * n + w;
            indices.push_back(id);
            indices.push_back(id + 1);
            indices.push_back(id + 1 + n);

            indices.push_back(id);
            indices.push_back(id + 1 + n);
            indices.push_back(id + n);
        }
    }

    Ptr<VertexBuffer> vbo = VertexBuffer::create(vertices.data(), sizeof(vec3) * vertices.size(), sizeof(vec3));
    Ptr<Geometry> geometry = Geometry::create();
    geometry->add_attribute("position", vbo);
    geometry->add_attribute("normal", vbo);
    Ptr<IndexBuffer> ibo = IndexBuffer::create(indices.data(), indices.size());
    geometry->set_indices(ibo);

    Ptr<Shader> shader = Shader::create(sphere_vs, sphere_fs);
    Ptr<ShaderMaterial> material = ShaderMaterial::create(shader);

    Ptr<TriMesh> mesh = TriMesh::create(geometry, material, "sphere");
    return mesh;
}


void initializeGL() {
    glClearColor(0.2f, 0.0f, 0.2f, 1.f);

    Ptr<TriMesh> box;
    Ptr<TextureCube> textureCube;
    {
        Ptr<Geometry> boxGeometry = Geometry::create_unit_box();
        Ptr<Shader> shader = Shader::create(box_vs, box_fs);
        Ptr<ShaderMaterial> material = ShaderMaterial::create(shader);

        void *data[6];
        string direction[] = {"r","l", "u", "d", "f", "b"};
        int x, y, ch;
        for (int i = 0; i<6; i++){
            const string file = string("../../resouces/skybox/") + direction[i] + ".jpg";
            data[i] = stbi_load(file.c_str(), &x, &y, &ch,3);
            assert(data[i]);
        }
        textureCube = TextureCube::create();
        textureCube->set_data(PixelFormat::RGBA, x, y, PixelFormat::RGB, TextureDataType::UBYTE, data);
        textureCube->generate_mipmap();
        textureCube->set_filter(TextureParameter::LinearMipMapLinear, TextureParameter::Linear);
        textureCube->set_wrap(TextureParameter::ClampToEdge, TextureParameter::ClampToEdge,TextureParameter::ClampToEdge);

        for (auto e:data) stbi_image_free(e);
        material->set_texture("cube", textureCube);
        box = TriMesh::create(boxGeometry, material);
        float scale = 300.0;
        box->set_scale(scale,scale,scale);
        box->set_name("box");
    }

    scene = Scene::create();
    {
        scene->add(box);

        Ptr<TriMesh> sphere = create_sphere();
        {
            sphere->material()->set_texture("cube", textureCube);
            sphere->set_position(vec3(0,0,-50));
            sphere->set_scale(30, 30, 30);
            sphere->material()->set_value("modelMatrix", sphere->get_modelMatrix());
            sphere->material()->set_value("eye", vec3(0,0,0));
            sphere->set_name("sphere");
        }
        scene->add(sphere);

    }

    camera = PerspectiveCamera::create();
    {
        camera->lookat(vec3(0,0,0),vec3(0,0,-1),vec3(0,1,0));
        camera->perspective(atan(100.0/100.0)*2.0, 1.0, 1.0, 1000.0);
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
