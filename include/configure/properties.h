// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_filesystem.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:28:37
//  描    述:
// =====================================================================================

#ifndef _PROPERTY_H_H_H
#define _PROPERTY_H_H_H

#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstdint>

namespace kgr {
    namespace config {
        class PropertyValue
        {
        public:
            PropertyValue() : m_value(""){};
            PropertyValue(const PropertyValue &property)
            {
                m_value = property.m_value;
            };
            PropertyValue(const std::string &value) : m_value(value){};
            PropertyValue(const char *value) : m_value(value){};
            PropertyValue(bool value)
            {
                m_value = value ? "true" : "false";
            };

            PropertyValue(float value)
            {
                m_value = std::to_string(value);
            };

            PropertyValue(double value)
            {
                m_value = std::to_string(value);
            };

            PropertyValue(int16_t value)
            {
                m_value = std::to_string(value);
            };

            PropertyValue(uint16_t value)
            {
                m_value = std::to_string(value);
            };

            PropertyValue(int32_t value)
            {
                m_value = std::to_string(value);
            };

            PropertyValue(uint32_t value)
            {
                m_value = std::to_string(value);
            };

            PropertyValue(int64_t value)
            {
                m_value = std::to_string(value);
            };

            PropertyValue(uint64_t value)
            {
                m_value = std::to_string(value);
            };

            ~PropertyValue(){};

            PropertyValue &operator=(const std::string &value)
            {
                m_value = value;
                return *this;
            }

            PropertyValue &operator=(const PropertyValue &property)
            {
                m_value = property.m_value;
                return *this;
            }

        public:
            std::string asString() const
            {
                return m_value;
            }

            int32_t asInt()
            {
                if (m_value.empty())
                    return 0;
                return std::stol(m_value);
            }

            uint32_t asUInt()
            {
                if (m_value.empty())
                    return 0;
                return std::stoul(m_value);
            }

            int64_t asInt64()
            {
                if (m_value.empty())
                    return 0;
                return std::stoll(m_value);
            }

            uint64_t asUInt64()
            {
                if (m_value.empty())
                    return 0;
                return std::stoull(m_value);
            }

            float asFloat()
            {
                if (m_value.empty())
                    return 0.0;
                return std::stof(m_value);
            }

            double asDouble()
            {
                if (m_value.empty())
                    return 0.0;

                return std::stod(m_value);
            }

            bool asBool()
            {
                if (m_value.empty())
                    return false;
                return m_value == "true";
            };

        public:
            std::string m_value;
        };

        class PropertyTree
        {
            typedef std::unordered_map<std::string, std::unordered_map<std::string, PropertyValue>> self_type;

        public:
            PropertyTree();
            ~PropertyTree();

        public:
            template <typename T>
            void           set(std::string section, std::string key, T value);
            PropertyValue &get(std::string section, std::string key);

            self_type::iterator begin()
            {
                return m_properties.begin();
            }

            self_type::const_iterator begin() const
            {
                return m_properties.begin();
            }

            self_type::iterator end()
            {
                return m_properties.end();
            }

            self_type::const_iterator end() const
            {
                return m_properties.end();
            }

        private:
            std::unordered_map<std::string, std::unordered_map<std::string, PropertyValue>> m_properties;
        };

        template <typename T>
        void PropertyTree::set(std::string section, std::string key, T value)
        {
            if (m_properties.find(section) == m_properties.end()) {
                std::unordered_map<std::string, PropertyValue> unorderedMap;
                m_properties.insert(std::make_pair(section, unorderedMap));
            }
            m_properties[section][key] = PropertyValue(value);
        }

        /**
         * 读取配置文件
         */
        bool read_profile(const std::string &filename, PropertyTree &pt);

        /**
         * 写入配置文件
         */
        bool write_profile(const std::string &filename, const PropertyTree &pt);

    } // namespace config
} // namespace kgr

#endif