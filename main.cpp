#include <cstdio>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "absl/container/btree_map.h"
#include "absl/container/btree_set.h"
#include "absl/container/flat_hash_set.h"

void Arrays() {
  // Static arrays. The number in the [] _has_ to be a
  // compile time value. These are generally kind of bad form and not used much.
  // They're bad form because it was a really common way for hackers to break
  // into systems by writing too many values (>10 here) into these fixed arrays
  // and the memory next to the 10 values would be critical information like
  // "which function do we go back to on return".
  // https://en.cppreference.com/w/cpp/language/array
  int my_nums[10];
  my_nums[0] = 5;

  // Dynamic array with raw pointers. Array size can be known at runtime.
  // Generally using raw pointers and new/delete is kind of bad form since it's
  // easy to mess up or forget to delete. Or if an exception gets thrown you
  // might not get a chance to free the memory. This is the only example
  // where you have to manually deal with the memory.
  // https://en.cppreference.com/w/cpp/language/new
  int array_size = 10;
  int* num_array = new int[array_size];
  num_array[0] = 5;
  delete[] num_array;

  // Same as the dynamic array above but with good style. unique_ptr is a
  // wrapper around a raw pointer that will automatically do the deleting for
  // you and is very well defined. make_unique is an alternative to "new" that
  // avoids some edge cases where memory can get leaked.
  // One difficulty is that you can't make a copy of a unique_ptr (hence
  // unique). So if you want to return it from a function you might need to
  // return std::move(ptr). Or if you pass it as an argument function you have
  // to make sure it's const unique_ptr<T>& arg.
  // https://en.cppreference.com/w/cpp/utility/move
  // https://en.cppreference.com/w/cpp/memory/unique_ptr
  // https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
  std::unique_ptr<int[]> num_array_unique = std::make_unique<int[]>(array_size);
  num_array_unique[0] = 5;

  // Array for 99% of use cases: vector.
  // Vector is a dynamic array that can also be resized. It's very fast and very
  // useful. There is almost no downside to using vector. Use it for everything.
  // https://en.cppreference.com/w/cpp/container/vector
  std::vector<int> nums_vector(array_size);
  nums_vector[0] = 5;
  nums_vector.push_back(777);  // Adds an 11th element with value 777.
  nums_vector.pop_back();      // removes that element.

  // std::queue and std::stack are both thin wrappers around std::vector. I
  // usually avoid std::stack because it's already very easy to push/pop with
  // vector's builtin functions. std::queue can be useful.
}

struct Person {
  std::string name;
  int age;
  bool operator<(const Person& rhs) const { return age < rhs.age; }
};

void Trees() {
  // Set keeps one copy of every kind of value. The values are stored in a tree
  // so you can look up a value with O(log(N)) time. Recommended.
  // https://en.cppreference.com/w/cpp/container/set
  std::set<int> int_set;
  int_set.insert(7);
  if (int_set.find(7) != int_set.end()) {
    printf("Has a 7\n");
  }
  if (int_set.count(7) != 0) {
    printf("Strangely, another way of checking for presence.\n");
  }

  // Map works like set, but has a key and value. This is the closest thing to a
  // python dictionary. Highly recommended.
  // https://en.cppreference.com/w/cpp/container/map
  std::map<std::string, int> ages;
  // Add an element to the map:
  ages["Bill"] = 38;
  // Better style: use insert instead.
  ages.insert({"Brian", 40});
  // Map pitfall: The following statement will actually _add_ an entry for Jen
  // with an age of 0. It does not return some default value and actually
  // modifies the map.
  int jens_age = ages["Jen"];
  // Instead what you should do is use find and deal with the possibility of
  // non-existence.
  auto itr = ages.find("Jen");
  if (itr != ages.end()) {
    // itr here is an iterator to a std::pair<string,int>, where the first
    // element is the key "Jen" and the second element is her age.
    // https://en.cppreference.com/w/cpp/container/map/find
    printf("Jens age is %d\n", itr->second);
  } else {
    printf("Could not find Jen's age.\n");
  }

  // Priority queue: always keeps the smallest (using < operator) object at the
  // front and maintains the order efficiently. Insert and pop both take
  // O(log(N)) time.
  // https://en.cppreference.com/w/cpp/container/priority_queue
  std::priority_queue<Person> people;
  Person brian;
  brian.name = "Brian";
  brian.age = 39;
  people.push(brian);
  people.push(Person{"Bill", 37});
  people.push({"Jen", 38});
  // Expected that p is "Bill" since that is the smallest age. This uses
  // operator< declared above to determine which "Person" is "Smallest".
  Person p = people.top();
  people.pop();  // Pop doesn't return the value annoyingly.
  // You can also provide a custom comparator, though it's really annoying and
  // gross syntax.
  auto person_comp = [](const Person& lhs, const Person& rhs) {
    return lhs.name < rhs.name;
  };
  std::priority_queue<Person, std::vector<Person>, decltype(person_comp)>
      people2(person_comp);
  // Here people2 will do the same thing but in alphabetical order by name.

  // ABSL btree set and map. We used these (when we could be bothered) in
  // google. They are more efficient and have more options than the std::
  // versions, but are effectively the same and have all the same methods.
  absl::btree_set<Person> people3;
  absl::btree_map<std::string, Person> people4;
}

