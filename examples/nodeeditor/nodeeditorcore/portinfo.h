// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_PORTINFO_H
#define NODEEDITORCORE_PORTINFO_H

//! @file portinfo.h
//! Collecti

#include <string>

namespace NodeEditor {

//! Aggregate to hold basic port information: type and color.
//! Colors must be what QColor understands (i.e. https://www.w3.org/TR/css-color-3/#svg-color).

struct PortInfo {
    const std::string m_type;
    const std::string m_color;
};

const static PortInfo ParticlePort = {"Particle", "cornflowerblue"};
const static PortInfo TransformationPort = {"Transformation", "fuchsia"};

} // namespace NodeEditor

#endif //  NODEEDITORCORE_PORTINFO_H
