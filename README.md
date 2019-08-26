# Pylontech Battery Monitoring via WiFi

This project allows you to control and monitor Pylontech US2000B batteries via console port over WiFi.
It it's a great starting point to integrate battery with your home automation.

Features:
- Low cost (around 20$ in total).
- Adds WiFi capability to your Pylontech US2000B battery.
- Device exposes web interface that allows to:
    * send console commands and read response over WiFi (no PC needed)
    * battery information can be retrevied also in JSON format for easy parsing
- Easy to modify code using Arduino IDE and flash new firmware over WiFi (no need to disconnect from the battery).

Parts needed:
- [Wemos D1 mini microcontroller](https://www.amazon.co.uk/Makerfire-NodeMcu-Development-ESP8266-Compatible/dp/B071S8MWTY/).
- [SparkFun MAX3232 Transceiver](https://www.sparkfun.com/products/11189).
- Cable with RJ10 connector (some RJ10 cables have only two wires, make sure to buy one that has all four wires present).
- Capacitors C1: 10uF, C2: 0.1uF (this is not strictly required, but recommended as Wemos D1 can have large current spikes).

![Schematics](Schemetics.png)
