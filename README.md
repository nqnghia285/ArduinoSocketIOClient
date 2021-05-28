# ArduinoSocketIOClient for Arduino [![Build Status](https://github.com/Links2004/arduinoWebSockets/workflows/CI/badge.svg?branch=master)](https://github.com/nqnghia285/ArduinoSocketIOClient)

A library support connect to server use [Socket.IO](https://socket.io/).

##### Support features:

-  Connect to server with root path = "/" or namespace.
-  Connect to server with SSL and CA.
-  Customize event handle function.
-  Add listener to handle event.
-  Send event with format JSON.

##### Supported Hardware

-  ESP8266 [Arduino for ESP8266](https://github.com/esp8266/Arduino/)
-  ESP32 [Arduino for ESP32](https://github.com/espressif/arduino-esp32)
-  ESP31B
-  Particle with STM32 ARM Cortex M3
-  ATmega328 with Ethernet Shield (ATmega branch)
-  ATmega328 with enc28j60 (ATmega branch)
-  ATmega2560 with Ethernet Shield (ATmega branch)
-  ATmega2560 with enc28j60 (ATmega branch)

### Dependencies:

ArduinoSocketIOClient library used WebSockets library (v2.3.6) and ArduinoJson library (v6.18.0).

### High Level Client API

-  `begin` : Initiate connection sequence to the [Socket.IO](https://socket.io) host.

```c++
    void begin(const char *host, uint16_t port = 80, const char *nsp = "/", const char *url = "/socket.io/?EIO=4", const char *protocol = "arduino");
```

```c++
    void begin(String host, uint16_t port = 80, String nsp = "/", String url = "/socket.io/?EIO=4", String protocol = "arduino");
```

-  `beginSSL` : Initiate connection sequence with SSL to the Socket.IO host.

```c++
    void beginSSL(const char *host, const char *nsp = "/", uint16_t port = 443, const char *url = "/socket.io/?EIO=4", const char *protocol = "arduino");
```

```c++
    void beginSSL(String host, String nsp = "/", uint16_t port = 443, String url = "/socket.io/?EIO=4", String protocol = "arduino");
```

-  `beginSSLWithAC` : Initiate connection sequence with SSL + CA to the Socket.IO host.

```c++
    void beginSSLWithCA(const char *host, const char *nsp = "/", uint16_t port = 443, const char *url = "/socket.io/?EIO=4", const char *CA_cert = NULL, const char *protocol = "arduino");
```

```c++
    void beginSSLWithCA(const char *host, const char *nsp = "/", uint16_t port = 443, const char *url = "/socket.io/?EIO=4", BearSSL::X509List *CA_cert = NULL, const char *protocol = "arduino");
```

-  `setSSLClientCertKey` :

```c++
    void setSSLClientCertKey(const char *clientCert = NULL, const char *clientPrivateKey = NULL);
```

```c++
    void setSSLClientCertKey(BearSSL::X509List *clientCert = NULL, BearSSL::PrivateKey *clientPrivateKey = NULL);
```

-  `isConnected` : Check whether the client is connected to the host or not.

```c++
    bool isConnected(void);
```

-  `onEvent`: Set callback function. This function is used for customizing your event handle function.

```c++
    void onEvent(SocketIOClientEvent cbEvent);
```

-  `send` : Send text data to the host.

```c++
    bool send(socketIOmessageType_t type, uint8_t *payload, size_t length = 0, bool headerToPayload = false);
```

```c++
    bool send(socketIOmessageType_t type, const uint8_t *payload, size_t length = 0);
```

```c++
    bool send(socketIOmessageType_t type, char *payload, size_t length = 0, bool headerToPayload = false);
```

```c++
    bool send(socketIOmessageType_t type, const char *payload, size_t length = 0);
```

```c++
    bool send(socketIOmessageType_t type, String &payload);
```

-  `sendEVENT` : Send event data to the host.

```c++
    bool sendEVENT(uint8_t *payload, size_t length = 0, bool headerToPayload = false);
```

```c++
    bool sendEVENT(const uint8_t *payload, size_t length = 0);
```

```c++
    bool sendEVENT(char *payload, size_t length = 0, bool headerToPayload = false);
```

```c++
    bool sendEVENT(const char *payload, size_t length = 0);
```

```c++
    bool sendEVENT(String &payload);
```

-  `handleEvent` : This function is used for handling event that is sent from server. If you don't customize event handle function (call onEvent), you don't must call this function.

```c++
    void handleEvent(uint8_t *payload);
```

-  `on` : Add a listener function into \_packets, this listener can handle event that is sent from server.

```c++
    void on(const char *event, std::function<void(const char *payload, size_t length)>);
```

```c++
    void on(String event, std::function<void(const char *payload, size_t length)>);
```

-  `remove` : Remove the event handle function in \_events of class ArduinoSocketIOClient.

```c++
    void remove(const char *event);
```

```c++
    void remove(String event);
```

-  `removeAll` : Remove all of event handle functions in \_events of class ArduinoSocketIOClient.

```c++
    void removeAll(void);
```

-  `emit` : Function send event + message to server. This function support format JSON message.

```c++
    void emit(const char *event, const char *payload = NULL);
```

```c++
    void emit(String event, String payload);
```

-  `loop` : Loop function is used for handling and sending events to server.

```c++
    void loop(void);
```

### Example

Visit to: https://github.com/nqnghia285/ArduinoSocketIOClient/blob/main/examples/ExampleForESP8266.cpp

### Issues

Submit issues to: https://github.com/nqnghia285/ArduinoSocketIOClient/issues
