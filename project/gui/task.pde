import processing.serial.*;
import g4p_controls.*;


Serial connexion;

public void setup() {
  printArray(Serial.list());
  String portName = Serial.list()[0];
  int baud_rate = 115200;
  connexion = new Serial(this, portName, baud_rate);
  size(720, 360);
  createGUI();
}

public void draw() {
 
}
