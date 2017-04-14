extern int getCanvasWidth();
extern int getCanvasHeight();
extern unsigned int compileShader(char* source, unsigned int type);
extern unsigned int linkShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId);

extern void glClearColor(float, float, float, float);
extern void glEnable(unsigned int);
extern void glDepthFunc(unsigned int);
extern void glClear(unsigned int);
extern int glGetAttribLocation(unsigned int, char*);
extern int glGetUniformLocation(unsigned int, char*);
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



void* malloc(unsigned int);
void mfree(void*);
unsigned int msize(void*);
void* memcpy(void*, void const*, unsigned int);

int width;
int height;

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

unsigned int programId;
int positionAttributeLocation;
int offsetUniformLocation;
unsigned int positionBuffer;

void onInit() {
  width = getCanvasWidth();
  height = getCanvasHeight();

  glClearColor(0.1, 0.1, 0.1, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  char* vs = (char*) malloc(sizeof(vertexShader) - 1);
  memcpy(vs, vertexShader, msize(vs));
  unsigned int vsId = compileShader(vs, GL_VERTEX_SHADER);
  mfree(vs);

  char* fs = (char*) malloc(sizeof(fragmentShader) - 1);
  memcpy(fs, fragmentShader, msize(fs));
  unsigned int fsId = compileShader(fs, GL_FRAGMENT_SHADER);
  mfree(fs);

  programId = linkShaderProgram(vsId, fsId);

  char posAttrName[] = "a_position";
  char* positionAttributeName = (char*) malloc(sizeof(posAttrName) - 1);
  memcpy(positionAttributeName, posAttrName, msize(positionAttributeName));
  positionAttributeLocation = glGetAttribLocation(programId, positionAttributeName);
  mfree(positionAttributeName);

  char offsetUnifName[] = "u_offset";
  char* offsetUniformName = (char*) malloc(sizeof(offsetUnifName) - 1);
  memcpy(offsetUniformName, offsetUnifName, msize(offsetUniformName));
  offsetUniformLocation = glGetUniformLocation(programId, offsetUniformName);
  mfree(offsetUniformName);

  positionBuffer = glCreateBuffer();
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);

  float positions[] = {0, 0, 0, 0.5, 0.7, 0};
  unsigned int num_positions = sizeof(positions)/sizeof(float);
  float* positionsPtr = (float*) malloc(sizeof(positions));
  memcpy(positionsPtr, positions, sizeof(positions));
  glBufferData(GL_ARRAY_BUFFER, positionsPtr, num_positions, GL_STATIC_DRAW);
  mfree(positionsPtr);
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
  // logic

  previous = timestamp;
}

// Malloc/mfree/msize

typedef struct Block {
  unsigned int size;
  unsigned int usize;
  struct Block* next;
  struct Block* prev;
} Block;

Block* usedBlocks = 0;
Block* freeBlocks = 0;
Block* nextBlock = (Block*) 1024;

void* malloc(unsigned int size) {
  Block* b = freeBlocks;
  while (b && b->size < size) b = b->next;

  if(!b) {
    b = nextBlock;
    b->size = size;
    nextBlock += size + sizeof(Block); // Header + data
  }

  b->usize = size;
  b->next = usedBlocks;
  if(b->next) b->next->prev = b;
  b->prev = 0;
  usedBlocks = b;

  return (void*) b + sizeof(Block);
}

void mfree(void* data) {
  Block* b = data - sizeof(Block);
  if(b->prev) b->prev->next = b->next;
  b->next = freeBlocks;
  if(b->next) b->next->prev = b;
  b->prev = 0;
  freeBlocks = b;
}

unsigned int msize(void* data) {
  Block* b = data - sizeof(Block);
  return b->usize;
}

void* memcpy(void* dst, void const* src, unsigned int bytes) {
  for(unsigned int i = 0; i < bytes; ++i) {
    ((char*)dst)[i] = ((char*)src)[i];
  }
  return dst;
}
