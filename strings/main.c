extern int consoleLog(unsigned int*, unsigned int len);

void logTwice(unsigned int* s, unsigned int len) {
  unsigned int* response = (unsigned int*) 128; // arbitrary number, we have ALL the memory
  for(int i = 0; i < len; ++i) {
    response[i] = s[i];
    response[i+len] = s[i];
  }
  consoleLog(response, len*2);
}
