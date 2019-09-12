
#include <rviz/ogre_helpers/color_material_helper.h>
#include <OgreColourValue.h>
#include <OgreMaterialManager.h>

namespace rviz
{

ColorHelper::ColorHelper()
{
    color_values_.emplace_back(QColor("red"));
    color_values_.emplace_back(QColor("green"));
    color_values_.emplace_back(QColor("blue"));
    color_values_.emplace_back(QColor("yellow"));
    color_values_.emplace_back(QColor("cyan"));
    color_values_.emplace_back(QColor("magenta"));
    color_values_.emplace_back(QColor("darkRed"));
    color_values_.emplace_back(QColor("darkCyan"));
    color_values_.emplace_back(QColor("darkMagenta"));
    color_values_.emplace_back(QColor("darkGreen"));
    color_values_.emplace_back(QColor("orange"));

    color_names_.emplace_back("Red");
    color_names_.emplace_back("Green");
    color_names_.emplace_back("Blue");
    color_names_.emplace_back("Yellow");
    color_names_.emplace_back("Cyan");
    color_names_.emplace_back("Magenta");
    color_names_.emplace_back("Darkred");
    color_names_.emplace_back("Darkcyan");
    color_names_.emplace_back("Darkmagenta");
    color_names_.emplace_back("Darkgreen");
    color_names_.emplace_back("Orange");
}

QColor ColorHelper::getColor(int i)
{
    return color_values_[i];
}

QColor ColorHelper::getNextColor()
{
    counter = (counter + 1) % color_values_.size();
    return color_values_[counter];
}

Ogre::ColourValue ColorHelper::getOgreColor(int i)
{
    return qtToOgre(color_values_[i]);
}

Ogre::ColourValue ColorHelper::getNextOgreColor()
{
    counter = (counter + 1) % color_values_.size();
    return qtToOgre(color_values_[counter]);
}

Ogre::ColourValue ColorHelper::qtToOgre(const QColor& c)
{
    return Ogre::ColourValue(c.redF(), c.greenF(), c.blueF(), c.alphaF());
}

void ColorMaterialHelper::createColorMaterial(const std::string& name,
                                              const Ogre::ColourValue& color,
                                              bool use_self_illumination)
{

    Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(name, "rviz");
    mat->setAmbient(color * 0.5f);
    mat->setDiffuse(color);
    if (use_self_illumination)
    {
        mat->setSelfIllumination(color);
    }
    mat->setLightingEnabled(true);
    mat->setReceiveShadows(false);
}
void ColorMaterialHelper::createColorMaterials()
{
    for (size_t i = 0; i < color_helper.color_values_.size(); i++)
    {
        std::stringstream ss;
        ss << "Custom/" << color_helper.color_names_[i];
        createColorMaterial(ss.str(), color_helper.getOgreColor(i), true);
        color_names_.push_back(ss.str());
    }
}
ColorHelper& ColorMaterialHelper::getColorHelper()
{
    return color_helper;
}
std::string ColorMaterialHelper::getMaterialName(int i)
{
    return color_names_[i];
}
size_t ColorMaterialHelper::getNumMaterials()
{
    return color_names_.size();
}
}