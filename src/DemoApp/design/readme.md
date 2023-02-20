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
interface ServerAdapter
class TaskPool
class Task
Task --* TaskPool
class Server
class Client
class ClientManager
ClientManager *-- Client
Demo o-- ClientManager
Demo o-- Server
TaskManager o-- TaskPool
Demo o-- TaskManager
Server <-- ClientManager

@enduml
```