//
// Copyright 2018 Intel
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//

#ifndef HDOSPRAY_MATERIAL_H
#define HDOSPRAY_MATERIAL_H

#include "pxr/pxr.h"
#include "pxr/imaging/hd/material.h"

#include "ospray/ospray.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdOSPRayMaterial final : public HdMaterial {
public:
  HdOSPRayMaterial(SdfPath const& id)
    : HdMaterial(id)
  {

  }

  virtual ~HdOSPRayMaterial() = default;

  struct HdOSPRayTexture
  {
    std::string file;
    enum class WrapType{ NONE,BLACK,CLAMP,REPEAT,MIRROR};
    WrapType wrapS, wrapT;
    GfVec4f scale;
    enum class ColorType{ NONE,RGBA,RGB,R,G,B,A};
    ColorType type;
  };

    /// Synchronizes state from the delegate to this object.
    virtual void Sync(HdSceneDelegate *sceneDelegate,
                      HdRenderParam   *renderParam,
                      HdDirtyBits     *dirtyBits) override;

    /// Returns the minimal set of dirty bits to place in the
    /// change tracker for use in the first sync of this prim.
    /// Typically this would be all dirty bits.
    virtual HdDirtyBits GetInitialDirtyBitsMask() const override
  {
    return AllDirty;
  }

    /// Causes the shader to be reloaded.
    virtual void Reload() override
  {
  }

    /// Summary flag. Returns true if the material is bound to one or more
    /// textures and any of those textures is a ptex texture.
    /// If no textures are bound or all textures are uv textures, then
    /// the method returns false.
  inline bool HasPtex() const { return false; }

  inline const OSPMaterial GetOSPRayMaterial() const { return _ospMaterial; }

//void
//  _GetMaterialNetworkMap(UsdPrim const &usdPrim,
//    HdMaterialNetworkMap *materialNetworkMap) const
//{
//    UsdShadeMaterial material(usdPrim);
//    if (!material) {
//        TF_RUNTIME_ERROR("Expected material prim at <%s> to be of type "
//                         "'UsdShadeMaterial', not type '%s'; ignoring",
//                         usdPrim.GetPath().GetText(),
//                         usdPrim.GetTypeName().GetText());
//        return;
//    }
//    const TfToken context = _GetMaterialNetworkSelector();
//    if (UsdShadeShader s = material.ComputeSurfaceSource(context)) {
//        _WalkGraph(s, &materialNetworkMap->map[UsdImagingTokens->bxdf],
//                  _GetShaderSourceTypes());
//    }
//    if (UsdShadeShader d = material.ComputeDisplacementSource(context)) {
//        _WalkGraph(d, &materialNetworkMap->map[UsdImagingTokens->displacement],
//                  _GetShaderSourceTypes());
//    }
//}

protected:
  GfVec4f diffuseColor;
  GfVec4f emissveColor;
  GfVec4f specularColor;
  float metallic;
  float roughness;
  GfVec4f clearcoat;
  float clearcoatRoughness;
  float ior;
  float opacity;

  HdOSPRayTexture map_diffuseColor;
  HdOSPRayTexture map_emissiveColor;
  HdOSPRayTexture map_specularColor;
  HdOSPRayTexture map_metallic;
  HdOSPRayTexture map_roughness;
  HdOSPRayTexture map_clearcoat;
  HdOSPRayTexture map_clearcoatRoughness;
  HdOSPRayTexture map_ior;
  HdOSPRayTexture map_opacity;
  HdOSPRayTexture map_normal;
  HdOSPRayTexture map_displacement;

  OSPMaterial _ospMaterial{nullptr};
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif HDOSPRAY_MATERIAL_H