void HashTables() {
  // C++ only somewhat recently got hashtables. std::set and std::map are
  // implemented as red-black trees and the only Type requirement they have is
  // that objects can be '<' compared (see the operator< function in Person
  // above). The hash table equivalents are unordered_map and unordered_set.

  // But with the hash table versions, there needs to be a way to "hash" the
  // key value and provide a way to check equality. For ints or strings that is
  // already built-in. For your own type like Person, you have to provide a hash
  // function. That is basically a function that takes your custom key as input
  // and spits out a 'size_t' (unsigned int) with totally random bits based on
  // the input. We could just hash Person based on name, but if we wanted people
  // to be unique based on age also then we would have to make sure the random
  // value produced is different if age == age but name != name, or name == name
  // but age != age.

  // https://en.cppreference.com/w/cpp/container/unordered_set

  // Simple use case
  std::unordered_map<std::string, int> ages;
  ages.insert({"Bill", 38});

  // Annoyingly complex declaration using custom types hash functions and ==.
  auto hash_fn = [](const Person& person) {
    return std::hash<std::string>{}(person.name);
  };
  auto eq_fn = [](const Person& lhs, const Person& rhs) {
    return lhs.name == rhs.name;  // Don't do age since we didn't include it in
                                  // the hash function.
  };
  std::unordered_set<Person, decltype(hash_fn), decltype(eq_fn)> people_set(
      /*bucket_size????=*/0, hash_fn, eq_fn);
  people_set.insert(Person{"Bill", 38});

  // One major reason to use the tree alternatives is that if you ever need to
  // iterate through all elements in a set or map, then the order will be
  // deterministic and in ascending order.
  std::set<std::string> names;
  std::unordered_set<std::string> unordered_names;
  names.insert({"Bill", "Jen", "Brian", "Steve"});
  unordered_names.insert({"Bill", "Jen", "Brian", "Steve"});
  // Names should always be printed in alphabetical order because of std::set vs
  // unordered set.
  for (const std::string& name : names) {
    printf("Ordered Name: %s\n", name.c_str());
  }
  // Who knows. Can even change from run to run of the program:
  for (const std::string& name : unordered_names) {
    printf("Unordered Name: %s\n", name.c_str());
  }

  // For this reason I almost always used the tree-based sets/maps. Unless you
  // are pushing 1 million+ elements into the table the big-O performance
  // differences between them are not relevant.

  // There are also absl versions of the hash tables that are probably better
  // alternatives if you actually want to use a hash table:
  // https://abseil.io/docs/cpp/guides/container#hash-tables

  absl::flat_hash_set<std::string> more_names;
  // It has its own hashing system that has a handy way to combine the hashes
  // from multiple fields.
}

void NotArrays() {
  // std::array is exactly equivalent to the static array above but it's a
  // template. This is almost never used even though the name makes it seem like
  // it would be. I think it only exists for some technical
  // template-metaprogramming reason.
  std::array<int, 10> ints;
  ints[0] = 5;

  // Pair is just a 2 value structure. It's mainly used in things like std::map
  // where it's essentially a std::set but with each element being a
  // pair<Key,Value>. Not used super often in
  std::pair<std::string, int> my_pair;
  my_pair.first = "Bill";
  my_pair.second = 38;

  // Another way of making pairs which is super convenient. make_pair figures
  // out the types to put into the <> based on type deduction. Unfortunately the
  // first type here will be "const char*" and not "std::string".
  auto my_second_pair = std::make_pair("Bill", 38);

  // Tuples are like pairs with any number of values. The size of tuples and
  // what types they hold are always known at compile time. This is very close
  // to just making a struct with these values. You get the values back out
  // using std::get with the index of the element you want (also has to be known
  // at compile time).
  std::tuple<std::string, int, double> person =
      std::make_tuple("Bill", 38, 6.5);
  printf("%s is %d years old and %.1f feet tall\n", std::get<0>(person).c_str(),
         std::get<1>(person), std::get<2>(person));

  // Most commonly I'd use a tuple in a situation where a funciton _needs_ to
  // return multiple values and you can't be fucking bothered to make a
  // structure for it. One handy thing you can do is assign into multiple values
  // from a tuple.
  auto get_person = []() {
    return std::make_tuple(std::string("Sam"), 14, 5.2);
  };
  // This breaks up the tuple into multiple local variables. I only learned
  // about this recently at google.
  auto [name, age, height] = get_person();
  printf("Also %s is %d years old and %.1f feet tall\n", name.c_str(), age,
         height);
}

int main() {
  Arrays();
  Trees();
  HashTables();
  NotArrays();
  return 0;
}