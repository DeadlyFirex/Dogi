#include <commands.h>
#include <utilities.h>
#include <display.h>
#include <monitor.h>
#include <bluetooth.h>
#include <config.h>

void setup() {
  time::sync();
  cfg::setup_wdt();
  Serial.begin(9600);

  #if DEBUG_SERIAL == 1
  while (!Serial);
  delay(100);
  #endif

  Serial.println("Core 0; ready");
}

void loop() {
  cfg::reset_wdt();

  if (utl::sanitize(Serial, cmd::current_message, MAX_MESSAGE)) {
      if (!cmd::process(cmd::current_message)) {
          utl::soft_error(Serial, "Invalid command.");
      }
  }
  delay(75);
}

void setup1() {
  #if DEBUG_SERIAL == 1
  while (!Serial);
  delay(100);
  #endif

  Serial.println("Core 1; ready");

  if (!dsp::setup(), !mon::setup(), !ble::setup()) {
    utl::error(Serial, "Component failed to start.");
  }
}

void loop1(){
  char time_message[5];
  sprintf(time_message, "%d:%d", hour(), minute());

  mon::check();
  ble::advertise();
  ble::update(mon::detected, mon::last_detected);
  dsp::draw_display({
    mon::detected, mon::since_message,
    ble::initialized, (bool) Serial, time_message
    });
  cfg::reset_wdt();
  delay(5);
}
