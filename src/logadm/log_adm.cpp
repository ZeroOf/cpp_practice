//
// Created by Will Lee on 2023/4/11.
//

#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <thread>

using namespace std;
using namespace boost::interprocess;

//定义共享内存的结构体
struct SharedMemoryData {
  bool modified;
  int logLevel;
};

int main(int argc, char *argv[]) {
  try {
    //检查命令行参数
    if (argc < 2) {
      cout << "Usage: " << argv[0] << " <log_level>" << endl;
      return 1;
    }

    //解析命令行参数
    int logLevel = atoi(argv[1]);

    //打开共享内存对象
    shared_memory_object shm(open_only, "Log_Shared_Memory", read_write);

    //将共享内存映射到当前进程的地址空间
    mapped_region region(shm, read_write);

    //获取共享内存的地址
    void *address = region.get_address();

    //将地址转换为共享内存的结构体类型
    SharedMemoryData *sharedMemory = static_cast<SharedMemoryData *>(address);

    //修改共享内存数据
    sharedMemory->logLevel = logLevel;
    sharedMemory->modified = true;

    //等待一段时间
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Log level has been modified to " << logLevel << endl;
  }
  catch (const exception &ex) {
    cerr << ex.what() << endl;
    return 1;
  }

  return 0;
}
