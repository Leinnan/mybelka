#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>

using std::string;

namespace la {

class Category
{
public:
    Category(string m_name, string m_color);
    Category(){};
private:
    string name;
    string color;
};

}
#endif // CATEGORY_H
