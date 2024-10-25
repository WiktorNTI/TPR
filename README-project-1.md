# Creating a README.md file for the Clock and Temperature Project with the provided Markdown content

# Define the content of the README
readme_content = """
# Clock and Temperature Project

**Author**: Wiktor Nordström  
**Date**: October 25, 2024  

## Project Overview

This project creates a digital clock and temperature display using a DS3231 RTC module, a 1306 OLED display, an analog temperature sensor, and a WS2812B LED ring. It reads time from the RTC, displays it on the OLED screen, and uses temperature readings to adjust LED colors on the LED ring. The setup is ideal for visualizing room temperature dynamically on a display.

## Hardware Components

- **DS3231 RTC Module** - Measures and keeps track of time.
- **1306 OLED Display** - Shows the current time in `hh:mm:ss` format.
- **Analog Temperature Sensor** - Monitors ambient temperature.
- **WS2812B LED Ring** - Visualizes temperature on a 30-LED ring with a color spectrum.

## Code Explanation

### Libraries Used

- **RTClib**: Manages time and date with the DS3231 RTC module.
- **Wire**: Handles I2C communication.
- **U8glib**: Controls the OLED display.
- **WS2812FX**: Manages LED effects on the WS2812B LED ring.

### Constants and Variables

- `tmpPin` (Analog Input): Pin connected to the temperature sensor.
- `LED_COUNT`: Number of LEDs in the WS2812B ring.
- `LED_PIN`: Output pin for WS2812B LED control.
- **Temperature Sensor Constants**:  
  `c1`, `c2`, `c3` - Steinhart-Hart coefficients for the thermistor, allowing accurate temperature measurement.

### Core Functions

1. **`setup()`**: Initializes the hardware, sets up communication protocols, adjusts RTC time, and configures OLED and LED ring settings.
2. **`loop()`**:  
   - Displays time on the OLED screen.
   - Adjusts LED colors based on current temperature.
   - Maintains service for LED animations.

### Helper Functions
"""

# Save to a README.md file
with open("/mnt/data/README.md", "w") as file:
    file.write(readme_content)

"/mnt/data/README.md"
