extern unsigned int compileShader(char const* source, unsigned int len, unsigned int type);
extern unsigned int linkShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId);

extern void glClearColor(float, float, float, float);
extern void glEnable(unsigned int);
extern void glDepthFunc(unsigned int);
extern void glBlendFunc(unsigned int, unsigned int);
extern void glClear(unsigned int);
extern int glGetAttribLocation(unsigned int, char const*, unsigned int);
extern int glGetUniformLocation(unsigned int, char const*, unsigned int);
extern void glUniform4fv(int, float, float, float, float);
extern void glUniform1i(int, int);
extern void glUniform1f(int, float);
extern unsigned int glCreateBuffer();
extern void glBindBuffer(unsigned int, unsigned int);
extern void glBufferData(unsigned int, float const*, unsigned int, unsigned int);
extern void glUseProgram(unsigned int);
extern void glEnableVertexAttribArray(unsigned int);
extern void glVertexAttribPointer(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void glDrawArrays(unsigned int, unsigned int, unsigned int);
extern unsigned int glCreateTexture();
extern void glBindTexture(unsigned int, unsigned int);
extern void glTexImage2D(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned char const*, unsigned int);
extern void glTexParameteri(unsigned int, unsigned int, unsigned int);
extern void glActiveTexture(unsigned int);

extern void consoleLog(unsigned int);
extern void playAudio(float*, unsigned int);
extern void setScore(unsigned int, unsigned int);

// Identifier constants pulled from WebGLRenderingContext
unsigned int const GL_VERTEX_SHADER = 35633;
unsigned int const GL_FRAGMENT_SHADER = 35632;
unsigned int const GL_ARRAY_BUFFER = 34962;
unsigned int const GL_TRIANGLES = 4;
unsigned int const GL_STATIC_DRAW = 35044;
unsigned int const GL_FLOAT = 5126;
unsigned int const GL_DEPTH_TEST = 2929;
unsigned int const GL_LEQUAL = 515;
unsigned int const GL_COLOR_BUFFER_BIT = 16384;
unsigned int const GL_DEPTH_BUFFER_BIT = 256;
unsigned int const GL_TEXTURE_2D = 3553;
unsigned int const GL_RGBA = 6408;
unsigned int const GL_UNSIGNED_BYTE = 5121;
unsigned int const GL_TEXTURE_MAG_FILTER = 10240;
unsigned int const GL_TEXTURE_MIN_FILTER = 10241;
unsigned int const GL_NEAREST = 9728;
unsigned int const GL_TEXTURE0 = 33984;
unsigned int const GL_BLEND = 3042;
unsigned int const GL_SRC_ALPHA = 770;
unsigned int const GL_ONE_MINUS_SRC_ALPHA = 771;
unsigned int const GL_ONE= 1;



char const vertexShader[] =
"attribute vec2 a_position;"
"attribute vec2 a_texcoord;"
"uniform vec4 u_offset;"
"varying mediump vec2 v_texcoord;"
"void main() {"
"  gl_Position = vec4(a_position, 1.0, 1.0) + u_offset;"
"  v_texcoord = a_texcoord;"
"}";

char const fragmentShader[] =
"precision mediump float;"
"varying mediump vec2 v_texcoord;"
"uniform sampler2D u_sampler;"
"uniform float u_opacity;"
"void main() {"
" gl_FragColor = texture2D(u_sampler, v_texcoord);"
" gl_FragColor.a *= u_opacity;"
"}";

float const BALL_VERTICES[] = {
  -0.05,-0.05,0,0, 0.05,0.05,1,1, -0.05,0.05,0,1,
  -0.05,-0.05,0,0, 0.05,-0.05,1,0, 0.05,0.05,1,1
};

unsigned char const BALL_TEXTURE[] = {
  0x00,0x00,0x00,0x00, 0xDD,0x00,0x00,0xFF, 0xDD,0x00,0x00,0xFF, 0x00,0x00,0x00,0x00,
  0xDD,0x00,0x00,0xFF, 0xFF,0x00,0x00,0xFF, 0xFF,0x44,0x44,0xFF, 0xDD,0x00,0x00,0xFF,
  0xDD,0x00,0x00,0xFF, 0xFF,0x44,0x44,0xFF, 0xFF,0x88,0x88,0xFF, 0xDD,0x00,0x00,0xFF,
  0x00,0x00,0x00,0x00, 0xDD,0x00,0x00,0xFF, 0xDD,0x00,0x00,0xFF, 0x00,0x00,0x00,0x00
};
float const BALL_TAIL_VERTICES[] = {
  -0.04,-0.04,0,0, 0.04,0.04,1,1, -0.04,0.04,0,1,
  -0.04,-0.04,0,0, 0.04,-0.04,1,0, 0.04,0.04,1,1
};

unsigned char const BALL_TAIL_TEXTURE[] = {
  0x00,0x00,0x00,0x00, 0xFF,0x00,0x00,0xCC, 0xFF,0x00,0x00,0xCC, 0x00,0x00,0x00,0x00,
  0xFF,0x00,0x00,0xCC, 0xFF,0x00,0x00,0xCC, 0xFF,0x00,0x00,0xCC, 0xFF,0x00,0x00,0xCC,
  0xFF,0x00,0x00,0xCC, 0xFF,0x00,0x00,0xCC, 0xFF,0x00,0x00,0xCC, 0xFF,0x00,0x00,0xCC,
  0x00,0x00,0x00,0x00, 0xFF,0x00,0x00,0xCC, 0xFF,0x00,0x00,0xCC, 0x00,0x00,0x00,0x00
};

float const PADDLE_VERTICES[] = {
  -0.05,-0.20,0,0, 0.05,0.20,1,1, -0.05,0.20,0,1,
  -0.05,-0.20,0,0, 0.05,-0.20,1,0, 0.05,0.20,1,1
};

unsigned char const PADDLE_TEXTURE[] = {
  0x00,0xDD,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xDD,0x00,0xFF,
  0x00,0xDD,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xDD,0x00,0xFF,
  0x00,0xDD,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xDD,0x00,0xFF,
  0x00,0xDD,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xDD,0x00,0xFF,
  0x00,0xDD,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xDD,0x00,0xFF,
  0x00,0xDD,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xDD,0x00,0xFF,
  0x00,0xDD,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xDD,0x00,0xFF,
  0x00,0xDD,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF, 0x00,0xEE,0x00,0xFF, 0x00,0xDD,0x00,0xFF,
};

float const FIELD_VERTICES[] = {
  -1,-1,0,0, 1,1,1,1, -1,1,0,1,
  -1,-1,0,0, 1,-1,1,0, 1,1,1,1
};

unsigned char const FIELD_TEXTURE[] = {
  0x33,0x33,0x33,0xFF, 0x22,0x22,0x22,0xFF, 0x11,0x11,0x11,0xFF, 0x66,0x66,0x66,0xFF, 0x55,0x55,0x55,0xFF, 0x11,0x11,0x11,0xFF, 0x22,0x22,0x22,0xFF, 0x33,0x33,0x33,0xFF, 
  0x33,0x33,0x33,0xFF, 0x22,0x22,0x22,0xFF, 0x11,0x11,0x11,0xFF, 0x55,0x55,0x55,0xFF, 0x66,0x66,0x66,0xFF, 0x11,0x11,0x11,0xFF, 0x22,0x22,0x22,0xFF, 0x33,0x33,0x33,0xFF, 
  0x33,0x33,0x33,0xFF, 0x22,0x22,0x22,0xFF, 0x11,0x11,0x11,0xFF, 0x66,0x66,0x66,0xFF, 0x55,0x55,0x55,0xFF, 0x11,0x11,0x11,0xFF, 0x22,0x22,0x22,0xFF, 0x33,0x33,0x33,0xFF, 
  0x33,0x33,0x33,0xFF, 0x22,0x22,0x22,0xFF, 0x11,0x11,0x11,0xFF, 0x55,0x55,0x55,0xFF, 0x66,0x66,0x66,0xFF, 0x11,0x11,0x11,0xFF, 0x22,0x22,0x22,0xFF, 0x33,0x33,0x33,0xFF, 
  0x33,0x33,0x33,0xFF, 0x22,0x22,0x22,0xFF, 0x11,0x11,0x11,0xFF, 0x66,0x66,0x66,0xFF, 0x55,0x55,0x55,0xFF, 0x11,0x11,0x11,0xFF, 0x22,0x22,0x22,0xFF, 0x33,0x33,0x33,0xFF, 
  0x33,0x33,0x33,0xFF, 0x22,0x22,0x22,0xFF, 0x11,0x11,0x11,0xFF, 0x55,0x55,0x55,0xFF, 0x66,0x66,0x66,0xFF, 0x11,0x11,0x11,0xFF, 0x22,0x22,0x22,0xFF, 0x33,0x33,0x33,0xFF, 
  0x33,0x33,0x33,0xFF, 0x22,0x22,0x22,0xFF, 0x11,0x11,0x11,0xFF, 0x66,0x66,0x66,0xFF, 0x55,0x55,0x55,0xFF, 0x11,0x11,0x11,0xFF, 0x22,0x22,0x22,0xFF, 0x33,0x33,0x33,0xFF, 
  0x33,0x33,0x33,0xFF, 0x22,0x22,0x22,0xFF, 0x11,0x11,0x11,0xFF, 0x55,0x55,0x55,0xFF, 0x66,0x66,0x66,0xFF, 0x11,0x11,0x11,0xFF, 0x22,0x22,0x22,0xFF, 0x33,0x33,0x33,0xFF, 
};

float const SPARK_VERTICES[] = {
  -0.01,-0.01,0,0, 0.01,0.01,1,1, -0.01,0.01,0,1,
  -0.01,-0.01,0,0, 0.01,-0.01,1,0, 0.01,0.01,1,1
};

unsigned char const SPARK_TEXTURE[] = {
  0x00,0x00,0x00,0x00, 0xFF,0xFF,0x00,0xFF, 0xFF,0xFF,0x00,0xFF, 0x00,0x00,0x00,0x00,
  0xFF,0xFF,0x00,0xFF, 0xFF,0xFF,0x88,0xFF, 0xFF,0xFF,0x88,0xFF, 0xFF,0xFF,0x00,0xFF,
  0xFF,0xFF,0x00,0xFF, 0xFF,0xFF,0x88,0xFF, 0xFF,0xFF,0x88,0xFF, 0xFF,0xFF,0x00,0xFF,
  0x00,0x00,0x00,0x00, 0xFF,0xFF,0x00,0xFF, 0xFF,0xFF,0x00,0xFF, 0x00,0x00,0x00,0x00,
};

unsigned int const AUDIO_BUFFER_SIZE = 8192;
float beep[AUDIO_BUFFER_SIZE] = { 0 };
float boop[AUDIO_BUFFER_SIZE] = { 0 };
float bloop[AUDIO_BUFFER_SIZE] = { 0 };

float const PADDLE_SPEED = 0.001;
float const BALL_SPEED = 0.0012;

typedef struct Vec2 {
  float x;
  float y;
} Vec2;

typedef struct Model {
  unsigned int vertexBufferId;
  unsigned int numVertices;
  unsigned int textureId;
  Vec2 extent;
} Model;

typedef struct Sprite {
  Vec2 position;
  Model* model;
} Sprite;

typedef struct Paddle {
  Sprite sprite;
  char up;
  char down;
} Paddle;

typedef struct Ball {
  Sprite sprite;
  Vec2 velocity;
} Ball;

typedef struct Particle {
  Vec2 position;
  Vec2 velocity;
  Vec2 acceleration;
  unsigned int life;
  unsigned int totalLife;
} Particle;

unsigned int const MAX_PARTICLES = 100;

typedef struct ParticleSystem {
  Particle particles[MAX_PARTICLES];
  Model* model;
  unsigned int alive;
} ParticleSystem;

void createParticle(ParticleSystem*, float x, float y, float vx, float vy, float ax, float ay, int life);
void updateParticleSystem(ParticleSystem*, unsigned int);
void renderParticleSystem(ParticleSystem const*);

unsigned int programId;
int positionAttributeLocation;
int texcoordAttributeLocation;
int offsetUniformLocation;
int samplerUniformLocation;
int opacityUniformLocation;
unsigned int positionBuffer;

Model ballModel = {0, 0, 0, {}};
Model ballTailModel = {0, 0, 0, {}};
Model paddleModel = {0, 0, 0, {}};
Model fieldModel = {0, 0, 0, {}};
Model sparkModel = {0, 0, 0, {}};

Ball ball = { { {0, 0}, &ballModel }, {1, 1} };
Paddle left = { { {-0.9, 0}, &paddleModel }, 0, 0};
Paddle right = { { {0.9, 0}, &paddleModel }, 0, 0};
Sprite field = { {0, 0}, &fieldModel };
ParticleSystem sparks = { { { {0,0}, {0,0}, {0,0}, 0, 0 } }, &sparkModel, 0 };
ParticleSystem ballTail = { { { {0,0}, {0,0}, {0,0}, 0, 0 } }, &ballTailModel, 0 };

unsigned int leftScore = 0;
unsigned int rightScore = 0;

unsigned int initTexture(unsigned char const* data, unsigned int width, unsigned int height) {
  unsigned int id = glCreateTexture();
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data, width * height * sizeof(float));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  return id;
}
void initModel(Model* m, float const vertices[], unsigned int numVertices, unsigned int textureId) {
  m->vertexBufferId = glCreateBuffer();
  m->numVertices = numVertices;
  m->textureId = textureId;
  glBindBuffer(GL_ARRAY_BUFFER, m->vertexBufferId);
  glBufferData(GL_ARRAY_BUFFER, vertices, numVertices, GL_STATIC_DRAW);

  for(unsigned int i = 0; i < numVertices; i += 4) {
    float fx = vertices[i];
    float fy = vertices[i+1];
    m->extent.x = fx > m->extent.x ? fx : -fx > m->extent.x ? -fx : m->extent.x;
    m->extent.y = fy > m->extent.y ? fy : -fy > m->extent.y ? -fy : m->extent.y;
  }
  m->extent.x *= 0.9;
  m->extent.y *= 0.9;
}

