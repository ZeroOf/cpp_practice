# Function

1. working as server
2. compose a resp with request, server A resp and serverB resp
3. Server A use short connection and Server B use long connection

# class

```plantuml
@startuml demoServer
class Demo
class TaskManager {
    +void ProcessMsg(shared_ptr<Task>);
}
interface ServerAdapter {
+{abstract}bool SendMessage(std::vector<char> buffer)
}
interface TcpIO.ClientFactory {
+std::shared_ptr<TcpIO::Client> GetClient(boost::asio::ip::tcp::socket &&socket)
}
class TaskPool
class Task
Task --* TaskPool
class Server
class Client
class ClientManager
Demo o-- ClientManager
Demo o-- Server
ClientManager *-- Client
TaskManager o-- TaskPool
Server <-- ClientManager
Demo o-- TaskManager
ClientManager --|> TcpIO.ClientFactory
@enduml
```