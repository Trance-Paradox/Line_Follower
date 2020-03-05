int err()
{
  if (digitalRead(12) == 0 && digitalRead(13) == 0)
    return 1;
  ir_arr = 0;
  for (int i = 0; i < sizeof(ir_array); i++)
    ir_arr |= digitalRead(ir_array[i]) << i;
  int error = 0;
  for (int i = 0; i < 4; i++)
    if (ir_arr & (1 << i))
      error += 1 << (4 - i);
  error -= (ir_arr & 0b11110000) >> 3;
  //  for (int i = 4; i < 8; i++)
  //    if (ir_arr & (1 << i))
  //      error -= 1 << (i - 3);
  return error;
}

void diffSpeed()
{
  int error = 0;
  int mul = 16;
  //  error += (~ir_arr) & 0b1111;
  //  error -= (ir_arr >> 4) & 0b1111;

  for (int i = 0; i < 4; i++)
    if (ir_arr & (1 << i))
      error += 1 << (4 - i);
  error -= (ir_arr & 0b11110000) >> 3;
  //  for (int i = 4; i < 8; i++)
  //    if (ir_arr & (1 << i))
  //      error -= 1 << (i - 3);

  error = error * 16;
  
  //  Serial.println(error);
  
  if (error > 0 && error < 256)
  {
    L_motor.FORWARD();
    R_motor.FORWARD();
    L_motor.setSpeed(255 - error);
    R_motor.setSpeed(255);
    return;
  }
  else if (error > 256)
  {
    L_motor.BACKWARD();
    R_motor.FORWARD();
    L_motor.setSpeed(255);
    R_motor.setSpeed(255);
    return;
  }
  else if (error < 0 && error > -256)
  {
    L_motor.FORWARD();
    R_motor.FORWARD();
    R_motor.setSpeed(255 + error);
    L_motor.setSpeed(255);
    return;
  }
  else if (error < -256)
  {
    L_motor.FORWARD();
    R_motor.BACKWARD();
    R_motor.setSpeed(255);
    L_motor.setSpeed(255);
    return;
  }
  else if (ir_arr)
  {
    if (digitalRead(12) == digitalRead(13))
    {
      L_motor.FORWARD();
      R_motor.FORWARD();
      R_motor.setSpeed(255);
      L_motor.setSpeed(255);
      return;
    }
    else if (digitalRead(13) > digitalRead(12))
    {
      L_motor.BACKWARD();
      R_motor.FORWARD();
      R_motor.setSpeed(200);
      L_motor.setSpeed(200);
      while (!err());
      return;
    }
    else if (digitalRead(12) > digitalRead(13))
    {
      R_motor.BACKWARD();
      L_motor.FORWARD();
      R_motor.setSpeed(200);
      L_motor.setSpeed(200);
      while (!err());
      return;
    }
  }
}
