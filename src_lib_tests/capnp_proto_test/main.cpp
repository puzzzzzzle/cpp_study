#include <capnp/message.h>
#include <capnp/serialize.h>

#include "common_includes.h"
#include "myschema.capnp.h"

TEST(capnp, 1) {
  kj::Array<capnp::word> arr;
  {
    ::capnp::MallocMessageBuilder message{};
    auto data = message.initRoot<Date>();
    data.setDay(23);
    data.setMonth(8);
    data.setYear(2023);
    LOG_DEBUG(data.toString().flatten().cStr())
    arr = capnp::messageToFlatArray(message);
  }

  {
    ::capnp::FlatArrayMessageReader reader(arr);
    auto data = reader.getRoot<Date>();
    LOG_DEBUG(data.toString().flatten().cStr())
    ASSERT_EQ(data.getDay(), 23);
  }
}
TEST(capnp, official_example) {
  kj::Array<capnp::word> arr;

  {
    ::capnp::MallocMessageBuilder message{};
    AddressBook::Builder addressBook = message.initRoot<AddressBook>();
    ::capnp::List<Person>::Builder people = addressBook.initPeople(2);

    Person::Builder alice = people[0];
    alice.setId(123);
    alice.setName("Alice");
    alice.setEmail("alice@example.com");
    // Type shown for explanation purposes; normally you'd use auto.
    ::capnp::List<Person::PhoneNumber>::Builder alicePhones =
        alice.initPhones(1);
    alicePhones[0].setNumber("555-1212");
    alicePhones[0].setType(Person::PhoneNumber::Type::MOBILE);
    alice.getEmployment().setSchool("MIT");

    Person::Builder bob = people[1];
    bob.setId(456);
    bob.setName("Bob");
    bob.setEmail("bob@example.com");
    auto bobPhones = bob.initPhones(2);
    bobPhones[0].setNumber("555-4567");
    bobPhones[0].setType(Person::PhoneNumber::Type::HOME);
    bobPhones[1].setNumber("555-7654");
    bobPhones[1].setType(Person::PhoneNumber::Type::WORK);
    bob.getEmployment().setUnemployed();

    LOG_DEBUG(addressBook.toString().flatten().cStr())
    arr = capnp::messageToFlatArray(message);
  }

  {
    ::capnp::FlatArrayMessageReader reader(arr);
    auto data = reader.getRoot<AddressBook>();
    LOG_DEBUG(data.toString().flatten().cStr())
  }
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}