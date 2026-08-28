#include <Arduino.h>

const char *DEVICE_ID = "UNO-001";

void setup()
{

    Serial.begin(9600);

    delay(1000);

    Serial.println("================================");
    Serial.println("RFID Attendance Terminal");
    Serial.println("Device: UNO-001");
    Serial.println("Status: READY");
    Serial.println("================================");
}

void loop()
{

    String cardUid = "A3:91:72:4F";

    String json = "{";

    json += "\"deviceId\":\"";
    json += DEVICE_ID;
    json += "\",";

    json += "\"cardUid\":\"";
    json += cardUid;
    json += "\",";

    json += "\"action\":\"LOGIN\"";

    json += "}";

    Serial.println(json);

    Serial.println("Waiting for backend response...");

    unsigned long startTime = millis();

    bool responseReceived = false;

    while (millis() - startTime < 5000)
    {

        if (Serial.available())
        {

            String response = Serial.readStringUntil('\n');

            response.trim();

            if (response.length() > 0)
            {

                Serial.println("Backend response:");
                Serial.println(response);

                responseReceived = true;

                break;
            }
        }
    }

    if (!responseReceived)
    {

        Serial.println("ERROR: Backend timeout");
    }

    delay(5000);
}