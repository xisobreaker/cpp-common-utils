#include "properties.h"

#include "xiso_string.h"

#include <fstream>
#include <unordered_map>
#include <utility>

namespace xiso {
namespace config {

PropertyTree::PropertyTree()
{
}

PropertyTree::~PropertyTree()
{
}

PropertyValue &PropertyTree::get(std::string section, std::string key)
{
    if (m_properties.find(section) == m_properties.end()) {
        std::unordered_map<std::string, PropertyValue> unorderedMap;
        m_properties.insert(std::make_pair(section, unorderedMap));
    }
    if (m_properties[section].find(key) == m_properties[section].end()) {
        throw PropertyException("[PropertyTree::get]: not found " + section + "." + key);
        // m_properties[section].insert(std::make_pair(key, PropertyValue("")));
    }
    return m_properties[section].at(key);
}

bool read_profile(const std::string &filename, PropertyTree &pt)
{
    std::ifstream ifile(filename);
    if (!ifile.is_open())
        return false;

    std::string line    = "";
    std::string section = "";
    while (std::getline(ifile, line)) {
        line = str_trim(line, ' ');
        if (str_startswith(line, "#"))
            continue;

        if (str_startswith(line, "[")) {
            if (!str_endswith(line, "]"))
                continue;

            section = line.substr(1, line.length() - 2);
        }

        int position = 0;
        if ((position = line.find("=")) == line.npos)
            continue;

        if (section.empty())
            continue;

        std::string key   = str_trim(line.substr(0, position), ' ');
        std::string value = str_trim(line.substr(position + 1, line.npos), ' ');
        pt.set(section, key, value);
    }
    ifile.close();
    return true;
}

bool write_profile(const std::string &filename, const PropertyTree &pt)
{
    std::ofstream ofile(filename);
    if (!ofile.is_open())
        return false;

    for (auto &sectionProp : pt) {
        std::string section = "[" + sectionProp.first + "]\n";
        ofile.write(section.c_str(), section.length());
        for (auto &prop : sectionProp.second) {
            std::string property = prop.first + " = " + prop.second.asString() + "\n";
            ofile.write(property.c_str(), property.length());
        }
        ofile.write("\n", 1);
    }
    ofile.close();
    return true;
}

} // namespace config
} // namespace xiso
