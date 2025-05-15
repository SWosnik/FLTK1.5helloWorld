// mvp_interfaces.h
#ifndef MVP_INTERFACES_H
#define MVP_INTERFACES_H

#include <string>
#include <functional>

class IView {
public:
    virtual ~IView() = default;
    virtual void updateData(const double& data) = 0;
    virtual void showLoading(bool isVisible) = 0;
    virtual void setMinValue(double set_value) = 0;
    virtual void setMaxValue(double set_value) = 0;
    virtual double getMinValue( void ) = 0;
    virtual double getMaxValue( void ) = 0;
    virtual void addValue(double set_value) = 0;

};

class IPresenter {
public:
    virtual ~IPresenter() = default;
    virtual void onUserInput( void) = 0;
    virtual void onDestroy() = 0;
};

class IModel {
public:
    virtual ~IModel() = default;
    virtual void processData( void ) = 0;
    virtual void onDataProcessed(std::function<void(const double&)> callback) = 0;
};

#endif // MVP_INTERFACES_H