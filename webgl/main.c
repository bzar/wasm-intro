extern unsigned int compileShader(char const* source, unsigned int len, unsigned int type);
extern unsigned int linkShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId);

extern void glClearColor(float, float, float, float);
extern void glEnable(unsigned int);
extern void glDepthFunc(unsigned int);
extern void glClear(unsigned int);
extern int glGetAttribLocation(unsigned int, char const*, unsigned int);
extern int glGetUniformLocation(unsigned int, char const*, unsigned int);
extern void glUniform4fv(int, float, float, float, float);
extern unsigned int glCreateBuffer();
extern void glBindBuffer(unsigned int, unsigned int);
extern void glBufferData(unsigned int, float*, unsigned int, unsigned int);
extern void glUseProgram(unsigned int);
extern void glEnableVertexAttribArray(unsigned int);
extern void glVertexAttribPointer(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void glDrawArrays(unsigned int, unsigned int, unsigned int);

// Identifier constants pulled from WebGLRenderingContext
unsigned int GL_VERTEX_SHADER = 35633;
unsigned int GL_FRAGMENT_SHADER = 35632;
unsigned int GL_ARRAY_BUFFER = 34962;
unsigned int GL_TRIANGLES = 4;
unsigned int GL_STATIC_DRAW = 35044;
unsigned int GL_FLOAT = 5126;
unsigned int GL_DEPTH_TEST = 2929;
unsigned int GL_LEQUAL = 515;
unsigned int GL_COLOR_BUFFER_BIT = 16384;
unsigned int GL_DEPTH_BUFFER_BIT = 256;

char vertexShader[] = 
"attribute vec4 a_position;"
"uniform vec4 u_offset;"
"void main() {"
"  gl_Position = a_position + u_offset;"
"}";

char fragmentShader[] =
"precision mediump float;"
"void main() {"
" gl_FragColor = vec4(0.3, 0.6, 1.0, 1.0);"
"}";

float positions[] = {0, 0, 0, 0.5, 0.7, 0};

unsigned int programId;
int positionAttributeLocation;
int offsetUniformLocation;
unsigned int positionBuffer;

void onInit() {
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  unsigned int vsId = compileShader(vertexShader, sizeof(vertexShader) - 1, GL_VERTEX_SHADER);
  unsigned int fsId = compileShader(fragmentShader, sizeof(fragmentShader) - 1, GL_FRAGMENT_SHADER);

  programId = linkShaderProgram(vsId, fsId);

  positionAttributeLocation = glGetAttribLocation(programId, "a_position", sizeof("a_position") - 1);
  offsetUniformLocation = glGetUniformLocation(programId, "u_offset", sizeof("u_offset") - 1);

  positionBuffer = glCreateBuffer();
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
  glBufferData(GL_ARRAY_BUFFER, positions, 6, GL_STATIC_DRAW);
}

void onAnimationFrame(int timestamp) {
  static int previous = 0;
  static float x = 0;

  int delta = previous ? timestamp - previous : 0;
  x += delta / 1000.0;
  if(x > 1) x = -2;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(programId);
  glEnableVertexAttribArray(positionAttributeLocation);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
  glVertexAttribPointer(positionAttributeLocation, 2, GL_FLOAT, 0, 0, 0);
  glUniform4fv(offsetUniformLocation, x, 0.0f, 0.0f, 0.0f);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  previous = timestamp;
}
