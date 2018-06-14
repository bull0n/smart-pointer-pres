## Smart Pointers

@div[left-50]


Par Biloni Kim, Wermeille Bastien et Bulloni Lucas

@divend

@div[right-50]
![Pointeurs](pictures/pointers.png)
@divend

---

### Sommaire

@ul
- Qu'est ce que les Smart Pointers?
- STD bibliothèque
 - shared_ptr
 - weak_ptr
 - unique_ptr
- Qt
 - Pointeurs similaires
 - QSharedDataPointer
 - QScopedPointer et QScopedArrayPointer
@ulend

---

### Qu'est-ce que les Smarts Pointers

- But : ne pas devoir à réfléchir quand `delete`
- Objet qui va stocker un pointeur
- Ce n'est pas un système Garbage Collector comme en java
- Il faut quand même réfléchir auquel utiliser

---

#### Principe

```c++
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
```

---

### STD biblothèque

 - `#include <memory>`
 - auto_ptr avec C++98
  - Déprecié
 - Utiliser les pointeurs que l'on va vous présenter.
 - Accéder au pointeur originel avec .get()

---

#### unique_ptr

---

#### shared_ptr

 - Pointeur partagé entre plusieurs objets
 - Sera détruit quand la dernière référence sera détruite
 - /!\ Ne pas créer de smart pointers depuis un pointeurs déjà dans un shared_ptr /!\

```c++
Sofa* sofa = new Sofa();
Simpson homer("homer", sofa); // NON !
```

 - http://en.cppreference.com/w/cpp/memory/shared_ptr

---

#### shared_ptr (code)

 ```c++
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
 Simpson(string name, shared_ptr<Sofa> sofa) : sofa(sofa)
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

 ```

---

#### shared_ptr (code)

```c++
int main()
{
  shared_ptr<Sofa> sofa(new Sofa());
  Simpson homer("homer", sofa);
  Simpson marge("marge", sofa);
  Simpson bart("bart", sofa);
  Simpson lisa("lisa", sofa);

  cout << "The Simpsons are going home" << endl;
}
```

---

#### shared_ptr (exécution)

![Pointeurs](pictures/execution_shared_ptr.png)

---

![Pointeurs](pictures/simpsons-sofa.jpg)

---

#### weak_ptr

---

### Qt
Notions élémentaires:
- Shared pointer versus shared data
- Shared pointer
 - Partage d'un pointeur
 - Aucun intérêt pour les données partagées en soit
- Shared Data
 - Partage de données
 - Aucun intérêt pour le pointer en soit ou la manière dont sont partagées les données
---

### Qt
Notions élémentaires 2
- Strong versus weak

---

#### Pointeurs similaires

---

#### QSharedDataPointer
- Partage de **données**, pas d'un ~~pointeur~~
- Ce qui implique quelles peuvent être copiées

```c++
#include <QSharedData>
#include <QString>

class EmployeeData : public QSharedData
{
  public:
    EmployeeData() : id(-1) { }
    EmployeeData(const EmployeeData &other)
        : QSharedData(other), id(other.id), name(other.name) { }
    ~EmployeeData() { }

    int id;
    QString name;
};

class Employee
{
  public:
    Employee() { d = new EmployeeData; }
    Employee(int id, const QString &name) {
        d = new EmployeeData;
        setId(id);
        setName(name);
    }
    Employee(const Employee &other)
          : d (other.d)
    {
    }
    void setId(int id) { d->id = id; }
    void setName(const QString &name) { d->name = name; }

    int id() const { return d->id; }
    QString name() const { return d->name; }

  private:
    QSharedDataPointer<EmployeeData> d;
};

int main()
{
    Employee e1(1001, "Albrecht Durer");
    Employee e2 = e1;
    e1.setName("Hans Holbein");
}
```

---
#### `QExplicitlySharedDataPointer`
- Identique à `QSharedDataPointer` à une énorme différences près:
 - Lors que l'on fait une copie de l'objet partagé, ne le copie *PAS*
 - _Possibilité de préciser si l'on veut que les données soient dupliquées avec **detach()**_

---

#### `QScopedPointer`
- Permet d'assurer qu'un objet sera supprimé à la sortie de la portée dans laquelle il est instancié

Exemple sans
```c++
void myFunction(bool useSubClass)
{
    MyClass \*p = useSubClass ? new MyClass() : new MySubClass;
    QIODevice \*device = handsOverOwnership();

    if (m_value > 3) {
        delete p;
        delete device;
        return;
    }

    try {
        process(device);
    } catch (...) {
        delete p;
        delete device;
        throw;
    }

    delete p;
    delete device;
}
```

---
#### `QScopedPointer`
Exemple avec:

```c++
void myFunction(bool useSubClass)
{
    // assuming that MyClass has a virtual destructor
    QScopedPointer<MyClass> p(useSubClass ? new MyClass() : new MySubClass);
    QScopedPointer<QIODevice> device(handsOverOwnership());

    if (m_value > 3)
        return;

    process(device);
}
```

---

#### `QScopedArrayPointer`
- Identique à `QScopedPointer` mais pour des tableaux d'objets

```c++
void foo()
{
    QScopedArrayPointer<int> i(new int[10]);
    i[2] = 42;
    ...
    return; // our integer array is now deleted using delete[]
}
```
---

### Exercice

---

### Conclusion

---

### Référence


 - https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one
 - http://ootips.org/yonat/4dev/smart-pointers.html
 - https://www.codeproject.com/Articles/541067/Cplusplus-Smart-Pointers
 - https://wiki.qt.io/Smart_Pointers
