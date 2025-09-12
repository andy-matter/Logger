#include "HardwareSerial.h"
#include "Logger.h"

/////  The log-level is staticly defined in Logger.h  /////

const float value = 432.764544;

void SerialLogHandler(int level, const std::string_view module, const std::string_view msg) {   // Define new log-handler according to the handler function signature
  const char* out = std::format("{}:  [{}] {}", LOG_LEVEL_STRINGS[level], module, msg).c_str();
  Serial.println(out);
}


int main(void) {
  Serial.begin(115200);   // Start the serial port
  Log::addLogger(SerialLogHandler);   // Add the log-handler to the logger

  while(1) {
    Log::Alarm("Main", "This is a alarm");    // Passing the module and message to the logger
    Log::Trace("Main", std::format("Value is {:.2f}", value));    // Use format to include variables
  }
}