#ifndef PATH_HANDLER_H
#define PATH_HANDLER_H

#include <iostream>
#include <string>

/// Function Prototypes
void getDirFileName(const std::string &path, std::string *dir, std::string *file);
void getPrefixExtension(const std::string &fileName, std::string *prefix, std::string *extension);

#endif // PATH_HANDLER_H
