#include <iostream>
#include <cstring>

using namespace std;

class String 
{
private:
    char* data;
    int length;
    int capacity;

public:
    String() 
    {
        data = nullptr;
        length = 0;
        capacity = 0;
    }

    String(const String& str) 
    {
        length = str.length;
        capacity = str.capacity;
        data = new char[capacity];
        memcpy(data, str.data, length + 1);
    }

    String(const char* str) 
    {
        length = strlen(str);
        capacity = length + 1;
        data = new char[capacity];
        memcpy(data, str, length + 1);
    }

    ~String() 
    {
        if (data != nullptr)
            delete[] data;
    }

    int size() const 
    {
        return length;
    }

    int getCapacity() const 
    {
        return capacity;
    }

    void clear() 
    {
        length = 0;
        if (data != nullptr)
            delete[] data;
        data = nullptr;
    }

    char at(int index) const 
    {
        if (index < 0 || index >= length) 
            return '\0';
        return data[index];
    }

    void insert(char symbol) 
    {
        if (capacity == length) 
        {
            capacity *= 2;
            char* new_data = new char[capacity];
            memcpy(new_data, data, length);
            new_data[length++] = symbol;
            delete[] data;
            data = new_data;
        }
        else 
            data[length++] = symbol;
    }

    void insert(int index, char symbol) 
    {
        if (index < 0 || index > length) {
            return;
        }
        if (capacity == length) 
        {
            capacity *= 2;
            char* new_data = new char[capacity];
            memcpy(new_data, data, index);
            new_data[index] = symbol;
            memcpy(new_data + index + 1, data + index, length - index + 1);
            delete[] data;
            data = new_data;
        }
        else
        {
            char temp = data[index];
            data[index] = symbol;
            for (int i = index + 1; i < length; i++) 
            {
                char temp2 = data[i];
                data[i] = temp;
                temp = temp2;
            }
        }
        length++;
    }

    void insert(int index, char symbol, int count) 
    {
        if (index < 0 || index > length) 
        {
            return;
        }
        if (capacity < length + count) 
        {
            capacity = length + count + 1;
            char* new_data = new char[capacity];
            memcpy(new_data, data, index);
            for (int i = 0; i < count; i++)
                new_data[index + i] = symbol;
            memcpy(new_data + index + count, data + index, length - index + 1);
            delete[] data;
            data = new_data;
        }
        else 
        {
            for (int i = 0; i < count; i++) 
                insert(index + i, symbol);
        }
        length += count;
    }

    void insert(int index, const char* substr) 
    {
        if (index < 0 || index > length) {
            return;
        }
        int sub_len = strlen(substr);
        if (capacity < length + sub_len) 
        {
            capacity = length + sub_len + 1;
            char* new_data = new char[capacity];
            memcpy(new_data, data, index);
            memcpy(new_data + index, substr, sub_len);
            memcpy(new_data + index + sub_len, data + index, length - index + 1);
            delete[] data;
            data = new_data;
        }
        else
        {
            memcpy(data + index, substr, sub_len);
            length += sub_len;
        }
    }

    int find(const String& substr) const 
    {
        int sub_len = substr.size();
        for (int i = 0; i < length - sub_len + 1; i++) 
        {
            if (memcmp(data + i, substr.data, sub_len) == 0)
                return i;
        }
        return -1;
    }

    String operator+(const String& str) const 
    {
        String new_str(*this);
        new_str.insert(new_str.length, str.data);
        return new_str;
    }

    String& operator+=(const String& str) 
    {
        insert(length, str.data);
        return *this;
    }

    char nullchar = '\0';

    char& operator[](int index) 
    {
        if (index < 0 || index >= length) 
            return nullchar;
        return data[index];
    }

    const char& operator[](int index) const 
    {
        if (index < 0 || index >= length)
            return nullchar;
        return data[index];
    }

    bool operator==(const String& str) const 
    {
        if (length != str.length)
            return false;
        for (int i = 0; i < length; i++) 
        {
            if (data[i] != str.data[i]) 
                return false;
        }
        return true;
    }

    bool operator!=(const String& str) const 
    {
        return !(*this == str);
    }

    bool operator<(const String& str) const 
    {

        for (int i = 0; i < length && i < str.length; i++) 
        {
            if (data[i] < str.data[i])
                return true;
            else if (data[i] > str.data[i]) 
                return false;
        }
        return length < str.length;
    }

    friend ostream& operator<<(ostream& os, const String& str) 
    {
        os << str.data;
        return os;
    }
};

int main() {
    String str1 = "Hello, world! ";
    cout << str1 << endl;
    String str2 = "This is a string.";
    cout << str2 << endl;
    String str3 = str1 + str2;
    cout << str3 << endl;
    int index = str3.find("world");
    cout << "The index of 'world' is: " << index << endl;
    if (index < 0)
        cout << "The string 'world' was not found." << endl;
    else 
    {
        str3[index] = 'W';
        cout << str3 << endl;
    }

    cout << endl;

    str3.insert(5, ", Miles");
    cout << str3 << endl;
    int index1 = str3.find("world");
    cout << "The index of 'world' is: " << index1 << endl;
    if (index1 < 0) 
        cout << "The string 'world' was not found." << endl;
    else 
    {
        str3[index1] = 'W';
        cout << str3 << endl;
    }
    return 0;
}
