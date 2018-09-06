#ifndef OSGMANIPULATOR_COMMANDMANAGER
#define OSGMANIPULATOR_COMMANDMANAGER 1

#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Display/VBF_Dragger/Selection.h>
#include <VBF_Display/VBF_Dragger/Constraint.h>

namespace osgManipulator {

/**
 * Deprecated.
 * CommandManager class is now no longer required as Dragger now matains all references to Constraints and Selections (now just generic MatrixTransforms).
 * To replace CommandManager usage simple replace cmdMgr->connect(*dragger, *selection) with dragger->addTransformUpdating(selection) and
 * cmdMgr->connect(*dragger, *selection) with dragger->addConstaint(constraint).
 */
class CommandManager : public ::CVBF_Referenced
{
    public:
        CommandManager() {}

        bool connect(Dragger& dragger, Selection& selection)
        {
            dragger.addTransformUpdating(&selection);

            return true;
        }

        bool connect(Dragger& dragger, Constraint& constraint)
        {
            dragger.addConstraint(&constraint);

            return true;
        }

        bool disconnect(Dragger& dragger)
        {
            dragger.getConstraints().clear();
            dragger.getDraggerCallbacks().clear();

            return true;
        }

        typedef std::list< ref_ptr<Selection> > Selections;

        Selections getConnectedSelections(Dragger& dragger)
        {
            Selections selections;

            for(Dragger::DraggerCallbacks::iterator itr = dragger.getDraggerCallbacks().begin();
                itr != dragger.getDraggerCallbacks().end();
                ++itr)
            {
                DraggerCallback* dc = itr->get();
                DraggerTransformCallback* dtc = dynamic_cast<DraggerTransformCallback*>(dc);
                if (dtc && dtc->getTransform()) selections.push_back(dtc->getTransform());
            }

            return selections;
        }

    protected:

        virtual ~CommandManager() {}

};

}

#endif
