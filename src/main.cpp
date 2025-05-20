#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>

#include "mvp_interfaces.h"
#include "presenter.h"
#include "view.h"
#include "model.h"


int main(int argc, char **argv) {
    // Create components
    int retVal = 0;
    View* view = new View("Data-Test");
    Model* model = new Model();
    Presenter* presenter = &Presenter::getInstance();

    // Set model for presenter
    presenter->setIModel(model);
    // Set view for presenter
    presenter->setIView(view);

    // Set presenter in view
    view->setPresenter(presenter);


    // Example logging messages
    view->log("Program started");

    view->show(argc, argv);

    retVal = Fl::run();

    return retVal;
}
