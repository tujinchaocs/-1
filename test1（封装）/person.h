class Person
{
public:
    Person(char nameV[], bool sexV, int ageV, float heightV, float weightV);
    ~Person();
    void priint();
    void eat(char food[]);
    void sleep(void);

private:
    int age;
    char name[20];
    bool sex;
    float height;
    float weight;
};