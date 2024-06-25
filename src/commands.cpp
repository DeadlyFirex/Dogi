#include "commands.h"

char cmd::current_message[MAX_MESSAGE] = "null";
std::list<uint16_t> cmd::command_list[MAX_SIZE];

bool cmd::process(const char * message) {
    static std::map<std::string, std::function<void()>> commandMap = {
        {"date", date},
        {"raw_time", raw_time},
        {"help", help},
        {"time", time},
        {"internal", internal},
        {"last", last},
        {"pause", pause},
        {"resume", resume},
        {"readout", readout}
    };

    auto command = commandMap.find(message);

    if (command != commandMap.end()) {
        command->second();
        return true;
    }
    return false;
}

void cmd::help() {
     Serial.println(R"(
Available commands:
help     - Display this message.

Operation
pause    - Pause operation.
resume   - Resume operation.

Time
time     - Display the current time.
date     - Display the current date.
raw_time - Display the raw time.
internal - Display the internal time.

Debugging
last     - Display last message received.
readout  - Display the command queue.
)");
}

void cmd::time() {
    Serial.printf("Time >: %d:%d:%d\n", hour(), minute(), second());
}

void cmd::date() {
    Serial.printf("Date >: %d/%d/%d\n", day(), month(), year());
}

void cmd::raw_time() {
    Serial.printf("Raw-Time >: %lld\n", time::get());
}

void cmd::internal() {
    Serial.printf("Internal-Time >: %llu\n", millis());
}

void cmd::last() {
    Serial.printf("Last-Message >: <%s>\n", cmd::current_message);
}

void cmd::pause() {
    Serial.println("Pausing operation.");
    rp2040.idleOtherCore();
}

void cmd::resume() {
    Serial.println("Resuming operation.");
    rp2040.resumeOtherCore();
}

void cmd::readout() {
    Serial.printf("Queue size >: %d\n", cmd::command_list->size());

    for (size_t i = 0; i < cmd::command_list->size(); i++)
    {
        Serial.printf("- Entry #%d = %d\n", i, cmd::command_list[i]);
    }
}