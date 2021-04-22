#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoSocketIOClient.h>

// Note: SocketIOClient used ArduinoJson and Websockets library, so you must import them into your project.

// Event
// Server send
#define SSAC "server-send-ack-connected"
#define SSM "server-send-message"

// Client send
#define CC "client-connect"
#define CSM "client-send-message"

////////////////////////////////
// SSID and password WiFi
const char *ssid = "ssid-of-wifi";
const char *pwd = "password-of-wifi";

// Config server side
const char host[] = "xxx.xxx.xxx.xxx";
uint16_t port = 5000; // If you connect to a VPS hosting run HTTP, you must set port = 80.
const char ssl_host[] = "example.com";
const char path[] = "/client"; // If you connect with namespace, set path = "/your-nsp". Default path = "/".

ArduinoSocketIOClient socket;

void serverSendAckConnected(const char *payload, size_t length)
{
    Serial.print("Server says: ");
    Serial.println(payload);
}

void serverSendMessage(const char *payload, size_t length)
{
    Serial.print("Server says: ");
    Serial.println(payload);
}

// Use for customizing event handle function. If you don't want to customize, you can ignore it.
// void socketEvent(socketIOmessageType_t type, uint8_t *payload, size_t length)
// {
//     switch (type)
//     {
//     case sIOtype_DISCONNECT:
//         SOCKETIOCLIENT_DEBUG("[SIoC] Disconnected!\n");
//         break;
//     case sIOtype_CONNECT:
//         SOCKETIOCLIENT_DEBUG("[SIoC] Connected to url: %s\n", payload);

//         // join default namespace (no auto join in Socket.IO V4)
//         // Connect to server with default path: "/" or with namespace
//         socket.send(sIOtype_CONNECT, path);

//         break;
//     case sIOtype_EVENT:
//         SOCKETIOCLIENT_DEBUG("[SIoC] get event: %s\n", payload);

//         // Handle message sent from server
//         socket.handleEvent(payload);
//         break;
//     case sIOtype_ACK:
//         SOCKETIOCLIENT_DEBUG("[SIoC] get ack: %u\n", length);
//         hexdump(payload, length);
//         break;
//     case sIOtype_ERROR:
//         SOCKETIOCLIENT_DEBUG("[SIoCc] get error: %u\n", length);
//         hexdump(payload, length);
//         break;
//     case sIOtype_BINARY_EVENT:
//         SOCKETIOCLIENT_DEBUG("[SIoC] get binary: %u\n", length);
//         hexdump(payload, length);
//         break;
//     case sIOtype_BINARY_ACK:
//         SOCKETIOCLIENT_DEBUG("[SIoC] get binary ack: %u\n", length);
//         hexdump(payload, length);
//         break;
//     }
// }

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    // Connect to wifi
    Serial.print("Connecting to ");
    Serial.print(ssid);
    WiFi.begin(ssid, pwd);

    //  Wait esp8266 connected to wifi
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print('.');
    }

    Serial.println();
    Serial.print("Connected WiFi: ");
    Serial.println(ssid);
    Serial.println("IP address(ESP):");
    Serial.println(WiFi.localIP());

    // Connect to server with namespace
    socket.begin(host, port, path);
    // or socket.begin(host, port); if you want to connect to root path. Default nsp(path) = "/".
    // If you want to connect to server witn ssl, you can follow code below:
    // socket.beginSSL(ssl_host, path); // Default port = 443.

    // If you want to override event handle function, you can use below code:
    // socket.onEvent(socketEvent); // this function must be called after begin function was called.

    //  Setup 'on' event listeners
    socket.on(SSAC, serverSendAckConnected);
    socket.on(SSM, serverSendMessage);

    // Remove event handle functions
    // socket.remove(SSM);
}

// Send message
void sendMessage(String message)
{
    socket.emit(CSM, message);
}

unsigned long previousTime = 0;
unsigned long duration = 2000;

void loop()
{
    // Loop function
    socket.loop();

    unsigned long now = millis();

    // Send meesage to server every $duration$ millisecond.
    if (now - duration > previousTime)
    {
        previousTime = now;
        String ms = "{message:\"Hello Server: " + String(now, DEC) + "\"}";
        Serial.println("Debug: " + ms);
        sendMessage(ms);
    }
}