#include "Files.hpp"
#include <fstream>

#if defined(_WIN32) || defined(_WIN64)
#include "../util/dirent_win.h"
#else
#include <dirent.h>
#endif // defined

namespace AI {
    namespace Files {
        std::vector<std::string> listdir(std::string path) {
            // Open Directory
            DIR *dir_count;
            struct dirent *ent_count;
            dir_count = opendir(path.c_str());


            /// Check for Errors
            if (dir_count == NULL) {
                printf("Error, can't open directory of path %s\n", path.c_str());
            }

            // Store all file names
            std::vector<std::string> list_files;
            while ((ent_count = readdir(dir_count)) != NULL) {
                if (std::string(ent_count->d_name) == "." || std::string(ent_count->d_name) == "..") {
                    continue;
                }
            }

            return list_files;
        }

        std::string get_extension(std::string path) {
            size_t lastdot = path.find_last_of(".");
            if (lastdot == std::string::npos) {
                return "";
            }

            return path.substr(lastdot, path.size());
        }
    
        std::string remove_extension(std::string path) {
            size_t lastdot = path.find_last_of(".");
            if (lastdot == std::string::npos) {
                return path;
            }

            return path.substr(0, lastdot);
        }
    
        bool exists(std::string path) {
            std::ifstream file(path);
            if (file) {
                return true;
            }
            
            return false;
        }
    } /* namespace Files */
} /* namespace AI */
