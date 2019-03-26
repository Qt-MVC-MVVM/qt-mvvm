// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonitemtag.h"
#include "sessionitemtag.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

namespace
{
QStringList expected_keys();
}

using namespace ModelView;

const QString JsonItemTag::tagInfoKey = "tagInfo";
const QString JsonItemTag::itemsKey = "items";


JsonItemTag::~JsonItemTag() = default;

QJsonObject JsonItemTag::to_json(const SessionItemTag&)
{
    return QJsonObject();
}

std::unique_ptr<SessionItemTag> JsonItemTag::from_json(const QJsonObject&)
{
    return {};
}

//! Returns true if given object represents SessionItemTag.

bool JsonItemTag::isSessionItemTag(const QJsonObject& object)
{
    static const QStringList expected = expected_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}

namespace
{
QStringList expected_keys()
{
    QStringList result = QStringList() << JsonItemTag::tagInfoKey << JsonItemTag::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}
} // namespace
