#include "COWString.h"

using namespace std;

int main()
{

    cout << "sizeof(size_t) = " << sizeof(size_t) << endl;
#if 0
    String s1;
	String s2(s1);
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << endl;
#endif

    COWString s3("hello,world");
    COWString s4(s3);
    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;
    cout << "s3' refcount = " << s3.refcount() << endl;
    cout << "s4' refcount = " << s4.refcount() << endl;
    printf("s3' addr = %p\n", s3.c_str());
    printf("s4' addr = %p\n", s4.c_str());

    COWString s5("wangdao");
    cout << "s5 = " << s5 << endl;
    cout << endl << "执行s5 = s3 " << endl;
    s5 = s3;
    cout << "s3' refcount = " << s3.refcount() << endl;
    cout << "s4' refcount = " << s4.refcount() << endl;
    cout << "s5' refcount = " << s5.refcount() << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;
    cout << "s5 = " << s5 << endl;
    printf("s3' addr = %p\n", s3.c_str());
    printf("s4' addr = %p\n", s4.c_str());
    printf("s5' addr = %p\n", s5.c_str());

    //s3 = s5;
    s5[0] = 'X';
    cout << endl << "执行写操作 s5[0]=‘X’ 之后:" << endl;
    cout << "s3' refcount = " << s3.refcount() << endl;
    cout << "s4' refcount = " << s4.refcount() << endl;
    cout << "s5' refcount = " << s5.refcount() << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;
    cout << "s5 = " << s5 << endl;
    printf("s3' addr = %p\n", s3.c_str());
    printf("s4' addr = %p\n", s4.c_str());
    printf("s5' addr = %p\n", s5.c_str());

    cout << endl <<"执行读操作s4[0] = " << s4[0] << endl;
    cout << "s3' refcount = " << s3.refcount() << endl;
    cout << "s4' refcount = " << s4.refcount() << endl;
    cout << "s5' refcount = " << s5.refcount() << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;
    cout << "s5 = " << s5 << endl;
    printf("s3' addr = %p\n", s3.c_str());
    printf("s4' addr = %p\n", s4.c_str());
    printf("s5' addr = %p\n", s5.c_str());


    return 0;
}

