#include <iostream>
#include <memory>

using namespace std;

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
    Person* dumb = new Person("Dumb");
    unique_ptr<Person> smart(new Person("Smart"));
    // unique_ptr<Person> smartClone(smart.get()); // with unique_ptr the object can only be used in one smart pointer -> this line will provoke a segmentation error
    unique_ptr<int[]> intPtr(new int[10000000]);

    cout << smart.get() << endl;

    return 0;
}
