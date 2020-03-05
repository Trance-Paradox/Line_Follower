void diffSpeed()
{
  int error = 0;
  //  error += (~ir_snsr) & 0b1111;
  //  error -= (ir_snsr >> 4) & 0b1111;

  for (int i = 0; i < 4; i++)
    if (ir_snsr & (1 << i) == HIGH)
      error = error + 1 << (3 - i);
  for (int i = 4; i < 8; i++)
    if (ir_snsr & (1 << i) == HIGH)
      error = error - 1 << (i - 4);

  if (error > 0)
  {
    L_motor.setSpeed(255 - error * 8);
    R_motor.setSpeed(255);
  }
  if (error < 0)
  {
    R_motor.setSpeed(255 + error * 8);
    L_motor.setSpeed(255);
  }
}
