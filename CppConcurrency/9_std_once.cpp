/*
ʹ��std::onece��std::once_flag����ֻ����һ�ε���
*/

#include <iostream>
#include <thread>
#include <mutex>
//����once_flag

static std::once_flag resource_flag;

void do_one()
{
	std::cout << "call " << __FUNCTION__ << " once" << std::endl;
}

void func()
{
	std::call_once(resource_flag, do_one);
}

int main9()
{
	std::thread t1(func);
	std::thread t2(func);

	t1.join();
	t2.join();
	return 0;
}