#include "plugin.h"
#include "TurnMotor.h"
#include <cedar/processing/ElementDeclaration.h>

void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
    cedar::proc::ElementDeclarationPtr summation_decl
    (
        new cedar::proc::ElementDeclarationTemplate <TurnMotor>("Utilities")
    );
    plugin->add(summation_decl);
}
