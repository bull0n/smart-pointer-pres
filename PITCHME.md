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

---

### STD biblothèque

---

#### shared_ptr

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
- Partage de "données" et non pas d'un "pointeur" sur ces données!!!
- Ce qui implique quelles peuvent être copiées(dupliquées)
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
#### QExplicitlySharedDataPointer
- Identique à QSharedDataPointer à une énorme différences près:
 - Lors que l'on fait une copie de l'objet partagé, NE le copie PAS

---

#### QScopedPointer

---

#### QScopedArrayPointer

---

### Exercice

---

### Conclusion

---

### Bibliographie

@ul

 - https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one
 - http://ootips.org/yonat/4dev/smart-pointers.html

@ulend
