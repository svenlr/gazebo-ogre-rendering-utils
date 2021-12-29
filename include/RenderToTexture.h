//
// Created by sven on 12/22/20.
//

#pragma once

#include <string>
#include <utility>
#include <OGRE/Ogre.h>


/**
 * A helper class that initializes a RenderTexture and target.
 * Allows to manually render images of a given camera with specific settings.
 */
class RenderToTexture {
public:
    std::string name;
    int width = 0;
    int height = 0;
    std::shared_ptr<Ogre::PixelBox> pixel_box;
    Ogre::Viewport *view_port{};
    Ogre::Texture *rendering_texture{};
    Ogre::RenderTexture *target{};

    /**
     * Actually initialize the pointers in this class.
     * @param name_ the name of the texture that the images are rendered to. Can be anything, but must be unique.
     * @param camera the camera to use for rendering
     * @param w camera width
     * @param h camera height
     * @param for_seg whether the image should be segmentable by object color, i.e. no lighting, no shadows, no shading
     * @param shading enable or disable shading. automatically disabled by for_seg=true
     */
    void initialize(std::string name_, Ogre::Camera *camera, int w, int h,
                    bool for_seg = false, bool shading = true);

    /**
     * Render the current scene to the given buffer. Buffer must be created previously with sufficient size, e.g. W*H*3
     *
     * @param buffer pointer to buffer
     */
    void render_to_buffer(unsigned char *buffer);
};

/** Get the maximum available FSAA level in gazebo */
unsigned int get_max_fsaa();
