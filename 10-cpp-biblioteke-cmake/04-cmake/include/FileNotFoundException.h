#ifndef FILE_NOT_FOUND_EXCEPTION_H
#define FILE_NOT_FOUND_EXCEPTION_H

#include <exception>
#include <string>

class FileNotFoundException final : public std::exception
{
public:
    FileNotFoundException(const char* message);
    [[nodiscard]] const char* what() const noexcept override;
    
private:
    std::string message_;
};

#endif // FILE_NOT_FOUND_EXCEPTION_H
