#ifndef PRESENTER_H
#define PRESENTER_H

#include <iostream>
#include <sstream>

class Presenter : public IPresenter {
public:
    static Presenter& getInstance() {
        static Presenter instance;
        return instance;
    }

    // Prevent copying
    Presenter(const Presenter&) = delete;
    Presenter& operator=(const Presenter&) = delete;

    void setIView(IView* view) {
        this->view = view;   // Assignment
        // model must be load before view
        if( NULL != model ) {
          double value;

          const char* response = model->requestConfig("min", value);
          if( NULL == response ) {
            std::ostringstream oss;
            oss << "Set min value"<< ": " << value;
            view->log(oss.str());
            view->setMinValue(value);
          } else {
            view->showMessage(response);
          }

          response = model->requestConfig("max", value);
          if( NULL == response ) {
            std::ostringstream oss;
            oss << "Set max value"<< ": " << value;
            view->log(oss.str());
            view->setMaxValue(value);
          } else {
            view->showMessage(response);
          }
        } else {
          view->showMessage("presenter: set model fefore view");
        }
    }

    void setIModel(IModel* model) {
        this->model = model;   // Assignment
    }

    void onUserInput( void ) override {
        view->showLoading(true);
        view->log("Request Data from model");
        model->processData();
        model->onDataProcessed([this](const double& processedData) {
            view->log("Response Data from model");
            view->updateData(processedData);
            view->showLoading(false);
        });
    }

private:
    IView* view = NULL;
    IModel* model = NULL;

    ~Presenter() override
    {
      if( NULL != view )
        delete view;

      if( NULL != model )
        delete model;
    };



    Presenter() {
    }

    void onDestroy() override {
        view = nullptr;
        model = nullptr;
    }
};

#endif  // PRESENTER_H
