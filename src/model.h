#ifndef MODEL_H
#define MODEL_H

class Model : public IModel {
    // Class definition...
private:
    double processedData;

public:
    void processData( void ) override {
        // Simulate data processing
        processedData = 12.34;
    }

    void onDataProcessed(std::function<void(const double&)> callback) override {
        // Simulate async processing
        callback(processedData);
    }

};

#endif  // MODEL_H

