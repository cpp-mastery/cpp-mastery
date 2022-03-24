/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <utility>

using namespace std;

class Vector {

public:
    int* data;

    Vector(int d);

    Vector(const Vector& a);            // CC
    Vector& operator=(const Vector& a); // CA

    Vector(Vector&& a);                 // MC
    Vector& operator=(Vector&& a);      // MA

    Vector operator+(Vector& v);        // Copy
    Vector operator+(Vector&& v1);      // Move

};

Vector::Vector(int d) {
    data = new int;
    *data = d;
    cout << "Const" << endl;
}

Vector::Vector(const Vector& a): Vector{ *a.data } {        // CC
    cout << "CC" << endl;
}

Vector& Vector::operator=(const Vector& a){     // CA
    cout << "CA" << endl;
}

Vector::Vector(Vector&& a) : data{ a.data } {            // MC
    cout << "MC" << endl;
}

Vector& Vector::operator=(Vector&& a) {         // MA
    cout << "MA" << endl;
    return a;
}

Vector Vector::operator+(Vector& v1){   // Copy
    cout << "copy plus" << endl;
    return Vector( *(this->data) + *(v1.data) ) ;
}

Vector Vector::operator+(Vector&& v1){  // Move
    cout << "move plus" << endl;
    *(v1.data) += *(this->data);
    return v1 ;
}

void separateLine() { cout << "---" << endl; }

Vector doSomething() {
    return Vector(1);
}
Vector doSomething2() {
    Vector v = Vector(1);
    cout << "hi" << endl;
    return v;
}

Vector passReturn(Vector v) {
    return v;
}
//Vector passReturnL(Vector& v) {     // error!
//    return v;
//}
Vector passReturnR(Vector&& v) {
    cout << *(v.data) << endl;
    cout << &v << endl;
    return v;
}

void q1() {

    Vector v0(0);                    // Const
    separateLine();
    Vector* v1 = new Vector(1);      // Const ; called when new Vector()
    separateLine();
    Vector v2 = v0;                     // Const, CC ; const called when making v2, and copy called
    separateLine();
    Vector v3 = *(new Vector(3));    // Const, Const, CC ; const called when making new V, and then v3, and then copying values
    separateLine();
    Vector v4{ Vector{4} };           // Const
    separateLine();
    Vector v5 = Vector(5);           // Const
    separateLine();
    Vector v6 = doSomething();          // Const; WHY? I think optimized
    separateLine();
    Vector v9 = doSomething2();         // Const, hi, Const
    separateLine();
    Vector v7 = std::move(v0);          // MC ; v0 treated as rvalue and MC called
    separateLine();
    Vector v8 = std::move( Vector(1) ); // Const, MC
    separateLine();

}

void q2() {

    Vector v0 = Vector(1);                  // Const
    separateLine();
    Vector v1 = passReturn(v0);                 // Const,CC,MC; Const when setting v, and CC when copying, and then MC when getting returned rvalue
    separateLine();
    //Vector v2 = passReturnR(v0);              // An Error!
    separateLine();

    int tmp=0; cout << &tmp << endl;
    Vector v3 = passReturnR( Vector(1) ); // Const, MC; Const when setting, and nothing when moving rvalue, and MC when getting back to V3
    cout << &v3 << endl;
    int tmp2=0; cout << &tmp2 << endl;
    separateLine();

    Vector v4(1);                           // Const
    v4 = Vector(1);                         // Const, MA; Const when Vector(1), and MA when moving assign

}

void q3() {

    Vector v1 = Vector(1);                  // Const
    Vector v2 = Vector(2);                  // Const
    Vector v_sum = v1 + v2;                     // copy plus, Const when copying
    cout << *(v_sum.data) << endl;              // 3
    separateLine();
    Vector v3 = Vector(3);
    Vector v_sum_2 = v3 + Vector(4);         // move plus, MC when moving result
    cout << *(v_sum_2.data) << endl;            // 7

}

void q4() {

    Vector v1 = Vector(1);                  // Const
    Vector v2 = Vector(2);                  // Const
    Vector v3 = Vector(3);                  // Const
    Vector v4 = Vector(4);                  // Const
    Vector v_sum = v1 + v2 + v3 + v4;           // cp, const, cp, const, cp, const
    cout << *(v_sum.data) << endl;              // 10
    separateLine();


    Vector v_sum_2 = Vector(1) + Vector(2) + Vector(3) + Vector(4);         // mp, mc, mp, mc, mp, mc
    cout << *(v_sum_2.data) << endl;            // 10

}

int main()
{
    //q1();
    //q2();
    //q3();
    q4();

}
