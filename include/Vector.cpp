#include "Vector.h"
Vector::Vector(int n)
{n=abs(n);
size=n;
Vec=new double[n];
for (int i=0;i<n;i++) Vec[i]=0;
}
Vector::Vector (double *A,int n)
{n=abs(n);
size=n;
Vec=new double[n];
for (int i=0;i<n;i++) Vec[i]=A[i];
}
Vector::Vector (const Vector &A)
{size=A.size;
Vec=new double [size];
for(int i=0;i<size;i++) Vec[i]=A.Vec[i];
}
Vector::~Vector()
{delete [] Vec;
}
Vector& Vector::operator =(const Vector &A)
{if (size!=A.size) 
{delete [] Vec;
size=A.size;
Vec=new double[A.size];
}
for (int i=0;i<size;i++) Vec[i]=A.Vec[i];
return *this;
}
Vector Vector::operator+(const Vector &A)
{Vector R(*this);
if (size>=A.size) for(int i=0;i<A.size;i++) R.Vec[i]+=A.Vec[i];
if (size<A.size) {Vector Z(A); for(int i=0;i<size;i++) Z.Vec[i]+=Vec[i];R=Z;}
return R;
}
double Vector::operator*(const Vector &A)
{double res=0;
if (size<=A.size) for(int i=0;i<size;i++) res+=A.Vec[i]*Vec[i];
if (size>A.size) for(int i=0;i<A.size;i++) res+=A.Vec[i]*Vec[i];
return res;
}
double Vector::lenvec()
{double res;
res=sqrt(*this**this);
return res;
}
int Vector::operator==(const Vector &A)
{int res=1;
if(size!=A.size) res=0;
else for(int i=0;i<size;i++) if (Vec[i]!=A.Vec[i]) {res=0;break;}
return res;
}
void Vector::printv()
{for(int i=0;i<size;i++) cout<<Vec[i]<<" ";
}
ostream& operator<<(ostream& stream, const Vector& vec)
{stream <<"(";
for (int i=0;i<vec.size-1;i++) stream << vec.Vec[i]<<" ";
stream<<vec.Vec[vec.size-1]<<")";
return stream;
}
istream& operator>>(istream& stream, Vector& vec)
{int n=0;
cout<<"¬ведите размер вектора: ";
cin>>n;
vec.size=n;
delete [] vec.Vec;
vec.Vec=new double[n];
cout<<"¬вод вектора: ";
for (int i=0;i<vec.size;i++) stream>>vec[i];
return stream;
}
Vector& Vector::operator +=(const Vector &A)
{*this=*this+A;
return *this;
}
double& Vector::operator [](int ind)
{return Vec[ind];
}
Vector Vector::operator ++()
{for(int i=0;i<size;i++) Vec[i]+=1;
return *this;
}
Vector Vector::operator ++(int)
{Vector Res(*this);
for(int i=0;i<size;i++) Vec[i]+=1;
return Res;
}