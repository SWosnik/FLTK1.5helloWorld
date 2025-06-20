#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>

#if DEBUG
#include <iostream>
#include "oakum/oakum_api.h"
#define ERR_LOG_STREAM std::cout
#else
#define ERR_LOG_STREAM //
#endif

#include "mvp_interfaces.h"
#include "presenter.h"
#include "view.h"
#include "model.h"

#if DEBUG
#define EXPECT_OAKUM_SUCCESS(expr)                                                                 \
    {                                                                                              \
        const auto result = (expr);                                                                \
        if (result != OAKUM_SUCCESS) {                                                             \
            ERR_LOG_STREAM << "Error: Oakum API error in \"" << #expr << "\" error=" << result << '\n'; \
            exit(1);                                                                               \
        }                                                                                          \
    }

void initMemLeakChecker( void ) {
    ERR_LOG_STREAM << "Initializing Oakum library\n";
    OakumInitArgs initArgs{};
    initArgs.trackStackTraces = true;
    initArgs.threadSafe = false;
    initArgs.fallbackSymbolName = "<unknown_symbol>";
    initArgs.fallbackSourceFileName = "<unknown_file>";
    EXPECT_OAKUM_SUCCESS(oakumInit(&initArgs));
}

void evalMemLeaks( void ) {
    ERR_LOG_STREAM << "Getting detailed leaks information\n";
    OakumAllocation *allocations{};
    size_t allocationsCount{};
    EXPECT_OAKUM_SUCCESS(oakumGetAllocations(&allocations, &allocationsCount));
    EXPECT_OAKUM_SUCCESS(oakumResolveStackTraceSymbols(allocations, allocationsCount));
    EXPECT_OAKUM_SUCCESS(oakumResolveStackTraceSourceLocations(allocations, allocationsCount));

    for (size_t i = 0; i < allocationsCount; i++) {
        OakumAllocation &allocation = allocations[i];

        ERR_LOG_STREAM << "  id=" << allocation.allocationId << ", size=" << allocation.size << ", capturedStackFrames=" << allocation.stackFramesCount << '\n';
        for (size_t stackFrameIndex = 0u; stackFrameIndex < allocation.stackFramesCount; stackFrameIndex++) {
            OakumStackFrame &frame = allocation.stackFrames[stackFrameIndex];
            ERR_LOG_STREAM << "    " << frame.symbolName;
            ERR_LOG_STREAM << " in file " << frame.fileName << ":" << frame.fileLine;
            ERR_LOG_STREAM << "\n";
        }
        ERR_LOG_STREAM << '\n';
    }

    ERR_LOG_STREAM << "Detected " << allocationsCount << " leaks\n";

    ERR_LOG_STREAM << "Cleaning up library resources\n";
    EXPECT_OAKUM_SUCCESS(oakumReleaseAllocations(allocations, allocationsCount));
    EXPECT_OAKUM_SUCCESS(oakumDeinit(false));

    ERR_LOG_STREAM << "Press Enter to close this window\n";
    std::cin.get(); // do not close console
}

#else
void initMemLeakChecker( void ) {}

void evalMemLeaks( void ) {}
#endif

int main(int argc, char **argv) {
    initMemLeakChecker();
    // Create components
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

    int retVal = Fl::run();

    presenter->cleanup();
    evalMemLeaks();

    return retVal;
}
