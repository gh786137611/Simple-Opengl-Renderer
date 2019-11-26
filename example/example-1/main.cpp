#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>


#include <SGL.h>
#include <stb_image.h>

using namespace std;
using  namespace glm;
using namespace SGL;
Ptr<Scene> scene;
Ptr<PerspectiveCamera> perspectiveCamera;
int WinX = 512, WinY = 512;

const string vert = R"(
#version 330 core
in vec3 position;
uniform mat4 modelviewMatrix;
uniform mat4 projectionMatrix;
out vec3 u_dir;
void main() {
    gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
    u_dir = position;
}
)";
const string frag = R"(
#version 130
in vec3 u_dir;
uniform samplerCube cube;
uniform vec4 mask;
void main() {
    gl_FragColor = texture(cube, normalize(u_dir)) * mask;
}
)";

const string vert2 = R"(
#version 130
in vec3 position;
uniform mat4 modelviewMatrix;
uniform mat4 projectionMatrix;
void main() {
    gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
}
)";
const string frag2 = R"(
#version 130
void main() {
    gl_FragColor = vec4(1.0, 0.0, 0.0, 0.1);
}
)";

const string vert3= R"(
#version 130
in vec3 position;
uniform mat4 modelviewMatrix;
uniform mat4 projectionMatrix;
void main() {
    gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
}
)";
const string frag3 = R"(
#version 130
uniform vec3 u_color;
void main() {
    gl_FragColor = vec4(u_color, 1.0);
}
)";

void initializeGL() {
    glClearColor(0.6,0.0,0.6,1.0);

    Ptr<Geometry> box = Geometry::create_unit_box();

    scene = Scene::create();
    {
        Ptr<Shader> shader = Shader::create(vert, frag);
        Ptr<ShaderMaterial> material = ShaderMaterial::create(shader);

        void *data[6];
        string direction[] = {"r","l", "u", "d", "f", "b"};
        int x, y, ch;
        for (int i = 0; i<6; i++){
            const string file = string("../../resouces/skybox/") + direction[i] + ".jpg";
            data[i] = stbi_load(file.c_str(), &x, &y, &ch,3);
            assert(data[i]);
        }
        Ptr<TextureCube> textureCube = Texture::create_cube_texture();
        textureCube->set_data(PixelFormat::RGBA, x, y, PixelFormat::RGB, TextureDataType::UBYTE, data);
        textureCube->generate_mipmap();
        textureCube->set_filter(TextureParameter::LinearMipMapLinear, TextureParameter::Linear);
        textureCube->set_wrap(TextureParameter::ClampToEdge, TextureParameter::ClampToEdge,TextureParameter::ClampToEdge);

        for (auto e:data) stbi_image_free(e);
        material->set_texture("cube", textureCube);
        material->set_value("mask", vec4(1,0,1,1));
        Ptr<Object3D> mesh = TriMesh::create(box, material);
        float scale = 300.0;
        mesh->set_scale(scale,scale,scale);
        scene->add(mesh);
    }
    {
        auto shader = Shader::create(vert2,frag2);
        auto material = ShaderMaterial::create(shader);
        material->set_blend(true);
        auto childBox = TriMesh::create(box, material);
        childBox->set_position(vec3(0,0,-10));
        Ptr<Object3D> childBox_2 = TriMesh::create(box, material);
        childBox_2->set_position(vec3(0,2,0));
        Ptr<Object3D> t(childBox);
        t->add_child(childBox_2);
        scene->add(t);
    }
    {
        vec3 v[]={vec3(0,-30,0), vec3(0,0,0), vec3(0,30,0)};
        auto vbo = VertexBuffer::create(v, sizeof(v), sizeof(vec3));
        auto g = Geometry::create();
        g ->add_attribute("position",vbo);
        auto shader = Shader::create(vert3,frag3);
        auto m = ShaderMaterial::create(shader);
        m->set_value("u_color",vec3(0,1,0));
        auto line = Line::create(g, m);
        line->set_position(vec3(0,0,-100));
        line->set_line_width(2.f);
        scene->add(line);
    }

    {
        vector<vec3> v;
        v.reserve((100 * 100 * 100));
        float h = 20 / 5.f;
        for (float x = -10; x <10; x+=h){
            for (float y = -10; y <10; y+=h){
                for (float z = -10; z <10; z+=h){
                    v.push_back(vec3(x,y,z));
                }
            }
        }
        auto vbo = VertexBuffer::create(v.data(), sizeof(vec3)*v.size(), sizeof(vec3));
        auto g = Geometry::create();
        g->add_attribute("position",vbo);
        auto shader = Shader::create(vert3,frag3);
        auto m = ShaderMaterial::create(shader);
        m->set_value("u_color",vec3(0,1,1));
        auto points = Point::create(g, m);
        points->set_position(vec3(0,0,-50));
        scene->add(points);
        points->set_size(2.f);
    }

    perspectiveCamera = Camera::createPerspective();
    perspectiveCamera->lookat(glm::vec3(0,0,0), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    perspectiveCamera->perspective( atan(100.0/100.0)*2, double(WinX)/double(WinY), 1.0, 500.0);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0, WinX, WinY);

    scene->draw(perspectiveCamera.get());
    glutSwapBuffers();
}

void resizeGL(int w, int h) {
    WinX = w;
    WinY = h;
    perspectiveCamera->perspective( atan(100.0/100.0)*2, double(WinX)/double(WinY), 1, 500.0);
    glutPostRedisplay();
}



void keyboard(unsigned char ch, int x, int y) {
    static float  t = 0.;
    if (ch =='a') {
        t += 0.03;
        mat4 r = glm::rotate(glm::mat4(1.0f), t,glm::vec3(0.0f, 1.0f, 0.0f));
        float x = sin(t), z = -cos(t);
        perspectiveCamera->lookat(vec3(0,0,0), vec3(x, 0, z), vec3(0,1,0));
    }else if (ch == 'd'){
        t -= 0.03;
        mat4 r = glm::rotate(glm::mat4(1.0f), t,glm::vec3(0.0f, 1.0f, 0.0f));
        float x = sin(t), z = -cos(t);
        perspectiveCamera->lookat(vec3(0,0,0), vec3(x, 0, z), vec3(0,1,0));
    }
    else if (ch =='e') {
        PrintGLError(glGetError());
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutCreateWindow("test");

    if (glewInit() != GLEW_OK) {
        cout <<"failed to init glew" << endl;
        return 1;
    }

    initializeGL();
    glutDisplayFunc(display);
    glutReshapeFunc(resizeGL);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}