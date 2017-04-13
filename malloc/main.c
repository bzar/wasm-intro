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
