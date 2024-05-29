#ifndef TRACEPP_MODELIO_H
#define TRACEPP_MODELIO_H

#include <iostream>
#include <format>
#include <utility>
#include <variant>
#include <string>
#include <vector>
#include <fstream>
#include <ranges>

#include <boost/algorithm/string.hpp>

#include "types.h"
#include "math.h"
#include "scene.h"

namespace trace {

// GENERIC SCENE STRUCTURE

// PLY STRUCTURE AND BASIC LOADING

using PlyType = std::variant<i8, u8, i16, u16, i32, u32, f32, f64>;

struct PlySingle {
    std::string name;
    std::string type_of;
    std::vector<PlyType> content;

    PlySingle(std::string name, std::string typeOf) : name(std::move(name)), type_of(std::move(typeOf)) {
        this->content = std::vector<PlyType>{};
    }
};

struct PlyList {
    std::string name;
    std::string index_type;
    std::string type_of;
    std::vector<std::vector<PlyType>> content;

    PlyList(std::string name, std::string indexType, std::string typeOf)
            : name(std::move(name)), index_type(std::move(indexType)), type_of(std::move(typeOf)) {
        this->content = std::vector<std::vector<PlyType>>{};
    }
};

using PlyProperty = std::variant<PlySingle, PlyList>;

struct PlyElement {
    std::string name;
    size_t count;
    std::vector<PlyProperty> properties;

    PlyElement(std::string name, size_t count) : name(std::move(name)), count(count) {
        this->properties = std::vector<PlyProperty>{};
    }

