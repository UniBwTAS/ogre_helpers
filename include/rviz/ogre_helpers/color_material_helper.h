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
    size_t getColorListSize();
    QColor getColorFromList(int i);
    QColor getNextColorFromList();
    Ogre::ColourValue getOgreColorFromList(int i);
    Ogre::ColourValue getNextOgreColorFromList();
    static Ogre::ColourValue getRainbowOgreColor(float value);
    static inline Ogre::ColourValue qtToOgre(const QColor& c);
    static inline QColor ogreToQt(const Ogre::ColourValue& c);

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
    std::string getMaterialNameFromList(int i);
    size_t getMaterialNameListSize();
    void createMaterialList();
    static void
    createColorMaterial(const std::string& name, const Ogre::ColourValue& color, bool use_self_illumination);
};

} // namespace rviz
