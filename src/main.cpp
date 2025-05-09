#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>

#include "view.h"
#include "model.h"
#include "presenter.h"


int main(int argc, char **argv) {

    View* view = new View("Data-Test");
    view->show(argc, argv);

    return(Fl::run());

}