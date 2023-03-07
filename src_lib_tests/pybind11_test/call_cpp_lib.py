import out_lib.src_lib_tests_pybind11_test as cpp

print(cpp.Add(1, 1))
print(cpp.Add.__doc__)
print(cpp.Add(3))
print(cpp.Add())

p = cpp.Person()
print(p.name)

p = cpp.Person("tom")
print(p.name)
print(p.Hello("bob"))
p.name="test"
print(p.Hello("bob"))
print(p.Play(1))
print(p.Play(3.14))
