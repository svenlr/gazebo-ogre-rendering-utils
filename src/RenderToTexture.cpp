//
// Created by sven on 12/22/20.
//

#include "RenderToTexture.h"

#include <gazebo/rendering/RTShaderSystem.hh>
#include <gazebo/rendering/RenderEngine.hh>
#include <gazebo/rendering/Conversions.hh>
#include <gazebo/rendering/RenderTypes.hh>
#include <gazebo/rendering/Scene.hh>


unsigned int get_max_fsaa() {
    unsigned int fsaa = 0; // anti-aliasing

    std::vector<unsigned int> fsaaLevels = gazebo::rendering::RenderEngine::Instance()->FSAALevels();

    if (!fsaaLevels.empty()) {
        // set the best anti-aliasing
        unsigned int targetFSAA = 16;
        if (std::find(fsaaLevels.begin(), fsaaLevels.end(), targetFSAA) != fsaaLevels.end()) {
            fsaa = targetFSAA;
        } else {
            fsaa = fsaaLevels.back();
        }
    }
    return fsaa;
}

void RenderToTexture::initialize(std::string name_, Ogre::Camera *camera, int w, int h, bool for_seg, bool shading) {
    name = std::move(name_);
    width = w;
    height = h;
    auto visibility_mask = GZ_VISIBILITY_ALL & ~(GZ_VISIBILITY_GUI | GZ_VISIBILITY_SELECTABLE);

    auto fsaa = get_max_fsaa();
    if (for_seg) {
        fsaa = 0;
    }

    pixel_box = std::make_shared<Ogre::PixelBox>(w, h, 1, Ogre::PF_R8G8B8_UINT);
    rendering_texture = Ogre::TextureManager::getSingleton().createManual(
            name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,
            width, height, 0,
            Ogre::PF_R8G8B8_UINT,
            Ogre::TU_RENDERTARGET,
            nullptr, false, fsaa).getPointer();

    target = rendering_texture->getBuffer()->getRenderTarget();
    target->setAutoUpdated(false);

    view_port = target->addViewport(camera);
    view_port->setOverlaysEnabled(false);
    view_port->setClearEveryFrame(true);

    view_port->setShadowsEnabled(not for_seg);
    view_port->setSkiesEnabled(not for_seg);
    if (not for_seg) {
        auto scene = gazebo::rendering::RenderEngine::Instance()->GetScene(0);
        auto const &ignBG = scene->BackgroundColor();
        view_port->setBackgroundColour(gazebo::rendering::Conversions::Convert(ignBG));
        if (shading) {
            gazebo::rendering::RTShaderSystem::AttachViewport(this->view_port, scene);
        }
    }
    view_port->setVisibilityMask(visibility_mask);
}

void RenderToTexture::render_to_buffer(unsigned char *buffer) {
    target->update();
    pixel_box->data = buffer;
    target->copyContentsToMemory(*pixel_box, Ogre::RenderTarget::FrameBuffer::FB_AUTO);
}
