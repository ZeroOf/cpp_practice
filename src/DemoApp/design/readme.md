# Function

1. working as server
2. compose a resp with request, server A resp and serverB resp
3. Server A use short connection and Server B use long connection

# class

```plantuml
@startuml
class Demo
class TaskManager {
    void ProcessMsg(shared_ptr<Task>);
}
class TaskPool
class Task
Task --* TaskPool
class Server
class Client
class ClientFactory
ClientFactory *-- Client
Demo o-- ClientFactory
Demo o-- Server
TaskManager o-- TaskPool
Demo o-- TaskManager
Server <-- ClientFactory
@enduml
```