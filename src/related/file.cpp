#include <limits.h>
#include <unistd.h>
#include <string>

std::string getExecutablePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, sizeof(result));
    if (count <= 0) return "";
    return std::string(result, count);
}

std::string getExecutableDir() {
    std::string execPath = getExecutablePath();
    size_t pos = execPath.find_last_of('/');
    if (pos == std::string::npos) return "";
    return execPath.substr(0, pos); // directory only
}

std::string pathJoin(const std::string& base, const std::string& rel) {
    if (base.back() == '/')
        return base + rel;
    return base + "/" + rel;
}

