# Video Game Network Protocol README

## Overview

This document provides an overview of our Video Game Network Protocol, including its purpose, architecture, and communication protocols. The Video Game Network Protocol is a network protocol designed for use in our engine that allows for real-time communication between players and server.

## Purpose

The purpose of the Video Game Network Protocol is to provide a reliable, low-latency network infrastructure that can support real-time multiplayer gaming. The Video Game Network Protocol is designed to be scalable and flexible, allowing it to support a variety of different games and use cases.

## Architecture

The Video Game Network Protocol is a client-server architecture that consists of multiple clients, each of which communicates with a central server. The server is responsible for managing game sessions, and data synchronization between clients.

The communication between clients and the server is achieved using a message-based protocol. Messages can be sent between clients and the server at any time and can contain a variety of different data types, including structs.

## Communication Protocols

The Video Game Network Protocol uses a variety of communication protocols to support real-time multiplayer gaming. These include:

- User Datagram Protocol (UDP): A protocol that is designed for real-time applications, such as online gaming. UDP is used for low-latency, real-time communication between clients and the server.

- Structs: A data type that is used to define custom data structures. Structs can be used to send complex data types, such as game state updates or player positions, between clients and the server.

## Example Struct Message

Here's an example of differents struct message that could be sent between clients and the server and in what circumstances it is used:

```c++
struct Header
{
    int _id;
};
```
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
