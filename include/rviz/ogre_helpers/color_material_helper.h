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
  public:
    ColorHelper();
    std::vector<QColor> color_values_;
    std::vector<std::string> color_names_;

  private:
    size_t counter = -1;

  public:
    QColor getColor(int i);
    QColor getNextColor();
    Ogre::ColourValue getOgreColor(int i);
    Ogre::ColourValue getNextOgreColor();

    static inline Ogre::ColourValue qtToOgre(const QColor& c);

    void resetCounter()
    {
        counter = -1;
    }
};

class ColorMaterialHelper
{
  private:
    ColorHelper color_helper;

  public:
    std::vector<std::string> color_names_;

  public:
    ColorHelper& getColorHelper();
    std::string getMaterialName(int i);
    size_t getNumMaterials();
    void createColorMaterials();
    static void
    createColorMaterial(const std::string& name, const Ogre::ColourValue& color, bool use_self_illumination);
};

} // namespace rviz
