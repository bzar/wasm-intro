extern void setFillColor(int, int, int, int);
extern void fillRect(int, int, int, int);
extern int getCanvasWidth();
extern int getCanvasHeight();

typedef struct  {
  float x;
  float y;
  float vx;
  float vy;
} Particle;

Particle particles[100];
int width;
int height;

void bounce(float* position, float* velocity, float minValue, float maxValue) {
  if (*position > maxValue) {
    *position -= *position - maxValue;
    *velocity = -*velocity;
  } else if (*position < minValue) {
    *position = minValue + (minValue - *position);
    *velocity = -*velocity;
  }
}

void onInit() {
  width = getCanvasWidth();
  height = getCanvasHeight();
  for (int i = 0; i < 100; ++i) {
    particles[i].x = width/2.0;
    particles[i].y = height/2.0;
    particles[i].vx = ((i*7 % 200) - 100)/100.0;
    particles[i].vy = ((i*19 % 200) - 100)/100.0;
  }
}

void onAnimationFrame(int timestamp) {
  static int previous = 0;

  int delta = previous ? timestamp - previous : 0;

  setFillColor(64,64,64,255);
  fillRect(0, 0, width, height);

  setFillColor(255,0,0,255);
  for (int i = 0; i < 100; ++i) {
    particles[i].vy += 0.001 * delta;
    particles[i].x += particles[i].vx * delta;
    particles[i].y += particles[i].vy * delta;

    bounce(&particles[i].x, &particles[i].vx, 0, width - 10);
    bounce(&particles[i].y, &particles[i].vy, 0, height - 10);

    fillRect((int) (particles[i].x + 0.5), (int) (particles[i].y + 0.5), 10, 10);
  }

  previous = timestamp;
}
