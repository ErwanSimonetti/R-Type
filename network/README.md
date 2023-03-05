Network Protocol RFC

1. Introduction
   This document defines the Network Protocol for communication between a client and server. The protocol is designed to be efficient, reliable, and secure.

2. Protocol Overview
   The Network Protocol consists of a series of messages that are exchanged between the client and server. Each message is composed of a header and payload. The header contains metadata about the message, such as the message type and payload length. The payload contains the actual data being transmitted.

3. Message Format
   The message format for the Network Protocol is as follows:
   
   - Header: 4 bytes
     - Message Type: 1 byte
     - Payload Length: 3 bytes

    ```c++
    struct Header
    {
        int _id;
    };
    ```
     
   - Payload: Variable length, up to 65,535 bytes

    According to the message type's value. Payload can be as follow.

    This first structure is always sent in messages and its purpose is to inform the receiver about the nature of the message.
    There are different codes for the message types.

    ```c++
    struct DeleteEntities
    {
        int _id;
    };
    ```
    This structure is used to send information that an entity has been destroyed. It notifies the receiver to delete an entity.

    ```c++
    struct ClientData {
        int16_t entity;
        uint16_t inputs[10];

    };
    ```
    This struct gets the actions done by a client and notifies the server which entity performs them.

    ```c++
    struct ServerData {
        int16_t entities[4];
        uint16_t posX[4];
        uint16_t posY[4];
        uint16_t inputs[4][10];
    };
    ```
    This last structure sends to all clients the positions and inputs of the different players.

5. Conclusion
   The Network Protocol provides a secure and efficient means of communication between a client and server. Its message format and security measures ensure reliable and secure transmission of data.

