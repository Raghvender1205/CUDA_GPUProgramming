#ifndef FILES_HPP
#define FILES_HPP

#include <string>
#include <vector>

namespace AI {
    namespace Files {
        std::vector<std::string> listdir(std::string path);
        std::string get_extension(std::string path);
        std::string remove_extension(std::string path);
        bool exists(std::string path);
    }; // namespace Files
} // namespace AI
#endif // FILES_HPP