void onInit() {
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glDepthFunc(GL_LEQUAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  unsigned int vsId = compileShader(vertexShader, sizeof(vertexShader) - 1, GL_VERTEX_SHADER);
  unsigned int fsId = compileShader(fragmentShader, sizeof(fragmentShader) - 1, GL_FRAGMENT_SHADER);

  programId = linkShaderProgram(vsId, fsId);

  positionAttributeLocation = glGetAttribLocation(programId, "a_position", sizeof("a_position") - 1);
  texcoordAttributeLocation = glGetAttribLocation(programId, "a_texcoord", sizeof("a_texcoord") - 1);
  offsetUniformLocation = glGetUniformLocation(programId, "u_offset", sizeof("u_offset") - 1);
  samplerUniformLocation = glGetUniformLocation(programId, "u_sampler", sizeof("u_sampler") - 1);
  opacityUniformLocation = glGetUniformLocation(programId, "u_opacity", sizeof("u_opacity") - 1);

  unsigned int ballTextureId = initTexture(BALL_TEXTURE, 4, 4);
  unsigned int ballTailTextureId = initTexture(BALL_TAIL_TEXTURE, 4, 4);
  unsigned int paddleTextureId = initTexture(PADDLE_TEXTURE, 8, 8);
  unsigned int fieldTextureId = initTexture(FIELD_TEXTURE, 8, 8);
  unsigned int sparkTextureId = initTexture(SPARK_TEXTURE, 4, 4);
  initModel(&ballModel, BALL_VERTICES, sizeof(BALL_VERTICES)/sizeof(float), ballTextureId);
  initModel(&ballTailModel, BALL_TAIL_VERTICES, sizeof(BALL_TAIL_VERTICES)/sizeof(float), ballTailTextureId);
  initModel(&paddleModel, PADDLE_VERTICES, sizeof(PADDLE_VERTICES)/sizeof(float), paddleTextureId);
  initModel(&fieldModel, FIELD_VERTICES, sizeof(FIELD_VERTICES)/sizeof(float), fieldTextureId);
  initModel(&sparkModel, SPARK_VERTICES, sizeof(SPARK_VERTICES)/sizeof(float), sparkTextureId);

  for(unsigned int i = 0; i < AUDIO_BUFFER_SIZE; ++i) {
    beep[i] = (i/64)%2 ? 0.1 : -0.1;
    boop[i] = (i/128)%2 ? 0.1 : -0.1;
    bloop[i] = beep[i]/2 + boop[i]/2;
  }
}

void renderSprites(Sprite* const* ss, unsigned int n) {
  glBindBuffer(GL_ARRAY_BUFFER, ss[0]->model->vertexBufferId);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, ss[0]->model->textureId);
  glVertexAttribPointer(positionAttributeLocation, 2, GL_FLOAT, 0, 16, 0);
  glVertexAttribPointer(texcoordAttributeLocation, 2, GL_FLOAT, 0, 16, 8);
  glUniform1i(samplerUniformLocation, 0);
  glUniform1f(opacityUniformLocation, 1.0f);

  unsigned int numTriangles = ss[0]->model->numVertices / 4;
  for(unsigned int i = 0; i < n; ++i) {
    Sprite* s = ss[i];
    glUniform4fv(offsetUniformLocation, s->position.x, s->position.y, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, numTriangles);
  }
}

