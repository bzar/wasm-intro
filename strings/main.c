extern int consoleLog(unsigned int, unsigned int len);

unsigned int* memory = 0;

void mirrorLog(unsigned int offset, unsigned int len) {
  unsigned int* s = memory + offset;
  unsigned int responseOffset = 128; // arbitrary number, we have ALL the memory
  unsigned int* response = memory + responseOffset;
  for(unsigned int i = 0; i < len; ++i) {
    response[i] = s[i];
    response[len*2-i-1] = s[i];
  }
  consoleLog(responseOffset, len*2);
}
