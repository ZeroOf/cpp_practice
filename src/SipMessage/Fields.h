//
// Created by God on 2021/7/26.
//

#ifndef CPP_PRACTICE_FIELDS_H
#define CPP_PRACTICE_FIELDS_H

#include <unordered_map>
#include <string>


enum class Field : unsigned {
    unknown = 0,
    from,
    to
};


class Fields {
public:
    void Set(Field field, std::string value);

private:
    std::unordered_map<Field, std::string> m_fields;
};


#endif //CPP_PRACTICE_FIELDS_H