float clamp(float v, float min, float max) {
  return v < min ? min : v > max ? max : v;
}

char spriteCollide(Sprite* a, Sprite* b) {
  return (a->position.x < b->position.x ? b->position.x - a->position.x : a->position.x - b->position.x) < a->model->extent.x + b->model->extent.x &&
    (a->position.y < b->position.y ? b->position.y - a->position.y : a->position.y - b->position.y) < a->model->extent.y + b->model->extent.y;
}

void createSparks(ParticleSystem* ps, float x, float y, float dx, float dy) {
  for(unsigned int i = 0; i < 4; ++i) {
    float ddx = (i+1)*dx/10.0f;
    float ddy = (i+1)*dy/10.0f;
    createParticle(ps, x, y, dy+ddx, -dx+ddy, 0, 0, 100);
    createParticle(ps, x, y, -dy+ddx, dx+ddy, 0, 0, 100);
  }
}

void onAnimationFrame(int timestamp) {
  static int previous = 0;

  int delta = previous ? timestamp - previous : 0;

  left.sprite.position.y = clamp(left.sprite.position.y + (left.up - left.down) * PADDLE_SPEED * delta, -0.8, 0.8);
  right.sprite.position.y = clamp(right.sprite.position.y + (right.up - right.down) * PADDLE_SPEED * delta, -0.8, 0.8);

  ball.sprite.position.x += ball.velocity.x * BALL_SPEED * delta;
  if(spriteCollide(&ball.sprite, &left.sprite) || spriteCollide(&ball.sprite, &right.sprite)) {
    ball.velocity.x = -ball.velocity.x;
    ball.sprite.position.x += ball.velocity.x * BALL_SPEED * delta;
    createSparks(&sparks,
        (ball.velocity.x > 0 ? -1 : 1) * ball.sprite.model->extent.x + ball.sprite.position.x,
        ball.sprite.position.y, 2*ball.velocity.x, 0);
    playAudio(beep, AUDIO_BUFFER_SIZE);
  } else if(ball.sprite.position.x > 1.05) {
    ball.sprite.position.x = 0;
    ball.velocity.x = 1 - 2 * (timestamp % 2);
    ball.velocity.y = 1 - 2 * ((timestamp/7) % 2);
    leftScore += 1;
    setScore(0, leftScore);
    playAudio(bloop, AUDIO_BUFFER_SIZE);
  } else if(ball.sprite.position.x < -1.05) {
    ball.sprite.position.x = 0;
    ball.velocity.x = 1 - 2 * (timestamp % 2);
    ball.velocity.y = 1 - 2 * ((timestamp/7) % 2);
    rightScore += 1;
    setScore(1, rightScore);
    playAudio(bloop, AUDIO_BUFFER_SIZE);
  }

  ball.sprite.position.y += ball.velocity.y * BALL_SPEED * delta;
  if(spriteCollide(&ball.sprite, &left.sprite) || spriteCollide(&ball.sprite, &right.sprite)) {
    ball.velocity.y = -ball.velocity.y;
    ball.sprite.position.y += ball.velocity.y * BALL_SPEED * delta;
    createSparks(&sparks, ball.sprite.position.x,
        (ball.velocity.y > 0 ? -1 : 1) * ball.sprite.model->extent.y + ball.sprite.position.y,
        0, 2*ball.velocity.y);
    playAudio(beep, AUDIO_BUFFER_SIZE);
  } else if(ball.sprite.position.y > 0.95) {
    ball.velocity.y = -1;
    createSparks(&sparks, ball.sprite.position.x,
        ball.sprite.model->extent.y + ball.sprite.position.y,
        0, 2*ball.velocity.y);
    playAudio(boop, AUDIO_BUFFER_SIZE);
  } else if(ball.sprite.position.y < -0.95) {
    ball.velocity.y = 1;
    createSparks(&sparks, ball.sprite.position.x,
        -ball.sprite.model->extent.y + ball.sprite.position.y,
        0, 2*ball.velocity.y);
    playAudio(boop, AUDIO_BUFFER_SIZE);
  }

  createParticle(&ballTail, ball.sprite.position.x, ball.sprite.position.y,0,0, 0, 0, 1000);

  updateParticleSystem(&sparks, delta);
  updateParticleSystem(&ballTail, delta);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(programId);
  glEnableVertexAttribArray(positionAttributeLocation);
  glEnableVertexAttribArray(texcoordAttributeLocation);
  Sprite* const fields[] = {&field};
  renderSprites(fields, 1);
  Sprite* const paddles[] = {&left.sprite, &right.sprite};
  renderSprites(paddles, 2);
  renderParticleSystem(&ballTail);
  Sprite* const balls[] = {&ball.sprite};
  renderSprites(balls, 1);

  renderParticleSystem(&sparks);

  previous = timestamp;
}

