
#include <Arduino.h>

#include <GoBLE.hpp>
#include <SerialBLE.hpp>

#define Console Serial
SerialBLE Bluetooth;
_GoBLE<SerialBLE, HardwareSerial> Goble(Bluetooth, Console);

int joystickX, joystickY;
int joystickX2, joystickY2;
static int buttonState[MAXBUTTONID + 1];

void setup() {
  Console.begin(115200);
  Bluetooth.begin();
  Goble.begin();
}

void loop() {
  if (!Goble.available()) {
    static auto timeout = millis();
    if (millis() >= timeout) {
      Console.println("no data");
      timeout = millis() + 1000;
    }
    return;
  }
  
  joystickX = Goble.readJoystickX();
  joystickY = Goble.readJoystickY();
  joystickX2 = Goble.readJoystickX2();
  joystickY2 = Goble.readJoystickY2();
  buttonState[0] = 0;  //
  buttonState[SWITCH_UP] = Goble.readSwitchUp();
  buttonState[SWITCH_DOWN] = Goble.readSwitchDown();
  buttonState[SWITCH_LEFT] = Goble.readSwitchLeft();
  buttonState[SWITCH_RIGHT] = Goble.readSwitchRight();
  buttonState[SWITCH_SELECT] = Goble.readSwitchSelect();
  buttonState[SWITCH_START] = Goble.readSwitchStart();
  buttonState[SWITCH_ACTION] = Goble.readSwitchAction();
  buttonState[SWITCH_MID] = Goble.readSwitchMid();
  buttonState[SWITCH_TILT_UP] = Goble.readSwitchTiltUp();
  buttonState[SWITCH_TILT_DN] = Goble.readSwitchTiltDn();
  buttonState[SWITCH_PAN_LF] = Goble.readSwitchPanLf();
  buttonState[SWITCH_PAN_RT] = Goble.readSwitchPanRt();

  Console.print("\nJoystick Value: X ");
  Console.print(joystickX);
  Console.print(", Y ");
  Console.println(joystickY);
  Console.print("Joystick Value: X2 ");
  Console.print(joystickX2);
  Console.print(", Y2 ");
  Console.println(joystickY2);

  for (int i = 1; i < MAXBUTTONID + 1; i++) {
    Console.print("Button ID: ");
    Console.print(i);
    Console.print("\t State: ");
    if (buttonState[i] == PRESSED) {
      Console.println("Pressed!");
    } else {
      Console.println("Released!");
    }
  }
  Console.println();
}