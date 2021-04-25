#include <iostream>
template<class t>
class base{
    public:
        template<class s>
        class inherit{
            foo(){cout << "foo called\n";}
        };
        
};

int main(){
    return 0;
}
