extern int getCanvasWidth();
extern int getCanvasHeight();
extern void initGL(char* vertexShader, char* fragmentShader);

int width;
int height;

char vertexShader[] = 
"void main() {"
"  gl_Position = vec4(position, 1.0);"
"}";

char fragmentShader[] =
"void main() {"
" gl_FragColor = vec4(0.3, 0.6, 1.0, 1.0);"
"}";

void onInit() {
  width = getCanvasWidth();
  height = getCanvasHeight();

  char* vs = malloc(sizeof(vertexShader));
  char* fs = malloc(sizeof(fragmentShader));

  // copy shader content
  
  initGL(vs, fs);

  mfree(vs);
  mfree(fs);
}

void onAnimationFrame(int timestamp) {
  static int previous = 0;

  int delta = previous ? timestamp - previous : 0;

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