unsigned int const KEY_UP = 38;
unsigned int const KEY_DOWN = 40;
unsigned int const KEY_A = 65;
unsigned int const KEY_Z = 90;

void onKey(unsigned int keyCode, char state) {
  switch(keyCode) {
    case KEY_UP:
      right.up = state;
      break;
    case KEY_DOWN:
      right.down = state;
      break;
    case KEY_A:
      left.up = state;
      break;
    case KEY_Z:
      left.down = state;
      break;
    default:
      break;
  }
}

void createParticle(ParticleSystem* ps, float x, float y, float vx, float vy, float ax, float ay, int life) {
  if(ps->alive < MAX_PARTICLES) {
    Particle* np = &ps->particles[ps->alive];
    np->position.x = x;
    np->position.y = y;
    np->velocity.x = vx;
    np->velocity.y = vy;
    np->acceleration.x = ax;
    np->acceleration.y = ay;
    np->life = life;
    np->totalLife = life;
    ps->alive += 1;
  }
}

void updateParticleSystem(ParticleSystem* ps, unsigned int delta) {
  for(unsigned int i = 0; i < ps->alive; ++i) {
    Particle* p = &ps->particles[i];
    if(delta > p->life) {
      ps->alive -= 1;
      if(i < ps->alive) {
        Particle* np = &ps->particles[ps->alive];
        p->position = np->position;
        p->velocity = np->velocity;
        p->acceleration = np->acceleration;
        p->life = np->life;
        p->totalLife = np->totalLife;
        i -= 1;
      }
    } else {
      p->life -= delta;
      p->velocity.x += p->acceleration.x * delta / 1000.0f;
      p->velocity.y += p->acceleration.y * delta / 1000.0f;
      p->position.x += p->velocity.x * delta / 1000.0f;
      p->position.y += p->velocity.y * delta / 1000.0f;
    }
  }
}

void renderParticleSystem(ParticleSystem const* ps) {
  glBindBuffer(GL_ARRAY_BUFFER, ps->model->vertexBufferId);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, ps->model->textureId);
  glVertexAttribPointer(positionAttributeLocation, 2, GL_FLOAT, 0, 16, 0);
  glVertexAttribPointer(texcoordAttributeLocation, 2, GL_FLOAT, 0, 16, 8);
  glUniform1i(samplerUniformLocation, 0);

  unsigned int numTriangles = ps->model->numVertices / 4;
  for(unsigned int i = 0; i < ps->alive; ++i) {
    Particle const* p = &ps->particles[i];
    glUniform1f(opacityUniformLocation, p->life/(float)p->totalLife);
    glUniform4fv(offsetUniformLocation, p->position.x, p->position.y, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, numTriangles);
  }
}
