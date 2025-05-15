#ifndef PRESENTER_H
#define PRESENTER_H


void my_sleep(unsigned duration)
{
    time_t start = time(NULL);
    double end = duration;
    time_t now;
    do {
        Fl::wait();
        now = time(NULL);
    } while (difftime(now, start) < end);
}

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
        view->addValue(1.234567);
        view->addValue(12.34567);
        view->addValue(123.4567);
        view->addValue(1234.567);
    }

    void setIModel(IModel* model) {
        this->model = model;   // Assignment
    }

    void onUserInput( void ) override {
        view->showLoading(true);
        model->processData();
        my_sleep(3);
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
