#include <iostream>
#include <memory>

using namespace std;

class Sofa
{
public:
  Sofa() {}
  ~Sofa()
  {
    cout << "nobody's sofa, it has been dumped" << endl;
  }
};

class Simpson
{
public:
  Simpson(string name, Sofa* sofa) : sofa(sofa)
  {
    this->name = name;
  }
  ~Simpson()
  {
    cout << this->name << " got lost" << endl;
  }
private:
  shared_ptr<Sofa> sofa;
  string name;
};

int main()
{
  Sofa* sofa = new Sofa();
  Simpson homer("homer", sofa);
  Simpson marge("marge", sofa);
  Simpson bart("bart", sofa);
  Simpson lisa("lisa", sofa);

  cout << "The Simpsons are going home" << endl;
}
