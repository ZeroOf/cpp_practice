//
// Created by Will Lee on 2023/3/29.
//

#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

void save_page(const std::string &url) {
  // 模拟一个长时间的页面获取
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::string result = "fake content";

  // 使用 scoped_lock 一次性锁定多个互斥锁
  std::scoped_lock<std::mutex> lock(g_pages_mutex);
  g_pages[url] = result;
}

int main() {
  std::thread t1(save_page, "http://foo");
  std::thread t2(save_page, "http://bar");
  t1.join();
  t2.join();

  // 现在可以不用锁就安全地访问 g_pages 了，因为线程已经结束
  for (const auto &pair : g_pages) {
    std::cout << pair.first << " => " << pair.second << std::endl;
  }
}