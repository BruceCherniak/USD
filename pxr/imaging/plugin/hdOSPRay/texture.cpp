//
// Copyright 2016 Pixar
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
#include "texture.h"

#include "pxr/base/gf/vec3f.h"
#include "pxr/usd/sdf/assetPath.h"

#include "pxr/imaging/hd/sceneDelegate.h"
#include "pxr/imaging/hd/textureResource.h"
#include "pxr/imaging/hdOSPRay/config.h"
#include "pxr/imaging/hdOSPRay/context.h"

#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE


HdOSPRayTexture::HdOSPRayTexture(SdfPath const& id)
  : HdTexture(id)
{
  std::cout << "hdOSPRayTexture::HdOSPRayTexture\n";
}

HdOSPRayTexture::~HdOSPRayTexture()
{
}

void
HdOSPRayTexture::Sync(HdSceneDelegate *sceneDelegate,
                HdRenderParam   *renderParam,
                HdDirtyBits     *dirtyBits)
{
  std::cout << "hdOSPRayTexture::Sync\n";
  HdTexture::Sync(sceneDelegate, renderParam,dirtyBits);
}

HdTextureResourceSharedPtr
HdOSPRayTexture::_GetTextureResource( HdSceneDelegate *sceneDelegate,
                                  const SdfPath &sceneID,
                                  HdTextureResource::ID texID) const
{
    return sceneDelegate->GetTextureResource(sceneID);
}

PXR_NAMESPACE_CLOSE_SCOPE

