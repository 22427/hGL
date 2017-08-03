#ifndef MGL_BUILDING_DLL
#include "hgles_context_state.h"
#include "hgles_window.h"
#include "hgles_input.h"

class OpenGLApplication :
		public hgles::WindowListener,
		public hgles::KeyboardListener
{
	hgles::Window win;
	hgles::InputSystem ins;
	hgles::ContextState gles;

	GLuint vao;
	GLuint vbo;
	float brightness;
public:

	OpenGLApplication():win(800,600)
	{
		// setup the system:
		// init the input system. It needs the window to do so.
		ins.init(&win);
		brightness = 1.0f;

		// in order to access events we need to register as listener
		win.add_window_listener(this);
		ins.add_keyboard_listener(this);

		// lets create some simple geometry
		float vd[] = {-1,-1,0,
					  1,-1,0,
					  0,1,0};
		gles.GenVertexArrays(1,&vao);
		gles.GenBuffers(1,&vbo);
		gles.BindVertexArray(vao);
		gles.BindBuffer(GL_ARRAY_BUFFER,vbo);
		gles.BufferData(GL_ARRAY_BUFFER,9*sizeof(float),vd,GL_STATIC_DRAW);

		// choose binding and attribute id ...
		const GLuint attrib_id = 0;

		// set the attributes format: how does one of this attributes look like
		// insida a set of attributes.
		gles.EnableVertexAttribArray(attrib_id);
		gles.VertexAttribPointer(attrib_id,
								 3,
								 GL_FLOAT,
								 GL_FALSE,
								 3*sizeof(float),
								 0);

		// create a shader using a util_ function ... making it easy to
		// create a shader from a strings.

		auto p = gles.CreateProgam();
		auto vs = gles.util_CreateShader(GL_VERTEX_SHADER,
										   "#version 100\n "
										   "attribute vec3 pos; \n"
										   "void main(){\n"
										   "gl_Position = vec4(pos,1.0);\n}");
		auto fs = gles.util_CreateShader(GL_FRAGMENT_SHADER,
										   "#version 100\n "
										   "void main(){\n"
										   "gl_FragColor = vec4(1,0,0,1);\n}");
		gles.AttachShader(p,vs);
		gles.AttachShader(p,fs);
		gles.BindAttribLocation(p,0,"pos");

		gles.LinkProgram(p);

		gles.DeleteShader(vs);
		gles.DeleteShader(fs);
		// we wont use any other program so we can bind it and keep it that way!
		gles.UseProgram(p);

	}

	void start_rendering()
	{
		int i=  0;
		while(!win.should_close())
		{
			i++;
			if(i%60<30)
				gles.ClearColor(0,brightness,0,1);
			else
				gles.ClearColor(0,0,brightness,1);

			if(ins.is_key_down(hgles::K_UP) && brightness < 1.0f)
				brightness+=0.01f;
			if(ins.is_key_down(hgles::K_DOWN) && brightness >=0.0f)
				brightness-=0.01f;
			if(ins.is_key_down(hgles::K_KP_ADD))
				win.set_size(win.get_size()+glm::ivec2(10));
			if(ins.is_key_down(hgles::K_KP_SUBTRACT))
				win.set_size(win.get_size()-glm::ivec2(10));

			if(ins.is_key_down(hgles::K_W))
				win.set_position(win.get_position()+glm::ivec2(0,-10));
			if(ins.is_key_down(hgles::K_A))
				win.set_position(win.get_position()+glm::ivec2(-10,0));
			if(ins.is_key_down(hgles::K_S))
				win.set_position(win.get_position()+glm::ivec2(0,10));
			if(ins.is_key_down(hgles::K_D))
				win.set_position(win.get_position()+glm::ivec2(10,0));


			gles.Clear(GL_COLOR_BUFFER_BIT);
			gles.BindVertexArray(vao);
			gles.DrawArrays(GL_TRIANGLES,0,3);

			// swap buffers
			win.swap_buffers();
			// check for new events!
			win.poll_events();
			ins.poll_events();
		}
	}

	void size_changed(const int w, const int h)
	{
		glViewport(0,0,w,h);
	}

	void key_down(const hgles::Key k)
	{
		if(k == hgles::K_ESCAPE)
		{
			win.set_should_close();
		}
	}

};
int main()
{

	OpenGLApplication app;
	app.start_rendering();

	return 0;
}
#endif
