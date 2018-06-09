#include <iostream>

using namespace std;

template <typename T>
class UniquePtr
{
public:
  UniquePtr(T* object)
  {
    this->object = object;
  }
  ~UniquePtr()
  {
    delete this->object;
  }
private:
  T* object;
};

class Person
{
public:
    Person(string name)
    {
        this->name = name;
    }
    ~Person()
    {
        cout << this->name << " died, RIP" << endl;
    }
private:
    string name;
};

int main()
{
    UniquePtr<Person> smart(new Person("Smart"));

    return 0;
}
