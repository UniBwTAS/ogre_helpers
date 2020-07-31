#pragma once

#include <QColor>
#include <vector>

namespace Ogre
{
class ColourValue;
}

namespace rviz
{

class ColorHelper
{
  private:
    static std::vector<QColor> color_values_;
    static QStringList color_names_;

    static std::vector<std::string> color_material_names_;

  private:
    static void initColorList();
    static void initColorMaterialList();

  public:
    static size_t getColorListSize();
    static QColor getColorFromList(int i);
    static Ogre::ColourValue getOgreColorFromList(int i);
    static Ogre::ColourValue getRainbowOgreColor(float value);
    static Ogre::ColourValue qtToOgre(const QColor& c);
    static QColor ogreToQt(const Ogre::ColourValue& c);

    static std::string getColorMaterialNameFromList(int i, bool use_self_illumination);
    static size_t getColorMaterialNameListSize();
    static void
    createColorMaterial(const std::string& name, const Ogre::ColourValue& color, bool use_self_illumination);
    static std::string createColorMaterial(const Ogre::ColourValue& color, bool use_self_illumination);
};

} // namespace rviz
