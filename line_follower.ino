#include <Arduino.h>

uint8_t ir_snsr;

class motor                                             //motor_class containg all its functions
{
    int F_pin, R_pin, S_pin;

  public:
    motor(int F, int R, int S)
      : F_pin(F), R_pin(R), S_pin(S)
    {
      pinMode(F_pin, OUTPUT);
      pinMode(R_pin, OUTPUT);
      pinMode(S_pin, OUTPUT);
    }
    void FORWARD()
    {
      digitalWrite(F_pin, HIGH);
      digitalWrite(R_pin, LOW);
    }
    void BACKWARD()
    {
      digitalWrite(F_pin, LOW);
      digitalWrite(R_pin, HIGH);
    }
    void STOP()
    {
      digitalWrite(F_pin, LOW);
      digitalWrite(R_pin, LOW);
    }
    void HOLD()
    {
      digitalWrite(F_pin, HIGH);
      digitalWrite(R_pin, HIGH);
    }
    void setSpeed(int spd = 255)
    {
      analogWrite(S_pin, spd);
    }
};


motor L_motor(14, 15, 5);                                 //variables of motor_class with output pins
motor R_motor(16, 17, 6);                                 //variables of motor_class with output pins


uint8_t ir_array[] = {2, 3, 4, 5, 6, 7, 8, 9};


void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < sizeof(ir_array); i++)
    pinMode(ir_array[i], OUTPUT);

}



void loop()
{
  for (int i = 0; i < sizeof(ir_array); i++)
    ir_snsr |= digitalRead(ir_array[i]) << i;

  Serial.println(ir_snsr, BIN);

  L_motor.FORWARD();
  R_motor.FORWARD();

}
