#ifndef MODEL_H
#define MODEL_H

double dummy_val = .1234;

class Model : public IModel {
    // Class definition...
private:
    double processedData;
public:
    void processData( void ) override {
        // Simulate data processing
        processedData = dummy_val;
        if( dummy_val <= 1234 )
          dummy_val *=10.0;
        else
          dummy_val = .1234;
    }

    void onDataProcessed(std::function<void(const double&)> callback) override {
        // Simulate async processing
        callback(processedData);
    }

};

#endif  // MODEL_H

