# Templates in C++98

## 1. What a template is

A template is a blueprint, not code. Each time you use it with a new type, the compiler generates a separate, concrete version: `larger<int>` and `larger<double>` are two different functions from the same source. This is called **instantiation**.

Two consequences follow:

- **A template places implicit requirements on its types.** If the body uses `<`, `=` or a copy, every type used with it must support those operations.
- **Errors appear at instantiation.** A template is only fully checked when used with a real type, and members of a class template are only compiled if they're called. Test with several kinds of types: built-ins, `std::string`, and a class of your own.

## 2. Function templates and argument deduction

```cpp
template <typename T>
T const & larger(T const & a, T const & b)
{
    return (a > b) ? a : b;
}

larger(3, 7);            // T deduced as int
larger<double>(3, 7.5);  // T given explicitly
```

`typename` and `class` are interchangeable in the parameter list.

**Deduction rules:**

- Every argument involving `T` must deduce the same `T`. `larger(3, 7.5)` fails: one says `int`, the other `double`.
- Deduction applies no conversions.
- Explicit arguments (`larger<double>(...)`) skip deduction, and normal conversions then apply.

**How the parameter form affects deduction:**

| Parameter written as | Argument | `T` deduced as |
|---|---|---|
| `T x` (by value) | `const int` | `int` (const dropped, it's a copy) |
| `T & x` | `const int` | `const int` (const becomes part of `T`) |
| `T const & x` | `int` or `const int` | `int` |
| `T * x` | `int *` | `int` |
| `T * x` | `const int *` | `const int` |

When the parameter is a reference or pointer, a const argument makes `T` itself const. One template body can therefore handle both const and non-const data, but anything in the body that modifies through `T` fails to compile in the const case.

**Returning references.** Returning `T const &` to a parameter avoids a copy. It dangles if the caller passes temporaries and keeps the reference beyond the full expression. With references, *which* object you return is observable, not just its value, so when two arguments compare equal, the choice between them is visible to the caller.

## 3. Overloading and name lookup

**Overload resolution with templates:**

- A non-template function that matches equally well beats a template.
- Several templates can share a name with different parameter shapes.
- When two templates both match, the more specialized one wins. For example, `f(T &)` and `f(T const &)` can coexist: a non-const argument picks the first, a const one the second.

**The global scope operator.** `::f(x)` calls the `f` declared at global scope. This is a **qualified** call.

**Argument-dependent lookup (ADL).** For an *unqualified* call `f(x)`, the compiler also searches the namespaces of the argument types. If `x` is a `std::string`, it searches `std`. The standard library has `std::swap`, `std::min` and `std::max`, and headers like `<string>` or `<iostream>` may declare them indirectly. So an unqualified call to your own global `swap` with `std::string` arguments can find both versions and be ambiguous. A qualified call (`::swap(a, b)`) disables ADL and calls exactly the global one. `using namespace std;` makes collisions more likely.

## 4. Passing functions as arguments

**Function pointers:**

```cpp
void (*fp)(int &);       // pointer to a function taking int& and returning void

void apply(int & x, void (*f)(int &)) { f(x); }
```

A function name decays to a pointer, so `apply(n, inc)` and `apply(n, &inc)` are equivalent.

**Function pointer types must match exactly.** A function pointer's type includes its exact parameter and return types, and C++ has no implicit conversion between different function pointer types. Calling a function that takes `int const &` with a plain `int` is perfectly fine, but a *pointer* to that function has type `void (*)(int const &)`, which cannot be converted to `void (*)(int &)`, nor the other way around. The same goes for return types: `int (*)(int)` doesn't convert to `void (*)(int)`.

```cpp
void print(int const & x);
void inc(int & x);

void (*f1)(int &)       = inc;     // OK: exact match
void (*f2)(int const &) = print;   // OK: exact match
void (*f3)(int &)       = print;   // ERROR: no conversion between function pointer types
```

Outside templates this shows up as an "invalid conversion" error. Inside a template, it usually shows up as a deduction conflict instead (see below).

**Templates that take functions** come in two common shapes.

Spelling out the function pointer type in terms of `T`:

```cpp
template <typename T>
void callOn(T & x, void (*f)(T &));
```

Here `T` is deduced from *both* arguments, and they must agree. If `x` is `const int` (so `T = const int`) but `f` takes `int &` (so `T = int`), deduction conflicts and the call fails.

Making the callable its own parameter:

```cpp
template <typename T, typename F>
void callOn(T & x, F f);
```

Now `F` is deduced independently and can be any function pointer type. A mismatch, such as a function needing a non-const reference given const data, then shows up as an error inside the body rather than at the call.

**Passing an instance of a function template.** A template's name alone (`show`) names a family of functions, not one function. The compiler often can't pick an instance, especially when the receiving parameter is itself a deduced type like `F`. Select one explicitly:

```cpp
template <typename T>
void show(T const & v) { std::cout << v << std::endl; }

callOn(n, show<int>);
```

`show<int>` is an ordinary function of type `void (int const &)`, so the exact-match rule above applies to it like to any other function.

## 5. const correctness

- `T const &` and `const T &` are the same.
- `const int * p` is a pointer to const data. `int * const p` is a const pointer.
- A top-level `const` on a by-value parameter (`void f(int const n)`) only affects the function's own copy. It isn't part of the signature.

**const member functions.** `int size() const;` promises not to modify the object. Only const members can be called on a const object or through a const reference.

**Overloading on const.** A class can provide both:

```cpp
T & get(int i);                // non-const objects: allows modification
T const & get(int i) const;    // const objects: read-only
```

The compiler picks based on whether the object is const. This is the standard pattern for members that return a reference into the object.

## 6. Class templates

```cpp
template <typename T>
class Box
{
public:
    Box();
    Box(T const & v);
    Box(Box const & other);
    Box & operator=(Box const & rhs);
    ~Box();

    T const & get() const;

private:
    T * _ptr;
};
```

Out-of-class definitions repeat the template header and qualify with `Box<T>::`:

```cpp
template <typename T>
Box<T>::Box(T const & v) : _ptr(new T(v)) {}

template <typename T>
T const & Box<T>::get() const { return *_ptr; }
```

Inside the class and inside a member's parameter list and body, `Box` alone means `Box<T>`. A return type written *before* `Box<T>::` needs the full form:

```cpp
template <typename T>
Box<T> & Box<T>::operator=(Box const & rhs) { /* ... */ return *this; }
```

C++98 can't deduce class template arguments, so you always write `Box<int> b(5);`.

## 7. Organizing template code in files

The compiler only generates a template instance where it's used and needs the full definition there. If definitions sit in a separately compiled `.cpp`, nothing gets generated and linking fails with `undefined reference`.

Two layouts work:

- **Everything in the header.**
- **Header plus `.tpp`.** The header holds the declaration, and a `.tpp` with the definitions is `#include`d at the bottom of the header, inside the include guard. To the compiler this is the same as one header. The `.tpp` is never compiled on its own.

Headers should include everything they depend on and have include guards.

## 8. Dynamic arrays in templates

**`new[]` pairs with `delete[]`**, and `new` with `delete`. Mixing them is undefined behavior.

**Default versus value initialization:**

| Expression | Class types | Built-in types |
|---|---|---|
| `new T[n]` | default constructor runs | indeterminate (garbage) |
| `new T[n]()` | default constructor runs | zero-initialized |

The same applies to single objects: `new int()` gives 0, `new int` leaves garbage. In generic code you don't know which kind `T` is, so the difference matters. The parentheses must be empty for arrays, so arrays of a class type require a default constructor.

**Edge cases:**

- `new T[0]` is legal. It returns a valid pointer that must not be dereferenced but must still be `delete[]`d.
- `delete[]` on a null pointer is safe and does nothing.
- A failed allocation throws `std::bad_alloc`; `new` never returns null.

**Copying elements generically.** Copy element by element with `T`'s own assignment. Byte copies (`memcpy`) break types that manage resources, like `std::string`.

## 9. The Rule of Three and deep copies

The compiler-generated copy constructor and assignment operator copy each member. For a pointer, that copies the *address*. Two objects then share one buffer: changes through one are visible in the other, and both destructors free it.

**Rule of Three:** if a class needs a destructor because it owns a resource, it also needs a user-written copy constructor and assignment operator that make independent copies.

**In the assignment operator:**

- **Handle self-assignment.** In `a = a`, freeing your own memory first destroys the source.
- **Allocate and copy before freeing.** If allocation or an element copy throws, the object is then left intact.
- **Return `*this` by reference** so `a = b = c` works.

**In the copy constructor**, the object is brand new and its members are uninitialized, so there's nothing to free. Don't reuse cleanup code that would `delete` an uninitialized pointer.

## 10. Exceptions

```cpp
try
{
    riskyOperation();
}
catch (std::exception const & e)
{
    std::cerr << e.what() << std::endl;
}
```

- `throw` an object; the nearest matching `catch` handles it.
- Catch by reference to keep the real type and its message.

**Standard exceptions.** `std::exception` (in `<exception>`) is the base. `<stdexcept>` provides derived classes that take a message, such as `std::out_of_range`:

```cpp
throw std::out_of_range("index too large");
```

**Custom exceptions** derive from `std::exception` and override `what()`. In C++98 the override must include `throw()` to match the base:

```cpp
class EmptyBoxError : public std::exception
{
public:
    virtual const char * what() const throw() { return "the box is empty"; }
};
```

Without `throw()` you get a "looser throw specifier" error.

**Nested in a class template**, an exception class is defined out of class with the template header and full qualification:

```cpp
template <typename T>
const char * Box<T>::Empty::what() const throw()
{
    return "the box is empty";
}
```

## 11. Unsigned indices

- A negative value passed to an `unsigned int` parameter wraps around: `-1` becomes 4294967295 on typical systems. An upper-bound check then catches it.
- Comparing signed and unsigned values triggers `-Wsign-compare` (enabled by `-Wall` in C++). Keep index and size types consistent.

## 12. C++98 limitations to keep in mind

| Not available | Use instead |
|---|---|
| Lambdas | Named functions |
| `auto` | Spell out the type |
| `nullptr` | `NULL` or `0` |
| `noexcept` | `throw()` |
| Class template argument deduction | Always write `Box<int>` |
| `>>` closing two template lists | `> >` with a space |

## 13. Common errors

| Error | Usual cause |
|---|---|
| `undefined reference to ...<int>...` | Template definitions in a separately compiled `.cpp` |
| `call of overloaded 'f(...)' is ambiguous` | Unqualified call; ADL also found a `std::` function |
| `deduced conflicting types for parameter 'T'` | Arguments deduce different `T`, often const vs non-const |
| `couldn't deduce template parameter` | Function template passed without `<T>` |
| `invalid conversion from 'void (*)(const int&)' to 'void (*)(int&)'` | Function pointer types don't match exactly |
| `passing 'const X' as 'this' argument discards qualifiers` | Non-const member called on a const object |
| `binding reference of type 'int&' to 'const int' discards qualifiers` | Const data passed to a non-const reference parameter |
| `looser throw specifier` | Missing `throw()` on an overridden `what()` |
| Double free or crash at exit | Shallow copy (Rule of Three not followed) |
| Garbage values in a new array | `new T[n]` without `()` for built-in types |
