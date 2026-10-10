#pragma once
#include <exception>
#include <string>

class ShelterException : public std::exception {
protected:
    std::string message;
public:
    ShelterException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override { return message.c_str(); }
};

class DuplicateDogException : public ShelterException {
public:
    DuplicateDogException() : ShelterException("A dog with this breed and name already exists!") {}
};

class InexistentDogException : public ShelterException {
public:
    InexistentDogException() : ShelterException("No dog found with the given breed and name!") {}
};

class ValidationException : public ShelterException {
public:
    ValidationException(const std::string& msg) : ShelterException(msg) {}
};