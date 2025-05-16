#ifndef PRESENTER_H
#define PRESENTER_H


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
        view->setMinValue(10.0);
        view->setMaxValue(1234.0);
    }

    void setIModel(IModel* model) {
        this->model = model;   // Assignment
    }

    void onUserInput( void ) override {
        view->showLoading(true);
        model->processData();
        model->onDataProcessed([this](const double& processedData) {
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
