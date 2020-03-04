void motor_speed()                                              //set speed for 2 motors
{
  int error=0;
  for(int i=0; i<4; i++)
    if(ir_snsr[i]==HIGH)
      error = error + 2^(4-i);
  for(int i=4; i<8; i++)
    if(ir_snsr[i]==HIGH)
      error = error - 2^(i-4);
  if(error>0)
    {
      L_motor.setSpeed(255 - error*8);
      R_motor.setSpeed(255);
    }
  if(error<0)
    {
      R_motor.setSpeed(255 + error*8);
      L_motor.setSpeed(255);
    }
}
