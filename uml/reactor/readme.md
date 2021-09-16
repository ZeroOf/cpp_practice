# reactor

```puml
@startuml
interface ReactorInterface {
    +void RegisterHander(Hander hander);
    +void RemoveRegisterHander(Hander hander);
    void HanderEvent();
}

interface Hander {
    + void HandleInput();
    + void HandleOutput();
    + void HandleExcept();
}

ReactorInterface --> Hander

class Task {
    +void Run();
}

class ThreadPool {
    void Push(Task task);
}

ThreadPool --> Task

Hander --> ThreadPool
Hander --> Task

@enduml
```