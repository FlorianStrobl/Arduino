void ModeButton() {
  if (++mode >= 3)
    mode = 0;
  State();
}

void SpeedButton() {
  if (mode != 2) {
    // Speed: theColor = 0;
    speedS += 300;
    if (speedS >= 1800)
      speedS = defaultSpeed;
  } else {
    // Color: theSpeed = defaultSpeed;
    if (++color >= 21)
      color = 0;
  }

  State();
}

void BrightnessButton() {
  brightness += 50;
  if (brightness >= 300)
    brightness = 0;

  strip.setBrightness(brightness);
  State();
}

