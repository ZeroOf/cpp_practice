#include <memory>
#include <vector>
#include "Point.h"
#include "Parent.h"
#include "Child.h"

using namespace std;

void TestAuto() {
  cout << __func__ << endl;
  auto_ptr<Point> ap(new Point(1, 2));
  cout << "ap'get = " << ap.get() << endl;
  cout << "*ap = " << *ap << endl;
  ap->display();
  cout << endl;

  auto_ptr<Point> ap2(ap);//在语法上是一个复制操作
  //但实现时，已经发生了所有权的转移
  //存在缺陷
  cout << "*ap2 = " << *ap2 << endl;
  cout << "ap = " << ap.get() << endl;//error，段错误
}

void TestShared() {
  cout << __func__ << endl;
  shared_ptr<Point> sp(new Point(1, 2));
  cout << "sp' use_count = " << sp.use_count() << endl;
  cout << "*sp = " << *sp << endl;
  cout << "sp'get = " << sp.get() << endl << endl;


  //shared_ptr是共享所有权的智能指针
  //当进行复制或赋值时，只需要将引用计数加1
  shared_ptr<Point> sp2(sp);//复制语义
  cout << "*sp = " << *sp << endl;
  cout << "*sp2 = " << *sp2 << endl;

  cout << "sp' use_count = " << sp.use_count() << endl;
  cout << "sp2' use_count = " << sp2.use_count() << endl << endl;

  shared_ptr<Point> sp3;
  sp3 = sp2;//赋值
  cout << "sp2' use_count = " << sp2.use_count() << endl;
  cout << "sp3' use_count = " << sp3.use_count() << endl;
}

void TestSharedRound() {
  cout << __func__ << endl;
  shared_ptr<Parent> pParent(new Parent());
  shared_ptr<Child> pChild(new Child());

  cout << "pParent ' use_count = " << pParent.use_count() << endl;
  cout << "pChild' use_count = " << pChild.use_count() << endl;

  pParent->_childPtr = pChild;
  pChild->_parentPtr = pParent;
  cout << "pParent ' use_count = " << pParent.use_count() << endl;
  cout << "pChild' use_count = " << pChild.use_count() << endl;

}

unique_ptr<Point> getPoint() {
  unique_ptr<Point> up(new Point(5, 6));
  return up;
}

void TestUnique() {
  cout << __func__ << endl;
  unique_ptr<Point> up(new Point(1, 2));
  cout << "*up = " << *up << endl;
  cout << "up'get = " << up.get() << endl;

  //unique_ptr不能进行复制或赋值,表达的是对象语义, 独享所有权
  //unique_ptr<Point> up2(up);//error
  unique_ptr<Point> up3(new Point(3, 4));
  //up = up3;//error

  cout << "*up3 = " << *up3 << endl;
  up3 = getPoint();//unique_ptr具有移动语义，其内部定义了移动构造函数和移动赋值运算符函数
  cout << "*up3 = " << *up3 << endl;

  cout << endl << "将点放入容器之中:" << endl;
  vector<unique_ptr<Point>> points;
  //points.push_back(up);//error, up是左值,会进行复制
  points.push_back(std::move(up));//必须用右值的方式放入
  points.push_back(std::move(up3));

  //cout << "*up3 = " << * up3 << endl;//error, up3被托管的对象已经转移到容器之中去了, 不能直接使用
  //reset重新托管一个对象
  up.reset(new Point(10, 11));

  cout << "*up = " << *up << endl;
}

void TestWeak() {
  cout << __func__ << endl;
  weak_ptr<Point> wp;

  {//语句块
    shared_ptr<Point> sp(new Point(1, 2));
    wp = sp;//
    cout << "wp' use_count = " << wp.use_count() << endl;
    //cout << "*wp = " << *wp << endl;//error

    //如果要访问weak_ptr中托管的对象,必须要提升成一个shared_ptr
    shared_ptr<Point> sp2 = wp.lock();
    if (sp2) {
      cout << "weak_ptr提升成功，" << wp.lock().use_count() << endl;
      cout << "*sp2 = " << *sp2 << endl;
    } else {
      cout << "weak_ptr提升失败, 托管的对象已经被销毁" << endl;
    }
  }

  cout << endl;
  //weak_ptr知道其所托管对象的生命周期是否结束
  shared_ptr<Point> sp2 = wp.lock();
  if (sp2) {
    cout << "weak_ptr提升成功，" << endl;
    cout << "*sp2 = " << *sp2 << endl;
  } else {
    cout << "weak_ptr提升失败, 托管的对象已经被销毁" << endl;
  }
}

int main() {
  cout << __FILE__ << endl;
//    TestAuto();
//    TestShared();
//    TestSharedRound();
//    TestUnique();
  TestWeak();
}