    auto add_property(const PlyProperty &prop) -> void {
        this->properties.push_back(prop);
    }
};

using PlyModel = std::vector<PlyElement>;

constexpr void
add_prop_single(const std::string &type_of, std::vector<PlyType> &content, const std::string &value) {
    if (type_of == "char") {
        i8 tmp{};
        std::sscanf(value.c_str(), "%s", &tmp);
        content.emplace_back(tmp);
    } else if (type_of == "uchar") {
        u8 tmp{};
        std::sscanf(value.c_str(), "%s", &tmp);
        content.emplace_back(tmp);
    } else if (type_of == "short") {
        i16 tmp{};
        std::sscanf(value.c_str(), "%hd", &tmp);
        content.emplace_back(tmp);
    } else if (type_of == "ushort") {
        u16 tmp{};
        std::sscanf(value.c_str(), "%hu", &tmp);
        content.emplace_back(tmp);
    } else if (type_of == "int") {
        i32 tmp{};
        std::sscanf(value.c_str(), "%d", &tmp);
        content.emplace_back(tmp);
    } else if (type_of == "uint") {
        u32 tmp{};
        std::sscanf(value.c_str(), "%d", &tmp);
        content.emplace_back(tmp);
    } else if (type_of == "float") {
        f32 tmp{};
        std::sscanf(value.c_str(), "%f", &tmp);
        content.emplace_back(tmp);
    } else if (type_of == "double") {
        f64 tmp{};
        std::sscanf(value.c_str(), "%lf", &tmp);
        content.emplace_back(tmp);
    } else {
        std::cerr << "Error to parse value of single property!\n";
        exit(3);
    }
}

constexpr void add_prop_list(const std::string &type_of, std::vector<std::vector<PlyType>> &content,
                             const std::vector<std::string> &values) {
    std::vector<PlyType> accumulator{};

    if (type_of == "char") {
        std::transform(values.begin(), values.end(), std::back_inserter(accumulator), [](auto a) {
            u8 tmp{};
            std::sscanf(a.c_str(), "%s", &tmp);
            return PlyType{tmp};
        });
    } else if (type_of == "uchar") {
        std::transform(values.begin(), values.end(), std::back_inserter(accumulator), [](auto a) {
            i8 tmp{};
            std::sscanf(a.c_str(), "%s", &tmp);
            return PlyType{tmp};
        });
    } else if (type_of == "short") {
        std::transform(values.begin(), values.end(), std::back_inserter(accumulator), [](auto a) {
            i16 tmp{};
            std::sscanf(a.c_str(), "%hd", &tmp);
            return PlyType{tmp};
        });
    } else if (type_of == "ushort") {
        std::transform(values.begin(), values.end(), std::back_inserter(accumulator), [](auto a) {
            u16 tmp{};
            std::sscanf(a.c_str(), "%hu", &tmp);
            return PlyType{tmp};
        });
    } else if (type_of == "int") {
        std::transform(values.cbegin(), values.cend(), std::back_inserter(accumulator), [](auto a) -> PlyType {
            i32 tmp{};
            std::sscanf(a.c_str(), "%d", &tmp);
            return PlyType{tmp};
        });
    } else if (type_of == "uint") {
        std::transform(values.begin(), values.end(), std::back_inserter(accumulator), [](auto a) {
            u32 tmp{};
            std::sscanf(a.c_str(), "%u", &tmp);
            return PlyType{tmp};
        });
    } else if (type_of == "float") {
        std::transform(values.begin(), values.end(), std::back_inserter(accumulator), [](auto a) {
            f32 tmp{};
            std::sscanf(a.c_str(), "%f", &tmp);
            return PlyType{tmp};
        });
    } else if (type_of == "double") {
        std::transform(values.begin(), values.end(), std::back_inserter(accumulator), [](auto a) {
            f64 tmp{};
            std::sscanf(a.c_str(), "%lf", &tmp);
            return PlyType{tmp};
        });
    } else {
        std::cerr << "Error to parse value of single property!\n";
        exit(3);
    }

    content.push_back(accumulator);
}

auto load_ply(const std::string &filename) -> PlyModel {
    auto ply_model{PlyModel{}};
    auto format{std::string{}};
    auto first_elem = true;
    PlyElement elem{"", 0};
    size_t count_t{};

    auto file{std::ifstream{filename}};
    if (!file) {
        std::cerr << std::format("Error to open file: {}\n", filename);
        exit(1);
    }

    std::string line{};
    std::vector<std::string> splitted{};
    while (std::getline(file, line)) {
        // Split line by ' '
        boost::split(splitted, line, boost::is_any_of(" "));
        if (splitted[0] == "ply" || splitted[0] == "comment") {
            continue;
        } else if (splitted[0] == "format") {
            format = splitted[1];
        } else if (splitted[0] == "element") {
            if (first_elem) {
                first_elem = false;
            } else {
                ply_model.push_back(elem);
            }

            auto name = splitted[1];
            std::sscanf(splitted[2].c_str(), "%zu", &count_t);
            elem = PlyElement{name, count_t};
        } else if (splitted[0] == "property") {
            auto prop_type = splitted[1];
            if (prop_type == "list") {
                auto index_type = splitted[2];
                auto type_of = splitted[3];
                auto name = splitted[4];
                auto ply_list = PlyList{name, index_type, type_of};
                elem.add_property(PlyProperty{ply_list});
            } else {
                const auto &type_of = prop_type;
                auto name = splitted[2];
                auto ply_single = PlySingle{name, type_of};
                elem.add_property(PlyProperty{ply_single});
            }
        } else if (splitted[0] == "end_header") {
            break;
        } else {
            std::cerr << "Error while parsing header of Ply file";
            exit(2);
        }
    }

    if (!first_elem) {
        ply_model.push_back(elem);
    }

    // Preallocate memory
    for (auto &element: ply_model) {
        for (auto &prop: element.properties) {
            if (std::holds_alternative<PlySingle>(prop)) {
                std::get<PlySingle>(prop).content.reserve(element.count);
            } else {
                std::get<PlyList>(prop).content.reserve(element.count);
            }
        }
    }

    // Parse Content
    for (auto &element: ply_model) {
        if (std::holds_alternative<PlySingle>(element.properties[0])) {
            for (int _: std::views::iota(0, static_cast<int>(element.count))) {
                size_t index{0};
                std::getline(file, line);
                boost::split(splitted, line, boost::is_any_of(" "));
                for (auto &prop: element.properties) {
                    add_prop_single(std::get<PlySingle>(prop).type_of, std::get<PlySingle>(prop).content,
                                    splitted[index]);
                    index += 1;
                }
            }
        } else {
            for (int _: std::views::iota(0, static_cast<int>(element.count))) {
                std::getline(file, line);
                boost::split(splitted, line, boost::is_any_of(" "));
                // skip first
                splitted.erase(splitted.begin());

                add_prop_list(std::get<PlyList>(element.properties[0]).type_of,
                              std::get<PlyList>(element.properties[0]).content, splitted);
            }
        }
    }

    file.close();
    return ply_model;
}

auto load_shape(const std::string& filename) -> ShapeData {
    auto shape = ShapeData{};
    return shape;
}

auto load_ply_scene(const std::string& filename) -> SceneData {
    auto scene = SceneData{};



    return scene;
}

}

#endif //TRACEPP_MODELIO_H
