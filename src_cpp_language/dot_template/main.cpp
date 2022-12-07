//
// Created by tao on 19-1-17.
//
#include <iostream>

#include "common_includes.h"

template <int N>
struct Collection {
  int data[N];

  Collection() {
    for (int i = 0; i < N; ++i) {
      data[i] = 0;
    }
  };

  void SetValue(int v) {
    for (int i = 0; i < N; ++i) {
      data[i] = v;
    }
  };

  template <int I>
  int GetValue(void) const {
    return data[I];
  };
};

template <int N, int I>
void printElement(Collection<N> const &c) {
  // Missing 'template' keyword prior to dependent template name 'GetValue'
  std::cout << c.template GetValue<I>()
            << std::endl;
}

TEST(dotTest, dot1) {
  Collection<10> myc;
  myc.SetValue(5);
  printElement<10, 2>(myc);
}
// https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords/17579889#17579889
/*
While the rules in C++03 about when you need typename and template are largely reasonable, there is one annoying disadvantage of its formulation

template<typename T>
struct A {
  typedef int result_type;

  void f() {
    // error, "this" is dependent, "template" keyword needed
    this->g<float>();

    // OK
    g<float>();

    // error, "A<T>" is dependent, "typename" keyword needed
    A<T>::result_type n1;

    // OK
    result_type n2;
  }

  template<typename U>
  void g();
};
As can be seen, we need the disambiguation keyword even if the compiler could perfectly figure out itself that A::result_type can only be int (and is hence a type), and this->g can only be the member template g declared later (even if A is explicitly specialized somewhere, that would not affect the code within that template, so its meaning cannot be affected by a later specialization of A!).

Current instantiation
To improve the situation, in C++11 the language tracks when a type refers to the enclosing template. To know that, the type must have been formed by using a certain form of name, which is its own name (in the above, A, A<T>, ::A<T>). A type referenced by such a name is known to be the current instantiation. There may be multiple types that are all the current instantiation if the type from which the name is formed is a member/nested class (then, A::NestedClass and A are both current instantiations).

Based on this notion, the language says that CurrentInstantiation::Foo, Foo and CurrentInstantiationTyped->Foo (such as A *a = this; a->Foo) are all member of the current instantiation if they are found to be members of a class that is the current instantiation or one of its non-dependent base classes (by just doing the name lookup immediately).

The keywords typename and template are now not required anymore if the qualifier is a member of the current instantiation. A keypoint here to remember is that A<T> is still a type-dependent name (after all T is also type dependent). But A<T>::result_type is known to be a type - the compiler will "magically" look into this kind of dependent types to figure this out.

struct B {
  typedef int result_type;
};

template<typename T>
struct C { }; // could be specialized!

template<typename T>
struct D : B, C<T> {
  void f() {
    // OK, member of current instantiation!
    // A::result_type is not dependent: int
    D::result_type r1;

    // error, not a member of the current instantiation
    D::questionable_type r2;

    // OK for now - relying on C<T> to provide it
    // But not a member of the current instantiation
    typename D::questionable_type r3;
  }
};
That's impressive, but can we do better? The language even goes further and requires that an implementation again looks up D::result_type when instantiating D::f (even if it found its meaning already at definition time). When now the lookup result differs or results in ambiguity, the program is ill-formed and a diagnostic must be given. Imagine what happens if we defined C like this

template<>
struct C<int> {
  typedef bool result_type;
  typedef int questionable_type;
};
A compiler is required to catch the error when instantiating D<int>::f. So you get the best of the two worlds: "Delayed" lookup protecting you if you could get in trouble with dependent base classes, and also "Immediate" lookup that frees you from typename and template.

Unknown specializations
In the code of D, the name typename D::questionable_type is not a member of the current instantiation. Instead the language marks it as a member of an unknown specialization. In particular, this is always the case when you are doing DependentTypeName::Foo or DependentTypedName->Foo and either the dependent type is not the current instantiation (in which case the compiler can give up and say "we will look later what Foo is) or it is the current instantiation and the name was not found in it or its non-dependent base classes and there are also dependent base classes.

Imagine what happens if we had a member function h within the above defined A class template

void h() {
  typename A<T>::questionable_type x;
}
In C++03, the language allowed to catch this error because there could never be a valid way to instantiate A<T>::h (whatever argument you give to T). In C++11, the language now has a further check to give more reason for compilers to implement this rule. Since A has no dependent base classes, and A declares no member questionable_type, the name A<T>::questionable_type is neither a member of the current instantiation nor a member of an unknown specialization. In that case, there should be no way that that code could validly compile at instantiation time, so the language forbids a name where the qualifier is the current instantiation to be neither a member of an unknown specialization nor a member of the current instantiation (however, this violation is still not required to be diagnosed).

Examples and trivia
You can try this knowledge on this answer and see whether the above definitions make sense for you on a real-world example (they are repeated slightly less detailed in that answer).

The C++11 rules make the following valid C++03 code ill-formed (which was not intended by the C++ committee, but will probably not be fixed)

struct B { void f(); };
struct A : virtual B { void f(); };

template<typename T>
struct C : virtual B, T {
  void g() { this->f(); }
};

int main() {
  C<A> c; c.g();
}
This valid C++03 code would bind this->f to A::f at instantiation time and everything is fine. C++11 however immediately binds it to B::f and requires a double-check when instantiating, checking whether the lookup still matches. However when instantiating C<A>::g, the Dominance Rule applies and lookup will find A::f instead.
 */
int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}