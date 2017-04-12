unsigned int* memory = 0;

unsigned int put(unsigned int offset, unsigned int value) {
  *(memory + offset) = value;
  return *(memory + offset);
}

unsigned int get(unsigned int offset) {
  return *(memory + offset);
}
