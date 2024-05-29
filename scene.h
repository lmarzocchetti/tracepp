#ifndef TRACEPP_SCENE_H
#define TRACEPP_SCENE_H

#include <vector>

#include "types.h"
#include "math.h"
#include "image.h"

namespace trace {

inline const int invalidid = -1;

struct CameraData {
    Frame3f frame = identity3x4f;
    bool ortographic = false;
    f32 lens = 0.050f;
    f32 film = 0.036f;
    f32 aspect = 1.500f;
    f32 focus = 10000;
    f32 aperture = 0;
};

struct InstanceData {
    Frame3f frame = identity3x4f;
    i32 shape = invalidid;
    i32 material = invalidid;
};

struct EnvironmentData {
    Frame3f frame = identity3x4f;
    Vec3f emission = {0, 0, 0};
    i32 emission_tex = invalidid;
};

struct ShapeData {
    // Element Data
    std::vector<i32> points = {};
    std::vector<Vec2i> lines = {};
    std::vector<Vec3i> triangles = {};
    std::vector<Vec4i> quads = {};

    // Vertex Data
    std::vector<Vec3f> positions = {};
    std::vector<Vec3f> normals = {};
    std::vector<Vec2f> texcoords = {};
    std::vector<Vec4f> colors = {};
    std::vector<f32> radius = {};
    std::vector<Vec4f> tangents = {};
};

struct TextureData {
    Image<Vec4f> pixelsf = {};
    Image<Vec4b> pixelsb = {};
    bool nearest = false;
    bool clamp = false;
};

enum struct MaterialType {
    MATTE, GLOSSY, REFLECTIVE, TRANSPARENT, REFRACTIVE, SUBSURFACE, VOLUMETRIC, GLTFPBR
};

struct MaterialData {
    MaterialType type = MaterialType::MATTE;
    Vec3f emission = {0, 0, 0};
    Vec3f color = {0, 0, 0};
    f32 roughness = 0;
    f32 metallic = 0;
    f32 ior = 1.5f;
    Vec3f scattering = {0, 0, 0};
    f32 scanisotropy = 0;
    f32 trdepth = 0.01f;
    f32 opacity = 1;

    // textures
    i32 emission_tex = invalidid;
    i32 color_tex = invalidid;
    i32 roughness_tex = invalidid;
    i32 scattering_tex = invalidid;
    i32 normal_tex = invalidid;
};

struct SceneData {
    // Scene Elements
    std::vector<CameraData> cameras = {};
    std::vector<InstanceData> instances = {};
    std::vector<EnvironmentData> environments = {};
    std::vector<ShapeData> shapes = {};
    std::vector<TextureData> texture = {};
    std::vector<MaterialData> materials = {};

    // Names
};
}

#endif //TRACEPP_SCENE_H
