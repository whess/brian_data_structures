#include <cstdio>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "absl/container/btree_set.h"
#include "absl/container/btree_map.h"

int main() {
  printf("Hello brian.\n");
  return 0;
}

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
  delete num_array;

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