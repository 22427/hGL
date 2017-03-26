#include "mgl_context_state.h"
#include "mgl_glfw_window.h"

class OpenGLApplication
{
	mgl::Window_GLFW win;
	mgl::ContextState cs;

	mgl::VertexArray vao;
	mgl::Buffer vbo;

public:
	void handle_keys(int key, int /*code*/, int /*modifier*/)
	{
		if(key == GLFW_KEY_ESCAPE)
			win.set_should_close();
		if(key == GLFW_KEY_D)
			win.toggle_decoration();
		if(key == GLFW_KEY_F)
			win.toggle_fullscreen();
	}
	OpenGLApplication():win(800,600)
	{
		float vd[] = {-1,-1,0,
					  1,-1,0,
					  0,1,0};

		// Lets make some opengl 4.5 geometry!
		// create vao
		vao = cs.createVertexArray();
		// create vbo
		auto vbo = cs.createBuffer();
		// write data to vbo
		vbo.bufferData(9*sizeof(float),vd,GL_STATIC_DRAW);

		// choose binding and attribute id ...
		const GLuint attrib_id = 0;

		// set the attributes format: how does one of this attributes look like
		// insida a set of attributes.
		vao.vertexAttribPointer(vbo,attrib_id,3,GL_FLOAT,GL_FALSE,0,0);
		vao.enableVertexAttribArray(attrib_id);


		// create a shader using a util_ function ... making it easy to
		// create a shader from two strings.

		auto p = cs.util_create_program( "#version 100\n "
										   "layout(location=0) in vec3 pos; \n"
										   "void main(){\n"
										   "gl_Position = vec4(pos,1.0);\n}",

										   "#version 100\n "
										   "layout(location=0) out vec4 clr; \n"
										   "void main(){\n"
										   "clr = vec4(1,0,0,1);\n}");

		// we wont use any other program so we can bind it and keep it that way!
		cs.useProgram(p);


		//setting the resize callback  callback as a lambda.
		win.set_size_callback([this](int w, int h){glViewport(0,0,w,h);});

		// settting a method as the key_up callback using lambdas
		win.set_key_up_callback(
					[this](int a, int b, int c)
		{
			this->handle_keys(a,b,c);
		});
	}

	void start_rendering()
	{
		int i=  0;
		while(!win.should_close())
		{
			i++;
			if(i%60<30)
				glClearColor(0,1,0,1);
			else
				glClearColor(0,0,1,1);

			glClear(GL_COLOR_BUFFER_BIT);
			cs.bindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES,0,3);

			// swap buffers
			win.swap_buffers();
			// check for new events!
			win.poll_events();
		}
	}
};
int main()
{

	OpenGLApplication app;
	app.start_rendering();

	return 0;
}
