#ifndef DICTIONARY_H_
#define DICTINARY_H_
#include <string>
#include <climits>
 
 
class Dictionary{
public:
    Dictionary(): key(""), code(UINT_MAX){}
    Dictionary(int i, std::string c=""): code(i), key(c){}
    Dictionary(const Dictionary & rhs): code(rhs.code), key(rhs.key) {}
	bool operator == (const Dictionary & rhs) const;
    bool operator != (const Dictionary & rhs) const;
    void operator = (Dictionary & rhs);
    unsigned code;
    std::string key;
};
 
unsigned hashing(const Dictionary & d, int size);

bool Dictionary::operator == (const Dictionary & rhs) const
{
    return code==rhs.code;
}
 
bool Dictionary::operator != (const Dictionary & rhs) const
{
    return code!=rhs.code;
}
 
unsigned hashing(const Dictionary & d, int size)
{
    return d.code%size;
}
 
void Dictionary::operator = (Dictionary & rhs)
{
    code=rhs.code;
    key=rhs.key;
}

#endif