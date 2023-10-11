#include <PenguinEngine/Inc/PenguinEngine.h>

using namespace::PenguinEngine::Core;

class Student
{
public:
	Student() = default;
	Student(int i)
	{

	}
	Student(const char* name, int i)
	{

	}
	void DoWork()
	{
		//
	}

private:
	std::string mName;
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 100);

	Student* a = studentPool.New();
	Student* b = studentPool.New();
	Student* c = studentPool.New(0);
	Student* d = studentPool.New(0);

	studentPool.Delete(c);
	studentPool.Delete(d);
	Student* e = studentPool.New("Joe", 0);

	studentPool.Delete(a);
	studentPool.Delete(b);
	studentPool.Delete(e);

	return 0;
}