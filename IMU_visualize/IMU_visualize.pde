import processing.serial.*;
Serial port;

final int BAUD = 115200;
int PORT_INDEX = 0; // <-- you will set this after step 3 below

float rollDeg=0, pitchDeg=0, yawDeg=0;
float rollSm=0, pitchSm=0, yawSm=0;
float alpha = 0.20; // smoothing 0..1 (higher = snappier)

PFont font;

void setup() {
  size(900, 700, P3D);
  println("Available serial ports:");
  println(Serial.list()); // <-- check console, set PORT_INDEX to the Teensy entry
  // pick the correct entry number from the printed list:
  port = new Serial(this, Serial.list()[PORT_INDEX], BAUD);
  port.clear();
  port.bufferUntil('\n');

  font = createFont("Consolas", 14, true);
  textFont(font);
  smooth(8);
}

void draw() {
  background(10);
  lights();

  // HUD
  hint(DISABLE_DEPTH_TEST);
  fill(255);
  text("RPY (deg)  R: " + nf(rollDeg,1,2) +
                 "  P: " + nf(pitchDeg,1,2) +
                 "  Y: " + nf(yawDeg,1,2) +
                 "   FPS: " + int(frameRate), 12, 20);
  hint(ENABLE_DEPTH_TEST);

  // Camera pose
  pushMatrix();
  translate(width/2, height/2 + 60, 0);
  rotateX(radians(-18));
  rotateY(radians(25));

  rotateX(radians(90));

  // Ground grid + world axes
  //drawGrid(16, 25);
  drawAxes(120, 3, 80, true);  // faint world axes

  // Apply orientation: Yaw(Z) -> Pitch(Y) -> Roll(X)
  float r = radians(rollSm);
  float p = radians(pitchSm);
  float y = radians(yawSm);
  pushMatrix();
  rotateZ(y);
  rotateY(p);
  rotateX(r);

  // Body axes (thick, colored)
  drawAxes(150, 8, 255, false);

  // IMU box
  fill(0, 160, 255);
  box(60,  80, 17);
  popMatrix();
  popMatrix();
}

void serialEvent(Serial p) {
  String line = p.readStringUntil('\n');
  if (line == null) return;
  line = trim(line);
  String[] tok = split(line, ',');
  if (tok.length != 3) return;
  try {
    float rIn  = float(tok[0]);
    float pIn  = float(tok[1]);
    float yIn  = float(tok[2]);

    rollDeg  = rIn;
    pitchDeg = pIn;
    yawDeg   = yIn;

    // smooth for nicer visuals
    rollSm  = lerp(rollSm,  rIn, alpha);
    pitchSm = lerp(pitchSm, pIn, alpha);
    yawSm   = lerp(yawSm,   yIn, alpha);
  } catch (Exception e) { }
}

void drawAxes(float L, float thickness, float alpha255, boolean faint) {
  float a = faint ? 90 : alpha255;

  // X (red)
  pushMatrix();
  stroke(255,0,0, a); strokeWeight(thickness);
  line(0,0,0,  L,0,0);
  noStroke(); translate(L,0,0);
  fill(255,0,0, a); cone(8, 20, 16);
  popMatrix();

  // Y (green)
  pushMatrix();
  stroke(0,255,0, a); strokeWeight(thickness);
  line(0,0,0,  0,-L,0);
  noStroke(); translate(0,-L,0);
  fill(0,255,0, a); cone(8, 20, 16);
  popMatrix();

  // Z (blue)
  pushMatrix();
  stroke(0,0,255, a); strokeWeight(thickness);
  line(0,0,0,  0,0,L);
  noStroke(); translate(0,0,L);
  fill(0,0,255, a); cone(8, 20, 16);
  popMatrix();
}

// cone helper oriented along +X
void cone(float radius, float height, int detail) {
  pushMatrix();
  rotateZ(HALF_PI);
  beginShape(TRIANGLE_FAN);
  vertex(0, 0, 0);
  for (int i = 0; i <= detail; i++) {
    float ang = TWO_PI * i / detail;
    vertex(height, radius*cos(ang), radius*sin(ang));
  }
  endShape();
  popMatrix();
}

void drawGrid(int halfCells, float cell) {
  stroke(120, 120, 120, 80);
  strokeWeight(1);
  for (int i=-halfCells; i<=halfCells; i++) {
    line(i*cell, 0, -halfCells*cell,  i*cell, 0, halfCells*cell);
    line(-halfCells*cell, 0, i*cell,  halfCells*cell, 0, i*cell);
  }
  noStroke();
}
