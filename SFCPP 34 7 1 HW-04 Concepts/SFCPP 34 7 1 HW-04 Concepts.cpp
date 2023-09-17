#include <iostream>
#include <string>
#include <type_traits>

// Declaration of the MyType structure that satisfies ComplexConcept
struct MyType {
    long hash() const {
        return 42;
    }
    std::string toString() const {
        return "MyType";
    }
};

// Structure that satisfies only part of the requirements
struct NoLongType {
    std::string toString() const {
        return "NoLongType";
    }
};

// Structure that satisfies only part of the requirements
struct NoStringType {
    long hash() const {
        return 42;
    }
};

// Structure with a virtual destructor
struct NoVirtualDestructorType {
    virtual ~NoVirtualDestructorType() {}
};

// Declaration of the ComplexConcept concept
template <typename T>
concept ComplexConcept = requires(T t) {
    // Check for the presence of a hash method that returns a type convertible to long
    { t.hash() } -> std::convertible_to<long>;

    // Check for the presence of a toString method that returns std::string
    { t.toString() } -> std::same_as<std::string>;

    // Check for the absence of a virtual destructor
    !std::has_virtual_destructor<T>::value;
};

// Function that accepts an argument that satisfies ComplexConcept
template <typename T>
void ProcessComplexConcept(const T& object) {
    std::cout << "Hash: " << object.hash() << std::endl;
    std::cout << "ToString: " << object.toString() << std::endl;
}

int main() {
    MyType myObject;
    // Check for compliance with the ComplexConcept
    if constexpr (ComplexConcept<MyType>) {
        std::cout << "myObject satisfies ComplexConcept." << std::endl;
        ProcessComplexConcept(myObject); // Call the function with MyType object
    }
    else {
        std::cout << "myObject does not satisfy ComplexConcept." << std::endl;
    }

    NoLongType noLongTypeObject;
    // Check for compliance with ComplexConcept for NoLongType
    if constexpr (ComplexConcept<NoLongType>) {
        std::cout << "noLongTypeObject satisfies ComplexConcept." << std::endl;
        ProcessComplexConcept(noLongTypeObject);
    }
    else {
        std::cout << "noLongTypeObject does not satisfy ComplexConcept." << std::endl;
    }

    NoStringType noStringTypeObject;
    // Check for compliance with ComplexConcept for NoStringType
    if constexpr (ComplexConcept<NoStringType>) {
        std::cout << "noStringTypeObject satisfies ComplexConcept." << std::endl;
        ProcessComplexConcept(noStringTypeObject);
    }
    else {
        std::cout << "noStringTypeObject does not satisfy ComplexConcept." << std::endl;
    }

    NoVirtualDestructorType noVirtualDestuctorObject;
    // Check for compliance with ComplexConcept for NoVirtualDestructorType
    if constexpr (ComplexConcept<NoVirtualDestructorType>) {
        std::cout << "noVirtualDestuctorObject satisfies ComplexConcept." << std::endl;
        ProcessComplexConcept(noVirtualDestuctorObject);
    }
    else {
        std::cout << "noVirtualDestuctorObject does not satisfy ComplexConcept." << std::endl;
    }

    return 0;
}
