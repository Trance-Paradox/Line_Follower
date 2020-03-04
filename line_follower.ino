#include <Arduino.h>

int ir_snsr[8];

class motor                                             //motor_class containg all its functions
{
    int F_pin, R_pin, S_pin;

  public:
    motor(int F, int R, int S)
    {
      F_pin = F;
      R_pin = R;
      S_pin = S;
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
    void setSpeed(int spd)
    {
      analogWrite(S_pin, spd);
    }
};


motor L_motor(14, 15, 5);                                 //variables of motor_class with output pins
motor R_motor(16, 17, 6);                                 //variables of motor_class with output pins



void setup()
{
  Serial.begin(9600);

  for (int i = 7; i <= 17; i++)
    if (i < 7 || i >= 13)
      pinMode(i, OUTPUT);                               //motor control pins

  for (int i = 3; i < 13; i++)                          //ir sensor pins
    if (i < 5 || i >= 7)
      pinMode(i, INPUT);

}



void loop()
{
  ir_snsr[0] = digitalRead(4);
  for (int i = 7; i < 14; i++)
    ir_snsr[i - 6] = digitalRead(i);



  motor_speed();
  L_motor.FORWARD();
  R_motor.FORWARD();

}
