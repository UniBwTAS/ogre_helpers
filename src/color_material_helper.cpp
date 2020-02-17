
#include <OgreColourValue.h>
#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#include <rviz/ogre_helpers/color_material_helper.h>

#include <cmath>

namespace rviz
{

std::vector<QColor> ColorHelper::color_values_;
std::vector<std::string> ColorHelper::color_names_;
std::vector<std::string> ColorHelper::color_material_names_;

void ColorHelper::initColorList()
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

size_t ColorHelper::getColorListSize()
{
    if (color_values_.empty())
    {
        initColorList();
    }
    return color_values_.size();
}

QColor ColorHelper::getColorFromList(int i)
{
    if (color_values_.empty())
    {
        initColorList();
    }
    return color_values_[i];
}

Ogre::ColourValue ColorHelper::getOgreColorFromList(int i)
{
    if (color_values_.empty())
    {
        initColorList();
    }
    return qtToOgre(color_values_[i]);
}

Ogre::ColourValue ColorHelper::getRainbowOgreColor(float value)
{
    Ogre::ColourValue color;
    // this is HSV color palette with hue values going only from 0.0 to 0.833333.

    value = std::min(value, 1.0f);
    value = std::max(value, 0.0f);

    float h = value * 5.0f + 1.0f;
    int i = std::floor(h);
    float f = h - i;
    if (!(i & 1))
        f = 1 - f; // if i is even
    float n = 1 - f;
    if (i <= 1)
        color[0] = n, color[1] = 0, color[2] = 1;
    else if (i == 2)
        color[0] = 0, color[1] = n, color[2] = 1;
    else if (i == 3)
        color[0] = 0, color[1] = 1, color[2] = n;
    else if (i == 4)
        color[0] = n, color[1] = 1, color[2] = 0;
    else if (i >= 5)
        color[0] = 1, color[1] = n, color[2] = 0;

    return color;
}

Ogre::ColourValue ColorHelper::qtToOgre(const QColor& c)
{
    return Ogre::ColourValue(c.redF(), c.greenF(), c.blueF(), c.alphaF());
}

QColor ColorHelper::ogreToQt(const Ogre::ColourValue& c)
{
    return {static_cast<int>(c.r * 255.f),
            static_cast<int>(c.g * 255.f),
            static_cast<int>(c.b * 255.f),
            static_cast<int>(c.a * 255.f)};
}

std::string ColorHelper::createColorMaterial(const Ogre::ColourValue& color, bool use_self_illumination)
{
    std::stringstream ss;
    ss << "TempColor/" << color.r << "_" << color.g << "_" << color.b << "_" << color.a;
    if (!use_self_illumination)
    {
        ss << "_shaded";
    }
    std::string name = ss.str();
    createColorMaterial(name, color, use_self_illumination);

    return name;
}

void ColorHelper::createColorMaterial(const std::string& name,
                                      const Ogre::ColourValue& color,
                                      bool use_self_illumination)
{

    if (Ogre::MaterialManager::getSingleton().resourceExists(name))
    {
        return;
    }

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

void ColorHelper::initColorMaterialList()
{
    if (color_values_.empty())
    {
        initColorList();
    }

    for (size_t i = 0; i < color_values_.size(); i++)
    {
        std::stringstream ss;
        ss << "ColorMaterialList/" << color_names_[i];
        createColorMaterial(ss.str(), getOgreColorFromList(i), true);
        color_material_names_.push_back(ss.str());
    }
    for (size_t i = 0; i < color_values_.size(); i++)
    {
        std::stringstream ss;
        ss << "ColorMaterialList/" << color_names_[i] << "_shaded";
        createColorMaterial(ss.str(), getOgreColorFromList(i), false);
        color_material_names_.push_back(ss.str());
    }
}

std::string ColorHelper::getColorMaterialNameFromList(int i, bool use_self_illumination)
{
    if (color_material_names_.empty())
    {
        initColorMaterialList();
    }

    if (use_self_illumination)
    {
        return color_material_names_[i];
    }
    else
    {
        return color_material_names_[i + color_material_names_.size() / 2];
    }
}

size_t ColorHelper::getColorMaterialNameListSize()
{
    if (color_material_names_.empty())
    {
        initColorMaterialList();
    }

    return color_material_names_.size() / 2;
}

} // namespace rviz